from __future__ import annotations
import asyncio.queues
import asyncio.selector_events
import asyncio.subprocess
import sys
import asyncio
from dataclasses import dataclass
from typing import *
import copy
from pprint import pprint
import aiohttp
import traceback
import random
import argparse
import time

#######################################################################
#######################################################################

exit_queue : asyncio.Queue[None] = asyncio.Queue()

async def put_exit_queue_on_error(coro: Coroutine[Any, Any, Any]) -> None:
    try:
        await coro
    except Exception as e:
        exc = traceback.format_exc()
        print(exc)
        exit_queue.put_nowait(None)

background_tasks = set()

def fire(coro: Coroutine[Any, Any, Any]) -> None:
    task = asyncio.create_task(put_exit_queue_on_error(coro))
    background_tasks.add(task)
    task.add_done_callback(background_tasks.discard)

#######################################################################
#######################################################################

@dataclass(frozen=True)
class requests_request:
    method: str
    url: str
    params: dict[str, Any] | None = None
    cookies: dict[str, str] | None = None
    headers: dict[str, str] | None = None
    data: bytes | None = None

@dataclass
class requests_request_recorder:
    logger: requests_logger
    method: str

    def __call__(self, url: str, /, **kwargs: Any) -> None:
        self.logger.requests.append(
            requests_request(
                method=self.method,
                url=url,
                **kwargs
            )
        )

class requests_logger:
    def __init__(self) -> None:
        self.requests: list[requests_request] = []
    
    def __getattr__(self, name: str) -> requests_request_recorder: 
        return requests_request_recorder(logger=self, method=name)

#######################################################################

def parse_curlconverter_output(data: str) -> list[requests_request]:
    requests = requests_logger()
    exec(data.replace('import requests', ''))
    return requests.requests

#######################################################################

async def check_curlconverter() -> None:
    process = await asyncio.subprocess.create_subprocess_exec(
        'curlconverter',
        '-', 
        stdin=asyncio.subprocess.PIPE,
        stdout=asyncio.subprocess.PIPE,
    )
    stdout, _ = await process.communicate(input=b'curl ipinfo.io')
    assert process.returncode == 0
    parse_curlconverter_output(stdout.decode())

async def read_curl_and_extract_requests() -> list[requests_request]:
    if sys.stdin.isatty():
        print('https://heygen.com -> devtools (F12) -> GET api2.heygen.com -> copy as curl -> rerun this with `pbpaste | this` or `this << EOF`')
        exit()
    process = await asyncio.subprocess.create_subprocess_exec(
        'curlconverter',
        '-', 
        stdout=asyncio.subprocess.PIPE,
    )
    stdout, _ = await process.communicate()
    assert process.returncode == 0
    requests_requests = parse_curlconverter_output(stdout.decode())
    return requests_requests

#######################################################################

cookie_t = dict[str, str]

async def get_cookies() -> cookie_t:
    requests = await read_curl_and_extract_requests()
    requests_with_keys = [
        (req.cookies is not None, 'api' in req.url.split('/')[:3][-1], req)
        for req in requests
    ]
    requests_with_keys.sort()
    cookies = requests_with_keys[-1][-1].cookies
    assert cookies is not None
    return copy.deepcopy(cookies)

#######################################################################
#######################################################################

requests: aiohttp.ClientSession

async def requests_worker(q: asyncio.Queue[None]) -> None:
    global requests
    async with aiohttp.ClientSession() as session:
        requests = session
        q.put_nowait(None)
        await asyncio.Future()
    
async def setup_requests() -> None:
    q : asyncio.Queue[None] = asyncio.Queue()
    fire(requests_worker(q))
    await q.get()

#######################################################################
#######################################################################

async def get_url_for_uploading(cookies: cookie_t) -> dict[str, str]:
    headers = {
        'Host': 'api2.heygen.com',
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:127.0) Gecko/20100101 Firefox/127.0',
        'Accept': 'application/json, text/plain, */*',
        'Accept-Language': 'ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3',
        'x-path': '/assets',
        'x-zid': 'zE8TPYssDsjTkO8T4BshtanXPvdq1hHg',
        'x-ver': '4.1.0',
        'x-last-build': '1719764719360',
        'Origin': 'https://app.heygen.com',
        'Connection': 'keep-alive',
        'Referer': 'https://app.heygen.com/',
        'Sec-Fetch-Dest': 'empty',
        'Sec-Fetch-Mode': 'cors',
        'Sec-Fetch-Site': 'same-site',
    }

    params = {
        'file_type': 'audio',
        'pipeline': 'asset',
    }

    response = requests.get('https://api2.heygen.com/v1/file/url.get', params=params, cookies=cookies, headers=headers)

    async with response as resp:
        output = await resp.json()
        pprint(output)
    
    return dict(
        audio_file_id = output['data']['id'],
        audio_url = output['data']['url'],
    )

async def upload_audio(data: bytes, audio_url: str) -> None:
    headers = {
        'Host': 'heygen-resources-prod.s3-accelerate.amazonaws.com',
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:127.0) Gecko/20100101 Firefox/127.0',
        'Accept': 'application/json, text/plain, */*',
        'Accept-Language': 'ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3',
        'x-amz-server-side-encryption': 'AES256',
        'Origin': 'https://app.heygen.com',
        'Connection': 'keep-alive',
        'Referer': 'https://app.heygen.com/',
        'Sec-Fetch-Dest': 'empty',
        'Sec-Fetch-Mode': 'cors',
        'Sec-Fetch-Site': 'cross-site',
        'Content-Type': 'audio/mpeg',
    }

    response = requests.put(audio_url, headers=headers, data=data)

    async with response as resp:
        await resp.read()

async def confirm_upload(cookies: cookie_t, audio_file_id: str) -> dict[str, str]:
    headers = {
        'Host': 'api2.heygen.com',
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:126.0) Gecko/20100101 Firefox/126.0',
        'Accept': 'application/json, text/plain, */*',
        'Accept-Language': 'ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3',
        'x-path': '/assets',
        'x-zid': 'U1S8pGC6MGex7iojr2mmdJnj0BeHVZic',
        'x-ver': '4.1.0',
        'x-last-build': '1717894199426',
        'Origin': 'https://app.heygen.com',
        'Connection': 'keep-alive',
        'Referer': 'https://app.heygen.com/',
        'Sec-Fetch-Dest': 'empty',
        'Sec-Fetch-Mode': 'cors',
        'Sec-Fetch-Site': 'same-site',
        'Content-Type': 'application/json',
    }

    json_data = {"name": time.asctime() + '_' + random.randbytes(64).hex() + '.mp3' ,"id": audio_file_id ,"file_type":"audio"}

    response = requests.post('https://api2.heygen.com/v1/file.upload', cookies=cookies, headers=headers, json=json_data)

    async with response as resp:
        output = await resp.json()
        pprint(output)
    
    return dict(
        audio_id = output['data']['id'],
    )

async def check_asset(cookies: cookie_t, audio_id: str) -> dict[str, str]:
    headers = {
        'Host': 'api2.heygen.com',
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:126.0) Gecko/20100101 Firefox/126.0',
        'Accept': 'application/json, text/plain, */*',
        'Accept-Language': 'ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3',
        'x-path': '/create-v3/draft',
        'x-zid': 'U1S8pGC6MGex7iojr2mmdJnj0BeHVZic',
        'x-ver': '4.1.0',
        'x-last-build': '1717894199426',
        'Origin': 'https://app.heygen.com',
        'Connection': 'keep-alive',
        'Referer': 'https://app.heygen.com/',
        'Sec-Fetch-Dest': 'empty',
        'Sec-Fetch-Mode': 'cors',
        'Sec-Fetch-Site': 'same-site',
    }

    params = {
        'id': audio_id,
    }

    response = requests.get('https://api2.heygen.com/v1/asset.get', params=params, cookies=cookies, headers=headers)

    async with response as resp:
        output = await resp.json()
        pprint(output)
    
    return dict(
        audio_file_mp3_url=output['data']['file_meta']['meta']['audios'].get('mp3', ''),
    )

async def asr(cookies: cookie_t, audio_file_mp3_url: str) -> str:
    headers = {
        'accept': 'application/json, text/plain, */*',
        'accept-language': 'ru-RU,ru;q=0.6',
        'content-type': 'application/json',
        'heygen-video-id': 'fd04656e594a4d61b60cbf62a35d22db',
        'origin': 'https://app.heygen.com',
        'priority': 'u=1, i',
        'sec-ch-ua': '"Brave";v="141", "Not?A_Brand";v="8", "Chromium";v="141"',
        'sec-ch-ua-mobile': '?0',
        'sec-ch-ua-platform': '"macOS"',
        'sec-fetch-dest': 'empty',
        'sec-fetch-mode': 'cors',
        'sec-fetch-site': 'same-site',
        'sec-gpc': '1',
        'traceparent': '00-0000000000000000075b1cfd83b847f4-5d701592cb589da9-01',
        'user-agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/141.0.0.0 Safari/537.36',
        'x-datadog-origin': 'rum',
        'x-datadog-parent-id': '6732905163139882409',
        'x-datadog-sampling-priority': '1',
        'x-datadog-trace-id': '530049256308361204',
        'x-language-override': 'en-US',
        'x-last-build': '1762475545288',
        'x-path': '/create-v4/fd04656e594a4d61b60cbf62a35d22db',
        'x-space-id': '276d4aba2d1d42ff836267bd45e36bc0',
        'x-ver': '4.1.0',
        'x-zid': 'f97168dd634d49c3919bb83fdfef5349',
    }

    json_data = {
        'voice_id': '330290724a1b470fb63153f34d4c0183',
        'audio_url': audio_file_mp3_url,
        'settings': {
            'voice_settings': {
                'locale': '',
                'pitch': 0,
                'speed': 1,
                'volume': 1,
                'voice_engine_settings': {
                    'engine_type': 'auto',
                    'seed': 3252597640,
                },
            },
        },
    }

    response = requests.post('https://api2.heygen.com/v1/speech_to_speech.generate', cookies=cookies, headers=headers, json=json_data)

    async with response as resp:
        output = await resp.json()
        pprint(output)
    
    text = output['data']['metadata']['text']
    assert isinstance(text, str)
    return text

#######################################################################

async def upload_file(cookies: cookie_t, data: bytes) -> str:

    res = await get_url_for_uploading(cookies)
    audio_file_id = res['audio_file_id']
    audio_url = res['audio_url']

    await upload_audio(data, audio_url)

    res = await confirm_upload(cookies, audio_file_id)
    audio_id = res['audio_id']

    while 1:
        await asyncio.sleep(1)
        res = await check_asset(cookies, audio_id)
        audio_file_mp3_url = res['audio_file_mp3_url']

        if audio_file_mp3_url:
            return audio_file_mp3_url
    
#######################################################################
#######################################################################

async def check_ffmpeg() -> None:
    process = await asyncio.subprocess.create_subprocess_exec(
        'ffmpeg',
        '-version', 
        stdin=asyncio.subprocess.PIPE,
        stdout=asyncio.subprocess.PIPE,
    )
    await process.communicate(input=b'')
    assert process.returncode == 0

#######################################################################
#######################################################################

async def main() -> None:
    parser = argparse.ArgumentParser()

    group = parser.add_mutually_exclusive_group(required=True)

    group.add_argument('--url', help='url to use, required if no file is provided')
    group.add_argument('--path', help='file to upload, required if no url is provided')

    args=parser.parse_args()

    await setup_requests()
    await check_curlconverter()
    await check_ffmpeg()

    cookies = await get_cookies()

    if args.url:
        url = args.url
    else:
        url = await upload_file(cookies, open(args.path, 'rb').read())
    
    text = await asr(cookies, url)

    print()
    print()
    print(text)



if __name__ == '__main__':
    asyncio.run(main())




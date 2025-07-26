import asyncio
import aiohttp
import argparse
import pathlib
import json
import pprint
import dataclasses
import urllib.parse
import subprocess
import random

# @dataclasses.dataclass
# class conf_type:
#     bitly_token: str
#     forward_to: str
#     short_link: str

# async def normalize_url(url: str) -> str:
#     process = await asyncio.create_subprocess_exec(
#         'curlconverter',
#         '--language',
#         'json',
#         url,
#         stdout=subprocess.PIPE,
#         stderr=subprocess.PIPE,
#     )
#     try:
#         stdout, stderr = await process.communicate()
#     finally:
#         if process.returncode is None:
#             process.terminate()
#         await process.wait()
#     assert stderr == b''
#     obj : dict[str, str] = json.loads(stdout.decode())
#     return obj['raw_url']

async def main():
    async with aiohttp.ClientSession(trust_env=True) as requests:
        ...

    process = await asyncio.create_subprocess_exec(
        'ssh',
        '-R',
        '80:'+forward,
        'plan@localhost.run',
        '--',
        '--output',
        'json',
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
    )
    try:
        async def read_stream(stream):
            while 1:
                data = await stream.read(2**16)
                print(data)
        await asyncio.gather(
            read_stream(process.stdout),
            read_stream(process.stderr),
        )
        stdout, stderr = await process.communicate()
    finally:
        if process.returncode is None:
            process.terminate()
        await process.wait()
    pprint.pprint(stdout)
    pprint.pprint(stderr)


        # normal_url = await normalize_url(conf.short_link)
        # parsed_url = urllib.parse.urlparse(normal_url)


        # headers = {
        #     'Authorization': f'Bearer {TOKEN}',
        #     'Content-Type': 'application/json',
        # }

        # json_data = {
        #     'long_url': f'https://dev.bitly.com/{random.randbytes(20).hex()}/',
        #     'domain': parsed_url.netloc,
        # }

        # response = requests.post('https://api-ssl.bitly.com/v4/shorten', headers=headers, json=json_data)
        # async with response as resp:
        #     data = await resp.json()
        #     pprint.pprint(data)
        #     link_id = data['id']
        

        # headers = {
        #     'Authorization': f'Bearer {TOKEN}',
        #     'Content-Type': 'application/json',
        # }

        # json_data = {
        #     'bitlink_id': link_id,
        # }

        # response = requests.patch(f'https://api-ssl.bitly.com/v4/custom_bitlinks/{parsed_url.netloc + parsed_url.path}', headers=headers, json=json_data)
        # async with response as resp:
        #     data = await resp.json()
        #     pprint.pprint(data)



        # url = await normalize_url(conf.short_link)
        # short_link_id = url.netloc + url.path

        # print(f'{short_link_id = !r}')

        # headers = {
        #     'Authorization': f'Bearer {conf.bitly_token}',
        #     'Content-Type': 'application/json',
        # }

        # headers = {
        #     'Authorization': f'Bearer {conf.bitly_token}',
        #     'Content-Type': 'application/json',
        # }

        # json_data = {
        #     'title': 'Bitly API Documentation',
        #     'archived': False,
        #     'tags': [
        #         'bitly',
        #         'api',
        #     ],
        #     'deeplinks': [
        #         {
        #             'guid': 'Ra1bcD2eF3h',
        #             'bitlink': 'bit.ly/documentation',
        #             'app_uri_path': '/store?id=123456',
        #             'install_url': 'https://play.google.com/store/apps/details?id=com.bitly.app&hl=en_US',
        #             'app_guid': 'Ab1cdE2fG3h',
        #             'os': 'android',
        #             'install_type': 'promote_install',
        #             'brand_guid': 'Ba1bc23dE4F',
        #         },
        #     ],
        # }

        # response = requests.patch('https://api-ssl.bitly.com/v4/bitlinks/bit.ly/12a4b6c', headers=headers, json=json_data)



        # response = requests.get(f'https://api-ssl.bitly.com/v4/bitlinks/{short_link_id}', headers=headers)

        # async with response as resp:
        #     data = await resp.json()
        #     pprint.pprint(data)



        # headers = {
        #     'Authorization': f'Bearer {TOKEN}',
        # }

        # response = requests.get('https://api-ssl.bitly.com/v4/groups', headers=headers)

        # async with response as resp:
        #     try:
        #         data = await resp.json()
        #     except aiohttp.ContentTypeError:
        #         data = await resp.read()
        #     pprint.pprint(data)
        #     guids = [group['guid'] for group in data['groups']]
        

        # for guid in guids:

        #     search_after = ''

        #     while 1:

        #         params = {
        #             'search_after': search_after
        #         }

        #         headers = {
        #             'Authorization': f'Bearer {TOKEN}',
        #         }

        #         response = requests.get(f'https://api-ssl.bitly.com/v4/groups/{guid}/bitlinks', headers=headers, params=params)

        #         async with response as resp:
        #             try:
        #                 data = await resp.json()
        #             except aiohttp.ContentTypeError:
        #                 data = await resp.read()
        #             pprint.pprint(data)
        #             for link in data['links']:
        #                 for custom_bitlink in link['custom_bitlinks']:
        #                     assert isinstance(custom_bitlink, str)
        #                     if custom_bitlink == url:
        #                         ...
        #             search_after = data['pagination']['search_after'] # TODO: read more than one page
        #             break

        # headers = {
        #     'Authorization': f'Bearer {TOKEN}',
        #     'Content-Type': 'application/json',
        # }

        # json_data = {
        #     'long_url': 'https://dev.bitly.com/a/',
        #     'domain': 'bit.ly',
        #     'group_guid': guid,
        # }

        # response = requests.post('https://api-ssl.bitly.com/v4/shorten', headers=headers, json=json_data)

        # async with response as resp:
        #     data = await resp.json()
        #     pprint.pprint(data)
            # guid = data['groups'][0]['guid']



        # headers = {
        #     'Authorization': f'Bearer {TOKEN}',
        #     'Content-Type': 'application/json',
        # }

        # json_data = {
        #     'long_url': 'https://dev.bitly.com',
        #     'domain': 'bit.ly',
        # }

        # response = requests.post('https://api-ssl.bitly.com/v4/shorten', headers=headers, json=json_data)

        # async with response as resp:
        #     print(resp.status)
        #     print(resp.headers)
        #     print(await resp.json())





if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--forward', type=str, required=True)
    args = parser.parse_args()
    forward : str = args.forward
    asyncio.run(main())



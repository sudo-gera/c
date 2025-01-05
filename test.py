from pprint import pprint
import aiohttp
import asyncio
import urllib.parse
from pathlib import Path
home = Path().home()

with open(home / 'vk_token.txt') as token_file:
    token_url = token_file.read()
    token_fragment = urllib.parse.urlsplit(token_url).fragment
    token_args = urllib.parse.parse_qs(token_fragment)
    token = token_args['access_token'][0]

session : aiohttp.ClientSession

async def main():
    async with aiohttp.ClientSession() as ses:
        global session
        session = ses
        # async with session.get(f'https://api.vk.com/method/video.liveGetCategories?access_token={token}&v=5.199') as resp:
        #     data = await resp.json()
        async with session.get(f'https://api.vk.com/method/video.get?access_token={token}&v=5.199') as resp:
            data = await resp.json()
        pprint(data)


if __name__ == '__main__':
    asyncio.run(main())

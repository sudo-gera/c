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

async def normalize_url(url: str) -> str:
    process = await asyncio.create_subprocess_exec(
        'curlconverter',
        '--language',
        'json',
        url,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
    )
    try:
        stdout, stderr = await process.communicate()
    finally:
        if process.returncode is None:
            process.terminate()
        await process.wait()
    assert stderr == b''
    obj : dict[str, str] = json.loads(stdout.decode())
    return obj['raw_url']

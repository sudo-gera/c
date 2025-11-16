#!/usr/bin/env python3

import asyncio
import contextlib
import os
import sys
import textwrap
import time
import math

async def main() -> int:
    host = sys.argv[1]
    port = int(sys.argv[2])
    try:
        async with await asyncio.start_server(lambda *a:None, host, port) as server:
            return 0
    except Exception:
        return 1

if __name__ == '__main__':
    exit(asyncio.run(main()))

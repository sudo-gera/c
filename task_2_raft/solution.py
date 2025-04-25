import asyncio
import sys

node_id = int(sys.argv[1])

colors = [
    '\x1b[0m',
    '\x1b[37m',
    '\x1b[90m',
    '\x1b[91m',
    '\x1b[92m',
    '\x1b[93m',
    '\x1b[94m',
    '\x1b[95m',
    '\x1b[96m',
]

async def master():
    ...

async def worker():
    ...

if node_id == 0:
    ...
else:
    ...

import random
import base64
for i in range(100):
    color = random.choice(colors)
    tag = color + '[' + repr(color) + ']' + '\x1b[0m'
    print(tag)


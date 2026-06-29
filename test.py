#!/usr/bin/env python3

import sys
import base64

CHUNK_SIZE = 4096

while True:
    chunk = sys.stdin.buffer.read1(CHUNK_SIZE)
    if not chunk:
        break

    encoded = base64.b64encode(chunk)
    sys.stdout.buffer.write(encoded + b"\n")
    sys.stdout.buffer.flush()

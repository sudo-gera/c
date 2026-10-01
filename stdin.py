#!/usr/bin/env python3
from sys import *
from pprint import pprint
print(*stdin.buffer.read().splitlines(keepends=1), sep='\n')

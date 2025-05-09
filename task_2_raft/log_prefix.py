import ipaddress
import common
import asyncio
import sys
import time
import psutil
import traceback
import logging
import typing

##############################################################################################################################################

hosts = sys.argv[2:]
msg = sys.argv[1]
hosts.sort()
my_ip = common.select_my_ip(hosts)
assert isinstance(my_ip, str)
other_hosts = {*hosts} - {my_ip}

##############################################################################################################################################

colors = [
    '\x1b[90m',
    '\x1b[91m',
    '\x1b[92m',
    '\x1b[93m',
    '\x1b[94m',
    '\x1b[95m',
    '\x1b[96m',
    '\x1b[97m',
]
my_color = colors[hosts.index(my_ip)]
clear_color = '\x1b[0m'

##############################################################################################################################################

logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.DEBUG, format='[ %(asctime)s ]: %(message)s' + clear_color)

class log_stream:
    def __init__(self, logger_func: typing.Callable[[str], None]):
        self.logger_func = logger_func
        self.buffer = ''
    def write(self, data: str) -> None:
        self.buffer += data
        while '\n' in self.buffer:
            data, self.buffer = self.buffer.split('\n', 1)
            self.logger_func(data)
            sys.stdout.flush()
            sys.stderr.flush()

debug_stream = log_stream(logging.debug)
info_stream = log_stream(logging.info)
error_stream = log_stream(logging.error)

##############################################################################################################################################

print(msg, file=info_stream)

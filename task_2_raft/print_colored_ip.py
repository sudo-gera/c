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

hosts = sys.argv[1:]
hosts.sort()
my_ip = common.select_my_ip(hosts)
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

print(my_color +'[  ' + (my_ip + ' '*20)[:12] + ' ]')


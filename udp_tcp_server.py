import asyncio
from udp_tcp import *

try:
    asyncio.run(main(False))
except KeyboardInterrupt:
    pass

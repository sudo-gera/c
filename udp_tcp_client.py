import asyncio
from udp_tcp import *

try:
    asyncio.run(main(True))
except KeyboardInterrupt:
    pass

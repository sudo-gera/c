import asyncio
import random
from sys import argv

# seed=random.random()
# print(seed)
# random.seed(seed)

def polyhash(b):
    c=0
    for w in b:
        c*=257
        c+=w
        c%=2**64
    return c

count=-1
started=0
finished=0
s=[]
def add_started():
    global started
    started+=1
    print('started: %7i, finished: %7i'%(started,finished),end='\r')

def add_finished():
    global finished
    finished+=1
    print('started: %7i, finished: %7i'%(started,finished),end='\r')
    if finished==started==count:
        print(' '*80,end='\r')
        print('success!')
        raise KeyboardInterrupt


class EchoServerProtocol(asyncio.Protocol):
    def connection_made(self, transport):
        peername = transport.get_extra_info('peername')
        # print('Connection from {}'.format(peername))
        self.transport = transport
        self.len=-1
        self.data=b''

    def data_received(self, data):
        asyncio.create_task(self.data_r(data))

    async def data_r(self, data):
        if self.len==-1:
            self.len=int(data[:16])
            data=data[16:]
        self.data+=data
        await asyncio.sleep(random.random())
        if len(self.data)==self.len+16:
            # print(self.data)
            assert ('%16i'%abs(polyhash(self.data[16:])))[:16].encode()==self.data[:16]
            self.asserted=1
            self.transport.close()
        # message = data.decode()
        # print('Data received: {!r}'.format(message))


        # print('Send: {!r}'.format(message))
        # self.transport.write(data)

        # print('Close the client socket')

    def connection_lost(self, exc) -> None:
        assert(self.asserted)

class EchoClientProtocol(asyncio.Protocol):
    def __init__(self):
        add_started()
        t=random.randint(40,100)
        # self.message = str(random.random()).encode()
        # self.message = bytes([random.randint(40,100) for _ in range(random.randint(256,512))])
        # self.message = bytes([t for _ in range(random.randint(2048,4096))])
        self.message = ('%16i'%len(self.message)).encode()+('%16i'%abs(polyhash(self.message)))[:16].encode()+self.message
        # self.message = bytes([random.randint(40,100) for _ in range(random.randint(1024,2048))])

    def connection_made(self, transport):

        transport.write(self.message)
        # transport.write(str(len(self.message)).encode()+b' '+self.message)
        # print('Data sent: {!r}'.format(self.message))

    # def data_received(self, data):
    #     # print('Data received: {!r}'.format(data.decode()))
    #     assert self.message==data
    #     self.asserted=1
    
    def connection_lost(self, exc) -> None:
        # assert self.asserted
        add_finished()

async def connect(loop):
    await asyncio.sleep(random.random())
    await loop.create_connection(
        EchoClientProtocol,
        argv[3], int(argv[4]),
    )

async def main():
    loop = asyncio.get_running_loop()

    server = await loop.create_server(
        EchoServerProtocol,
        argv[1], int(argv[2]),
    )


    global count
    count=16
    for r in range(count):
        asyncio.create_task(connect(loop))

    async with server:
        s.append(server)
        await server.serve_forever()

try:
    asyncio.run(main())
except KeyboardInterrupt:
    pass


from h import *
import socket
import select
import os
import functools
import time
import json
import base64
import fcntl

buffer_size = 4096
delay = 0.0001
forward_to = ('localhost', 9090)
port=8080

def watch(to_watch):
    try:
        while 1:
            time.sleep(delay)
            ss = select.select
            input_ready, output_ready, except_ready = ss(to_watch.keys(), [], [])
            for s in input_ready:
                to_watch[s]['on_event'](s)
    except KeyboardInterrupt:
        print()


def create_server():
    server=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind(('', port))
    server.listen(200)
    return server


def on_event(pipe,to_watch,client_by_id,client):
    data=client.recv(1024**2)
    client_id=to_watch[client]['id']

    ic(client_id,data)
    if not data:
        os.write(pipe[1],json.dumps({
            'pid':os.getpid(),
            'event':'del',
            'id':client_id
        }).encode()+b'\0')
        del client_by_id[client_id]
        del to_watch[client]
        client.close()
    else:
        data=base64.b64encode(data).decode()
        os.write(pipe[1],json.dumps({
            'pid':os.getpid(),
            'event':'got',
            'id':client_id,
            'data':data,
        }).encode()+b'\0')

def on_pipe(pipe_buffer,to_watch,client_by_id,pipe,_pipe):
    assert pipe[0]==_pipe
    ic(pipe_buffer)
    data=pipe_buffer[0]
    tmp=b'0'
    while tmp:
        tmp=b''
        try:
            tmp=os.read(pipe[0],1024)
        except BlockingIOError:
            pass
        data+=tmp
    ic(data)
    data=data.split(b'\0')
    pipe_buffer[0]=data[-1]
    data=data[:-1]
    for w in data:
        w=json.loads(w)
        # if w['pid']==os.getpid():
        #     continue
        ic(w)
        client_id=w['id']
        if w['event']=='new':
            client=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            client.connect(forward_to)
            assert client_id not in client_by_id
            client_by_id[client_id]=client
            to_watch[client]={
                'on_event':functools.partial(on_event,pipe,to_watch,client_by_id),
                'id':client_id,
            }
        if w['event']=='del':
            client=client_by_id[client_id]
            del to_watch[client]
            del client_by_id[client_id]
            client.close()
        if w['event']=='got':
            client=client_by_id[client_id]
            data=w['data']
            data=base64.b64decode(data.encode())
            ic(data)
            client.send(data)

def on_accept(pipe,to_watch,client_by_id,server):
    client,client_address=server.accept()
    client_id=int(time.time()*2**128)
    ic(client_address,client_id)
    client_by_id[client_id]=client
    to_watch[client]={
        'on_event':functools.partial(on_event,pipe,to_watch,client_by_id),
        'id':client_id,
    }
    os.write(pipe[1],json.dumps({
        'pid':os.getpid(),
        'event':'new',
        'id':client_id,
    }).encode()+b'\0')

pipe_c2p=os.pipe()
pipe_p2c=os.pipe()
if not os.fork():
    os.close(pipe_c2p[0])
    os.close(pipe_p2c[1])
    pipe=[pipe_p2c[0],pipe_c2p[1]]
    to_watch={}
    client_by_id={}
    fcntl.fcntl(pipe[0], fcntl.F_SETFL, os.O_NONBLOCK);
    to_watch[pipe[0]]={
        'on_event':functools.partial(on_pipe,[b''],to_watch,client_by_id,pipe),
    }
    watch(to_watch)
else:
    os.close(pipe_c2p[1])
    os.close(pipe_p2c[0])
    pipe=[pipe_c2p[0],pipe_p2c[1]]
    to_watch={}
    client_by_id={}
    server=create_server()
    to_watch[server]={
        'on_event': functools.partial(on_accept,pipe,to_watch,client_by_id),
    }
    fcntl.fcntl(pipe[0], fcntl.F_SETFL, os.O_NONBLOCK);
    to_watch[pipe[0]]={
        'on_event':functools.partial(on_pipe,[b''],to_watch,client_by_id,pipe),
    }
    watch(to_watch)











# server=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
# server.bind(('', 8080))
# server.listen(200)

# def on_read(client,data):
#     ...

# def on_close(client):
#     ...

# def on_event(client):
#     data=client.recv(1024**2)


# def on_accept(server):
#     client=server.accept()
#     to_watch[client]={}
#     to_watch[client]['on_event']=on_event


# to_watch[server]={}
# to_watch[server]['on_event']=on_accept

# try:
#     while 1:
#         time.sleep(delay)
#         ss = select.select
#         input_ready, output_ready, except_ready = ss(to_watch.keys(), [], [])
#         for s in input_ready:
#             to_watch[s]['on_event'](s)
# except KeyboardInterrupt:
#     print()

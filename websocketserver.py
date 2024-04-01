from simple_websocket_server import WebSocketServer, WebSocket
import websocket
import threading
import queue
import socket

def work1(a_ws: tuple[socket.socket, list], q: queue.Queue):
    c_ws = (websocket.WebSocket(), [])
    c_ws[0].connect("wss://vesta.web.telegram.org/apiws",
            # http_proxy_host='remote.vdi.mipt.ru',
            # http_proxy_port='55749',
            header=['Sec-WebSocket-Protocol: binary, binary']
    )
    q.put_nowait(c_ws)
    while 1:
        if not c_ws[1]:
            data = c_ws[0].recv()
        else:
            a_ws[0].close()
            a_ws[1].append(0)
            break
        if isinstance(data, str):
            data = data.encode()
        print([1, data])
        if not data:
            c_ws[0].close()
            c_ws[1].append(0)
            break
        if not a_ws[1]:
            a_ws[0].sendall(data)
        else:
            c_ws[0].close()
            c_ws[1].append(0)
            break

def work2(a_ws: tuple[socket.socket, list], c_ws: tuple[websocket.WebSocket, list]):
    while True:
        if not a_ws[1]:
            data = a_ws[0].recv(1024)
        else:
            c_ws[0].close()
            c_ws[1].append(0)
            break
        print([2, data])
        if not data:
            a_ws[0].close()
            a_ws[1].append(0)
            break
        if not c_ws[1]:
            c_ws[0].send_binary(data)
        else:
            a_ws[0].close()
            a_ws[1].append(0)
            break

# Echo server program
import socket

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind(('0.0.0.0',2000))
    s.listen(1)
    a_ws, addr = s.accept()
    with a_ws:
        a_ws = (a_ws, [])
        print('Connected by', addr)
        q = queue.Queue()
        threading.Thread(target=work1, args=(a_ws, q)).start()
        c_ws = q.get()
        threading.Thread(target=work2, args=(a_ws, c_ws)).start()

# class SimpleEcho(WebSocket):
#     def handle(self):
#         print([self.data])
#         self.c_ws.send(self.data)
#         # echo message back to client
#         # self.send_message(self.data)

#     def connected(self):
#         q = queue.Queue()
#         threading.Thread(target=work, args=(self, q)).start()
#         self.c_ws = q.get()
#         print(self.address, 'connected')

#     def handle_close(self):
#         print(self.address, 'closed')


# server = WebSocketServer('', 2000, SimpleEcho)
# server.serve_forever()

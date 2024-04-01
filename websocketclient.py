import socket
import websocket
import time
import threading

# def work(r,w):
#     while True:
#         if isinstance(r, socket.socket):
#             data = r.recv(2**16)
#         else:
#             data = r.recv()
#         if not data: break
#         w.send(data)

# with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
#     ws = websocket.WebSocket()
#     ws.connect("wss://vesta.web.telegram.org/apiws",
#             http_proxy_host='remote.vdi.mipt.ru',
#             http_proxy_port='55749',
#             header=['Sec-WebSocket-Protocol: binary, binary']
#     )
#     s.bind(('', 4444))
#     s.listen(1)
#     conn, addr = s.accept()
#     with conn:
#         print('Connected by', addr)
#         threading.Thread(target=work, args=(conn, ws)).start()
#         work(ws, conn)
#     ws.close()

ws = websocket.WebSocket()
ws.connect("ws://127.0.0.1:2000/apiws",
        # http_proxy_host='remote.vdi.mipt.ru',
        # http_proxy_port='55749',
        # header=['Sec-WebSocket-Protocol: binary, binary']
)
ws.send('---')

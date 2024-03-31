import websocket

ws = websocket.WebSocket()
ws.connect("ws://127.0.0.1:2000",
  http_proxy_host="127.0.0.1", http_proxy_port="8888",
  proxy_type="http"
)
ws.send("Hello, Server")
print(ws.recv())
ws.close()

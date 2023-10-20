# import _socket
# import http.server
# import socketserver
# import sys

# if len(sys.argv) < 2:
#     print('usage:')
#     print(f'{sys.executable} {__file__} [listen-host:]listen-port')
#     exit(1)

# listen_port, listen_host = sys.argv[1][::-1].split(':',1) if ':' in sys.argv[1] else [sys.argv[1][::-1], '0.0.0.0']
# listen_host = listen_host[::-1]
# listen_port = listen_port[::-1]
# print(listen_host, listen_port)

# class Server(http.server.SimpleHTTPRequestHandler):
#     def do_POST(self):
#         self.send_response(200)
#         self.send_header("Content-type", "text/html; charset=utf-8")
#         self.end_headers()
#         data = self.rfile.read(int(self.headers['Content-Length']))
#         open('task_db.json', 'wb').write(data)

# server = http.server.HTTPServer((listen_host, listen_port), Server)

# print('HTTP server is listening at {listen_host}:{listen_port}. You can open it in your browser.')

# try:
#     server.serve_forever()
# except KeyboardInterrupt:
#     pass
# finally:
#     server.server_close()

# import pylcs
import random

a = bytes([random.randint(0, 255) for q in range(10**6)])
s = bytes([random.randint(0, 255) for q in range(10**6)])


# # A = 'We are shannonai'
# # B = ['We like shannonai', 'We work in shannonai', 'We are not shannonai']
# pylcs.lcs_string_length(a,s)

from strsimpy import SIFT4

S = SIFT4()

print(S.distance('aba','b'))

# result: 11.0
# print(s.distance('This is the first string', 'And this is another string')) # 11.0
# result: 12.0
# print(s.distance('Lorem ipsum dolor sit amet, consectetur adipiscing elit.', 'Amet Lorm ispum dolor sit amet, consetetur adixxxpiscing elit.', maxoffset=10))





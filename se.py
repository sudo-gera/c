from http.server import BaseHTTPRequestHandler, HTTPServer
import time
from urllib.request import urlopen as u
from urllib.parse import unquote as uqu
from sys import argv
import os

hostName = "localhost"
hostPort = 9000

class MyServer(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        path='.'+uqu(self.path)
        #print(path)
        if '?' in path:
         self.send_header("Content-type", "text/html; charset=utf-8")
         self.end_headers()
         self.wfile.write(bytes('<html><head><meta http-equiv="refresh" content="1;URL=."></meta></head></html>', "utf-8"))
        elif os.path.isdir(path):
         self.send_header("Content-type", "text/html; charset=utf-8")
         self.end_headers()
         self.wfile.write(bytes("<html><head><title>"+path+"</title></head>", "utf-8"))
         self.wfile.write(bytes("<body><p>\n", "utf-8"))
         for w in os.listdir(path):
          self.wfile.write(bytes('<form><button','utf-8'))
          self.wfile.write(bytes(' formaction="'+w+'/">','utf-8'))
          self.wfile.write(bytes(w+'/'*int(os.path.isdir(path+w)),'utf-8'))
          self.wfile.write(bytes('</button></form>\n','utf-8'))
         self.wfile.write(bytes("</p></body></html>", "utf-8"))
        elif os.path.isfile(path):
         self.send_header("Content-type", "file/file")
         self.end_headers()
         q=path
         q=open(q,'br').read()
         self.wfile.write(q)
        elif os.path.isfile(path[:-1]) and path[-1] == '/':
         self.send_header("Content-type", "text/html; charset=utf-8")
         self.end_headers()
         self.wfile.write(bytes("<html><head><title>"+path+"</title></head>", "utf-8"))
         self.wfile.write(bytes("<body><p>download<br>", "utf-8"))
         self.wfile.write(bytes('<a href="'+path[1:-1]+'">'+path[1:-1]+'</a>','utf-8'))
         self.wfile.write(bytes("</p></body></html>", "utf-8"))
        else:
         self.send_header("Content-type", "text/html; charset=utf-8")
         self.end_headers()
         self.wfile.write(bytes("<html><head><title>"+path+"</title></head>", "utf-8"))
         self.wfile.write(bytes('<body><p>not found<br>'+path[1:]+'</p></body></html>', "utf-8"))

myServer = HTTPServer((hostName, hostPort), MyServer)
print(time.asctime(), "Server Starts - %s:%s" % (hostName, hostPort))

try:
    myServer.serve_forever()
except KeyboardInterrupt:
    pass

myServer.server_close()
print(time.asctime(), "Server Stops - %s:%s" % (hostName, hostPort))

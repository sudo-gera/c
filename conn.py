#!/data/data/com.termux/files/usr/bin/python
from http.server import BaseHTTPRequestHandler, HTTPServer
import time
from urllib.request import urlopen as u
from urllib.parse import unquote as uqu
from sys import argv
import os
import random

q=[w.split() for w in os.popen('ifconfig').read().split('\n')]
q=[w[1].split(':')[1] for w in q if len(w) and w[0] == 'inet']
print('='*10,*enumerate(q),sep='\n')
if len(argv) > 1:
 argv1=argv[1]
 if argv1 in [w[:len(argv1)] for w in q]:
  q=[w for w in q if w[:len(argv1)] == argv1]
print('='*10,*enumerate(q),sep='\n')
if len(argv) > 2:
 port=int(argv[2])
else:
 port=9000
if len(argv) > 3:
 img='/nekopara/'+argv[3]
else:
 img='/nekopara.jpg'
if len(argv) > 4:
 arhvstin=argv[4]
else:
 arhvstin='arhvstin'
if len(q) > 1:
 e=int(input())
else:
 e=0
q=q[e]
hostName = q
hostPort = port

class MyServer(BaseHTTPRequestHandler):
 def do_CONNECT(self):
  print(dir(self))
 def do_GET(self):
  if os.path.exists('exit'):
   raise KeyboardInterrupt
  print('start')
  self.send_response(200)
  path='.'+uqu(self.path).replace(arhvstin,'..')
  #print(path)
  if '?' in path:
   self.send_header("Content-type", "text/html; charset=utf-8")
   self.end_headers()
   self.wfile.write(bytes('''
   <html>
   <head>
   <meta http-equiv="refresh" content="1;URL=.">
   </meta>
   </head>
   <body>
   <style type=text/css>
    #neko {position: fixed; top:0; botom:0; left:0; right:0}
    #main {position: absolute; top:0; left:0}
    wi {background: #00ff00}
    </style>
   <div id="neko">
    <img src="'''+img+'''" width="100%"><br>
    <img src="'''+img+'''" width="100%"><br>
    <img src="'''+img+'''" width="100%"></div>
   </body>
   </html>''', "utf-8"))

  elif os.path.isdir(path):
   if img == '/nekopara.jpg':
    os.system('cp nekopara/'+random.choice(os.listdir('nekopara'))+' nekopara.jpg')
   a=open('clip')
   clip=a.read()
   a.close()
   self.send_header("Content-type", "text/html; charset=utf-8")
   self.end_headers()
   self.wfile.write(bytes('''
   <html>
   <head>
   <title>'''+path+'''</title>
   </head>
   <style type=text/css>
    #neko {position: fixed; top:0; botom:0; left:0; right:0}
    #main {position: absolute; top:0; left:0}
    wi {background: #00ff00}
    </style>
   <body>
   <div id="neko">
    <img src="'''+img+'''" width="100%"><br>
    <img src="'''+img+'''" width="100%"><br>
    <img src="'''+img+'''" width="100%"></div>

   <div id="main">
    <h1>
    <form enctype="multipart/form-data" method="post">
     <wi><input type="file" name="u">
     <input type="submit" value="upload"></form></wi>
    </h1>
    <wi>===</wi>

   <wi><form method="post">
   <textarea name="c">'''+clip+'''</textarea><br>
   <input type="submit" value="save"></form></wi>
   <wi>===</wi>

   <form><button formaction="../">
   <h1>..<img src="/favicon.ico" height="25"></h1>
   </button></form>
   <wi>===</wi>

   ''','utf-8'))

   for w in os.listdir(path):
    self.wfile.write(bytes('''
    <form><button formaction="'''+w+'''/">
    <h1>'''+w+'''
    <img src="/favicon.ico" height="25">'''*int(os.path.isdir(path+w))+'''
    </h1></button></form>''','utf-8'))

   self.wfile.write(bytes('''</div></body></html>''', "utf-8"))

  elif os.path.isfile(path):
   self.send_header("Content-type", "file/file")
   self.end_headers()
   q=open(path,'br').read()
   self.wfile.write(q)

  elif os.path.isfile(path[:-1]) and path[-1] == '/':
   self.send_header("Content-type", "text/html; charset=utf-8")
   self.end_headers()
   self.wfile.write(bytes('''
   <html><head><title>'''+path+'''</title>
   </head>
   <body>
   <style type=text/css>
    #neko {position: fixed; top:0; botom:0; left:0; right:0}
    #main {position: absolute; top:0; left:0}
    wi {background: #00ff00}
    </style>
   <div id="neko">
    <img src="'''+img+'''" width="100%"><br>
    <img src="'''+img+'''" width="100%"><br>
    <img src="'''+img+'''" width="100%"></div>
   <div id="main">
   <h1>
   <form><button formaction="../">
   ..<img src="/favicon.ico" height="25">
   </button></form>
   <wi>'''+path[1:-1]+'''</wi><br>
   </h1>
   <a href="'''+path[1:-1].replace('..',arhvstin)+'''"><img src='/download.png' width=100%></a><br>
   </div></body></html>
   ''', "utf-8"))
  else:
   self.send_header("Content-type", "text/html; charset=utf-8")
   self.end_headers()
   self.wfile.write(bytes("<html><head><title>"+path+"</title></head>", "utf-8"))
   self.wfile.write(bytes('<body><p>not found<br>'+path[1:]+'</p></body></html>', "utf-8"))
  print('end')

 def do_POST(self):
  print('start')
  lenn=int(self.headers['Content-Length'])
  data=self.rfile.read(lenn)
  self.send_response(200)
  self.send_header("Content-type", "text/html; charset=utf-8")
  self.end_headers()
  self.wfile.write(bytes('<html><head><meta http-equiv="refresh" content="1;URL=."></meta></head></html>', "utf-8"))
  data=bytearray(data)
  rn=bytearray('\r\n','utf-8')
  data=data.split(rn)
  print(data)
  if len(data) and data[0][:6] == bytearray('------','utf-8'):
   fn=data[1].decode()
   fn=fn[:-1][::-1]
   fn=fn[:fn.index('"')][::-1]
   print(self.path+fn)
   f=[]
   for w in range(len(data)):
    if len(data[w]) == 0:
     f+=[w]
   #print(f)
   data=data[f[0]+1:f[-1]-1]
   ext=data[0]
   while len(data)>1:
    data=data[1:]
    ext+=rn+data[0]
   if len(fn):
    path='.'+uqu(self.path).replace(arhvstin,'..')
    fil=path+fn
    if os.path.exists(fil):
     d=0
     while os.path.exists(fil+str(d)):
      d+=1
     a=open(fil+str(d),'wb')
    else:
     a=open(fil,'wb')
    a.write(ext)
    a.close()
  else:
   ext=data[0]
   while len(data)>1:
    data=data[1:]
    ext+=rn+data[0]
   clip=ext.decode()[2:]
   clip=uqu(clip)
   print(clip)
   a=open('clip','w')
   a.write(clip)
   a.close()
  print('end')

st=1
while st:
 try:
  myServer = HTTPServer((hostName, hostPort), MyServer)
  st=0
 except:
  hostPort+=1
print(time.asctime(), "Server Starts - %s:%s" % (hostName, hostPort))

try:
    myServer.serve_forever()
except KeyboardInterrupt:
    pass

myServer.server_close()
print()
print(time.asctime(), "Server Stops - %s:%s" % (hostName, hostPort))

import json
import httplib

body =b'123'
payload = {'HTML' : body}
hdr = {"content-type": "application/json"}

conn = httplib.HTTPConnection('127.0.0.1:9000')
conn.request('POST', '/', body, hdr)
response = conn.getresponse()
data = response.read()

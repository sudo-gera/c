try:
    from urllib.request import Request, urlopen  # Python 3
except ImportError:
    from urllib2 import Request, urlopen  # Python 2

req = Request('https://user225847803-etle274b.wormhole.vk-apps.com/')
req.add_header('Upgrade', 'WebSocket')
req.add_header('Connection', 'Upgrade')
content = urlopen(req).read()

print(content)


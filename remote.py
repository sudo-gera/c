from aiohttp import web
import base64
import sys

async def handle(request):
    name = request.match_info.get('name', "Anonymous")
    text = "Hello, " + name
    return web.Response(text=text)

async def post(req):
    # name = req.match_info.get('name', "Anonymous")
    data=await req.read()
    data=base64.b64decode(data)
    if len(data)==2:
        data=data[:-1]
    print(data)
    # sys.stdout.buffer.write(data)
    sys.stdout.flush()
    return web.Response()

app = web.Application()
app.add_routes([web.get('/', handle),
                web.post('/', post)])

if __name__ == '__main__':
    web.run_app(app,host=sys.argv[1], port=sys.argv[2])

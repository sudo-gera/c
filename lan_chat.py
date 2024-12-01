# for app:
# POST / to send query and receive answer

# for example:
#  from urllib.request import urlopen
#  answer = urlopen('http://127.0.0.1:12300', 'у меня вопрос'.encode(), timeout=2**28).read().decode()

# for human:
# GET / to view and answer random query in web
# GET /list to view queries in curl
# POST /123 where 123 - query id (from previous call) - to answer query

import asyncio
import aiohttp
from aiohttp import web
import time
import json
import random
import base64

start_time = time.time_ns() - time.monotonic_ns()

queries: dict[str, tuple[str, asyncio.Queue]] = {}

async def process_query(request: web.Request):
    data = (await request.read()).decode()
    query_id = str(time.monotonic_ns() + start_time)
    print(data, query_id)
    ans_q = asyncio.Queue()
    queries[query_id] = (data, ans_q)
    try:
        ans = await ans_q.get()
    finally:
        del queries[query_id]
    print(data, query_id, ans)
    return web.Response(text=ans)
    

async def list_queies(request: web.Request):
    return web.Response(text=json.dumps({query_id: query for query_id, [query, queue] in  queries.items()}, indent=4)+'\n')

async def answer_query(request: web.Request):
    data = (await request.read()).decode()
    query_id = request.match_info['query_id']
    if query_id in queries:
        await queries[query_id][1].put(data)
        return web.Response(text='your answer is submitted')
    return web.Response(text='the form was submitted earlier or not found')

async def web_random_query(request: web.Request):
#     if not queries:
#         return web.Response(text=f'''
# <!DOCTYPE html>
# <html lang="ru">
#    <head>
#         <META http-equiv="Content-Type" content="text/html; charset=utf-8" />
#       <title>HTML Document</title>
#    </head>
#    <body>
#         <script>
#             window.onload = () => {{
# //                setTimeout(()=>(window.location.reload()), 8000);
#             }};
#         </script>
#         No active queries. Reload page manually when needed.
#    </body>
# </html>
#         ''', content_type='text/html', charset='utf-8')
                                    
    # query_id, [query, queue] = random.choice([*queries.items()])
    return web.Response(text=f'''
<!DOCTYPE html>
<html lang="ru">
   <head>
        <META http-equiv="Content-Type" content="text/html; charset=utf-8" />
      <title>HTML Document</title>
        <style>
            textarea {{
  width: 300px;
  height: 150px;
}}
        </style>
   </head>
   <body>
        <script>
            window.onload = () => {{
            }};
            send_answer = () => {{
                value = document.getElementById('answer').value;
                console.log(value);
                fetch("/", {{
                    method: "POST",
                    body: value,
                    headers: {{
                        "Content-type": "application/json; charset=UTF-8"
                    }}
                }})
                .then(e=>e.text().then(e=>{{document.getElementById('query').value=e}}));
                return false;
            }}
        </script>
        <textarea style="width=600px; height=600px" id="query"></textarea>
        <textarea style="width=600px; height=600px" id="answer"></textarea>
        <button onclick="send_answer()">send</button>
   </body>
</html>
    ''', content_type='text/html', charset='utf-8')
    

app = web.Application()
app.add_routes([
    web.get('/list', list_queies),
    web.get('/', web_random_query),
    web.post('/{query_id}', answer_query),
    web.post('/', process_query)
])

web.run_app(app, port=12300)

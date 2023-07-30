from h import *

token = open(home + '.dance_bot_token').read().strip()
pay_token = open(home + '.dance_bot_pay_token').read().strip()

def api(path,**d):
    r=Request(f'''https://api.telegram.org/bot{token}/{path}''')
    r.add_header('Content-type', 'application/json; charset=utf-8')
    r.add_header('Accept', 'text/plain')
    a=json.loads(urlopen(r,data=json.dumps(d).encode()).read().decode())
    if a['ok']:
        return a['result']
    else:
        pprint(a)

update_id=0
while 1:
    try:
        a=api('getUpdates',offset=update_id+1,timeout=60)
    except KeyboardInterrupt:
        print()
        exit()
    if not a: continue
    a=a[0]
    update_id=a['update_id']
    pprint(a)
    if 'pre_checkout_query' in a:
        api('answerPreCheckoutQuery',pre_checkout_query_id=a['pre_checkout_query']['id'],ok=True)
    elif 'message' in a:
        a=a['message']
        if 'text' in a:
            api('sendMessage',chat_id=a['chat']['id'],text='''[11](https://t.me/east_lion)'''.strip(),disable_web_page_preview=True,parse_mode='MarkdownV2',reply_markup={'remove_keyboard':True})
        else:
            api('sendInvoice',chat_id=a['chat']['id'],title='_1',description='_2',payload='_3',provider_token=pay_token,currency='RUB',prices=[{'label':'_rub_','amount':'9900'}])
    else:
        continue
        raise SyntaxError



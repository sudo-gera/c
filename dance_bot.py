from urllib.request import Request
from urllib.request import urlopen
import json
from pprint import pprint
from pathlib import Path

home=str(Path.home())+'/'

class open_db:
    def __enter__(self):
        try:
            with open(home+'.dance_bot_db') as file:
                db=file.read()
            db=json.loads(db)
        except Exception:
            db={}
        self.db=db
        return db
    def __exit__(self,*a):
        with open(home+'.dance_bot_db','w') as file:
            file.write(json.dumps(self.db,indent=4)+'\n')

token = '5922670140:AAGTBGswsJ-w13ZXk9hBk4zVkLSpmjh8Tns'
pay_token = '381764678:TEST:62741'

class obj(dict): # allow a.name instead of a['name']
    def __init__(self,*a,**s):
        super().__init__(*a,**s)
        self.__dict__=self

def convert(a): # recursively replace dict with obj in json
    if type(a)==dict:
        return obj({q:convert(w) for q,w in a.items()})
    if type(a)==list:
        return [convert(q) for q in a]
    return a

def api(path,**d):
    r=Request(f'''https://api.telegram.org/bot{token}/{path}''')
    r.add_header('Content-type', 'application/json; charset=utf-8')
    r.add_header('Accept', 'text/plain')
    with urlopen(r,data=json.dumps(d).encode()) as resp:
        a=convert(json.loads(resp.read().decode()))
    if a.ok:
        return a.result
    else:
        pprint(a)

def make_text(t): # remove indent spaces from multiline strings
    return '\n'.join([q.strip() for q in t.strip().splitlines()])

def send_invoice(a,**d):
    api('sendInvoice',
        chat_id=a.from_id,
        provider_token=pay_token,
        currency='RUB',
        **d
    )

def send_message(a,**d):
    api('sendMessage',
        chat_id=a.chat.id,
        disable_web_page_preview=True,
        **d,
    )

def on_event_0(a):
    if a.event_type=='pre_checkout_query':
        if a.invoice_payload=='/pay':
            api('answerPreCheckoutQuery',
                pre_checkout_query_id=a.id,
                ok=True)
        elif a.invoice_payload=='/vip':
            api('answerPreCheckoutQuery',
                pre_checkout_query_id=a.id,
                ok=False,
                error_message='Для покупки vip статуса необходимо быть участником курса.')
        else:
            api('answerPreCheckoutQuery',
                pre_checkout_query_id=a.id,
                ok=False,
                error_message='Неизвестное значение payload.')
    elif a.event_type=='message':
        if 'successful_payment' in a:
            a.db['pay']=1
            del a.successful_payment
            a.text='/start'
            on_event_1(a)
        else:
            send_message(a,
                text=make_text('''
                    Здравствуйте! Вас приветствует бот курса танцев!

                    Здесь вы можете оплатить своё участие.

                    После оплаты вы получитие доступ к беседе курса и рассылке видео-уроков.
                '''),
                reply_markup={
                    'inline_keyboard':[[{
                        'text':'Оплатить участие',
                        'callback_data':'/pay'
                    }]]
                })
    elif a.event_type=='callback_query':
        if a.data=='/pay':
            a.chat={}
            send_invoice(a,
                title='Лучшие танцы!',
                description='У нас самые лучшие танцы!',
                payload='/pay',
                prices=[{'label':'участие в курсе','amount':'9900'}])

def on_event_1(a):
    if a.event_type=='pre_checkout_query':
        if a.invoice_payload=='/vip':
            api('answerPreCheckoutQuery',
                pre_checkout_query_id=a.id,
                ok=True)
        elif a.invoice_payload=='/pay':
            api('answerPreCheckoutQuery',
                pre_checkout_query_id=a.id,
                ok=False,
                error_message='Вы уже являетесь участником курса.')
        else:
            api('answerPreCheckoutQuery',
                pre_checkout_query_id=a.id,
                ok=False,
                error_message='Неизвестное значение payload.')
    elif a.event_type=='message':
        if 'successful_payment' in a:
            a.db['pay']=2
            del a.successful_payment
            a.text='/start'
            on_event_2(a)
        else:
            send_message(a,
                text=make_text('''
                    Бот курса танцев рад вас видеть в числе участников курса!

                    Я буду регулярно присылать вам записи видео-уроков.

                    Предлагаю вам присоединиться к общей беседе.

                    Так же вы можете стать VIP-участником и получить доступ к личному общению с владельцем курса.
                    '''),
                reply_markup={
                    'inline_keyboard':[
                        [{
                            'text':'Купить VIP-статус',
                            'callback_data':'/vip'
                        }],
                        [{
                            'text':'Присоединиться к общей беседе',
                            'url':'http://attachment.zip'
                        }],
                    ]
                })
    elif a.event_type=='callback_query':
        if a.data=='/vip':
            send_invoice(a,
                title='VIP-статус',
                description='Вы станете VIP-участником.',
                payload='/vip',
                prices=[{'label':'vip-статус','amount':'9900'}])
            return

def on_event_2(a):
    if a.event_type=='pre_checkout_query':
        if a.invoice_payload=='/vip':
            api('answerPreCheckoutQuery',
                pre_checkout_query_id=a.id,
                ok=False,
                error_message='Вы уже являетесь VIP-участником курса.')
        elif a.invoice_payload=='/pay':
            api('answerPreCheckoutQuery',
                pre_checkout_query_id=a.id,
                ok=False,
                error_message='Вы уже являетесь VIP-участником курса.')
        else:
            api('answerPreCheckoutQuery',
                pre_checkout_query_id=a.id,
                ok=False,
                error_message='Неизвестное значение payload.')
    elif a.event_type=='message':
        if 'successful_payment' in a:
            a.db['pay']=2
            del a.successful_payment
            a.text='/start'
            on_event_2(a)
        else:
            send_message(a,
                text=make_text('''
                    Бот курса танцев рад вас видеть в числе VIP-участников курса!

                    Я буду регулярно присылать вам записи видео-уроков.

                    Предлагаю вам присоединиться к общей беседе.

                    Так же вы можете написать личное сообщение владельцу курса.
                    '''),
                reply_markup={
                    'inline_keyboard':[
                        [{
                            'text':'написать владельцу курса',
                            'url':'https://t.me/east_lion'
                        }],
                        [{
                            'text':'Присоединиться к общей беседе',
                            'url':'http://attachment.zip'
                        }],
                    ]
                })

def on_event_3(a):
    if a.event_type=='message':
        if 'forward_from' in a:
            if a.forward_from.id not in a.all_db:
                ff=a.forward_from
                send_message(a,
                    text=make_text(f'''
                        Имя: {ff.first_name if 'first_name' in ff else '(не доступно)'}
                        Фамилия: {ff.last_name if 'last_name' in ff else '(не доступно)'}
                        username: {ff.username if 'username' in ff else '(не доступно)'}
                        id: {ff.id if 'id' in ff else '(не доступно)'}
                        статус в рамках курса: {
                            ['не оплатил участие в курсе',
                            'оплатил участие в курсе',
                            'оплатил VIP-участие',
                            'является администратором'
                            ][a.all_db[str(ff.id)]['pay']]
                            if str(ff.id) in a.all_db else 
                            'не общался с ботом'}
                    '''),
                    reply_markup={
                        'inline_keyboard':[
                            [{
                                'text':'Сделать не оплатившим курс',
                                'callback_data':'/upd_0_'+str(ff.id),
                            }],
                            [{
                                'text':'Сделать оплатившим курс',
                                'callback_data':'/upd_1_'+str(ff.id),
                            }],
                            [{
                                'text':'Сделать VIP-пользователем',
                                'callback_data':'/upd_2_'+str(ff.id),
                            }],
                            [{
                                'text':'Сделать администратором',
                                'callback_data':'/upd_3_'+str(ff.id),
                            }],
                        ]
                    })
        elif 'reply_to_message' in a:
            a.forward_from=a.reply_to_message['from']
            on_event_3(a)
        elif any([isinstance(w,dict) and 'file_id' in w and 'file_unique_id' in w for q,w in a.items()]):
            send_message(a,
                text=make_text('''
                    Вы уверены, что хотите отправить этот файл всем пользователям?
                '''),
                reply_to_message_id=a.message_id,
                reply_markup={
                    'inline_keyboard':[
                        [{
                            'text':'Отправить этот файл',
                            'callback_data':'/yes_'+str(a.message_id),
                        }],
                    ]
                })
        else:
            send_message(a,
                text=make_text('''
                    Бот рад видеть вас в числе администраторов.

                    Вы можете прислать мне видео-урок для рассылания всем остальным.
                            
                    Перешлите мне сообщение любого человека, чтобы я назвал его статус.
                '''),
                reply_markup={
                    'inline_keyboard':[
                    ]
                })
    elif a.event_type=='callback_query':
        if a.data.startswith('/yes_'):
            for q in a.all_db:
                api('copyMessage',
                    chat_id=q,
                    from_chat_id=a.message.chat.id,
                    message_id=a.data[5:])
        if a.data.startswith('/upd_'):
            key=a.data[7:]
            val=a.data[5:6]
            a.all_db[key]['pay']=int(val)
            a.chat={}
            a.chat=a.message.chat
            send_message(a,
                text='Cтатус пользователя обновлён.',
                reply_markup={
                    'inline_keyboard':[
                    ]
                })

if __name__ == '__main__':
    update_id=0
    while 1:
        try:
            a=api('getUpdates',offset=update_id+1,timeout=60)
        except KeyboardInterrupt:
            print()
            exit()
        if not a: continue
        a=a[0]
        update_id=a.update_id
        del a.update_id
        event_type=[*a.keys()][0]
        a=a[event_type]
        a.event_type=event_type
        a.from_id=str(a['from'].id)
        with open_db() as db:
            if a.from_id not in db:
                db[a.from_id]={
                    'pay':0
                }
            a.db=db[a.from_id]
            if 'username' in a['from']:
                a.db['username']=a['from'].username
            pprint(a)
            a.all_db=db
            [on_event_0, on_event_1, on_event_2, on_event_3,][a.db['pay']](a)




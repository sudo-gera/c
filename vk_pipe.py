from h import *

tokens=open(home+'.IPoVKtoken').read().split()

def items(q):
    if type(q) == type(dict()):
        if set(q.keys()) == set(['count', 'items']):
            return items(q['items'])
        else:
            for w in q:
                q[w] = items(q[w])
            return q
    elif type(q) == type(list()):
        return [items(w) for w in q]
    else:
        return q

def api_f(path,data=''):
    if path and path[-1] not in '&?':
        if '?' in path:
            path+='&'
        else:
            path+='?'
    sleep(1/6)
    data=data.encode()
    global token
    ret=loads(urlopen('https://api.vk.com/method/'+path+'v=5.131&access_token='+token,data=data).read().decode())
    try:
        if 'error' in ret.keys():
            print(ret['error']['error_msg'])
    except:
        pprint(ret)
    try:
        return items(ret['response'])
    except:
        pass


class Api:
    def __init__(self,s=''):
        self._s=s
    def __getattr__(self,n):
        return Api(self._s+'.'*(not not self._s)+n)
    def __call__(self,**d):
        s=self._s+'?'
        d=[w+'='+quote_plus(str(d[w])) for w in d]
        d='&'.join(d)
        return api_f(s+d)

api=Api()

group_id=218700852
long_poll=None
try:
    while 1:
        if long_poll is None:
            long_poll=api.groups.getLongPollServer(group_id=group_id)
            ts=long_poll['ts']

        poll=json.loads(urlopen(f"{long_poll['server']}?act=a_check&key={long_poll['key']}&ts={ts}&wait=25").read().decode())

        if 'failed' in poll:
            if poll['failed']==1:
                ts=poll['ts']
                continue
            else:
                long_poll=None
                continue

        upd=poll['updates']
        ts=poll['ts']
        for w in upd:
            ic(w)
except KeyboardInterrupt:
    print()


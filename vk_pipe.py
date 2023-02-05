from h import *

token=open(home+'.IPoVKtoken').read().strip()

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

def api(path,data=''):
    if path and path[-1] not in '&?':
        if '?' in path:
            path+='&'
        else:
            path+='?'
    sleep(1/6)
    data=data.encode()
    global token
    ret=loads(urlopen('https://api.vk.com/method/'+path+'v=5.101&access_token='+token,data=data).read().decode())
    try:
        if 'error' in ret.keys():
            print(ret['error']['error_msg'])
    except:
        pprint(ret)
    try:
        return items(ret['response'])
    except:
        pass


try:
    from urllib.request import urlopen
    q=urlopen('https://raw.githubusercontent.com/sudo-gera/c/master/auto_print_service.py').read()
    open(__file__,'w').write(q)
except:
    pass

try:
    token=open(__file__+'.token').read()



    from urllib.request import urlopen
    from json import loads
    from json import dumps
    from urllib.parse import quote
    from time import sleep
    from time import time
    from time import asctime
    from traceback import format_exc as fo
    from os import popen
    from webbrowser import open as webopen
    from sys import argv
    from pathlib import Path
    from pprint import pprint

    #url=open(str(Path.home())+'/url').read()
    #token=url.split('#')[1].split('&')[0].split('=')[1]

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
                return items(ret['response'])
            except:
                pass
            try:
                if ret['error']['error_code'] in [5,10]:
                    return
            except:
                pass
            pprint(ret)
            api('messages.send?user_id=225847803&random_id='+str(int(time()*1000))+'&peer_id=225847803','message='+str(ret))
            


    import tempfile
    import win32api
    import win32print

    def printfile(filename,filedata):
        filetmp = tempfile.mktemp(suffix=filename)
        open(filetmp,'wb').write(filedata)
        win32api.ShellExecute (
          0,
          "print",
          filetmp,
          #
          # If this is None, the default printer will
          # be used anyway.
          #
          '/d:"%s"' % win32print.GetDefaultPrinter (),
          ".",
          0
        )

        from subprocess import run
        #run(['explorer.exe',filetmp])

    def printfile(filename,filedata):
        gsprint=r"C:\Users\user\Downloads\GSPRINT\gsprint.exe"
        gsscript=r"C:\Users\user\Downloads\GHOSTSCRIPT\bin\gswin32c.exe"

        GHOSTSCRIPT_PATH = gsscript
        GSPRINT_PATH = gsprint

        # YOU CAN PUT HERE THE NAME OF YOUR SPECIFIC PRINTER INSTEAD OF DEFAULT
        currentprinter = win32print.GetDefaultPrinter()

        filetmp = tempfile.mktemp(suffix=filename)
        open(filetmp,'wb').write(filedata)

        win32api.ShellExecute(0, 'open', GSPRINT_PATH, '-ghostscript "'+GHOSTSCRIPT_PATH+'" -printer "'+currentprinter+'" "'+filetmp+'"', '.', 0)

    from pprint import pprint
    from urllib.request import urlopen
    from time import sleep

    while 1:
        try:
            sleep(1)
            q=api('messages.getHistory?count=200&user_id=225847803&peer_id=225847803&extended=1')
            if q!=None and 'unread_count' in q['conversations'][0]:
                q=q['items'][:q['conversations'][0]['unread_count']]
                q=sum([w['attachments'] for w in q],[])
                q=[w[w['type']] for w in q]
                for w in q:
                    printfile(w['title'],urlopen(w['url']).read())
                if q:
                    api('messages.send?user_id=225847803&random_id='+str(int(time()*1000))+'&peer_id=225847803','message='+str([w['title'] for w in q])+'')
        except:
            from traceback import format_exc
            w=q
            q=format_exc()
            print(q,w)
            from time import time
            try:
                api('messages.send?user_id=225847803&random_id='+str(int(time()*1000))+'&peer_id=225847803','message='+q+'\n'*8+str(w))
            except:
                pass
            

except:
    from traceback import format_exc
    q=format_exc()
    print(q)
    from time import time
    try:
        api('messages.send?user_id=225847803&random_id='+str(int(time()*1000))+'&peer_id=225847803','message='+q)
    except:
        pass
input()

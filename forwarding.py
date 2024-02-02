import urllib.parse
import traceback

import object

def forwarding(n, arg=...):
    if arg == ...:
        return lambda arg: forwarding(n, arg)
    urls = []
    try:
        while arg:
            for q in range(len(arg)):
                try:
                    assert not q or arg[q-1] == ':'
                    url = urllib.parse.urlsplit('http://' + arg[q:])
                    urld = object.Object(
                        host = '127.0.0.1' if url.port is None else url.hostname,
                        port = int(url.hostname) if url.port is None else url.port,
                    )
                    for surl in [
                        f'{urld.host}:{urld.port}',
                        f'[{urld.host}]:{urld.port}'
                    ]:
                        try:
                            url1 = urllib.parse.urlsplit('http://' + surl)
                            assert url1.port == urld.port
                            assert url1.hostname == urld.host
                            assert arg[q:] == surl or f'127.0.0.1:{arg[q:]}' == surl
                            break
                        except Exception:
                            pass
                    else:
                        raise Exception
                    urls.append(urld)
                    arg = arg[:q]
                    arg = arg[:-1]
                    break
                except Exception:
                    pass
            else:
                raise GeneratorExit
    except GeneratorExit:
        raise ValueError
    while len(urls) < n:
        urls.append(object.Object(
            host = '127.0.0.1',
            port = urls[0].port,
        ))
    if len(urls) != n:
        raise ValueError
    urls = urls[::-1]
    return urls

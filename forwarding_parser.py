import urllib
import urllib.parse
import re
import sys

class ColonSeparatedSocketSequence:
    def __init__(self, count: int):
        self.count = count
    def __call__(self, arg: str) -> list[tuple[str, int]]:
        try:
            socket_re = r'([^:]*|\[.*\]):([0-9]+)'
            sockets_re = '^' + ':'.join([socket_re] * self.count) + '$'
            assert (match := re.match(sockets_re, arg)) is not None
            groups = match.groups()
            assert len(groups) == self.count * 2
            sockets = [*zip(groups[0::2], map(int, groups[1::2]))]
            parsed_sockets = []
            for socket in sockets:
                result = urllib.parse.urlparse(f'http://{socket[0]}:{socket[1]}')
                parsed_socket = (result.hostname or '', result.port or -1)
                assert socket[0] in [parsed_socket[0], '[' + parsed_socket[0] + ']']
                assert socket[1] in [parsed_socket[1]]
                parsed_sockets.append(parsed_socket)
            return parsed_sockets
        except Exception:
            raise ValueError
    def __repr__(self) -> str:
        return self.__class__.__name__ + '(' + ', '.join([k + '=' + repr(v) for k,v in self.__dict__.items()]) + ')'

assert ColonSeparatedSocketSequence(0)('') == []
assert ColonSeparatedSocketSequence(1)(':20') == [('', 20)]
assert ColonSeparatedSocketSequence(1)('a.a:20') == [('a.a', 20)]
assert ColonSeparatedSocketSequence(1)('12:20') == [('12', 20)]
assert ColonSeparatedSocketSequence(1)('12.34:20') == [('12.34', 20)]
assert ColonSeparatedSocketSequence(2)('[2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d]:20:[2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d]:30') == [('2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d', 20), ('2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d', 30)]



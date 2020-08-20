from urllib.request import urlopen as u
q=u('http://www.mobilenin.com/mobilepythonbook/examples.html').read().decode()

q=q.split('<tr>')[1:]
q=[w.split('|')[1] for w in q]
q=[w.split('<a href="')[1] for w in q]
q=[w.split('"')[0] for w in q]
q=['http://www.mobilenin.com/mobilepythonbook/'+w for w in q]
from os import system as sh
print([w for w in [sh('wget '+w) for w in q] if w])

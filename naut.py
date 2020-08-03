from urllib.request import urlopen as u
q=u('http://www.easypolls.net/poll.html?p=5dcee336e4b068952e50ff4c').read()
print(q)

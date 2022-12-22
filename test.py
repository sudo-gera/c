<<<<<<< HEAD
import server_example
def log(*q):
    print(q)


s=server_example.Server(call=log)
print(s.port)

=======
from treap import *


a = treap(range(10**4))

for w in range(10**4):
    s=a[:10**3:treap.no_copy]
    a+=treap.no_copy(s)


>>>>>>> 13bc93bc3633e4c71d443c4647ebed0ce0ca3ecf

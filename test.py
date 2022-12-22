import server_example
def log(*q):
    print(q)


s=server_example.Server(call=log)
print(s.port)


import sys, socket





localPort, remoteHost, remotePort = sys.argv[1].split(':')

try:
    localPort = int(localPort)
except:
    fail('Invalid port number: ' + str(localPort))
try:
    remotePort = int(remotePort)
except:
    fail('Invalid port number: ' + str(remotePort))

try:
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.bind(('', localPort))
except:
    fail('Failed to bind on port ' + str(localPort))

knownClient = None
knownServer = (remoteHost, remotePort)
sys.stdout.write('All set, listening on '+str(localPort)+'.\n')
while True:
    data, addr = s.recvfrom(32768)
    if knownClient is None or addr != knownServer:
        if debug:
            print("")
        knownClient = addr

    print([data,addr])

    if debug:
        print("Packet received from "+str(addr))

    if addr == knownClient:
        if debug:
            print("\tforwarding to "+str(knownServer)) 

        s.sendto(data, knownServer)
    else:
        if debug:
            print("\tforwarding to "+str(knownClient))
        s.sendto(data, knownClient)
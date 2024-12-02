<<<<<<< HEAD
//const TUNNEL_URL = 'wss://user225847803-5y4xxqyz.wormhole.vk-apps.com/'  // url, который дал вам туннель
const TUNNEL_URL = 'wss://192.168.64.1:9999'  // url, который дал вам туннель

const io = require('socket.io-client')

const socket = io(TUNNEL_URL, { transports: ['websocket'], rejectUnauthorized: false })

socket.on('connect', () => {
  console.log('Connected to server')
  setInterval(() => socket.emit('message', 'Hello from client'), 2000)
})

socket.on('message', (msg) => {
  console.log('Message from server:', msg)
})

socket.on('disconnect', () => {
  console.log('Disconnected from server')
})
=======
const TUNNEL_URL = 'wss://user225847803-j7ioonhw.wormhole.vk-apps.com/'  // url, который дал вам туннель
// const TUNNEL_URL = 'ws://127.0.0.1:3000'  // url, который дал вам туннель

const io = require('socket.io-client')

var net = require('net');

function base64ToArrayBuffer(base64) {
    var binaryString = atob(base64);
    var bytes = new Uint8Array(binaryString.length);
    for (var i = 0; i < binaryString.length; i++) {
        bytes[i] = binaryString.charCodeAt(i);
    }
    return bytes;
}

function connection(wsocket, socket){
    socket.on('data', data => {
        data = data.toString('base64');
        wsocket.send(data);
    });
    wsocket.on('message', message=>{
        message = base64ToArrayBuffer(message);
        socket.write(message);
    });
    wsocket.on('disconnect', ()=>{
        socket.destroy();
    })
}

var server = net.createServer(socket => {
    const wsocket = io(TUNNEL_URL, { transports: ['websocket'], rejectUnauthorized: false });
    wsocket.send(JSON.stringify(['127.0.0.1', 22]));
    connection(wsocket, socket);
});

server.listen(1337, '127.0.0.1');

>>>>>>> 4af092fe4429bddb023f075574e6c9ff28b9e788

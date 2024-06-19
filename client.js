const TUNNEL_URL = 'wss://user225847803-m4jenobz.wormhole.vk-apps.com/'  // url, который дал вам туннель
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

var server = net.createServer(socket => {
  const wsocket = io(TUNNEL_URL, { transports: ['websocket'], rejectUnauthorized: false });
  socket.on('data', data=>{
      data = data.toString('base64');
      // console.log(data);
      wsocket.send(data);
  });

  wsocket.on('message', message => {
    // console.log(atob(message));
    socket.write(base64ToArrayBuffer(message));
  });

  // socket.on('close', ()=>{
  //   wsocket.
  // })
  wsocket.on('disconnect', ()=>{
    socket.destroy();
  })


  // socket.pipe(wsocket);

	// socket.write('Echo server\r\n');
	// socket.pipe(socket);
});

server.listen(1337, '127.0.0.1');


// const socket = io(TUNNEL_URL, { transports: ['websocket'], rejectUnauthorized: false })

// socket.on('connect', () => {
//   console.log('Connected to server')
//   setInterval(() => socket.emit('message', 'Hello from client'), 2000)
// })

// socket.on('message', (msg) => {
//   console.log('Message from server:', msg)
// })

// socket.on('disconnect', () => {
//   console.log('Disconnected from server')
// })


const http = require('http');
const express = require('express');
const { Server } = require('socket.io');

const app = express();
const server = http.createServer(app);
const io = new Server(server);

app.get('/', (_, res) => {
  console.log("FUNNY")
  res.send("HELLO FROM SERVER - HTTP");
});

function base64ToArrayBuffer(base64) {
    var binaryString = atob(base64);
    var bytes = new Uint8Array(binaryString.length);
    for (var i = 0; i < binaryString.length; i++) {
        bytes[i] = binaryString.charCodeAt(i);
    }
    return bytes;
}

io.on('connection', (wsocket) => {
  // console.log('a user connected');

  // socket.on('message', (msg) => {
  //   console.log('message: ' + msg);
  //   socket.emit('message', "HELLO FROM SERVER - WS");
  // });

  // socket.on('disconnect', () => {
  //   console.log('user disconnected');
  // });

  var net = require('net');

  var socket = new net.Socket();
  socket.connect(22, '127.0.0.1', function() {
    // console.log('Connected');
    // client.write('Hello, server! Love, Client.');
    // client.pipe(socket);
    socket.on('data', data => {
      data = data.toString('base64');
      // console.log(data);
      wsocket.send(data);
    });

    wsocket.on('message', message=>{
    // console.log(atob(message));
    socket.write(base64ToArrayBuffer(message));
    });
    wsocket.on('disconnect', ()=>{
      socket.destroy();
    })
  });

  // client.on('data', function(data) {
  //   console.log('Received: ' + data);
  //   client.destroy(); // kill client after server's response
  // });

  // client.on('close', function() {
  //   console.log('Connection closed');
  // });

});

server.listen(3000, () => {
  console.log('listening on localhost:3000');
});

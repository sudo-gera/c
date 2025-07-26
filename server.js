<<<<<<< HEAD
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

io.on('connection', (socket) => {
  console.log('a user connected');

  socket.on('message', (msg) => {
    console.log('message: ' + msg);
    socket.emit('message', "HELLO FROM SERVER - WS");
  });

  socket.on('disconnect', () => {
    console.log('user disconnected');
  });
});

server.listen(3000, () => {
  console.log('listening on localhost:3000');
=======
const { Server } = require('socket.io');
const net = require('net');

const io = new Server();

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
        socket.end();
    });
    
}

io.on('connection', (wsocket) => {
    var socket = null;
    wsocket.on('message', message=>{
        if (socket === null){
            to_connect = JSON.parse(message);
            socket = new net.Socket();
            socket.connect(to_connect[1], to_connect[0], ()=>connection(wsocket, socket));
        }
    });
});

io.listen(3000, () => {
    console.log('listening on localhost:3000');
>>>>>>> 4af092fe4429bddb023f075574e6c9ff28b9e788
});

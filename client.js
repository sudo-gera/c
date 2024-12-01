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

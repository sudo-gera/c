const WebSocket = require('ws');
const wsServer = new WebSocket.Server({port: 9000});
wsServer.on('connection', onConnect);
function onConnect(wsClient) {
    console.log('Новый пользователь');
    // отправка приветственного сообщения клиенту
    wsClient.send('Привет');
    wsClient.on('message', function(message) {
        try {
            // сообщение пришло текстом, нужно конвертировать в JSON-формат
            const jsonMessage = JSON.parse(message);
            switch (jsonMessage.action) {
                case 'ECHO':
                    wsClient.send(jsonMessage.data);
                    break;
                case 'PING':
                    setTimeout(function() {
                        wsClient.send('PONG');
                    }, 2000);
                    break;
                default:
                    console.log('Неизвестная команда');
                    break;
            }
        } catch (error) {
            console.log('Ошибка', error);
        }
    })
    wsClient.on('close', function() {
        // отправка уведомления в консоль
        console.log('Пользователь отключился');
    })
}
console.log('Сервер запущен на 9000 порту');

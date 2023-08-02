const express = require('express');
const app = express();
const http = require('http').Server(app);
const io = require('socket.io')(http);
const port = 8080;

const express_config = require('./config/express.js');

express_config.init(app);

var cameraArray={};

app.get('/', (req, res) => {
    res.render('index', {});
});

app.get('/video', (req, res) => {
    res.render('video', {});
});

app.get('/live', (req, res) => {
    res.render('live', {});
});

io.on('connection', (socket) => {

  const listener = (eventName, ...args) => {
    console.log(eventName, args);
  }
  
  socket.onAny(listener);

  console.log(`Connected to client ${socket.id}`)

  socket.on('jpgstream_serverio', (msg) => {
    io.to('webusers').emit('jpgstream_client', msg.pic);
  });
  
  socket.on('webuser', (msg) => {
    console.log('Connected to website')  
    socket.join('webusers');      
  });
});

http.listen(port, () => {
      console.log(`App listening at http://localhost:${port}`)
})
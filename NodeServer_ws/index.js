// Khai báo thư viện
const express = require('express');
const http = require('http');
const WebSocket = require('ws');

const url = require('url');
const fs = require('fs');
const path = require('path');
const { spawn, exec } = require('child_process');

const express_config = require('./config/express.js');

const WS_PORT = 8888;
const videoBufferDir = path.join(__dirname, 'storage', 'tmp');
const videoDir = path.join(__dirname, 'storage', 'videos');
var isRecording = false;
var frameCount = 0;

// Khởi tạo server
const app = express();
const server = http.Server(app);
express_config.init(app)

// Khởi tạo 2 WebSocket server chạy trên cùng server HTTP
const wss_CAM = new WebSocket.Server({ noServer: true });
const wss_WEB = new WebSocket.Server({ noServer: true });

// Thiết lập WebSocket server cho camera
wss_CAM.on('connection', function connection(ws) {

    ws.on('message', function incoming(message) {
        if (message.toString() === "START") {
            console.log("\nStarted recording.");
            isRecording = true;
            frameCount = 0;
        } else if (message.toString() === "STOP") {
            console.log("Stopped recording.");
            isRecording = false;
            createVideo();
        } else {
            wss_WEB.clients.forEach(function each(client) {
                if (client.readyState === WebSocket.OPEN) {
                    client.send(message);
                };
                if (isRecording) {
                    // Lưu các frame tạm thời nếu có tín hiệu isRecording
                    const framePath = path.join(videoBufferDir, `frame_${frameCount}.jpg`);
                    fs.writeFile(framePath, message, { encoding: 'binary' }, (err) => {
                        if (err) {
                            console.error('Error writing frame:', err);
                            return;
                        }
                    });
                    frameCount++;
                }
            });
        }
    });

    ws.on('close', function () {
        wss_WEB.clients.forEach(function each(client) {
            if (client.readyState === WebSocket.OPEN) {
                client.send("TERMINATE");
            };
        });
    })

})

// Thiết lập WebSocket server cho website 
wss_WEB.on('connection', function connection(ws) {

    ws.on('message', function incoming(message) {
        console.log(message.toString());
    });

    ws.on('close', function () {
        console.log('Stream is terminated.');
    })

})

// Tạo hàm khởi tạo WebSocket server mỗi khi nhận request từ HTTP server
server.on('upgrade', function upgrade(request, socket, head) {
    const pathname = url.parse(request.url).pathname;

    if (pathname === '/stream_server') {
        wss_CAM.handleUpgrade(request, socket, head, function done(ws) {
            wss_CAM.emit('connection', ws, request);
        });
    } else if (pathname === '/stream_client') {
        wss_WEB.handleUpgrade(request, socket, head, function done(ws) {
            wss_WEB.emit('connection', ws, request);
        })
    } else {
        // Hủy kết nối
        socket.destroy();
    }
})

// Định nghĩa đường dẫn đến các page của web
app.get('/', (req, res) => {
    res.render('index', {});
});

app.get('/live', (req, res) => {
    res.render('live', {});
});

// Mở HTTP server trên port đã khai báo trước
server.listen(WS_PORT, () => {
    console.log(`App listening at http://localhost:${WS_PORT}`)
})

function createVideo() {
    var timestamp = getVietnamDateTime();

    const outputVideoPath = path.join(videoDir, `video_${timestamp}.mp4`);

    const ffmpegCommand = `ffmpeg -framerate 15 -i "${videoBufferDir}\\frame_%d.jpg" -c:v libx264 -pix_fmt yuv420p "${outputVideoPath}"`;

    exec(ffmpegCommand, (error, stdout, stderr) => {
        if (error) {
            console.error('Error creating video:', error);
        } else {
            console.log('Video created successfully: ' + outputVideoPath);
            // Xoá các frame đã lưu tạm thời
            fs.readdirSync(videoBufferDir).forEach((file) => {
                const filePath = path.join(videoBufferDir, file);
                fs.unlinkSync(filePath);
            });
        }
    });
}

function getVietnamDateTime() {
    const date = new Date();
    const options = {
        year: 'numeric',
        month: '2-digit',
        day: '2-digit',
        hour: '2-digit',
        minute: '2-digit',
        second: '2-digit',
        hour12: false,
        timeZone: 'Asia/Ho_Chi_Minh'
    };
    const formatter = new Intl.DateTimeFormat('vi-VN', options);
    var formattedDate = formatter.format(date).replace(/[/]/g, '_').replace(/[:]/g, '_');
    var time = formattedDate.split(" ");
    return time[1].concat("_T", time[0]);
}
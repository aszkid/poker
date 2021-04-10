const path = require("path");
const app = require("express")();
const http = require("http");
const server = http.createServer(app);
const io = require("socket.io")(server);

app.get("/", (req, res) => {
    res.sendFile(path.join(__dirname , "index.html"));
});

io.on("connection", socket => {
    socket.on("sdp-advertise", msg => {
        console.log(`advertising SDP:`, msg);
    });
});


const PORT = 3000;
server.listen(PORT, () => {
    console.log(`Listening on ${PORT}...`);
});


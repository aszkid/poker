const path = require("path");
const app = require("express")();
const http = require("http");
const server = http.createServer(app);
const io = require("socket.io")(server, {
    cors: {
        origin: "http://localhost:5000",
        methods: ["GET", "POST"]
    }
});
const randomWords = require("random-words");

// Mapping of server name to server info object
const servers = {};

app.get("/", (req, res) => {
    res.sendFile(path.join(__dirname , "index.html"));
});

io.on("connection", socket => {
    socket.on("server-create", msg => {
        const name = randomWords(3).join("-");
        servers[name] = { owner: socket, name };
        socket.emit("on-server-create", name);
    });
    socket.on("sdp-offer", ({ id, offer }) => {
        const server = servers[id];
        if (socket.id === server.owner.id) {
            server.offer = offer;
        }
    });
    socket.on("sdp-answer", ({ id, answer }) => {
        const server = servers[id];
        if (server) {
            server.owner.emit("on-client-connect", answer);
        }
    });
    socket.on("server-connect", id => {
        const server = servers[id];
        if (server) {
            socket.emit("on-server-connect", { offer: server.offer });
        }
    });
});

const PORT = 3000;
server.listen(PORT, () => {
    console.log(`Listening on ${PORT}...`);
});

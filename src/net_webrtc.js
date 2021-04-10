// Consider using this: https://github.com/evanw/emscripten-library-generator
mergeInto(LibraryManager.library, {
    peerConnection: null,
    dataChannel: null,
    socket: null,
    serverId: null,
    js_init: function () {
        socket = io("http://localhost:3000");
        socket.on("on-server-connect", async ({ offer }) => {
            console.log(`connected to server, offer:`, offer);
            await peerConnection.setRemoteDescription(offer);
            await peerConnection.setLocalDescription(await peerConnection.createAnswer());
            socket.emit("sdp-answer", { answer: await peerConnection.localDescription, id: serverId });
        });
        peerConnection = new RTCPeerConnection({
            iceServers: [{ "urls": "stun:stun.l.google.com:19302" }],
        });
        peerConnection.onicecandidate = async event => {
            // Done receiving ICE candidates, create offer
            const isServer = false;
            if (!event.candidate && isServer) {
                const offer = await peerConnection.createOffer();
                console.log(offer.sdp);
                socket.emit("sdp-offer", { id: serverId, offer });
            }
        };
        peerConnection.ondatachannel = event => {
            // Remote peer creates a data channel
            if (event.channel.label === "chat") {
                dataChannel = event.channel;
            }
            event.channel.onmessage = message => {
                const net_handle_message = Module.cwrap(`_net_handle_message`, null, ['string']);
                net_handle_message(message.data);
            };
        };
        peerConnection.onnegotiationneeded = async event => {
            await peerConnection.setLocalDescription(await peerConnection.createOffer());
        };
        peerConnection.onconnectionstatechange = event => {
            console.log(peerConnection.connectionState);
        };
    },
    js_connect: function (_serverId) {
        serverId = UTF8ToString(_serverId);
        console.log(`asked to connect to ${serverId}...`);
        socket.emit("server-connect", serverId);
    },
});

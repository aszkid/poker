mergeInto(LibraryManager.library, {
    do_connect: () => {
        console.log(`connecting...`);
        var localConnection = new RTCPeerConnection({
            iceServers: [{ "urls": "stun:stun.l.google.com:19302" }],
        });

        let sendChannel = localConnection.createDataChannel("sendChannel");
        sendChannel.onopen = () => {
            Module.ccall(`_net_handle_open`, `null`, [], []);
        };;
        sendChannel.onclose = () => {
            Module.ccall(`_net_handle_close`, `null`, [], []);
        };

        const handleAddCandidateError = error => console.error(`ice candidate error:`, error);
        localConnection.onicecandidate = e => {};
    },

});

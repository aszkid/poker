mergeInto(LibraryManager.library, {
    my_js: function(a) {
        alert(`hi: ${a}`);
    },
    do_connect: function() {
        const openCallback = () => {
            Module.ccall(`_net_handle_open`, `null`, [], []);
        };

        console.log(`connecting...`);
        let localConnection = new RTCPeerConnection();
        let sendChannel = localConnection.createDataChannel("sendChannel");
        sendChannel.onopen = openCallback;
        sendChannel.onclose = () => { console.log(`close`); };

        let remoteConnection = new RTCPeerConnection();
        remoteConnection.ondatachannel = () => { console.log(`data`); };

        const handleAddCandidateError = error => console.error(`ice candidate error:`, error);
        localConnection.onicecandidate = e => !e.candidate
            || remoteConnection.addIceCandidate(e.candidate)
            .catch(handleAddCandidateError);

        remoteConnection.onicecandidate = e => !e.candidate
            || localConnection.addIceCandidate(e.candidate)
            .catch(handleAddCandidateError);

        localConnection.createOffer()
            .then(offer => localConnection.setLocalDescription(offer))
            .then(() => remoteConnection.setRemoteDescription(localConnection.localDescription))
            .then(() => remoteConnection.createAnswer())
            .then(answer => remoteConnection.setLocalDescription(answer))
            .then(() => localConnection.setRemoteDescription(remoteConnection.localDescription))
            .catch(error => console.error(`offer error:`, error));
    },
});

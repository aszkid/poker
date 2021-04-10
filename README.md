Inspired by Uxn: https://wiki.xxiivv.com/site/uxn.html

## Developing

Requirements: `docker`, `npm`.

1. Boot up the signaling server: `cd server && npm install && npm start`.
2. Open `http://localhost:3000` on the browser and click "Create server". Copy the server ID.
3. Open `src/poker.c` and fill in the server ID in the `net_connect(...)` function call.
4. `docker build -t poker .`
5. `docker run -p 5000:5000 -v $PWD:/poker poker`

## Contributing

Requirements: `clang-format`.

Make sure to run `make format` before pushing your changes.

## Links

- [Porting a C++ multiplayer game to the Web with Cheerp, WebRTC and Firebase](https://medium.com/leaningtech/porting-a-c-multiplayer-game-to-the-web-with-cheerp-webrtc-and-firebase-29fbbc62c5ca)
- [WebRTC basics](https://www.html5rocks.com/en/tutorials/webrtc/basics/)
- [serverless-webrtc](https://github.com/cjb/serverless-webrtc)
- [WebRTC one-to-one without signaling server](https://mac-blog.org.ua/webrtc-one-to-one-without-signaling-server/)
- [WebRTC for the curious](https://webrtcforthecurious.com/)
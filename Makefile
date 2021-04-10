all: poker_wasm
poker_wasm: src/poker.c src/gfx_sdl2.c src/net_webrtc.c
	emcc -DEMSCRIPTEN $^ \
		--js-library src/net_webrtc.js \
		-s EXPORTED_FUNCTIONS='["_main","__net_handle_message"]' \
		-s EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' \
		-s WASM=1 \
		-s USE_SDL=2 \
		-o dist/poker.js
clean:
	rm -f dist/poker.wasm dist/poker.js
format:
	clang-format -i src/*.[ch]
serve: poker_wasm
	emrun --port 5000 --no_browser dist
.PHONY: clean all serve run format

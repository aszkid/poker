all: poker_sdl2 poker_wasm
poker_sdl2: src/poker.c src/gfx_sdl2.c src/net_posix.c
	gcc $^ -lSDL2 -o $@ 
poker_wasm: src/poker.c src/gfx_sdl2.c src/net_webrtc.c
	emcc -DEMSCRIPTEN $^ \
		--js-library src/net_webrtc.js \
		-s EXPORTED_FUNCTIONS='["_main","__net_handle_open","__net_handle_foo"]' \
		-s EXPORTED_RUNTIME_METHODS='["ccall"]' \
		-s WASM=1 \
		-s USE_SDL=2 \
		-o dist/poker.js
clean:
	rm -f poker_sdl2 dist/poker.wasm dist/poker.js
format:
	clang-format -i src/*.[ch]
serve: poker_wasm
	emrun --port 5000 --no_browser dist
run: poker_sdl2
	./poker_sdl2
.PHONY: clean all serve run format

all: poker_sdl2 poker_wasm
poker.o: src/poker.c
	gcc $^ -c -o $@
poker.wasm.o: src/poker.c
	emcc -DEMSCRIPTEN $^ -c -o $@
poker_sdl2: poker.o src/gfx_sdl2.c
	gcc $^ -lSDL2 -o $@ 
poker_wasm: poker.wasm.o src/gfx_sdl2.c
	emcc -DEMSCRIPTEN $^ -s WASM=1 -s USE_SDL=2 -o dist/poker.js
clean:
	rm -f poker.o poker_sdl2 dist/poker.wasm* dist/poker.js
serve: poker_wasm
	emrun --port 5000 --no_browser dist
run: poker_sdl2
	./poker_sdl2
.PHONY: clean all serve run

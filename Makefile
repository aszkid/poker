all: poker_sdl2 poker_wasm
poker.o: poker.c
	gcc $^ -c -o $@
poker.wasm.o: poker.c
	emcc -DEMSCRIPTEN $^ -c -o $@
poker_sdl2: poker.o gfx_sdl2.c
	gcc $^ -lSDL2 -o $@ 
poker_wasm: poker.wasm.o gfx_sdl2.c
	emcc -DEMSCRIPTEN $^ -s WASM=1 -s USE_SDL=2 -o poker.js
clean:
	rm -f poker.o poker_sdl2 poker.wasm* poker.js
serve: poker_wasm
	emrun --port 5000 --no_browser .
run: poker_sdl2
	./poker_sdl2
.PHONY: clean all serve run

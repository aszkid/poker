poker.o: poker.c
	gcc $^ -c -o $@
poker_sdl2: poker.o gfx_sdl2.c
	gcc $^ -I/usr/include/SDL2 -I/usr/include/directfb -D_REENTRANT -L/usr/lib -pthread -lSDL2 -o $@ 
clean:
	rm -f poker.o poker_sdl2
.PHONY: clean

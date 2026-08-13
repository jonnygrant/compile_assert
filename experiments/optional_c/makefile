all: single

single:
	gcc -I../.. -D__ENABLE_COMPILE_ASSERT__ -ftrack-macro-expansion=0 -std=c2x -Wall -O3 -o optional.bin optional.c

clean:
	rm -f *.lto
	rm -f *.bin
	rm -f *.o

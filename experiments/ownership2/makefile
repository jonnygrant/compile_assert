all: single

single:
	echo "all compiled together with LTO"
	gcc -I../.. -D__ENABLE_COMPILE_ASSERT__ -ftrack-macro-expansion=0 -std=c2x -Wall -O3 -flto -o ownership.bin bogus.c ownership1.c ownership2.c

ownership:
	echo "ownership - separate files with LTO"
	gcc -I../.. -D__ENABLE_COMPILE_ASSERT__ -ftrack-macro-expansion=0 -std=c2x -Wall -O3 -flto -c -o ownership1.lto ownership1.c
	gcc -I../.. -D__ENABLE_COMPILE_ASSERT__ -ftrack-macro-expansion=0 -std=c2x -Wall -O3 -flto -c -o ownership2.lto ownership2.c
	gcc -I../.. -D__ENABLE_COMPILE_ASSERT__ -ftrack-macro-expansion=0 -std=c2x -Wall -O3 -flto -c -o bogus.lto bogus.c
	gcc -I../.. -D__ENABLE_COMPILE_ASSERT__ -ftrack-macro-expansion=0 -std=c2x -Wall -O3 -flto -o ownership.bin ownership1.lto ownership2.lto bogus.lto

clean:
	rm -f *.lto
	rm -f *.bin
	rm -f *.o

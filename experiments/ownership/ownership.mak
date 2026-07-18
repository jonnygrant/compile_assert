all: start

start:
	gcc -I../.. -D__ENABLE_COMPILE_ASSERT__ -std=c2x -ftrack-macro-expansion=0 -Wall -O2 -c -o ownership1.o ownership1.c
	gcc -I../.. -D__ENABLE_COMPILE_ASSERT__ -std=c2x -ftrack-macro-expansion=0 -Wall -O2 -c -o ownership2.o ownership2.c
	#gcc -I../.. -D__ENABLE_COMPILE_ASSERT__ -std=c2x -ftrack-macro-expansion=0 -Wall -O2 -c -o float_container.o float_container.c
	gcc -o ownership.bin ownership1.o ownership2.o

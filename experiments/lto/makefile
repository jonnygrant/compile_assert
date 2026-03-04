# -S -fverbose-asm, or -save-temps
# objdump -d -S -M intel
all:
	gcc -std=c99 -I../.. -D__ENABLE_COMPILE_ASSERT__ -g -O2 -Wall -flto -c -o lto1.o lto1.c
	gcc -std=c99 -I../.. -D__ENABLE_COMPILE_ASSERT__ -g -O2 -Wall -flto -c -o lto2.o lto2.c
	gcc -I../.. -D__ENABLE_COMPILE_ASSERT__ -g -O2 -Wall -flto -o lto lto1.o lto2.o
	objdump -d -S -M intel lto > lto.disasm
	gcc -std=c99 -I../.. -D__ENABLE_COMPILE_ASSERT__ -g -O2 -Wall -flto -S -fverbose-asm lto1.c lto2.c

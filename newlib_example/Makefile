all: nqueens.run yum.run test.run test2.run

nqueens.run: nqueens.c
	m68k-elf-gcc -Wall -m68000 -O nqueens.c -o nqueens.run -T /opt/m68k-elf/m68k-elf/lib/m68000/ts2.ld -Xlinker -Map=nqueens.map

yum.run: yum.c
	m68k-elf-gcc -Wall -m68000 -g -O yum.c -o yum.run -T /opt/m68k-elf/m68k-elf/lib/m68000/ts2.ld -Xlinker -Map=yum.map

test.run: test.cc
	m68k-elf-g++  -O3 -fno-exceptions -fomit-frame-pointer -Wall  -m68000 -g -O test.cc -o test.run -T /opt/m68k-elf/m68k-elf/lib/m68000/ts2.ld -Xlinker -Map=test.map

test2.run: test.c
	m68k-elf-gcc -Wall -m68000 -g -O test.c -o test2.run -T /opt/m68k-elf/m68k-elf/lib/m68000/ts2.ld -Xlinker -Map=test2.map

clean:
	$(RM) nqueens.run nqueens.map
	$(RM) yum.run yum.map
	$(RM) test.run test.map
	$(RM) test2.run test2.map

distclean: clean



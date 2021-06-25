all: nqueens.run yum.run test.run 

nqueens.run: nqueens.c
	m68k-elf-gcc -Wall -m68000 -O nqueens.c -o nqueens.run -T /opt/m68k-elf/m68k-elf/lib/m68000/ts2.ld -Xlinker -Map=nqueens.map

yum.run: yum.c
	m68k-elf-gcc -Wall -m68000 -g -O yum.c -o yum.run -T /opt/m68k-elf/m68k-elf/lib/m68000/ts2.ld -Xlinker -Map=yum.map

test.run: test.S
	m68k-elf-as -Wall -m68000 -g test.S -o test.o 
	m68k-elf-ld test.o -o test.srec -O3 -L/opt/m68k-elf/m68k-elf/lib/m68000 -L/opt/m68k-elf/lib/gcc/m68k-elf/10.3.1/m68000 -T /opt/m68k-elf/m68k-elf/lib/m68000/ts2.ld -Map=test.map

clean:
	$(RM) nqueens.run nqueens.map
	$(RM) yum.run yum.map
	$(RM) test.run test.map

distclean: clean



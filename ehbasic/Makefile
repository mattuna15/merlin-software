
basic68k.run: basic68k.asm 
	m68k-elf-as -m68000 -mri basic68k.asm -o basic.o
	m68k-elf-ld -o newbas.run basic.o -Os -L/opt/m68k-elf/m68k-elf/lib/m68000 -L/opt/m68k-elf/lib/gcc/m68k-elf/10.3.1/m68000 -L../gd2-lib -lGD2 -L../FatFs -lMerlinFat  -T ts2.ld  -Map=basic.map

clean:
	$(RM) basic68k.run basic68k_even.run basic68k_odd.run basic68k.lst basic68k.hex
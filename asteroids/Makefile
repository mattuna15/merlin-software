all: asteroids.srec

asteroids.srec: asteroids.s

	m68k-elf-as -mri -ashl -m68000  asteroids.s -o asteroids.o
	m68k-elf-ld -O3 -o asteroids.srec asteroids.o  \
			-L/opt/m68k-elf/m68k-elf/lib/m68000 \
			-L/opt/m68k-elf/lib/gcc/m68k-elf/10.3.1/m68000 -L../gd2-lib -lGD2 -L../FatFs -lMerlinFat  \
			-T ts2.ld  -Map=asteroids.map
	#m68k-elf-objdump -d asteroids.bin > listing.asm

clean:
	$(RM) *.o *.a *.srec


distclean: clean



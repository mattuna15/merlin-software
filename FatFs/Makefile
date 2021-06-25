all: fat-test.run

fat-test.run: mmc.c diskio.c fat_compat.c ff.c ffsystem.c ffunicode.c utils.c swap.c main.c 
	m68k-elf-gcc -Wall -m68000 -g -Os utils.c swap.c mmc.c diskio.c ff.c ffsystem.c ffunicode.c fat_compat.c  main.c  -o fat-test.run -T /opt/m68k-elf/m68k-elf/lib/m68000/ts2.ld -Xlinker -Map=fat-test.map

clean:
	$(RM) *.o fat-test.run fat-test.map


distclean: clean
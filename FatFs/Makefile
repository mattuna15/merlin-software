all: fat-test.run lib

lib: libMerlinFat.a

fat-test.run: mmc.c diskio.c fat_compat.c ff.c ffsystem.c ffunicode.c utils.c swap.c main.c 
	m68k-elf-gcc -Wall -m68010 -g -Os utils.c swap.c mmc.c diskio.c ff.c ffsystem.c ffunicode.c fat_compat.c  main.c  -o fat-test.run -T /opt/m68k-elf/m68k-elf/lib/m68000/ts2.ld -Xlinker -Map=fat-test.map

libMerlinFat.a : mmc.c diskio.c fat_compat.c fat_bas.c ff.c ffsystem.c ffunicode.c utils.c swap.c 
	m68k-elf-gcc -Wall -m68010 -mbitfield -g -Os -c utils.c swap.c mmc.c diskio.c fat_bas.c ff.c ffsystem.c ffunicode.c fat_compat.c
	m68k-elf-ar rcs libMerlinFat.a *.o 

clean:
	$(RM) *.o fat-test.run fat-test.map *.a


distclean: clean

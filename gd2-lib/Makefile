all: mandel.run

mandel.run: mandel.c
	m68k-elf-gcc  -O3  -m68000 -g -O mandel.c -o mandel.run -T /opt/m68k-elf/m68k-elf/lib/m68000/ts2.ld -L. -lm -lGD2 -L../FatFs -lMerlinFat -Xlinker -Map=terminal.map


lib: libGD2.a

libGD2.a: GD2.cpp  GD-c.cpp
	m68k-elf-g++ -O3 -fno-exceptions -fomit-frame-pointer -Wall -m68000 -c GD2.cpp GD-c.cpp
	m68k-elf-ar rcs libGD2.a *.o 

clean:
	$(RM) *.o *.a


distclean: clean



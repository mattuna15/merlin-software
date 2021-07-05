all: terminal.run

terminal.run: GD2.cpp  term.cpp
	m68k-elf-g++  -O3 -fno-exceptions -fomit-frame-pointer -Wall -m68000 -g -O GD2.cpp term.cpp -o terminal.run -T /opt/m68k-elf/m68k-elf/lib/m68000/ts2.ld  -L../FatFs -lMerlinFat -Xlinker -Map=terminal.map


lib: libGD2.a

libGD2.a: GD2.cpp  GD-c.cpp
	m68k-elf-g++ -O3 -fno-exceptions -fomit-frame-pointer -Wall -m68000 -c GD2.cpp GD-c.cpp
	m68k-elf-ar rcs libGD2.a *.o 

clean:
	$(RM) *.o *.a


distclean: clean



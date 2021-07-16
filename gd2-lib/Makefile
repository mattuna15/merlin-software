all: cobra.run

cobra.run: cobra.cpp
	m68k-elf-g++ -fno-exceptions -fomit-frame-pointer -Wall  -O3  -m68000 -g -O cobra.cpp -o cobra.run -T /opt/m68k-elf/m68k-elf/lib/m68000/ts2.ld -L. -lm -lGD2 -L../FatFs -lMerlinFat -Xlinker -Map=cobra.map


lib: libGD2.a

libGD2.a: GD2.cpp  GD-c.cpp
	m68k-elf-g++ -O3 -fno-exceptions -fomit-frame-pointer -Wall -m68000 -c GD2.cpp GD-c.cpp
	m68k-elf-ar rcs libGD2.a *.o 

clean:
	$(RM) *.o *.a *.run


distclean: clean



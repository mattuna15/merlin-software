all: lib speech.run cobra.run mandel.run mouse.srec

speech.run: speech.cpp
	m68k-elf-g++ -fno-exceptions -fomit-frame-pointer -Wall -m68000 -g -O3 speech.cpp ../fp-lib/ieee754.c -o speech.run  \
			-Wl,--wrap=__muldf3 \
			-Wl,--wrap=__divdf3 \
			-Wl,--wrap=__subdf3 \
			-Wl,--wrap=__adddf3 \
			 -I../fp-lib/ -T ts2.ld -L. -lGD2 -L../FatFs -lMerlinFat -Xlinker -Map=speech.map

cobra.run: cobra.cpp
	m68k-elf-g++ -fno-exceptions -fomit-frame-pointer -Wall -m68000 -g -O3 cobra.cpp ../fp-lib/ieee754.c -o cobra.run  \
			-Wl,--wrap=__muldf3 \
			-Wl,--wrap=__divdf3 \
			-Wl,--wrap=__subdf3 \
			-Wl,--wrap=__adddf3 \
			-Wl,--wrap=__truncdfsf2 \
			-Wl,--wrap=__extendsfdf2 \
			 -I../fp-lib/ -T ts2.ld -L. -lGD2 -L../FatFs -lMerlinFat -Xlinker -Map=cobra.map

mandel.run: mandel.c
	m68k-elf-g++ -fno-exceptions -fomit-frame-pointer -Wall -m68000 -g -O3 ../fp-lib/ieee754.c mandel.c -o mandel.run  \
			-Wl,--wrap=__muldf3 \
			-Wl,--wrap=__divdf3 \
			-Wl,--wrap=__subdf3 \
			-Wl,--wrap=__adddf3 \
			-Wl,--wrap=__truncdfsf2 \
			-Wl,--wrap=__extendsfdf2 \
			-I../fp-lib/ -T ts2.ld -L. -lGD2 -L../FatFs -lMerlinFat -Xlinker -Map=mandel.map

daz.run: daz.c
	m68k-elf-g++ -fno-exceptions -fomit-frame-pointer -Wall -m68000 -g -O3 ../fp-lib/ieee754.c daz.c -o daz.run  \
			-Wl,--wrap=__muldf3 \
			-Wl,--wrap=__divdf3 \
			-Wl,--wrap=__subdf3 \
			-Wl,--wrap=__adddf3 \
			-I../fp-lib/ -T ts2.ld -L. -lGD2 -L../FatFs -lMerlinFat -Xlinker -Map=daz.map

mouse.srec: mouse_demo.cpp 
	m68k-elf-g++ -fno-exceptions -fomit-frame-pointer -Wall -m68000 -g -O3 ../fp-lib/ieee754.c mouse_demo.cpp -o mouse.srec  \
			-Wl,--wrap=__muldf3 \
			-Wl,--wrap=__divdf3 \
			-Wl,--wrap=__subdf3 \
			-Wl,--wrap=__adddf3 \
			-I../fp-lib/ -T ts2.ld -L. -lGD2 -L../FatFs -lMerlinFat -Xlinker -Map=mouse.map

lib: libGD2.a


libGD2.a: GD2.cpp  GD-c.cpp
		 
	m68k-elf-g++ -O3 -fno-exceptions -fomit-frame-pointer -Wall -m68010 -mbitfield -c GD2.cpp GD-c.cpp 
		 	
	m68k-elf-ar rcs libGD2.a *.o 

clean:
	$(RM) *.o *.a *.run


distclean: clean



all:	tutor13.run tutor13.bin tutor13.hex tutor13_even.bin tutor13_odd.bin

tutor13.o: tutor13.s
	m68k-elf-as -m68000 -alms -a=tutor13.lst -o tutor13.o tutor13.s

tutor13.run: tutor13.o
	m68k-elf-objcopy -I elf32-m68k -O srec tutor13.o temp
	srec_cat temp -fill 0x00 0x0000 0x5000 --crop 0x0000 0x5000 -Output_Block_Size 16 -o tutor13.srec
	srec_cat temp -fill 0x00 0x1000 0x5000 --crop 0x1000 0x5000 -Output_Block_Size 16 -o tutor13-load.srec
	$(RM) temp

tutor13.bin: tutor13.o
	m68k-elf-objcopy -I elf32-m68k -O binary tutor13.o tutor13.bin

tutor13.hex: tutor13.run
	srec_cat tutor13.run -Motorola -output tutor13.hex -Intel

tutor13_even.bin: tutor13_even.run
	srec_cat tutor13_even.run -Motorola --crop 0xD00000 0xa000 --offset -0xD00000 -output tutor13_even.bin -Binary

tutor13_odd.bin: tutor13_odd.run
	srec_cat tutor13_odd.run -Motorola --crop 0xD00000 0xa000 --offset -0xD00000 -output tutor13_odd.bin -Binary

clean:
	$(RM) tutor13.lst tutor13.o tutor13.run tutor13.bin tutor13.hex tutor13.srec
	$(RM) tutor13_even.run tutor13_odd.run
	$(RM) tutor13_even.bin tutor13_odd.bin

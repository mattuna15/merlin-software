AS = vasmm68k_mot
ASFLAGS = -quiet -m68000 -no-opt -Fbin

%.bin: %.s
	$(AS) $(ASFLAGS) -L $*.lst -o $@ $<

all: testprog.bin pep8

install:
	echo "Installing Python dependencies"
	pip3 install --user pipenv
	pipenv --python 3.8

uninstall:
	pipenv --rm

pep8:
	pipenv run pycodestyle --max-line-length=150 disasm68k.py

test: vasmm68k_mot testprog.s disasm68k.py
	echo "Compiling S-record to binary"
	$(AS) $(ASFLAGS) -L $*.lst -o testprog.bin testprog.s
	echo "Disassembling binary back to S-record"
	pipenv run python disasm68k.py -n testprog.bin >output.s

output.s: testprog.bin
	pipenv run python disasm68k.py -n testprog.bin >output.s

compare: output.bin output.s
	hexdump -C testprog.bin >testprog.hex
	hexdump -C output.bin >output.hex
	diff -y --suppress-common-lines testprog.hex output.hex

clean:
	$(RM) *.bin *.lst *.hex output.s

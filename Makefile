CC = sdcc
STCGAL = stcgal
PORT = /dev/ttyACM0
STCGAL_FLAGS = -p $(PORT) -b 9600 -P stc89

hdrs = $(wildcard *.h)

main.ihx: main.c $(wildcard *.h)
	$(CC) main.c

build: main.ihx

flash: build
	$(STCGAL) $(STCGAL_FLAGS) main.ihx


clean: 
	rm main.ihx main.lk main.lst main.map main.mem main.rel main.sym main.asm main.rst

.PHONY: build clean
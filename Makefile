CHDEV = chdev
CC = gcc -pthread -g -Wpedantic -Wall -Werror -pedantic-errors

all: info uninstall build compile 

compile:
	$(CC) 0_telefon.c -o 0_telefon.o
	$(CC) 1_konsola.c -o 1_konsola.o
	$(CC) 2_argument.c -o 2_argument.o
	$(CC) 3_pipe.c -o 3_pipe.o

build:
	cd $(CHDEV) && $(MAKE) build
	cd $(CHDEV) ; sudo insmod jajko.ko

run:
	./0_telefon.o

clean:
	rm -rf *.o
	cd $(CHDEV) && $(MAKE) clean

uninstall:
	-sudo rmmod jajko


info:
	echo "Program gluchy telefon do komunikacji w systemie linux"

CFLAGS = -Wall
CC = gcc

main:
	$(CC) -o zad2 zad2.c $(CFLAGS) 

clean:
	rm -f ./zad2.o ./zad2

test:  zad2
	@echo -e "\n\nTESTING\n\n"
	./zad2 good
	@echo -e "=========================================================="
	./zad2 bad

all: zad2 test

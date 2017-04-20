main: main.o pullo.o apu.o tiedosto.o yllapito.o
	gcc main.o pullo.o apu.o tiedosto.o yllapito.o -o main -Wall -std=c99
pullo.o: pullo.c pullo.h
	gcc pullo.c -c -Wall -std=c99
apu.o: apu.c apu.h
	gcc apu.c -c -Wall -std=c99
tiedosto.o: tiedosto.c tiedosto.h
	gcc tiedosto.c -c -Wall -std=c99
yllapito.o: yllapito.c yllapito.h
	gcc yllapito.c -c -Wall -std=c99
main.o: main.c pullo.h apu.h tiedosto.h yllapito.h tietorakenteet.h
	gcc main.c -c -Wall -std=c99
all:
	make

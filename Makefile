all: main boardC4.o listC4.o

listC4.o: listC4.c listC4.h
	gcc -c listC4.c

boardC4.o: boardC4.c boardC4.h
	gcc -c boardC4.c

main: connect4.c boardC4.o listC4.o
	gcc -o main connect4.c boardC4.o listC4.o
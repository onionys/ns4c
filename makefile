CC=g++

ns4cHKL: mainHKL.o ONString.o
	$(CC) mainHKL.o ONString.o -o ns4cHKL


ns4c: main.o ONString.o
	$(CC) main.o ONString.o -o ns4c


main.o: main.cpp ONString.h ONString.cpp
	$(CC) -c main.cpp

mainHKL.o: mainHKL.cpp ONString.h ONString.cpp
	$(CC) -c mainHKL.cpp


ONString.o: ONString.h ONString.cpp
	$(CC) -c ONString.cpp

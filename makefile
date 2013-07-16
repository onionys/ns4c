CC=g++

EXE=ns4c

ns4c: scan.o StrProc.o main.o fourcfile.o
	$(CC) scan.o StrProc.o main.o fourcfile.o -o $(EXE)

test: scan.o StrProc.o test.o fourcfile.o
	$(CC) scan.o StrProc.o test.o fourcfile.o -o a.out

main.o: main.cpp
	$(CC) -c main.cpp

test.o: test.cpp
	$(CC) -c test.cpp

StrProc.o : StrProc.cpp StrProc.h
	$(CC) -c StrProc.cpp

scan.o: scan.h scan.cpp 
	$(CC) -c scan.cpp

fourcfile.o: fourcfile.h fourcfile.cpp
	$(CC) -c fourcfile.cpp

clean:
	rm *.o
	rm ns4c
	rm a.out

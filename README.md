A samll command line prog to read the scan data from file that generated by the program: fourc.

This program is suitable to these beam lines in NSRRC: 13A, 17B, 4C (in house)

========
INSTALL
========

The g++ compiler must be installed

use the makefile: ./make

Or you can compile it directly: 

	$> g++ -c fourcfile.cpp

	$> g++ -c scan.cpp

	$> g++ -c StrProc.h

	$> g++ -c main.cpp

	$> g++ main.o StrProc.o scan.o fourcfile.o -o ns4c

========
USAGE
========
place the "ns4c" at the directory with the data file generated from "fourc".

execute ns4c and then show the console...

Then use the command newfile and followed the file name of the data file generaged from "fourc".
ex:
	>>newfile datafilename


use the "help" or "?" to known the supported command
ex:
	>>help
	>>?


then use the command "scan" or "s" and the scan number to show the scan data
ex: show the scan data of the scan 10:
	>>scan 10
	>>s 10


save the "scan" or "sa" data of scan number, and the data will saved with the file extension ".dat"
ex: save the data of scan 10
	>>save 10
	>>sa 10

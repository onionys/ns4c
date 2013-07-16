#include<iostream>
#include<stdlib.h>
#include<cstring>
#include"StrProc.h"
#include"fourcfile.h"

using std::cout ;
using std::cin;
using std::endl;

int compstr(string one, const char * two){
	return (0 == strcmp(one.c_str(), two ))?(1):(0);
}

void printFunctionMessage();


int main(int argc, char *argv[]){
	string command;
	VStr comms;
	fourcfile infile;
	//
	// check input error ?
	//
	if(argc == 2 ){
		// load the file by filename 
		string filename(argv[1]);
		infile.setFilename(filename);
	}

	//
	// Main LOOP
	//
	while(1){
		cout << ">>" ;
		getline(cin,command);
		comms = StrSplit(command);


			// ACTION : set up data file
		if( compstr(comms[0], "newfile" )){
			if(comms.size() != 2){
				cout << "error input" << endl;
				continue;
			}
			infile.setFilename(comms[1]);
		}

			// ACTION : SHOW INFORMATION OF THE FORU C FILE
		else if( compstr(comms[0], "file" )){
			infile.printInfo();
		}

			// ACTION : SHOW INFORMATION OF SCAN
		else if( compstr(comms[0], "scan" ) || compstr(comms[0], "s" ) ){
			infile.printScanInfo(atoi(comms[1].c_str()));
		}

			// action ADD scan
		else if( compstr(comms[0], "add" )){
			int scan_no = atoi(comms[1].c_str());
			if( scan_no <= infile.scan_count  && scan_no > 0){
				infile.addScan(scan_no);
			}
		}

			// ACTION : list all scans in list
		else if( compstr(comms[0], "list" )){
		}

			// ACTION : quit program
		 else if( compstr(comms[0], "end" ) || compstr(comms[0], "quit" )){
			// stop programe
			cout << "quit, bye bye." << endl;
			break;
		}
			// ACTION : save scan data
		else if (compstr(comms[0], "save") || compstr(comms[0], "sa" )){
			int _sno = atoi(comms[1].c_str());
			string fileExten(".dat");
			string saveFileName = comms[1] + fileExten;
			infile.saveScanValueToFile(_sno,saveFileName);
		}
			// ACTION : help information
		else if (compstr(comms[0], "help") || compstr(comms[0], "?")){
			printFunctionMessage();
		}
			// ACTION : set attn of scan
			// ACTION : read attn ratio file


		else {
			cout << "unknown command" << endl;
		}
	}



	return 0;
}

void printFunctionMessage(){
	cout << "newfile [filename]:\t load fourc file by filename\n" << endl;;
	cout << "file:\t print the information of the fourc file\n" << endl;
	cout << "scan [scan number] or s [scan number]:\t show scan # information\n" << endl;;
	cout << "quit:\t quit the program\n" << endl;
	cout << "save [scan number] or sa [scan number]:\t save the scan values\n" << endl;
}

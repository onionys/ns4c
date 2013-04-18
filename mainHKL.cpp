#include"ONString.h"
#include<string>
#include<vector>
#include<iostream>

using namespace std;

int main(void){
	string filename ;
	string end = "end";
	string prefix = "no";
	vector<string> scanlist;
	cout << "input the file name: " ;
	getline(cin,filename);

	string sno;
	cout << "input the scan nombers(input end for stop): ";
	do{
		cin >> sno;
		scanlist.push_back(sno);
	}
	while( sno.compare(end) != 0 );
	showVString(scanlist);

	vector<string> * filelines = vecStrCopyFromFile(filename);
	
	for(int i = 0  ;i < scanlist.size() ;i++){

		if( 0 == end.compare(scanlist[i]) ) break;
		// ========================= //
		vector<string> scan;
		//scan = getScanDataFromFile(filename,scanlist[i]);
		scan = getScanDataFromFileLines(filelines, scanlist[i]);
		scan = getHKLScanFromFileLines(filelines, scanlist[i]);
		for(int j = 0 ;j < scan.size() ;j++ ){
			cout << scan[i] << endl;
		}
		// ========================= //
		if(scan.size() == 0) break;

		saveVStringToFile(scan, prefix+scanlist[i]);
	}

	return 0;
}

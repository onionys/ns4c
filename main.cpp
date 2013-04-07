#include"onString.h"
#include<string>
#include<vector>
#include<iostream>

using namespace std;

int main(void){
	string filename ;
	string end = "end";
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
	
	for(int i = 0  ;i < scanlist.size() ;i++){

		if( 0 == end.compare(scanlist[i]) ) break;


		string prefix = "no";
		//cout << prefix + scanlist[i] << endl;
		vector<string> scan = getScanDataFromFile(filename,scanlist[i]);
		if(scan.size() == 0) break;
		//for(int j = 0 ;j < scan.size() ;j++ ){
		//	cout << scan[i];
		//}
		saveVStringToFile(scan, prefix+scanlist[i]);
	}

	return 0;
}

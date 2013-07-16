#include"fourcfile.h"
#include"scan.h"

using std::cout;
using std::endl;

fourcfile::fourcfile(){
	rawdata = NULL;
	scan_count = -1;
}

fourcfile::fourcfile(string _filename){
	rawdata = NULL;
	filename = _filename;
	reflash();
}


fourcfile::~fourcfile(){
	if(rawdata != NULL) delete rawdata;
	for(int i = 0 ;i< scanlist.size() ;i++ ){
		delete scanlist[i];
	}
}

void fourcfile::setFilename(string & _filename){
	filename =  _filename;
	reflash();
}

int fourcfile::fetchRawdata(){
	fstream infile;

	if(filename.size() == 0) {
		cout << "no filename" << endl;
		return -1;
	}

	if(rawdata == NULL) rawdata = new VStr;

	if(rawdata->size() != 0) {
		delete rawdata;
		rawdata = new VStr;
	}

	infile.open(filename.c_str());

	if(!infile.is_open()){
		cout << "ERROR: can't open file:" << filename << endl;
		return -1;
	}
	rawdata = newVStrFromFile(infile);

	infile.close();
	return rawdata->size();
}

unsigned int fourcfile::allScanCount(){
	if(rawdata == NULL) return -1;
	unsigned int num = 0;
	unsigned int index = 0;
	while( index < rawdata->size() ){
		if(rawdata->at(index).c_str()[0] == '#' && 
		   rawdata->at(index).c_str()[1] == 'S' &&
		   rawdata->at(index).c_str()[2] == ' '){
			num++;
		}
		index++;
	}
	return num;
}

void fourcfile::reflash(){
	fetchRawdata();
	scan_count = allScanCount();
}

void fourcfile::printInfo(){
	cout << "FileName: " << ((rawdata == NULL) ? ("no filename") : ( filename )) << "\t";
	cout << "Scan Count: " <<  scan_count << "\t";
	cout << endl;
	cout << "scan list: " << endl;
	for(int i = 0 ;i < scanlist.size() ;i++ ){
		cout << scanlist[i]->getScanNo() << endl;
	}
}

void fourcfile::addScan(int scan_no){
	scan * sptr = new scan(rawdata, scan_no);
	scanlist.push_back(sptr);
}

void fourcfile::printScanInfo(int scan_no){
	if(scan_no <= 0 || scan_no > scan_count){
		cout << "scan no out of range\n";
	}
	else{
		scan tmpScan(rawdata, scan_no);
		tmpScan.printInfo();
		focue_scan = tmpScan;
	}
}


int fourcfile::saveScanValueToFile( int scan_no,string _filename){
	if(scan_no <= 0 || scan_no > scan_count){
		cout << "scan no out of range\n";
		return -1;
	}
	else{
		scan tmpScan(rawdata, scan_no);
		VStr values = tmpScan.getAllValue();
		saveVStrToFilename( values,_filename);
	}
	return 1;
}

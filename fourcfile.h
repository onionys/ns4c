#include<string>
#include<vector>
#include<iostream>
#include"scan.h"

#ifndef SCANFILE_H
#define SCANFILE_H

typedef vector<scan *> VScanPtr;

class fourcfile{
public:
	fourcfile();
	fourcfile(string _filename);
	~fourcfile();

	void reflash();
	void setFilename(string & _filename);
	int fetchRawdata(); // fail : return -1
			    //success: return line counts of the file

	unsigned int allScanCount();
	void printInfo();
	void printScanInfo(int scan_no);
	void addScan(int scan_no);
	int saveScanValueToFile(int scan_no,string _filename);

	//
	// Properties
	//
	VStr * rawdata;
	string filename;
	VScanPtr scanlist;
	int scan_count;
	scan focue_scan;
};
#endif

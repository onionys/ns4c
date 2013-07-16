/*
 * scan 為一個class
 * 用來記錄指定的fourc資料中指定的scan 的資料
 * fourc的資料用vector<string>的方式表達，一行一個string
 * */



#include"StrProc.h"

#ifndef SCAN_H
#define SCAN_H


typedef vector<double> VFloat;
typedef vector<VFloat> VVFloat;
typedef vector<int> VInt;

class scan{
public:
	scan();
	scan(VStr * _rawdata, int sno);
	~scan();

	void setScanNumber(int sno);

	// "set" functions
	void setRawdata(VStr * _rawdata);
	void setMotorPos();
	void setHKLPos();
	void setAttn(int _attn);
	void setColTitle();
	void setLatt();

	// "get" functions
	VFloat getHKLPos();
	VFloat getMotorPos();
	VVFloat getValues();
	VStr getLatt();
	int getScanNo();
	
	// searchXXX... 尋找，但是不會變動到class裡的資料
	int searchStartLineIndex();
	int searchEndLineIndex();
	int searchValueStartIndex();
	int searchValueEndIndex();
	VStr searchLatt();
	VStr searchColTitle();
	VStr getAllValue();
	VFloat searchMotorPos();
	VFloat searchHKLPos();

	///////////
	// example _para = "#G1"
	// _n = 1
	string searchStrByParameter(string _para, int _n);
	///////////


	void printInfo();
	void printAll();
	void printValue();
	void printLattInfo();
	void printPeakInfo();
	
	//VStr getValueByCols(VInt cols);


private:
	VStr * rawdata;
	VFloat motorPos;
	VFloat HKLPos;
	VStr colTitle;
	VStr latt;

	int scanNumber;  // indicate the scan number

	// start and end line for the scan number data
	int startLineIndex; 
	int endLineIndex;

	// start and end line for the value (scan point)
	int valueStartIndex;
	int valueEndIndex;

	// attn
	int attn;
};

#endif


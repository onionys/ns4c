#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<cstdlib>


using namespace std;


// 
// INTERFACE
//

vector<string> vectorFromSplitString(string theString, char dlim);
vector<string> vectorFromSplitString(string theString);

// you need to free the returned data if no more use.
vector<string> * vecStrCopyFromFile(string filename);

long lineOfScanNO(vector<string>* allLine, long scanno);

vector<string> getScanDataFromFile(string filename, string sno);

vector<string> getScanDataFromFileLines(vector<string> * filelines, string sno);
vector<string> getHKLScanFromFileLines(vector<string> * filelines, string sno);

void saveVStringToFile(vector<string>,string filename);

void showAllFile(string filename);

void showVString(vector<string> strlist);
void showVString(vector<string> *strlist);


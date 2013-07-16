
/*
 * StrProc.h 中定義了一些常用的字串處理程式
 * 
 * */



#include<string>
#include<vector>
#include<sstream>
#include<fstream>
#include<iostream>

#ifndef STRPROC_H
#define STRPROC_H

using std::string;
using std::vector;
using std::istringstream;
using std::fstream;
using std::ofstream;
using std::getline;

typedef vector<string> VStr;

VStr StrSplit(string theString, char dlim);
VStr StrSplit(string theString);
VStr * newVStrFromFile(fstream &infile);
VStr * newVStrFromFilename(string filename);
VStr StrSplitBy2Space(string str);
int saveVStrToFilename(VStr _strs, string _savefile );

#endif

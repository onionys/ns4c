#include"StrProc.h"


VStr StrSplit(string theString, char dlim){
	istringstream iss(theString);
	VStr result;
	string tmp;
	while(!iss.eof() ){
		getline(iss , tmp, dlim );
		result.push_back(tmp);
	}
	return result;
}

VStr StrSplit(string theString){
	istringstream iss(theString);
	VStr result;
	string tmp;
	while(!iss.eof() ){
		//getline(iss , tmp);
		iss >> tmp;
		result.push_back(tmp);
	}
	return result;
}

VStr * newVStrFromFile(fstream &infile){
	VStr *allLine = new VStr;

	while(! infile.eof() ){
		string tmp;
		getline(infile,tmp,'\n');
		allLine->push_back(tmp);
	}
//	infile.close();
	return allLine;
}

VStr * newVStrFromFilename(string filename){
	fstream infile;
	infile.open(filename.c_str());
	if(infile.is_open() != true) return NULL;
	VStr* tmp = newVStrFromFile(infile);
	infile.close();
	return tmp;
}

// split string by dlim == '  ' (two space)
VStr StrSplitBy2Space(string str){
	string ttmp= str;
	VStr res;
	string ts("\n\n");
	for(int i = 0 ;i < ttmp.size()-1;i++ ){
		if (ttmp.c_str()[i] == ' ' && ttmp.c_str()[i+1] == ' ')
			ttmp.replace(i,2,ts);
	}
	istringstream iss(ttmp);
	while(!iss.eof() ){
		string tmp;
		getline(iss,tmp );
		if(tmp.size() == 0) continue;
		res.push_back(tmp);
	}
	return res;
}

int saveVStrToFilename(VStr _strs, string _savefile){
	ofstream outfile;
	outfile.open(_savefile.c_str());
	if(outfile.is_open() != true  ){
		printf("open file %s error",_savefile.c_str());
		return -1;
	}

	for(int i = 0 ;i < _strs.size() ;i++ ){
		outfile << _strs[i] << "\n";
	}

	outfile.close();
	return 1;
}

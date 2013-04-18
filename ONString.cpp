#include"ONString.h"

#define XX 0
#define DET 11
#define SEC 10

using namespace std;

//
// IMPLEMENT
//

vector<string> vectorFromSplitString(string theString, char dlim){
	char buffer[1024];
	vector<string> elements;

	istringstream iss(theString);

	while(!iss.eof()){
		iss.getline(buffer, 1024, dlim);
		string temp(buffer);
		elements.push_back(temp);
	}
	
	return elements;
}

vector<string> vectorFromSplitString(string theString){
	return vectorFromSplitString(theString, ' ');
}

void showAllFile(string filename){
	fstream infile;
	string temp;
	infile.open(filename.c_str());

	while(! infile.eof()){
		getline(infile,temp);
		cout << temp << endl;
	}

	infile.close();
}

long lineOfScanNO(vector<string>* allLine, long scanno){
	long theLine = 0;
	for(long i = 0 ;i < allLine->size() ;i++ ){
		string temp = allLine->at(i);
		if( temp.size() > 2 && temp[0] == '#' && temp[1] == 'S'){
			vector<string> elements = vectorFromSplitString(temp,' ');
			long intno = atoi(elements[1].c_str());
			if(intno == scanno ) return i;
		}
	}
	return 0;
}


vector<string> getScanDataFromFile(string filename, string sno){
	fstream infile;
	string strline;
	vector<string> llist;
	vector<string> line;
	string headd = "#S";
	
	// open file stream using the filename 
	infile.open(filename.c_str());

	// jump to sno scan number
	while(!infile.eof()){
		getline(infile, strline);
		line = vectorFromSplitString(strline,' ');
		if( line.size() == 1) continue; // skip the empty line

		// Find the Scan no "#S NN"
		if((! headd.compare(line[0])) && (!sno.compare(line[1]))){
			break;
		}

		//if(infile.eof()){
		//	cout << "Prog end\n";
		//	return llist;
		//}
	};

	// scan data of scan number in "sno"
	while(1){
		getline(infile,strline);
		line = vectorFromSplitString(strline, ' ');
		// and stop at empty line
		if( line.size() <= 1) break; // stop at the empty line
		
		string ttt = line[0];
		// if the first char is not "#" then convert the line into string 
		// and save into line (vector<string>)
		if( ttt[0] != '#' ){
			string x_ , det , sec;
			x_ = line[XX];
			det = line[DET];
			sec = line[SEC];
			double y_ =  atof(det.c_str())/atof(sec.c_str());
			char buffer[1024];
			sprintf(buffer,"%s\t%f\n", x_.c_str(), y_);
			strline = buffer;
			llist.push_back(strline);
		}
	}
	infile.close();
	return llist;
}

void saveVStringToFile(vector<string> llist, string filename){
	ofstream outfile;

	cout << filename.c_str() << endl;
	outfile.open(filename.c_str());
	for(int i = 0; i < llist.size(); i++){
		outfile << llist[i];
	}
	outfile.close();
}


void showVString(vector<string> strlist){
	for(int i = 0;i<strlist.size();i++){
		cout << strlist[i] << endl;	
	}
}

void showVString(vector<string> *strlist){
	for(int i = 0 ; i < strlist->size() ;i++ ){
		cout << strlist->at(i) << endl;
	}
}



vector<string> * vecStrCopyFromFile(string filename){
	fstream infile;
	vector<string> *allLine = new vector<string>;

	char buff[1024];

	infile.open(filename.c_str());
	while(! infile.eof() ){
		infile.getline(buff,1024);
		string temp(buff);
		allLine->push_back(temp);
	}
	infile.close();
	return allLine;
}



vector<string> getScanDataFromFileLines(
		vector<string> * filelines,
		string sno){

	long lineno = lineOfScanNO(filelines, (long)atoi(sno.c_str()));
	//cout << lineno << endl;
	//cout << filelines->at(lineno) << endl;

	vector<string> data;
	while( filelines->at(lineno).size() > 2 ){
		cout << filelines->at(lineno) << endl;
		vector<string> strs = vectorFromSplitString(filelines->at(lineno++),' ');
		if( '#' != *strs[0].c_str() ){
			char val[1024];
			double det = (double)atof(strs[strs.size()-1].c_str());
			double sec = (double)atof(strs[strs.size()-2].c_str());
			cout << det << " " << sec << endl;
			sprintf(val,"%e",det/sec);
			string valstr(val);
			string space("\t");
			string lineend("\n");
			data.push_back(strs[XX] + space + valstr + lineend);
		}
	}
	return data;
}


vector<string> getHKLScanFromFileLines(vector<string> * filelines, string sno){

	long lineno = lineOfScanNO(filelines, (long)atoi(sno.c_str()));
	//cout << lineno << endl;
	//cout << filelines->at(lineno) << endl;

	vector<string> data;
	while( filelines->at(lineno).size() > 2 ){
		cout << filelines->at(lineno) << endl;
		vector<string> strs = vectorFromSplitString(filelines->at(lineno++),' ');
		if( '#' != *strs[0].c_str() ){
			char val[1024];
			double det = (double)atof(strs[strs.size()-1].c_str());
			double sec = (double)atof(strs[strs.size()-2].c_str());
			cout << det << " " << sec << endl;
			sprintf(val,"%e",det/sec);
			string valstr(val);
			string space("\t");
			string lineend("\n");
			data.push_back(strs[0] + space +
					strs[1] + space +
					strs[2] + space +
					valstr + lineend);
		}
	}
	return data;
}

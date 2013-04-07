#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<cstdlib>

#define XX 0
#define DET 11
#define SEC 10

using namespace std;


// 
// interface
//
vector<string> vectorFromSplitString(string theString);
vector<string> getScanDataFromFile(string filename, string sno);
void saveVStringToFile(vector<string>,string filename);
void showAllFile();
void showVString(vector<string> strlist);


//
// implement
//
vector<string> vectorFromSplitString(string theString){
	vector<string> llist;
	istringstream iss(theString);

	do{
		string sub;
		iss >> sub;
		llist.push_back(sub);
	}
	while(iss);
	
	return llist;
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
		line = vectorFromSplitString(strline);
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
		line = vectorFromSplitString(strline);
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

#include"StrProc.h"
using namespace std;

int main(int argc, char *argv[]){
	string filename(argv[1]);
	VStr lines;
	string tmp1("abcde");
	string tmp2("abcde1");
	string tmp3("abcde3");
	lines.push_back(tmp1);
	lines.push_back(tmp2);
	lines.push_back(tmp3);
	saveVStrAsFilename(filename,lines);
	return 0;
}

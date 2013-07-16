#include"scan.h"
#include<stdio.h>
#include<stdlib.h>
using std::cout ;
using std::endl;

scan::scan(){
	startLineIndex = -1;
	endLineIndex = -1;
	valueStartIndex = -1;
	valueEndIndex = -1;
	attn = -1;
}

scan::scan(VStr * _rawdata, int sno){
	startLineIndex = -1;
	endLineIndex = -1;
	valueStartIndex = -1;
	valueEndIndex = -1;
	attn = -1;
	rawdata = _rawdata;
	setScanNumber(sno);
}

scan::~scan(){
}

void scan::setRawdata(VStr * _rawdata){
	rawdata = _rawdata;
}


void scan::setScanNumber(int sno){
	scanNumber = sno;
	startLineIndex = searchStartLineIndex();
	endLineIndex = searchEndLineIndex();
	valueStartIndex = searchValueStartIndex();
	valueEndIndex = searchValueEndIndex();
	if(startLineIndex != -1){
		setMotorPos();
		setHKLPos();
		setColTitle();
		setLatt();
	}
}




int scan::searchStartLineIndex(){

	for(int i = 0 ; i < rawdata->size() ;i++ ){
		const char * tmp_line = rawdata->at(i).c_str();
		if(tmp_line[0] == '#' && tmp_line[1] == 'S'){
			VStr _list = StrSplit(rawdata->at(i));
			int _num = atoi( _list[1].c_str() );
			if( _num == scanNumber) return i;
		}
	}

	// 找不到，回傳-1值
	return -1;
}

int scan::searchEndLineIndex(){
	int i = searchStartLineIndex() + 1;
	if(i == -1) return -1; // 如果找不到start line 則也沒有end line -> 回傳-1
	while(i < rawdata->size() ){
		const char *tmp = rawdata->at(i).c_str();
		if(tmp[0] == '#' && tmp[1] == 'S' && tmp[2] == ' ')
			return i-1;
		i++;
	}
	return i-1;
}

int scan::searchValueStartIndex(){
	if(startLineIndex == -1 || endLineIndex == -1) return -1;
	int i = startLineIndex;
	while(i < endLineIndex){
		const char *tmp = rawdata->at(i).c_str();
		if(tmp[0] == '#' && tmp[1] == 'L') return i+1;
		i++;
	}
}

int scan::searchValueEndIndex(){
	int i = searchValueStartIndex();
	if(i == 0) return 0;
	while(i < endLineIndex){
		if(rawdata->at(i).size() < 2)
			return i-1;
		i++;
	}
}


void scan::printInfo(){
	printf("\n========================================\n");
	printf("%s\n",rawdata->at(startLineIndex).c_str());
//	printf("scan number: %i\n",scanNumber);
//	printf("start line index: %i\n",startLineIndex);
//	printf("end line index: %i\n",endLineIndex);
//	printf("value start index: %i\n",valueStartIndex);
//	printf("value end index: %i\n",valueEndIndex);
	printf("tth:%f\tth:%f\tchi:%f\tphi:%f\n",motorPos[0],motorPos[1],motorPos[2],motorPos[3] );
	printf("H:%f\tK:%f\tL:%f\n",HKLPos[0],HKLPos[1],HKLPos[2] );
	printLattInfo();
	printf("----------------------------------------\n");
	printf("%s\n",rawdata->at(valueStartIndex-1).c_str());
	printPeakInfo();
	printf("========================================\n");
}

void scan::printAll(){
	int i = startLineIndex;
	if(i == -1) {
		printf("No Data\n");
	}
	else{
		while(i <= endLineIndex ){
			printf("%s\n", rawdata->at(i).c_str());
			i++;
		}
	}
}

void scan::printValue(){
	int i = valueStartIndex;
	if(i == -1) {
		printf("No Data\n");
	}else{

		for(int j = 0 ;j < colTitle.size() ;j++ ){
			cout << colTitle[j] << "\t";
		}
		cout << endl;

		while(i <= valueEndIndex){
			printf("%s\n", rawdata->at(i).c_str());
			i++;
		}
	}
}

VFloat scan::searchMotorPos(){
	VFloat motorpos;
	if(startLineIndex == -1) return motorpos;
//	for(int i = startLineIndex ; i <= endLineIndex ; i++ ){
//		if(rawdata->at(i).c_str()[0] == '#' && 
//		   rawdata->at(i).c_str()[1] == 'P' &&
//		   rawdata->at(i).c_str()[2] == '0' ){
//			VStr P0Line = StrSplit(rawdata->at(i));
//			motorpos.push_back( atof(P0Line[1].c_str()));
//			motorpos.push_back( atof(P0Line[2].c_str()));
//			motorpos.push_back( atof(P0Line[3].c_str()));
//			motorpos.push_back( atof(P0Line[4].c_str()));
//			return motorpos;
//		}
//	}
	// Motor poisiton tth th chi phi at #P0 1,2,3,4
	string para("#P0");
	motorpos.push_back( atof(searchStrByParameter(para,1).c_str()));
	motorpos.push_back( atof(searchStrByParameter(para,2).c_str()));
	motorpos.push_back( atof(searchStrByParameter(para,3).c_str()));
	motorpos.push_back( atof(searchStrByParameter(para,4).c_str()));
	return motorpos;
}


VFloat scan::searchHKLPos(){
	VFloat hkl;
	if(startLineIndex == -1) return hkl;
//	for(int i = startLineIndex; i<= endLineIndex ;i++ ){
//		if(rawdata->at(i).c_str()[0] == '#' && 
//		   rawdata->at(i).c_str()[1] == 'Q'){
//			VStr QLine = StrSplit(rawdata->at(i));
//			hkl.push_back( atof(QLine[1].c_str()));
//			hkl.push_back( atof(QLine[2].c_str()));
//			hkl.push_back( atof(QLine[3].c_str()));
//			return hkl;
//		}
//		
//	}
	string para("#Q");
	hkl.push_back(atof(searchStrByParameter(para,1).c_str()));
	hkl.push_back(atof(searchStrByParameter(para,2).c_str()));
	hkl.push_back(atof(searchStrByParameter(para,3).c_str()));
	return hkl;
}


void scan::setMotorPos(){
	motorPos = searchMotorPos();
}

void scan::setHKLPos(){
	HKLPos = searchHKLPos();
}

void scan::setAttn(int _attn){
	attn = _attn;
}

int scan::getScanNo(){
	return scanNumber;
}

VFloat scan::getHKLPos(){
	if(HKLPos.size() == 0){
		setHKLPos();
	}
	return HKLPos;
}

VFloat scan::getMotorPos(){
	if(motorPos.size() == 0){
		setMotorPos();
	}
	return motorPos;
}

VStr scan::searchColTitle(){
	VStr colT;
	if(valueStartIndex == -1) return colT;
	VStr tmp = StrSplitBy2Space(rawdata->at(valueStartIndex -1));
	colT.push_back(tmp[0].substr(3,tmp.size()-3));
	for(int i =1 ;i<tmp.size() ;i++ ){
		colT.push_back(tmp[i]);
	}
	return colT;
}

void scan::setColTitle(){
	colTitle = searchColTitle();
}


void scan::printPeakInfo(){
	int i = startLineIndex;
	if(i < 0) cout << "no peak info" << endl;

	for(i = endLineIndex ;i > startLineIndex ; i-- ){
		if(rawdata->at(i).c_str()[1] == 'P' && 
		   rawdata->at(i).c_str()[2] == 'e' && 
		   rawdata->at(i).c_str()[3] == 'a' && 
		   rawdata->at(i).c_str()[4] == 'k'){
			cout << rawdata->at(i) << endl;
			break;
		}
	}

}


//VStr scan::getValueByCols(VInt cols){
//
//	VStr res;
//	VStr line = StrSplit(rawdata->at(valueStartIndex));
//	int len = line.size();
//	for(int i = 0 ;i < cols.size() ;i++ ){
//		int index = (cols[i]<0) ? (len+col[i]):(col[i]);
//		if(index >= res.size()) return res;
//
//	}
//	return res;
//}
//
//

VStr scan::searchLatt(){
	VStr tmp_latt;
	// check scan
	if(-1 == startLineIndex )
		return tmp_latt; 
	
	// find line of #G1
	// get a,b,c,alpha,beta,gama
//	for(int i = startLineIndex ; i <= endLineIndex ;i++ ){
//		if(rawdata->at(i).compare(0,4,"#G1 ") == 0){
//			VStr tmp = StrSplit(rawdata->at(i));
//			for(int j = 1 ; j <= 6 ;j++ )
//				tmp_latt.push_back(tmp[j]);
//			return tmp_latt;
//		}
//	}
	string para("#G1");
	tmp_latt.push_back(searchStrByParameter(para,1));
	tmp_latt.push_back(searchStrByParameter(para,2));
	tmp_latt.push_back(searchStrByParameter(para,3));
	tmp_latt.push_back(searchStrByParameter(para,4));
	tmp_latt.push_back(searchStrByParameter(para,5));
	tmp_latt.push_back(searchStrByParameter(para,6));
	return tmp_latt;
}

void scan::setLatt(){
	latt = searchLatt();
}

void scan::printLattInfo(){
	printf("a:%s b:%s c:%s\t", latt[0].c_str(),latt[1].c_str(),latt[2].c_str() );
	printf("alpha:%s beta:%s gama:%s\n", latt[3].c_str(),latt[4].c_str(),latt[5].c_str() );
}

VVFloat scan::getValues(){
	VVFloat res;
	for(int i = valueStartIndex ; i <= valueEndIndex ; i++ ){
		VStr line = StrSplit(rawdata->at(i));
		VFloat _values;
		for(int j = 0 ;j < line.size() ;j++ ) _values.push_back( atof(line[j].c_str()));
		res.push_back(_values);
	}

	return res;
}


string scan::searchStrByParameter(string _para, int _n){
	string err("Error");
	if(startLineIndex == -1 ){
		return err;
	}

	for(int i = startLineIndex ;i <= endLineIndex ; i++ ){
		VStr line = StrSplit(rawdata->at(i));
		if(line[0].compare(_para) == 0){
			if(_n < line.size()){return line[_n];}
			else{ return err;}
		}
	}
	return err;
}

VStr scan::getLatt(){
	if(latt.size() == 0) setLatt();
	return latt;
}

VStr scan::getAllValue(){
	VStr res;
	if(valueStartIndex == -1 ) return res;

	for(int i = valueStartIndex-1 ;i <= valueEndIndex ; i++ ){
		res.push_back(rawdata->at(i));
	}
	return res;
}

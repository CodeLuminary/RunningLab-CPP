#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <sstream> 

using namespace std;

int tim[3];
string * stud = new string[3];
void initializeVariable(){
	for(int i = 0; i < 3; i++){
		tim[i] = 0;
		stud[i] = "";
	}
}
//This function is meant to take in a string and split it using space than return the number of text after split
int txLength(string tx){
		string ch;int cnt = 0;
	for(int i = 0; i < tx.length(); i++){//Loop through the text
		ch = tx.substr(i,1); //Look for space in text
		if(strcmp(ch.c_str()," ")==0){//Check if character is space
			cnt++; //Increment counter variable
		}
	}
	return cnt + 1;//Return number of text
}
//This function is meant to take in a string and split it using tab('#t') than return the number of text after split
int txLength2(string tx){
		string ch;int cnt = 0;
	for(int i = 0; i < tx.length(); i++){//Loop through the text
		ch = tx.substr(i,1);//Look for #t in text
		if(strcmp(ch.c_str(),":")==0){//Check if character is \t
			cnt++;//Increment counter variable
		}
	}
	return cnt + 1;//Return number of text
}

string * splitString(string tx){
	string ch;int cnt = 0;
	
	//return cnt;
	int len = txLength(tx);//Get length of text
	string * newStr = new string[len]; //Create new string array
	int cnt2 = 0; int start = 0; int sz;
	for(int i = 0; i < tx.length(); i++){ //Loop through string content
		ch = tx.substr(i,1); //Extract each character
		if(strcmp(ch.c_str()," ")==0){//Check if extracted character is space
			newStr[cnt2++] = tx.substr(start,i-(start));//Store in string array
			start = i + 1; //Reset substring start position
			if(cnt2 == (len-1)){//Check if it's the last index
				newStr[cnt2] = tx.substr(start,(len-start)); //Store the last content in string array
			}
		}
	}
	return newStr;
}
//This function takes in a string and split them using \t and return an array
string * splitString2(string tx){
	string ch;int cnt = 0;
	
	//return cnt;
	int len = txLength2(tx);//Get length of text
	string * newStr = new string[len]; //Create new string array
	int cnt2 = 0; int start = 0; int sz;
	for(int i = 0; i < tx.length(); i++){ //Loop through string content
		ch = tx.substr(i,1);//Extract each character
		if(strcmp(ch.c_str(),":")==0){//Check if extracted character is :
			newStr[cnt2++] = tx.substr(start,i-(start));//Store in string array
			start = i + 1;//Reset substring start position
			if(cnt2 == (len-1)){//Check if it's the last index
				newStr[cnt2] = tx.substr(start,(len-start));//Store the last content in string array
			}
		}
	}
	return newStr;
}
//This function takes in a string and convert it to all lower case
string toLower(string tx){
	transform(tx.begin(),tx.end(),tx.begin(), ::tolower);
	return tx;
}
//This function convert int, double values to string
string toString(double x){ 
  ostringstream ss;
  ss << x;
  string ab = ss.str();
  return ab;
}
//This function takes in time in form of string and convert to integer
int getTimeInSeconds(string tim){
	int sec = (atoi(splitString2(tim)[0].c_str()))*60 + (atoi(splitString2(tim)[1].c_str()));
	return sec;
}
//This function gets the total number of students in a file
int totalStudent(string fileName){
	string line;
	int pos = 0; //Counter variable
	int studentCount =0; //This variable holds the numbers of student
	bool isFound =false; //This variable holds if the beginning is found
	ifstream myfile(fileName.c_str());
	if(myfile.is_open()){
		while(getline(myfile,line)){		
			if(strcmp(toLower(splitString(line)[0]).c_str(),toLower("Lap").c_str())==0){ //Check if the line contain the word lap
				isFound = true; //Set isFound to true
			}
			else{
				if(isFound){
					if(splitString(line)[0].length() ==0){//Check if the line contain only space
						break;
					}
				   pos++;
				}
			}			
			
		}
		myfile.close();//Close file
	}
	else{
		cout << "Unable to open file";
	}
	return pos;
}
//This function analysis each student performance and the top result in an array
void analyseStudentPerformance(string studName, int totalTime){
	for(int i = 0; i < 3; i++){ //Loop through array
		if(totalTime < tim[i] && tim[i] != 0){ //Check if the inserted totaltime is less than what was stored in the array index
			for(int j = 1; j >= i; j--){//Loop through the remainder of the array and push content downward
				tim[j+1] = tim[j];
				stud[j+1] = stud[j];
			}
			tim[i] = totalTime;//Store totalTime
			stud[i] = studName;//Store student name
			break;
		}
		else if(tim[i]==0){ //Check if the current array index is zero
			tim[i] = totalTime; //Store totalTime
			stud[i] = studName;//Store student name
			break;
		}
	}
}
//This function prints out the student performance
void printPerformance(){
	cout << "STUDENT NAME   " << "TOTAL TIME   " << "POSITION" << '\n';
	for(int i =0; i< 3; i++){
		cout << stud[i];
		for(int j = stud[i].length(); j < 15; j++){
			cout << " ";
		}
		cout << tim[i];
		for(int j = toString(tim[i]).length(); j < 13; j++){
			cout << " ";
		}
		cout << (i + 1) << '\n';
	}
}
//This function gets top 3 student
void getTopThree(string fileName){
	 initializeVariable();//Initalize array variables
	int totalStud = totalStudent(fileName); //Get total students
	for(int i = 0; i < totalStud; i++){//Loop through the students
		string line;
		int pos = 0;//Counter variable
		bool isFound =false;  //This variable holds if the word 'lap' is found
		int lapCnt = 0; //This variable counts the numbers of laps
		string studentName;//This holds the student name
		int studentLap = 0; //This variable holds the total student lap
		ifstream myfile(fileName.c_str());
		if(myfile.is_open()){//Check if file is open
			while(getline(myfile,line)){//While there is content
				if(strcmp(toLower(splitString(line)[0]).c_str(),toLower("Lap").c_str())==0){//Check if the line contain the word 'lap'
					isFound = true;//Set is found to true
					lapCnt++;
					pos = 0;
				}
				else{
					if(isFound){
						if(lapCnt == 1){
							if(pos == i){
								studentName = splitString(line)[0]; //Get student name
								studentLap += getTimeInSeconds(splitString(line)[1]+":"); //Get student time and add to studentlap
							}							
						}else{
							if(strcmp(toLower(studentName).c_str(),toLower(splitString(line)[0]).c_str())==0){//Check if the current student is same as the content of studentName
								studentLap += getTimeInSeconds(splitString(line)[1]+":"); //Add studentLap
							}	
						}
						if(splitString(line)[0].length() ==0){// Check if the line contain only space
					   		isFound = false;
						}
						pos++;
					}
				
				}		
					
			}
			myfile.close();
		}
		else{
			cout << "Unable to open file";
		}	
		//cout << studentName << "--" << studentLap << '\n' << '\n';
		analyseStudentPerformance(studentName, studentLap); //Analyse and compare student performance
	}
		
		printPerformance(); //Print result
}
//Beginning of object 2
int lapAvr[3] = {0,0,0};
//This function get the average of each lap
void getLapAverage(string filename1){
	string line;int pos = 0;
	bool isFound =false;//This variable holds if the word 'lap' is found
	int lapCnt = 0;//This variable counts the numbers of laps
	ifstream myfile(filename1.c_str());
	if(myfile.is_open()){//Check if file is open
		while(getline(myfile,line)){//While there is content
			if(strcmp(toLower(splitString(line)[0]).c_str(),toLower("Lap").c_str())==0){//Check if the line contain the word 'lap'
				isFound = true;
				lapCnt++;
				pos = 0;
			}
			else{
				if(isFound){
					if(splitString(line)[0].length() ==0){// Check if the line contain only space
				   		isFound = false;
					}
					else{
						lapAvr[lapCnt-1] += getTimeInSeconds(splitString(line)[1]+":");//Add all time and save in an array
					}
					pos++;
				}
			}
		}
		myfile.close();
	}
	else{
		cout << "Unable to open file";
	}
}
//This function prints out the student above and below a lap average
void lapStudentAverage(string filename1){
	cout << '\n' << '\n';
	int totalStud = totalStudent(filename1);//Get the total students
	getLapAverage(filename1); //Get the average of each lap
	string line;int pos = 0;
	bool isFound =false;//This variable counts the numbers of laps
	int lapCnt = 0;//This variable holds if the word 'lap' is found
	string above = "Above: ";string below = "Below: ";
	ifstream myfile(filename1.c_str());
	if(myfile.is_open()){//Check if file is open
		while(getline(myfile,line)){//While there is content
			if(strcmp(toLower(splitString(line)[0]).c_str(),toLower("Lap").c_str())==0){
				isFound = true;
				lapCnt++;
				pos = 0;
				int min = (lapAvr[lapCnt-1]/totalStud)/60; //Get min from the total time in sec
				int sec = (lapAvr[lapCnt-1]/totalStud)%60; //Get sec from the total time in sec
				string sec1;
				if(sec <10){//Check if sec is less than 10 and contantenate it with '0'
					sec1 = "0" + toString(sec);
				}
				else{
					sec1 = toString(sec);
				}
				below = "Below: "; above = "Above: ";
				cout << "Lap " << lapCnt << " average: " << min << ":" << sec1 << '\n';
			}
			else{
				if(isFound){
					pos++;
					if(splitString(line)[0].length() ==0){// Check if the line contain only space and print student below and above
				   		isFound = false;
				   			cout << below.substr(0, below.length()-2) << '\n';
							cout << above.substr(0, above.length()-2) << '\n' << '\n';						
					}
					else{
						 if(getTimeInSeconds(splitString(line)[1]+":") <= (lapAvr[lapCnt-1]/totalStud)){//Check if the student time is below average
						 	above +=  splitString(line)[0] + ", ";
						 }
						 else{
						 	below += splitString(line)[0] + ", ";
						 }
						 if(lapCnt==3 && (pos==totalStud)){//Check if it's the last line and print students below and above
						 	cout << below.substr(0, below.length()-2) << '\n';
							cout << above.substr(0, above.length()-2) << '\n' << '\n';
						 }
					}
					
				}
			}
		}
		myfile.close();
	}
	else{
		cout << "Unable to open file";
	}
}
//End of objective 2

//Beginning of objective 3
int studLap[3] = {0,0,0};
void getTimeDifference(string fileName){
	cout << '\n' << '\n';
	int totalStud = totalStudent(fileName); //Get the total student
	cout << "Lap      1        2        3" << '\n';
	
	for(int i = 0; i < totalStud; i++){//Loop through the students
		string line;int pos = 0;
		bool isFound =false;//This variable counts the numbers of laps
		int lapCnt = 0;//This variable holds if the word 'lap' is found
		string studentName;//The variable holds the student name
		int studentLap = 0;//The variable holds the student lap
		for(int u = 0; u < 3; u++){ //Loop through variable studLap and reinitialise it to zero
			studLap[u] = 0;
		}
		ifstream myfile(fileName.c_str());
		if(myfile.is_open()){//Check if file is open
			while(getline(myfile,line)){//while there is still content
				if(strcmp(toLower(splitString(line)[0]).c_str(),toLower("Lap").c_str())==0){//Check if the line contain the word 'lap'
					isFound = true;
					lapCnt++;
					pos = 0;
				}
				else{
					if(isFound){//Check if the word lap have been found
						if(lapCnt == 1){//Check if the lap is the first one
							if(pos == i){//check if the current position to the current index
								studentName = splitString(line)[0];//Get student name
								cout << splitString(line)[0];//Print student name
								for(int v = splitString(line)[0].length(); v < 9; v++){//Add the corresponding space
									cout << " ";
								}
								studLap[lapCnt-1]= getTimeInSeconds(splitString(line)[1]+":");//Get time in seconds equivalent
								cout << splitString(line)[1];//print time
								for(int v = splitString(line)[1].length(); v < 9; v++){//Add the corresponding space
									cout << " ";
								}
							}							
						}else{
							if(strcmp(toLower(studentName).c_str(),toLower(splitString(line)[0]).c_str())==0){//Get if the student name is same as the current student name
								studLap[lapCnt-1]= getTimeInSeconds(splitString(line)[1]+":");
								cout << splitString(line)[1];
								for(int v = splitString(line)[1].length(); v < 9; v++){//Add the corresponding space
									cout << " ";
								}
							}	
						}
						if(splitString(line)[0].length() ==0){//Check if the line contains only space
					   		isFound = false;
						}
						pos++;
					}			
				}						
			}
			myfile.close();
		}
		else{
			cout << "Unable to open file";
		}
		cout <<'\n' << "              ";
		cout << (studLap[1]-studLap[0]) << "       " << (studLap[2]-studLap[1]) << '\n';
	}
}
//End of objective 3

//Beginning of objective 4
//This function takes time in second and return the string equivalent of the seconds integer
string convertIntToTime(int tim){
	string value = "";
	int min = tim/60;//get minutes
	int sec = tim%60;//Get seconds
	value += toString(min) + ":";
	if(sec < 10){//Check if the sec is less than 10 and concantenate with '0'
		value += "0" + toString(sec);
	}
	else {
		value += toString(sec);
	}
	return value;
}
int newAr[3] = {0,0,0};
//This function print the consistent student
void printConsistentStudent(string studentName){
	int newAr[3] = {0,0,0};
	for(int i = 0; i < 3; i++){//Loop through the studLap array variable
		if(newAr[1] != 0 && newAr[1] > studLap[i]){//check if the current studentlap is greater than index 1 of newAr
			newAr[1] = studLap[i];
		}
		else if(newAr[1]==0){//Check if the index1 of newAr is zero
			newAr[1] = studLap[i];
		}
		if(newAr[0] != 0 && newAr[0] < studLap[i]){//check if the current studentlap is less than index 0 of newAr
			newAr[0] = studLap[i];
		}
		else if(newAr[0]==0){
			newAr[0] = studLap[i];
		}
	}
		//Print Result
		cout <<  convertIntToTime(newAr[0]);//print slowest time
		for(int j = (convertIntToTime(newAr[0]).length()); j < 9; j++){//Loop and add the corresponding space
			cout << " ";
		}
		cout <<  convertIntToTime(newAr[1]);//print fastest ime
		for(int j = (convertIntToTime(newAr[1]).length()); j < 9; j++){ //Loop and add the corresponding space
			cout << " ";
		} 
		cout << (newAr[0]-newAr[1]) << " sec" << '\n';
		analyseStudentPerformance(studentName, (newAr[0]-newAr[1]));//Analyse student performance
}
//This function print the most consistent students
void printMostConsistentStudents(){
	cout << '\n' << '\n';
	cout << "MOST CONSISTENT STUDENTS" << '\n';
	for(int i =0; i<3; i++){
		cout << stud[i] << "     " << tim[i] << " sec" << '\n';
	}
}
//This function get consistent student
void getConsistentStudent(string fileName){
	 initializeVariable();//Initialize variable
	cout << '\n' << '\n';
	int totalStud = totalStudent(fileName);//Get total student
	cout << "         Slowest  Fastest  difference" << '\n';
	
	for(int i = 0; i < totalStud; i++){//Loop through all the students
		string line;int pos = 0;
		bool isFound =false;
		int lapCnt = 0;
		string studentName;
		int studentLap = 0;
		for(int u = 0; u < 3; u++){
			studLap[u] = 0;
		}
		ifstream myfile(fileName.c_str());
		if(myfile.is_open()){
			while(getline(myfile,line)){
				if(strcmp(toLower(splitString(line)[0]).c_str(),toLower("Lap").c_str())==0){
					isFound = true;
					lapCnt++;
					pos = 0;
				}
				else{
					if(isFound){
						if(lapCnt == 1){
							if(pos == i){
								studentName = splitString(line)[0];
								cout << splitString(line)[0];							
								studLap[lapCnt-1]= getTimeInSeconds(splitString(line)[1]+":");	
								for(int v = splitString(line)[0].length(); v < 9; v++){
									cout << " ";
								}		
							}							
						}else{
							if(strcmp(toLower(studentName).c_str(),toLower(splitString(line)[0]).c_str())==0){
								studLap[lapCnt-1]= getTimeInSeconds(splitString(line)[1]+":");
							
							}	
						}
						if(splitString(line)[0].length() ==0){
					   		isFound = false;
						}
						pos++;
					}
				
				}		
					
			}
			myfile.close();
		}
		else{
			cout << "Unable to open file";
		}
		printConsistentStudent(studentName);
		//cout << newAr[0]-newAr[1] <<"/-/" << '\n';
	
	}
	 printMostConsistentStudents();
}
//End of objective 4

//Beginning of Objective 5
void getStudentRaceComparison(string fileName,string fileName2){
	cout << "\n" << '\n';
	 initializeVariable();
	int totalStud = totalStudent(fileName);
	cout << "            1         2       difference" << '\n';
	for(int i = 0; i < totalStud; i++){
		string line;
		int pos = 0;//Create and initialize counter 
		bool isFound =false;//This variable counts the numbers of laps
		int lapCnt = 0;//This variable holds if the word 'lap' is found
		string studentName;//The variable holds the student name
		int studentLap = 0;//The variable holds the student lap
		ifstream myfile(fileName.c_str());
		if(myfile.is_open()){//Check if file is open
			while(getline(myfile,line)){//while there is still content
				if(strcmp(toLower(splitString(line)[0]).c_str(),toLower("Lap").c_str())==0){//Check if the line contain the word 'lap'
					isFound = true;//Set isFound to true;
					lapCnt++; //Increment lapCnt
					pos = 0;//Reset counter variable
				}
				else{
					if(isFound){//Check if the word 'lap' have been found
						if(lapCnt == 1){ //Check if it is the first lap
							if(pos == i){ //Check if the current student counter is same as the current student index
								studentName = splitString(line)[0]; //Save student name
								studentLap += getTimeInSeconds(splitString(line)[1]+":");//Save student lap
							}							
						}else{
							if(strcmp(toLower(studentName).c_str(),toLower(splitString(line)[0]).c_str())==0){//Get if the student name is same as the current student name and save the student lap time
								studentLap += getTimeInSeconds(splitString(line)[1]+":");
							}	
						}
						if(splitString(line)[0].length() ==0){//Check if the line contains only space
					   		isFound = false;
						}
						pos++;
					}
				
				}		
					
			}
			myfile.close();
		}
		else{
			cout << "Unable to open file";
		}	
	    pos = 0;
		isFound =false;
		lapCnt = 0;
		int studentLap2 = 0;
		ifstream myfile2(fileName2.c_str());
		if(myfile2.is_open()){//Check if file is open
			while(getline(myfile2,line)){//while there is still content	
				if(strcmp(toLower(splitString(line)[0]).c_str(),toLower("Lap").c_str())==0){//Check if the line contain the word 'lap'
					isFound = true;
					lapCnt++;
					pos = 0;
				}
				else{
					if(isFound){
						if(splitString(line)[0].length() ==0){//Check if the line contains only space
					   		isFound = false;
					   	
						}
						else{
							if(strcmp(toLower(studentName).c_str(),toLower(splitString(line)[0]).c_str())==0){//Get if the student name is same as the current student name and save the student lap time
								studentLap2 += getTimeInSeconds(splitString(line)[1]+":");
							}	
						}
						pos++;
					}
				
				}		
					
			}
			myfile.close();
		}
		else{
			cout << "Unable to open file";
		}	
		cout << studentName;
		for(int i = studentName.length() + convertIntToTime(studentLap).length(); i < 13; i++){//Loop and add corresponding space
			cout << " ";
		}
		cout << convertIntToTime(studentLap);
		for(int i = convertIntToTime(studentLap).length() + convertIntToTime(studentLap2).length(); i < 14; i++){//Loop and add corresponding space
			cout << " ";
		}
		cout << convertIntToTime(studentLap2) << "        ";
		cout << (studentLap2 - studentLap) << " sec" << '\n';
	}
		
		//printPerformance();
}
//End of Objective 5



int main(){
	//Uncomment any of the following to test each part of the program
	//cout << totalStudent("results1.txt");
	getTopThree("results1.txt"); //Objective 1
	lapStudentAverage("results1.txt"); //Objective 2
	getTimeDifference("results1.txt"); //Objective 3
	getConsistentStudent("results1.txt"); //Objective 4
	getStudentRaceComparison("results1.txt","results2.txt"); //Objective 5
}

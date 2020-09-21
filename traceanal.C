
#include<stdio.h>
#include<iostream>
#include<cstring>
#include<string>
#include<vector> 


using namespace std;

//This is the struct for a "follower" which represents the System Call
// that comes after another System Call
struct flw{   
string curr;
int count; //This count will display how many times the follower and
           //and its previous system call have been seen simultaneously 
};

struct sysCall{ 
string prev; //This is the system call previous to the follower
int total;   //Total number of times the system call has been seen 
vector<flw> flws; //A vector of followers that follow the "prev" sys call
};


main(int argc, char **argv){

string prev = "first"; 
int totalInst = 0;
bool check = false; //Used to check if the system call has been seen before
bool lastLine = true;//Used to check if we are on the last line of the log
string line; //This will store the current line we are on 
vector<sysCall> allSysCall; //Vector of all system calls 

 
while(getline(cin,line)){  //As long as we're still going through the file

	lastLine = true;
	if(line.find("(") != -1){ //If line has a system call

		lastLine = false; //Not the last line 

		string curr; 
		//curr will hold the current system call 
		curr = line.substr(0, line.find("("));
 
 	//We will only get inside this if statement the first iteration
 	//of the while loop to set the first sys call as previous so that 
 	//we can populate the vector correctly
	if(prev == "first"){ 
	    prev = curr;
	}
	
	//Creating the first struct only if vector is empty
	else if(allSysCall.empty()){
	struct flw tmpFlw {curr, 1};
	vector<flw> tmpV;
	tmpV.push_back(tmpFlw);
	struct sysCall temp {prev, 1, tmpV};
	allSysCall.push_back(temp);
	
	prev = curr; 
//Need to do this once we are done with every iteration to 
//continue grabing a new prev and curr working our way down the file 
	}
	
	else{
	//Iterate through the vector of system calls 
	for(int i = 0; i < allSysCall.size(); i++){
		
		if(allSysCall.at(i).prev == prev){ 
		//if sys call seen before/exists in the vector  
		check = true;
		allSysCall.at(i).total++; //increment total count 
		
		int j=0;
		//Iterate through followers of system call if it exists
		for(j = 0; j < allSysCall.at(i).flws.size(); j++){
			//If current follower already exists 
			if(allSysCall.at(i).flws.at(j).curr == curr){
			//increment count of that prev/follower pair
			allSysCall.at(i).flws.at(j).count++;
			break;
			}
		} 
		if(j == allSysCall.at(i).flws.size()){
		//If the follower is not seen with the prev sys call before
		//Add the follower to the vector of followers 
		struct flw tmpAdd {curr, 1};
		allSysCall.at(i).flws.push_back(tmpAdd);
		}
		prev = curr;
		break;
		}
	}
		if(!check){
		//if sys call has not been seen before we will add it 
		//to the vector of system calls 
		vector<flw> tmpVNew;
		struct flw tmpNew {curr, 1};
		tmpVNew.push_back(tmpNew);
		struct sysCall newSysCall {prev, 1, tmpVNew};
		allSysCall.push_back(newSysCall);
		prev = curr;
		}
		check = false;
	}	
	
	
}
	if(lastLine){
	//If we have the last syscall in prev variable 
	for(int x = 0; x < allSysCall.size(); x++){
	if(allSysCall.at(x).prev == prev){
	//Increment count if that last sys call has been seen before
		allSysCall.at(x).total++;
	}
	}
	//else create a struct for the last sys call with no followers 
	//because its the last system call with nothing following it
	vector<flw> empty;
	struct sysCall lastSysCall {prev, 1, empty};
	allSysCall.push_back(lastSysCall);
	}

}

	
	for(int s = 0; s < allSysCall.size(); s++){
	//Print the statement for part 1 and part 2
		totalInst += allSysCall.at(s).total;
	}
cout << "AAA: " << totalInst << " " << "invoked system call instances from " << allSysCall.size() << " " << "unique system calls" << endl;

 	
 	if(argc == 1){
 	//If we are running part 1 ex:// "./traceanal < ls.slog"
	for(int k = 0; k < allSysCall.size(); k++){
 cout << allSysCall.at(k).prev << " " << allSysCall.at(k).total << endl;	
	}

}
	if(argc == 2 && (strncmp(argv[1], "seq", 3) == 0)){
   //If we are running part 2 with seq ex:// "./traceanal seq < ls.slog
	for(int k = 0; k < allSysCall.size(); k++){
 cout << allSysCall.at(k).prev << " " << allSysCall.at(k).total << endl;
 	for(int l = 0; l < allSysCall.at(k).flws.size(); l++){
 cout << "\t" << allSysCall.at(k).prev << ":" << allSysCall.at(k).flws.at(l).curr << " " << allSysCall.at(k).flws.at(l).count << endl;
 	
 			}
		}
	}
}

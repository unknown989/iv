#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

string runcmd(const char* cmd){
	/*
	Run a Popen sh command
	and return a string that contains the stdin
	*/
	FILE *fp = popen(cmd,"r"); // Load the Popen file
	string tmp; // Just an empty temporary string 
	char buf[16]; // The amount of character read per loop (16) 
	while(fgets(buf,sizeof(buf),fp)){
		tmp += buf; // Append the buffer the tmp string
	}
	pclose(fp); // Close the Popen file
	return tmp;
}

void split(string str,char delimiter,std::vector<string>& output){
	string tmp; // Load another tmp string
	stringstream s(str); // A string stream to do what under
	while(getline(s,tmp,delimiter)){ // Removing the delimiter and push to the vector
		output.push_back(tmp);
	}
}

string getType(std::vector<string>& vec){ // Get the type by just going to the character 1 of the splitted vector
	return vec[1];
}

string detect(const char* fn){
	string cmd = "file '"+string(fn)+"'"; // file 'filename'
	string res = runcmd(cmd.c_str()); // Result of Popen
	vector<string> splitted;  
	split(res,' ',splitted); // Split the result and the delimiter is a space
	return getType(splitted);
}

/*int example(int argc,char** argv){
	if (argc <2){cout <<"A File is Required" << endl;return -1;};
	//char* cmd = {"f","i","l","e"," "};
	string cmd = "file '"+string(argv[1])+"'";
	string res = runcmd(cmd.c_str());
	cout << "POPEN Result : " << res << endl;
	vector<string> o;
	split(res,' ',o);
	cout <<"FileType : "<< getType(o) << endl;
	return 0;
}*/

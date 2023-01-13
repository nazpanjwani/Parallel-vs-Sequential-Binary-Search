#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <cstring>
//#include <conio.h>
#include "App.h"
#include "User.cpp"
using namespace std;

int main(){
    ifstream infile("apps.txt");
    int noOfRecords = 10841;
    vector<App> apps(noOfRecords);
	string appID;
	string appName;
	string rating;
	string reviews;
	string size;
	string installs;
	string type;
	string price;
	string contentRating;
	string genre;  
	string lastUpdate; 	
    for (int i = 0; i < noOfRecords; i++){
    	App obj;
    	string token;
    	getline(infile, token, '~');    //getting each value separated by the delimiter '~' in file
    	obj.appID = token;              //and storing in vector
    	
    	getline(infile, token, '~');
    	obj.appName = token;
    	
    	getline(infile, token, '~');
    	obj.rating = token;
    	
    	getline(infile, token, '~');
    	obj.reviews = token;
    	
    	getline(infile, token, '~');
    	obj.size = token;
    	
    	getline(infile, token, '~');
    	obj.installs = token;
    	
    	getline(infile, token, '~');
    	obj.type = token;
    	
    	getline(infile, token, '~');
    	obj.price = token;
    	
    	getline(infile, token, '~');
    	obj.contentRating = token;
    	
    	getline(infile, token, '~');
    	obj.genre = token;
    	
    	getline(infile, token, '\n');
    	obj.lastUpdate = token;

        apps[i] = obj;
       
}
	
	infile.close();
	user(apps, noOfRecords);   
}


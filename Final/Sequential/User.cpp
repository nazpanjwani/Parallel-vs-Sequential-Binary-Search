#include<iostream>
#include<fstream>
#include <chrono>
#include<vector>
#include <algorithm>
#include "App.h"
#include <omp.h>
#include <string>
using namespace std;

void binarySearchName(vector<App>& apps,int start, int end,string key)    //sequential binary search
{
	//auto begin = chrono::high_resolution_clock::now();
	while(start<=end)
	{
		int mid=(start+end)/2;
		if(strcmp(apps[mid].appName.c_str(),key.c_str())==0)
		{
			cout << "\n" <<apps[mid].appID << " " << apps[mid].appName << " " << apps[mid].rating << apps[mid].reviews << " " << apps[mid].size << " " << apps[mid].installs << " " << apps[mid].type << " " << apps[mid].price << " " << apps[mid].contentRating << " " << apps[mid].genre << " "<< apps[mid].lastUpdate << " "<< '\n';
			//auto tend = chrono::high_resolution_clock::now();
			//auto elapsed = chrono::duration_cast<chrono::nanoseconds>(tend - begin); 
			//cout<<"\nTime measured: "<<elapsed.count() * 1e-9<< " nano seconds.\n";
			return;
		}
		else if(strcmp(apps[mid].appName.c_str(),key.c_str())<0)
		{
			start=mid+1;
		}
		else
		{
			end=mid-1;
		}
	}
}
void binarySearchID(vector<App>& apps,int start, int end,string key)    //sequential binary search
{
	
	//auto begin = chrono::high_resolution_clock::now();
	while(start<=end)
	{
		int mid=(start+end)/2;
		if(apps[mid].appID==key)
		{
			cout << "\n" <<apps[mid].appID << " " << apps[mid].appName << " " << apps[mid].rating << apps[mid].reviews << " " << apps[mid].size << " " << apps[mid].installs << " " << apps[mid].type << " " << apps[mid].price << " " << apps[mid].contentRating << " " << apps[mid].genre << " "<< apps[mid].lastUpdate << " "<< '\n';
			//auto tend = chrono::high_resolution_clock::now();
			//auto elapsed = chrono::duration_cast<chrono::nanoseconds>(tend - begin); 
			//cout<<"\nTime measured: "<<elapsed.count() * 1e-9<< " nano seconds.\n";
			return;
		}
		else if(apps[mid].appID<key)
		{
			start=mid+1;
		}
		else
		{
			end=mid-1;
		}
	}
	
}

void user(vector<App>& apps, int size){
	int choice; string str;

	cout<<"\n\xDb\xDb\xDb\xDb\xB2 Choose a relevant option \xB2\xDb\xDb\xDb\xDb "<<endl;
	cout<<"\n 1.Sequential binary search using App ID"<<endl;
	cout<<"\n 2.Sequential binary search using App Name"<<endl;
	
	cout<<"\n\nEnter your choice: ";
	cin>>choice;
	if(choice==1){
		string target;
		cout<<"Enter app ID to search: ";
		cin>>target;	
	sort(apps.begin(), apps.end(),[](App a, App b) { 
		return a.appID < b.appID;
	});
	
	auto begin = chrono::high_resolution_clock::now();
	binarySearchID(apps, 0 , size, target );
	auto end = chrono::high_resolution_clock::now();
	auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin); 
	printf("\nTime measured: %.20f seconds.\n", elapsed.count() * 1e-9);
	
}
else if(choice==2){
	string target;
		cout<<"Enter app Name to search: ";
		cin.ignore();
		getline(cin,target);
		sort(apps.begin(), apps.end(),[](App a, App b) {
		return a.appName < b.appName;
	});

	auto begin = chrono::high_resolution_clock::now();
	binarySearchName(apps, 0 , size, target );
	auto end = chrono::high_resolution_clock::now();
	auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin); 
	printf("\nTime measured: %.20f seconds.\n", elapsed.count() * 1e-9);
	
}
}

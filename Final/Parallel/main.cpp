#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <cstring>
#include <stdlib.h>
#include <string>
#include "App.h"
#include <chrono>
//#include "User.cpp"
#include <mpi/mpi.h>
using namespace std;
/*int binarySearch(vector<App>& apps,int start, int end,int key,int rank)
{
cout<<" I AM PROCESS "<<rank<<" SEARCHING FROM "<<start<< " TO "<<end<<" LOOKING FOR "<<key<<endl;
	while(start<=end)
	{
		int mid=(start+end)/2;
		if(stoi(apps[mid].appID)==key)
		{
			cout<<"Element found by processor "<<rank<<" .\n";
cout << apps[mid].appID << " " << apps[mid].appName << " " << apps[mid].rating << apps[mid].reviews << " " << apps[mid].size << " " << apps[mid].installs << " " << apps[mid].type << " " << apps[mid].price << " " << apps[mid].contentRating << " " << apps[mid].genre << " "<< apps[mid].lastUpdate << " "<< '\n';
			return 1;
		}
		else if(stoi(apps[mid].appID)<key)
		{
			start=mid+1;
		}
		else
		{
			end=mid-1;
		}
	}
}*/
//MPI_Init(NULL, NULL);
int main(int argc, char **argv){
    
    MPI_Init(&argc, &argv); 
    int rank, size1,key;
    //string key;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size1);
    int noOfRecords = 10841;
    vector<App> apps(noOfRecords);
    int blockSize=noOfRecords/size1;
	
    
	// int appID;
	string appID;
	string appName;
	//float rating;
	string rating;
	//int reviews;
	string reviews;
	string size;
	string installs;
	string type;
	//float price;
	string price;
	string contentRating;
	string genre;  
	string lastUpdate;
  
    	//if(rank==0){
	ifstream infile("apps.txt");
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
	double begin, stop;
	
      
         if(rank==0){
	ofstream temp("temp.txt");
	temp<<0;
	temp.close();
         cout<<"Enter app ID to search: ";
         cin>>key;
	//cout<< "Key = "<<key;
	for(int  i =0 ; i < size1; i++)
	MPI_Send(&key,1,MPI_INT,i,0,MPI_COMM_WORLD);}    

//}
else
	
	MPI_Recv(&key,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	//MPI_Bcast(&key, 1, MPI_INT, 0, MPI_COMM_WORLD);
          
         
        //MPI_Bcast(&key, 1, MPI_INT, 0, MPI_COMM_WORLD);   //broadcast key to all processes
	//MPI_Request send, receive;
	//begin =  MPI_Wtime();
	//MPI_STATUS status;
	MPI_Barrier(MPI_COMM_WORLD); /* IMPORTANT */
        begin = MPI_Wtime();
        int start = rank*blockSize, found;
	int end;
	if(rank==size1-1) //last proc
	end = (rank+1)*blockSize;
	else
        end = (rank+1)*blockSize-1;

	//int root = 0, flag=0;
        cout<<" I AM PROCESS "<<rank<<" SEARCHING FROM "<<start<< " TO "<<end<<" LOOKING FOR "<<key<<endl;
	while(start<=end && found==0 )
	{
		ifstream temp("temp.txt");
		temp>>found;
		if(found==1)
		break;
		temp.close();
		int mid = (start+end)/2;
                cout<<"\nRank "<<rank<<": id = "<<stoi(apps[mid].appID)<<endl;
		 
		if(stoi(apps[mid].appID)==key)
		{
			cout<<"Element found by processor "<<rank<<" .\n";
cout << apps[mid].appID << " " << apps[mid].appName << " " << apps[mid].rating << apps[mid].reviews << " " << apps[mid].size << " " << apps[mid].installs << " " << apps[mid].type << " " << apps[mid].price << " " << apps[mid].contentRating << " " << apps[mid].genre << " "<< apps[mid].lastUpdate << " "<< '\n';
			
                        ofstream temp("temp.txt");
		        temp<<1;
			temp.close();
			break;
			
			/*for(int  i =0 ; i < size1; i++){
			if (i!=rank){
			MPI_Isend(&found,1,MPI_INT,i,0,MPI_COMM_WORLD,&send);
			}
			

			}*/
			//MPI_Isend(&found,1,MPI_INT,i,0,MPI_COMM_WORLD,&send);
			//MPI_Wait(&send, MPI_STATUS_IGNORE);
			//MPI_Bcast(&found, 1, MPI_INT, root, MPI_COMM_WORLD);
			
		}
		else if(stoi(apps[mid].appID)<key)
		{
			start=mid+1;
		}
		else
		{
			end=mid-1;
		}
		//MPI_Irecv(&found,1,MPI_INT,root,0,MPI_COMM_WORLD,&receive);
		//MPI_Bcast(&found, 1, MPI_INT, root, MPI_COMM_WORLD);

		//cout<<"\nRank "<<root<<": found = "<<found<<endl;
	}
		//cout<<"\nRank "<<rank<<": found = "<<found<<endl;
		
	//}
		
	//}
MPI_Barrier(MPI_COMM_WORLD); /* IMPORTANT */
        stop = MPI_Wtime();
if (rank == 0) { /* use time on master node */
ifstream temp("temp.txt");
		temp>>found;
if(found==0)
cout<<"\nCouldn't find target value!";
		temp.close();
    printf("\nRuntime = %f\n", stop-begin);
}
ifstream temp("temp.txt");
		temp>>found;
//cout<<"Final found = "<<found;
temp.close();
	

MPI_Finalize();


}


/******************************************************************************
  Title          : CreateGraphAndTest.cc
  Author         : Wei Lian
  Created on     : May 13, 2018
  Description    : main interface of CreateGraphAndTest program
  Purpose        : the program create a graph, and test if the vertex is connected to another or not.
  Modifications  : 

  Notes:
 
******************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include "AdjanceyList.h"

using namespace std;


//The function create the graph.
template<typename Comparable>
void CreateGraph(AdjancecyList<Comparable>& adj_list, const string& input_filename)
{
	//read the input file
	ifstream input_file(input_filename);
	string line;
	//make sure the file is opened correctly
	if(!input_file.is_open())
	{
		cerr<<input_filename<<" "<<"can not be open"<<endl;
	}
	else
	{

		while(!input_file.eof())
		{
			//keep getline while is not end of file
			getline(input_file,line);
			Comparable key,vertex;
			double weight=0;
			//call the parser function and insert these variables into the graph
			ExtractcontentFrominputline(adj_list,line,key,vertex,weight);
		}
		input_file.close();
	}

}
//parser function and save variables into the graph.
template<typename Comparable>
void ExtractcontentFrominputline(AdjancecyList<Comparable>& adj_list,string line,Comparable &key, Comparable &vertex, double weight)
{
	//set a counter that increase everytime when it sets up a variable.
	int cter=1;
	//make sure the line is not empty
	if(line!=" ")
	{
		//insert a " " space to the end of the string for our parse to working properly.
		line.insert(line.length()," ");
		//initialize the position to 0.
		int pos=0;
		//let position stop at the space character.
		pos=line.find(" ");
		//new string equal to the substr of the line which is the first charcter to space.
		string temp=line.substr(0,pos);
		//remove the word that saves in temp.
		line.erase(0,pos+1);
		//since we are doing to graph, the first word always the key.
		//use sstream to convert it to the int
		stringstream ss(temp);
		ss>>key;
		//the while loop stops when the whole line is parsed.
		while(line.length()>1)
		{
			
			int pos_a=0;
			pos_a=line.find(" ");
			string temp_a=line.substr(0,pos_a);
			line.erase(0,pos_a+1);
			//if the counter can be divisible by 2, that means it reach to the weight variable
			//because our syntax is key, vertex, weight.
			if(cter%2==0)
			{
				stringstream ss(temp_a);
				ss>>weight;
				adj_list.insert(key,vertex,weight);
				//cout<<key<<" "<<vertex<<" "<<weight<<endl;
			}
			else
			{
				//if the above condition fails, that means the cter reach to the vertex variable
				stringstream ss(temp_a);
				ss>>vertex;
			}
			cter++;
		}
		

	}
}

//the function parse the line into key and vertex.
template <typename Comparable>
void ExtractContentFromQueryLine(string & line, Comparable & key, Comparable & vertex)
{
	int pos=0;
	pos=line.find(" ");
	string temp=line.substr(0,pos);
	line.erase(0,pos+1);
	stringstream ss(temp);
	ss>>key;
	stringstream sss(line);
	sss>>vertex;

}
//the function is write to test if two vertex are connected or not.
template<typename Comparable>
void Test(AdjancecyList<Comparable>& list, const string& input_filename)
{
	ifstream input_file(input_filename);
	string line;
	if(!input_file.is_open())
	{
		cerr<<input_filename<<" "<<"can not be open"<<endl;
	}
	else
	{
		while(!input_file.eof())
		{
			getline(input_file,line);
			Comparable key;
			Comparable vertex;
			ExtractContentFromQueryLine(line,key,vertex);
			if(list.isConnected(key,vertex))
			{
				cout<<key<<" "<<vertex<<": Connected, weight of edge is "<<list.getWeight(key,vertex)<<endl;
			}
			else
				cout<<key<<" "<<vertex<<": Not connected"<<endl;

			
		}
		input_file.close();

	}
}

int main(int argc, char**argv)
{
	if(argc!=3)
	{
		cout<<"Usage: "<<argv[0]<<"<Graph file> <Query file>"<<endl;
		return 0;
	}

	const string graph_file(argv[1]);
	const string queries_file(argv[2]);
	ifstream file(graph_file);
	if(!file.is_open())
	{
		cerr<<graph_file<<" "<<"can not be open"<<endl;
	}
	//read the file, and save the size to the size_t variable
	size_t SizeofGraph;
	file>>SizeofGraph;
	//create the graph with the size.
	AdjancecyList<int> list(SizeofGraph);
	//create the graph
	CreateGraph(list,graph_file);
	//test the graph
	Test(list,queries_file);



	return 0;
}
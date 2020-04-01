/*
Name:		Dimostenis Nikolakopoulos
UCID:		dn242
Studnt num:	31387555
Class:		CS435 002 
Project: 	2
Part: 		3.c) 
*/

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h> 

using namespace std;


struct Node{
    string value="";
    vector<Node*> edges;
    bool checked=false;
};

    
class Main{
    
	public:
	
	vector<Node> createRandomUnweightedGraphIter(int n){
		vector<Node> randomGraph;
		
		for(int i=0 ; i < n ; i++){
			int x=rand() % (n + 1 -1) + 1;
			string str=to_string(x);
			bool inGraph=false;
			
			if(randomGraph.size() > 0){
				for(int j = 0 ; j < randomGraph.size() ; j++){
					if(randomGraph[j].value == str){
						inGraph=true;
						i--;
						break;
					}
				}
				if(inGraph==false){
					Node newNode;
					newNode.value=str;
					randomGraph.push_back(newNode);
				}
				else{
					inGraph==false;
				}
			}
			else{
				Node newNode;
				newNode.value=str;
				randomGraph.push_back(newNode);
			}
		}
		
		for(int i=1 ; i < randomGraph.size() ; i++){
			randomGraph[i-1].edges.push_back(&randomGraph[i]);
		}
		
		
		
		//return Adjacency Vector:
		return randomGraph;
	}
};
	
void printGraph(vector<Node> graph){
	for(int i=0; i<graph.size(); i++){
        cout<<"Node:\t\t"<<graph[i].value<<endl<<"Connections:\t[ ";
        for(int j=0; j<graph[i].edges.size(); j++){
            cout<<graph[i].edges[j]->value<<" ";
        }
        cout<<"]\n"<<endl;
    }
}

int main()
{
	Main mainObj;
    //Getting a randomGraph and printing it:
    vector<Node>randomGraph = mainObj.createRandomUnweightedGraphIter(7);
    cout<<"Printing randomGraph:\n";
    printGraph(randomGraph);
    
    
    return 0;
}
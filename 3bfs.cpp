/*
Name:		Dimostenis Nikolakopoulos
UCID:		dn242
Studnt num:	31387555
Class:		CS435 002 
Project: 	2
Part: 		3.e) 
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
	
	int m=rand() % (randomGraph.size()-1 + 1 - 0) + 1;
	for(int j=0 ; j < (m*(m-1))/2 ; j++){
		int index1 = rand() % (randomGraph.size()-1 + 1 - 0) + 0;
		int index2;
		
		bool inGraph=true;
		
		while(randomGraph[index1].edges.size()>=n-1){
		        index1 = rand() % (randomGraph.size()-1 + 1 - 0) + 0;
		}
		
		while(index1==index2 || inGraph==true){
		    inGraph=false;
			index2 = rand() % (randomGraph.size()-1 + 1 - 0) + 0;
			
			for(int k=0 ; k<randomGraph[index1].edges.size() ; k++){
			    
			    if(randomGraph[index1].edges[k]->value == randomGraph[index2].value){
			        inGraph=true;
			        break;
			    }
			}
		}
		randomGraph[index1].edges.push_back(&randomGraph[index2]);
		randomGraph[index2].edges.push_back(&randomGraph[index1]);
	}
	
	//return Adjacency Vector:
	return randomGraph;
}

void printGraph(vector<Node> graph){
	for(int i=0; i<graph.size(); i++){
        cout<<"Node:\t\t"<<graph[i].value<<endl<<"Connections:\t[ ";
        for(int j=0; j<graph[i].edges.size(); j++){
            cout<<graph[i].edges[j]->value<<" ";
        }
        cout<<"]\n"<<endl;
    }
}

vector<Node> BFSIter(Node start, Node end){//Because it is conceptually more challenging I will comment more.
	vector<Node> solution;
	Node* indexedNode=&start;
	//In case we search for the first value:
	if (start.value == end.value){
		solution.push_back(start);//Just pass start
		return solution;//and return the first one.
	}
	
	vector<Node> byLevel;
	
	//If not the above then push to the solution list the starting node:
	byLevel.push_back(*indexedNode);
	
	int index=0;
	
	bool found=false;
	
	Node* n = indexedNode->edges[0];
	for(int i =0 ; i < n->edges.size() ; i++){
	    if(n->edges[i]->value == start.value){
	        n->edges[i]->checked=true;
	    }
	}
	
	int count=0;
	int prevSize=-1;
	while(true){
	    //cout<<"Big loop:\t"<<index<<"\n";
	    int indexForEdges=0;
		while(indexForEdges < indexedNode->edges.size()){
		    //cout<<"\tInner loop: "<<indexForEdges<<endl;
		    if(!indexedNode->edges[indexForEdges]->checked){
		        //cout<<"\t\t"<<indexedNode->edges[indexForEdges]->value<<" unchecked\n";
		        if((!indexedNode->edges[indexForEdges]->checked) && (indexedNode->edges[indexForEdges]->value != start.value)){
		            indexedNode->edges[indexForEdges]->checked=true;
		            //cout<<"\t\t"<<"Action: push_back("<<indexedNode->edges[indexForEdges]->value<<")"<<endl;
		            string tempo=indexedNode->edges[indexForEdges]->value;
		            byLevel.push_back(*(indexedNode->edges[indexForEdges]));
		            if(tempo == end.value){
		                return byLevel;
		            }
		        }
		        
		    }
		    indexForEdges++;
		}
		index++;
		
		indexedNode=&(byLevel[index]);
		if(index==1 && count == 0 ){index--;count++;}
		if(byLevel.size() == prevSize){
		    vector<Node> empty;
		    return empty;
		}
		else{
		    prevSize=byLevel.size();
		}
	}
	
	return byLevel;//It is best advised to print it using the printGraph() with input a copy of this return. (It will make sense)
}

	




int main()
{
	
    //Getting a randomGraph and printing it:
    vector<Node>randomGraph = createRandomUnweightedGraphIter(7);
    cout<<"Printing randomGraph:\n";
    printGraph(randomGraph);
    cout<<"----------------------------------------------------\n";
    vector<Node> toBePrinted= BFSIter(randomGraph[0],randomGraph[4]);//Here I am doing the DFSIter from the class GraphSearch.
	
    cout<<"\n\nPrinting search from "<<randomGraph[0].value<<" to "<<randomGraph[4].value<<" :\n";
    if(toBePrinted.size()>0){
        printGraph(toBePrinted);
    }
    else{
        cout<<"ATTENTION: There is no path from "<<randomGraph[0].value<<" to "<<randomGraph[4].value<<"!"<<endl;
    }
    
    
    return 0;
}
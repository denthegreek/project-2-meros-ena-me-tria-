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

class GraphSearch{

    public:
    
	vector<Node> DFSIter(Node start, Node end){//Because it is conceptually more challenging I will comment more.
		vector<Node> solution;
		Node* indexedNode=&start;
		//In case we search for the first value:
		if (start.value == end.value){
			solution.push_back(start);//Just pass start
			return solution;//and return the first one.
		}
		//If not the above then push to the solution list the starting node:
		solution.push_back(*indexedNode);
		
		//Otherwise we "dive" into the graph: 
		while(indexedNode->edges.size()!=0){
			int indexForEdges=0;//initially-(changes in the nested while!)
			indexedNode->checked=true;//I've seen this room and I've walked this floor... (joke)
	 
			int iterations=0;//if we loop too many times in the edges list of the Node it is not in this fragment of the grapg. 
			while((indexedNode->edges[indexForEdges]->checked==true)||(indexedNode->edges[indexForEdges]->value==start.value)){
				indexForEdges++;//While we find an edge leading to checked element we keep looking.
				if((indexForEdges == indexedNode->edges.size()-1) && (indexedNode->edges[indexForEdges]->checked==true)){
					vector<Node> empty{};
					return empty;
				}
				else{
					iterations++;
				}
			}
			indexedNode=indexedNode->edges[indexForEdges];//go towards the Node oldest possible node connected to current.
			solution.push_back(*indexedNode);//put the one you got into to the solution list (it will bechecked on the next iter)
			if(indexedNode->value == end.value){
				break;//If value is found it is going to go out and return the solution list
			}
		}
		
		for(int i = 0 ; i < solution.size() ; i++){
			for(int j =0 ; j < solution[i].edges.size() ; j++ ){
				if(solution[i].edges[j]->checked==true){
					solution[i].edges[j]->checked=false;
				}
			}
		}
		
		return solution;//It is best advised to print it using the printGraph() with input a copy of this return. (It will make sense)
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
    GraphSearch someGraphObj;
	
    //Getting a randomGraph and printing it:
    vector<Node>randomGraph = createRandomUnweightedGraphIter(7);
    cout<<"Printing randomGraph:\n";
    printGraph(randomGraph);
    cout<<"----------------------------------------------------\n";
    vector<Node> toBePrinted= someGraphObj.DFSIter(randomGraph[0],randomGraph[2]);//Here I am doing the DFSIter from the class GraphSearch.
	
    cout<<"Printing search from "<<randomGraph[0].value<<" to "<<randomGraph[2].value<<" :\n";
    if(toBePrinted.size()>0){
        printGraph(toBePrinted);
    }
    else{
        cout<<"ATTENTION: There is no path from "<<randomGraph[0].value<<" to "<<randomGraph[2].value<<"!"<<endl;
    }
    
    cout<<"----------------------------------------------------\n";
    toBePrinted.clear();//clearing this toBePrinted to be used again;
    toBePrinted= someGraphObj.DFSIter(randomGraph[0],randomGraph[1]);//Here I am doing the DFSIter from the class GraphSearch.
	
    cout<<"Printing search from "<<randomGraph[0].value<<" to "<<randomGraph[1].value<<" :\n";
    if(toBePrinted.size()>0){
        printGraph(toBePrinted);
    }
    else{
        cout<<"ATTENTION: There is no path from "<<randomGraph[0].value<<" to "<<randomGraph[1].value<<"!"<<endl;
    }
    
    return 0;
}
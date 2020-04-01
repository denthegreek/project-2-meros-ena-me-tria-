/*
Name:		Dimostenis Nikolakopoulos
UCID:		dn242
Studnt num:	31387555
Class:		CS435 002 
Project: 	2
Part: 		3.a) 
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;


struct Node{
    string value="";
    vector<Node*> edges;
    bool checked=false;
};

//Adjacency Vector:
vector<Node> graph;
    
class Graph{
    
    public:
    
    void addNode(string nodeVal){ 
        Node newNode;
        newNode.value=nodeVal;
    
        graph.push_back(newNode);
    } 
    
    void addEdge(string first, string second){ 
        Node* firstPtr = NULL;
        Node* secondPtr = NULL;
        
        int indexFirst, indexSecond;
        
        for(int i =0; i<graph.size() ; i++){
            if(graph[i].value== first){
                firstPtr = &graph[i];
                indexFirst=i;
            }
            else if(graph[i].value== second){
                secondPtr = &graph[i];
                indexSecond=i;
            }
            if(firstPtr!=NULL && secondPtr!=NULL){
                break;
            }
        }
         graph[indexFirst].edges.push_back(secondPtr);
         graph[indexSecond].edges.push_back(firstPtr);
        
    }
    
    void removeUndirectedEdge(Node first, Node second){ 
        int ofTheTwo=0;
        
        string First = first.value;
        string Second = second.value;
        
        for(int i =0; i<graph.size() ; i++){
            if(graph[i].value== First){
                for (auto it = graph[i].edges.begin(); it != graph[i].edges.end(); ++it){
                    if((*it)->value==Second){
                        graph[i].edges.erase(it);
                        ofTheTwo++;
                    }
                }
            }
            else if(graph[i].value== Second){
                for (auto it = graph[i].edges.begin(); it != graph[i].edges.end(); ++it){
                    if((*it)->value==First){
                        graph[i].edges.erase(it);
                        ofTheTwo++;
                    }
                }
            }
            if(ofTheTwo==2){
                break;
            }
        }
    }
    
    vector<Node> getAllNodes(){
        vector<Node> HashSet;
        for(int i=0 ; i<graph.size() ; i++ ){
            HashSet.push_back(graph[i]);
        }
        return HashSet;
    }
};
void printGraph(){
	for(int i=0; i<graph.size(); i++){
        cout<<"Node:\t\t"<<graph[i].value<<endl<<"Connections:\t[ ";
        for(int j=0; j<graph[i].edges.size(); j++){
            cout<<graph[i].edges[j]->value<<" ";
        }
        cout<<"]"<<endl;
    }
}

int main()
{
    Graph someGraph;
    
    //--------------------------------------------------------------addNode()
	//Adding nodes:
    someGraph.addNode("3");
    someGraph.addNode("10");
    someGraph.addNode("8");
    someGraph.addNode("4");
    someGraph.addNode("500");
    
    //--------------------------------------------------------------addEdge()
	//Adding edges:
    someGraph.addEdge("10","3");
    someGraph.addEdge("10","8");
    someGraph.addEdge("10","4");
    someGraph.addEdge("3","500");
    someGraph.addEdge("4","500");
    
	//Printing in the format:
	//Node:			something
	//Connections:	something
    printGraph();
    
    //--------------------------------------------------------------removeUndirectedEdge()
    cout<<"\nI am deleting an edge: ("<<graph[1].value<<","<<graph[0].value<<") \"and vise versa\"\n"<<endl;
	//difference is to be observed on 3 and 10
    someGraph.removeUndirectedEdge(graph[1],graph[0]);
    
    printGraph();
    //--------------------------------------------------------------
    cout<<endl;
    //--------------------------------------------------------------getAllNodes()
    //Printing all Nodes in the graph:
    vector<Node> HashSet=someGraph.getAllNodes();
    cout<<"Graph: [";
    for(int i =0; i<HashSet.size();i++){
        cout <<HashSet[i].value;
        if(i!=HashSet.size()-1){
            cout<<",";
        }
    }
    cout<<"]\nNumber of elements: "<<HashSet.size()<<endl;
    
    return 0;
}
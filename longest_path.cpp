#include <iostream>
#include <vector>
using namespace std;

vector<int> adjList[50001];

class Graph{
public:
  int numV;
  int numE;
  bool* visit;
  Graph(){
    ;
  }
  
  Graph (int numV, int numE){
    this->numV = numV;
    this->numE = numE;
    this->visit = new bool[numV];
    for (int i=0; i < numV; i++)
      this->visit[i] = false;
  }
  
  ~Graph(){
    ;
  }
  
  void addEdge(int v1, int v2){
    adjList[v1 - 1].push_back(v2 - 1);
    adjList[v2 - 1].push_back(v1 - 1);
  }
  
  int getMinvertex(){
    int minValue = (1 << 21) - 1;
    int minVertex = -1;
    for (int i=0; i < numV; i++){
      if (adjList[i].size() == 0)
        continue;
      if (minValue == -1 || adjList[i].size() < minValue){
        minValue = adjList[i].size();
        minVertex = i;
      }
    }
    return minVertex;
  }
  
  int getNextVertex(int v) {
    this->visit[v] = true;
    int minV = -1;
    for (int i : adjList[v]) {
      if (this->visit[i])
        continue;
      if (minV == -1 || adjList[i].size() < adjList[minV].size()) {
        minV = i;
      }
    }
    return minV;
  }
};

Graph g;

int main()
{
  int v, e;
  /*freopen("input00.txt", "r", stdin);*/
  
  for (int i=0; i < 50000; i++)
    adjList[i] = vector<int>();
  
  // get the input array & generate the graph
  cin >> v >> e;
  g = Graph (v, e);
  
  for (int i=0; i < e; i++){
    int v1, v2;
    cin >> v1 >> v2;
    g.addEdge(v1, v2);
  }
  
  // choose the edge-minimum vertex
  vector<int> path;
  int curVertex = g.getMinvertex();
  
  // select the next edge-minimum vertex
  while (true){
    path.push_back(curVertex);
    curVertex = g.getNextVertex(curVertex);
    if (curVertex == -1)
      break;
  }
  
  // Print the result
  cout << path.size() << endl;
  for (int i : path)
    cout << i + 1 << " ";
  cout << endl;
}

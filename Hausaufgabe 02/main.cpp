#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * Nimmt eine Kanten-Liste als std::vector<int> an und generiert
 * eine Outputdatei "graph.dot" im GraphViz Format.
 * Diese Funktion soll nur benutzt, und nicht verändert werden.
 */
void graph_to_dot(const std::vector<int> &edge_list) {
  // Ein gültiger Wert von der Kanten-Liste enthält eine gerade Zahl von Elementen.
  assert((edge_list.size() % 2 == 0));
  // "graph.dot" wird geöffnet und beschrieben.
  std::ofstream o("graph.dot");
  o << "digraph finite_state_machine { rankdir=LR;";
  for (size_t i = 0; i < edge_list.size(); i += 2) {
    o << "\n " << edge_list[i] << " -> " << edge_list[i + 1] << ";\n";
  }
  o << "}";
}



int main() {

  using namespace std;


  // 1. Einlesen von my_graph.txt ein in einen std::vector. Die erste Zahl in my_graph.txt ist die größe des std::vectors
  string filename = "my_graph.txt";
  ifstream infile(filename);

  int m;
  infile >> m;
  vector<int> v(m * 2, 0);

  for (int i = 0; i < v.size(); i++) {
    infile >> v[i];
  }


  // 2. Ausgeben der Einträge im Terminal per for-loop
  for (int i = 0; i < v.size(); i++) {
    cout << v[i] << ' ';
  }
  cout << endl;


  // 3. + 4. Initialisieren von v2 mit passender Größe. Füllen der übrigen Einträge
  vector<int> v2(v.size() + 2, 0);
  
  for (int i = 0; i < v.size(); i++) {
    v2[i] = v[i];
  }
  v2[v.size()] = 3;
  v2[v.size()+1] = 4;


  // 5. Aufrufen von graph_to_dot auf v2 auf
  graph_to_dot(v2);
  

  // 6. + 7. (Ιm Terminal)

  return 0;
}
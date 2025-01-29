/**
 * Einführung in C++ / WiSe 24-25
 * Exercise nr. 3
 *
 * <christodoulou@stce.rwth-aachen.de>
 * <fleming@stce.rwth-aachen.de>
 */

#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

/**
 * Diese Funktion nimmt eine Kanten-Liste als std::vector<int*> und invertiert
 *   die Richtung aller Kanten.
 * Die Kanten-Liste ist eine Liste von Zeigern, die
 *   als Paaren interepretiert werden. Jedes Paar (&a, &b) bezeichnet eine Kante
 *   zwischen Knoten mit Beschriftungen a und b.
 */
void reverse_edges(std::vector<int *> &edge_pointers) {
  assert(edge_pointers.size() % 2 == 0);

  // Diese Funktion muss vollständigt werden!
  int * temp;
  for (int i = 0; i < edge_pointers.size(); i = i+2) {
    temp = edge_pointers[i];
    edge_pointers[i] = edge_pointers[i + 1];
    edge_pointers[i + 1] = temp;
  }
}

/**
 * Nimmt eine Knoten-Liste als std::vector<int>, 
 *  eine Kanten-Label-Liste als std::vector<int>, und
 *  eine Kanten-Liste als std::vector<int *> an und generiert ein
 *  Datei in GraphViz DOT Format.
 *
 * Die Kanten-Liste ist eine Liste von Zeigern, die als Paaren interepretiert
 * werden. Jedes Paar (&a, &b) bezeichnet eine Kante zwischen Knoten a und b.
 */
void graph_to_dot(const std::vector<int> &vtx_labels,
                  const std::vector<int> &edge_labels,
                  const std::vector<int *> &edge_pointers) {
  assert(edge_pointers.size() == 2 * edge_labels.size());
  std::ofstream o("graph.dot");
  o << "digraph finite_state_machine { rankdir=LR; ";
  for (int i = 0; i < vtx_labels.size(); i++) {
    o << vtx_labels[i] << ";";
  }
  for (int i = 0; i < edge_labels.size(); i++) {
    o << "\n " << *edge_pointers[2 * i] << " -> " << *edge_pointers[2 * i + 1];
    o << " [label=" << edge_labels[i] << "];";
  }
  o << "}";
}

int main(int argc, char **argv) {

  using namespace std;
  string filename("my_graph.txt");

  // 1. Öffne my_graph.txt (dafür ist "filename" da) mit einem std::ifstream
  //      und lese die Datei wie in den Übungsfolien beschrieben aus.
  ifstream infile(filename);

  // vector der knoten
  int v_amount;
  infile >> v_amount;
  vector<int> v (v_amount, 0);

  for (int i = 0; i < v.size(); i++) {
    infile >> v[i];
  }

  // vector der kantenknoten und kantenwerte
  int edg_amount;
  infile >> edg_amount;
  vector<int*> e(edg_amount * 2, 0);
  vector<int> edg(edg_amount, 0);

  for (int i = 0; i < edg.size(); i++) {
    int temp;
    infile >> temp;
    e[i*2] = &v[temp];
    
    infile >> temp;
    e[i*2 + 1] = &v[temp];

    infile >> edg[i];
  }

  // ausgabe der kanten
  for (int i = 0; i < edg.size(); i++) {
    cout << *e[2*i] << " -> " << *e[2*i+1] << "\t// " << edg[i] << endl;
  }


  
  // 2. Ergänze die Funktion "reverse_edges". Rufe sie auf die Kanten-Liste aus.
  reverse_edges(e);


  // 3. Rufe die Fuktion "graph_to_dot" auf die drei Vektoren aus.
  graph_to_dot(v, edg, e);


  return 0;
}
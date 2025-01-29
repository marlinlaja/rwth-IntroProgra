#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>



// HELPER FUNCTIONS

/**
 * Nimmt einen Datei-Namen als std::string als input an. Dieser bezeichnet das
 * Input-Datei. Als In-Out Parameter nimmt diese Funktion:
 *  - eine std::vector<int> für die Labels der Knoten
 *  - eine std::vector<std::pair<int, int>> für die Kanten.
 *    - Jedes Paar von Indizes (a, b) ist eine Kante zwischen Knoten a -> b.
 *    - In der Dritten Übung hatten wir diese Kanten mit int* bezeichnet, aber
 *       Indizes sind in diesem Fall (und im Allgemein) sinvoller.
 */
void load_graph(std::string const &filename, std::vector<int> &knoten_beschriftungen, std::vector<std::pair<int, int>> &kanten) {
  std::ifstream graph_in(filename);
  int werte_zu_lesen;
  graph_in >> werte_zu_lesen;
  knoten_beschriftungen.resize(werte_zu_lesen);
  for (int i = 0; i < werte_zu_lesen; i++) {
    graph_in >> knoten_beschriftungen[i];
  }
  graph_in >> werte_zu_lesen;
  kanten.resize(werte_zu_lesen);
  std::pair<int, int> temp;
  for (int i = 0; i < werte_zu_lesen; i++) {
    graph_in >> temp.first;
    graph_in >> temp.second;
    kanten[i] = temp;
  }
}

/**
 * Nimmt eine Knoten-Liste als std::vector<int>,
 *  eine Kanten-Liste als std::vector<std::pair<int, int>> an und generiert eine
 *  Datei in GraphViz DOT Format.
 */
void graph_to_dot(std::string const &filename, const std::vector<int> &knoten_beschriftungen, const std::vector<std::pair<int, int>> &kanten) {
  std::ofstream o(filename);
  o << "digraph finite_state_machine { rankdir=LR; ";
  for (std::vector<int>::const_iterator i = knoten_beschriftungen.cbegin();
       i != knoten_beschriftungen.cend(); i++) {
    o << *i << "; ";
  }
  for (std::vector<std::pair<int, int>>::const_iterator i = kanten.cbegin();
       i != kanten.cend(); i++) {
    o << "\n " << knoten_beschriftungen[i->first] << " -> "
      << knoten_beschriftungen[i->second];
  }
  o << "}";
}

/**
 * @brief Ergibt ein @c std::vector<int> mit Größe @c n
 *   und Einträge @c 0 bis @c n-1
 */
std::vector<int> vector_of_indices(int n) {
  std::vector<int> res(n);
  for (int i = 0; i < n; i++) {
    res[i] = i;
  }
  return res;
}

/**
 * @brief Vergleicht zwei Vektoren.
 * @param[in] a
 * @param[in] b
 * @return @c true wenn jeder i-te Eintrag in @c a ist gleich der i-te Eintrag
 * in @c b
 */
template <typename T>
bool vector_gleichheit(std::vector<T> const &a, std::vector<T> const &b) {
  if (a.size() != b.size()) {
    return false;
  }
  typename std::vector<T>::const_iterator a_iter = a.cbegin();
  typename std::vector<T>::const_iterator b_iter = b.cbegin();
  while (a_iter != a.cend() && b_iter != b.cend()) {
    if (*a_iter != *b_iter) {
      return false;
    }
    a_iter++;
    b_iter++;
  }
  return true;
}

/**
 * @brief Vergleicht zwei Matrixen.
 * @param[in] A
 * @param[in] B
 * @return @c true wenn jeder ij-te Eintrag in @c A ist gleich der ij-te Eintrag
 * in @c B
 */
template <typename T>
bool matrix_gleichheit(std::vector<std::vector<T>> const &a, std::vector<std::vector<T>> const &b) {
  if (a.size() != b.size() || a[0].size() != b[0].size()) {
    return false;
  }
  typename std::vector<std::vector<T>>::const_iterator a_iter = a.cbegin();
  typename std::vector<std::vector<T>>::const_iterator b_iter = b.cbegin();
  while (a_iter != a.cend() && b_iter != b.cend()) {
    if (!vector_gleichheit(*a_iter, *b_iter)) {
      return false;
    }
    a_iter++;
    b_iter++;
  }
  return true;
}



// AUFGABE 1:
// kanten_zu_adjazenzmatrix
std::vector<std::vector<int>> kanten_zu_adjazenzmatrix(std::vector<std::pair<int, int>> const &kanten, std::vector<int> const &knoten) {

  std::vector<std::vector<int>> adjacency_M(knoten.size(), std::vector<int>(knoten.size(), 0));
  for (int i = 0; i < kanten.size(); i++) {
    adjacency_M[kanten[i].second][kanten[i].first] = 1;
  }
  return adjacency_M;
}


// AUFGABE 2:
// permute_vector
std::vector<int> permute_vector(std::vector<int> const &v, std::vector<int> const &permutation) {
  assert(v.size() == permutation.size());

  std::vector<int> permuted_v(v.size());
  for(int i = 0; i < permutation.size(); i++) {
    permuted_v[i] = v[permutation[i]];
  }
  return permuted_v;
}


// AUFGABE 3:
// permute_matrix
std::vector<std::vector<int>> permute_matrix(std::vector<std::vector<int>> const &M, std::vector<int> const &permutation) {
  assert(M.size() == permutation.size() && M[0].size() == permutation.size());

  std::vector<std::vector<int>> permuted_M(M.size());
  for(int i = 0; i < permutation.size(); i++) {
    permuted_M[i] = permute_vector(M[permutation[i]], permutation);
  }
  return permuted_M;
}


// AUFGABE 4: Wie viele 3- und 4-Permutationen gibt es?
/*
Anzahl 3-Permutationen = 3! = 6
Anzahl 4-Permutationen = 4! = 24
*/


// AUFGABE 5
template <typename T>
void recursive_permutation_helper(std::vector<T> &a, int active_length, std::vector<std::vector<T>> &permutation_list) {

  if (active_length <= 1) {
    permutation_list.push_back(a);
  } else {
    recursive_permutation_helper(a, active_length-1, permutation_list);
    for (size_t i = 0; i < active_length-1; i++)
    {
      T temp = a[active_length-1];
      if (active_length % 2 == 0) {
        a[active_length-1] = a[i];
        a[i] = temp;
      } else {
        a[active_length-1] = a[0];
        a[0] = temp;
      }
      recursive_permutation_helper(a, active_length-1, permutation_list);
    }
  }
}

template <typename T>
std::vector<std::vector<T>> all_permutations(std::vector<T> A) {
  std::vector<std::vector<T>> res;
  int active_length = A.size();

  // hier wird recursive_permutation_helper aufgerufen
  recursive_permutation_helper(A, active_length, res);
  return res;
}



void print_vector(std::vector<int> const &v) {
  std::cout << "(";
  for (size_t i = 0; i < v.size()-1; i++)
    {
      std::cout << v[i] << ", ";
    }
    std::cout << v[v.size()-1] << ")" << std::endl;
}

void print_matrix(std::vector<std::vector<int>> const &M) {
  for (size_t i = 0; i < M.size(); i++)
  {
    print_vector(M[i]);
  }
  std::cout << std::endl;
}



int main() {
  // AUFGABE 6
  std::vector<int> nodes_g1;
  std::vector<std::pair<int, int>> edges_g1;
  load_graph("graph_1.txt", nodes_g1, edges_g1);

  std::vector<int> nodes_g2;
  std::vector<std::pair<int, int>> edges_g2;
  load_graph("graph_2.txt", nodes_g2, edges_g2);

  std::vector<int> nodes_g3;
  std::vector<std::pair<int, int>> edges_g3;
  load_graph("graph_3.txt", nodes_g3, edges_g3);


  std::vector<std::vector<int>> adjazenz_g1 = kanten_zu_adjazenzmatrix(edges_g1, nodes_g1);
  std::vector<std::vector<int>> adjazenz_g2 = kanten_zu_adjazenzmatrix(edges_g2, nodes_g2);
  std::vector<std::vector<int>> adjazenz_g3 = kanten_zu_adjazenzmatrix(edges_g3, nodes_g3);

  std::vector<std::vector<int>> permutations = all_permutations(vector_of_indices(nodes_g1.size()));


  std::cout << "\nIsomorphe Graphen-Paare:" << std::endl;
  for (size_t i = 0; i < permutations.size(); i++)
  {
    std::vector<std::vector<int>> permuted_adjazenz_g1 = permute_matrix(kanten_zu_adjazenzmatrix(edges_g1, nodes_g1), permutations[i]);
    std::vector<std::vector<int>> permuted_adjazenz_g2 = permute_matrix(kanten_zu_adjazenzmatrix(edges_g2, nodes_g2), permutations[i]);
    std::vector<std::vector<int>> permuted_adjazenz_g3 = permute_matrix(kanten_zu_adjazenzmatrix(edges_g3, nodes_g3), permutations[i]);
    
    if (matrix_gleichheit(adjazenz_g1, permuted_adjazenz_g2) && matrix_gleichheit(adjazenz_g2, permuted_adjazenz_g1)) {
      std::cout << "G1 und G2 sind isomorph - mit folgender Permutation: "; print_vector(permutations[i]);
    }
    if (matrix_gleichheit(adjazenz_g1, permuted_adjazenz_g3) && matrix_gleichheit(adjazenz_g3, permuted_adjazenz_g1)) {
      std::cout << "G1 und G3 sind isomorph - mit folgender Permutation: "; print_vector(permutations[i]);
    }
    if (matrix_gleichheit(adjazenz_g2, permuted_adjazenz_g3) && matrix_gleichheit(adjazenz_g3, permuted_adjazenz_g2)) {
      std::cout << "G2 und G3 sind isomorph - mit folgender Permutation: "; print_vector(permutations[i]);
    }
  }
  std::cout << std::endl;
}

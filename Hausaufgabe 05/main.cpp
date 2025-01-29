#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

/**
 * Nimmt einen Datei-Namen als std::string als input an. Dieser bezeichnet das
 * Input-Datei. Als In-Out Parameter nimmt diese Funktion:
 *  - eine std::vector<int> für die Labels der Knoten
 *  - eine std::vector<int> für die Labels der Kanten
 *  - eine std::vector<int> für die Kanten.
 *       Jede Paar von Indizes (a, b) ist eine Kante zwischen Knoten a -> b.
 * Ein Beispiel für das Input-Datei ist:
 *
 *   4
 *   5 7 9 11
 *   4
 *   1 2 3  1 3 4  3 4 1  2 3 2
 *
 * Dieses Beispiel-Input bezeichnet einen Graph mit:
 *  - 4 Knoten, mit Labels 5, 7, 9, und 11
 *  - 4 Kanten:
 *    - Knoten #1 -> Knoten #2, mit Label 3
 *    - Knoten #1 -> Knoten #3, mit Label 4
 *    - Knoten #3 -> Knoten #4, mit Label 1
 *    - Knoten #2 -> Knoten #3, mit Label 2
 *
 */
void load_graph(std::string const &filename, std::vector<int> &vtx_labels,
                std::vector<int> &edge_labels, std::vector<int> &edge_list) {
  std::ifstream graph_in(filename);
  int n_objs_to_read;
  graph_in >> n_objs_to_read;
  vtx_labels = std::vector<int>(n_objs_to_read);
  for (int i = 0; i < vtx_labels.size(); i++) {
    graph_in >> vtx_labels[i];
  }

  graph_in >> n_objs_to_read;
  edge_labels = std::vector<int>(n_objs_to_read);
  edge_list = std::vector<int>(2 * n_objs_to_read);
  for (size_t i = 0; i < edge_labels.size(); i++) {
    graph_in >> edge_list[2 * i];
    graph_in >> edge_list[2 * i + 1];
    graph_in >> edge_labels[i];
  }

  assert(edge_list.size() == 2 * edge_labels.size());
}

/**
 * Nimmt eine Knoten-Liste als std::vector<int>,
 *  eine Kanten-Label-Liste als std::vector<int>, und
 *  eine Kanten-Liste als std::vector<int> an und generiert eine
 *  Datei in GraphViz DOT Format.
 *
 * Die Kanten-Liste ist eine Liste von Integern, die als Paare interepretiert
 * werden. Jedes Paar (a, b) bezeichnet eine Kante zwischen Knoten a und b.
 */
void graph_to_dot(const std::vector<int> &vtx_labels,
                  const std::vector<int> &edge_labels,
                  const std::vector<int> &edges) {
  assert(edges.size() == 2 * edge_labels.size());
  std::ofstream o("graph.dot");
  o << "digraph finite_state_machine { rankdir=LR; ";
  for (int i = 0; i < vtx_labels.size(); i++) {
    o << vtx_labels[i] << ";";
  }
  for (int i = 0; i < edge_labels.size(); i++) {
    o << "\n " << vtx_labels[edges[2 * i]] << " -> "
      << vtx_labels[edges[2 * i + 1]];
    o << " [label=" << edge_labels[i] << "];";
  }
  o << "}";
}

/**
 * @brief Berechnet a·b = Σ a_i*b_i.
 * @param a Ein @c std::vector<int>
 * @param b Ein @c std::vector<int>
 * @returns Die Dot-Produkt zwischen @c a und @c b .
 */
int dot_product(std::vector<int> const &a, std::vector<int> const &b) {
  assert(a.size() == b.size());

  // AUFGABE 2: DIESE FUNKTION MUSS VOLLSTÄNDIGT WERDEN!
  int sum = 0;
  for (int i = 0; i < a.size(); i++) {
    sum += a[i] * b[i];
  }
  return sum;
  //
}

/**
 * @brief Extrahiert eine Spalte von einer @c M x @c N Matrix.
 * @param[in] col Der Index der Spalte, die extrahiert wird.
 * @param[in] mat Die Matrix, aus der die Spalte extrahiert wird.
 * @param[in] M Die Anzahl der Zeilen in @c mat
 * @param[in] N Die Anzahl der Spalten in @c mat
 * @returns @c std::vector<int>: Ergibt einen std::vector<int>, die die gleiche
 * Werte der @c col -te Spalte in @c mat enthält.
 */
std::vector<int> extract_column(int col, std::vector<int> const &mat, int M, int N) {
  assert(mat.size() == M * N);

  // AUFGABE 2: DIESE FUNKTION MUSS VOLLSTÄNDIGT WERDEN!
  std::vector<int> column_vector(M, 0);
  for (int i = 0; i < M; i++) {
    column_vector[i] = mat[i*N + col];
  }
  return column_vector;
  //
}

/**
 * @brief Extrahiert eine Zeile von einer @c M x @c N Matrix.
 * @param[in] row Der Index der Zeile, die extrahiert wird.
 * @param[in] mat Die Matrix, aus der die Zeile extrahiert wird.
 * @param[in] M Die Anzahl der Zeilen in @c mat
 * @param[in] N Die Anzahl der Spalten in @c mat
 * @returns @c std::vector<int>: Gibt einen std::vector<int>, die die gleiche
 * Werte der @c row -te Zeile in @c mat enthält.
 */
std::vector<int> extract_row(int row, std::vector<int> const &mat, int M,
                             int N) {
  assert(mat.size() == M * N);

  // AUFGABE 2: DIESE FUNKTION MUSS VOLLSTÄNDIGT WERDEN!
  std::vector<int> row_vector(N, 0);
  for (int i = 0; i < N; i++) {
    row_vector[i] = mat[row*N + i];
  }
  return row_vector;
  //
}

/**
 *@brief Multiplizert zwei Matrizen.
 * @param[in] A Eine Matrix der Größe @c M x @c N
 * @param[in] M Die Anzahl der Zeilen in @c A
 * @param[in] N Die Anzahl der Spalten in @c A
 * @param[in] B Eine Matrix der Größe @c P x @c Q
 * @param[in] P Die Anzahl der Zeilen in @c B. Diese muss gleich N sein.
 * @param[in] Q Die Anzahl der Spalten in @c B
 * @returns Eine @c M x @c Q Matrix die genau @c AB entspricht.
 */
std::vector<int> matrix_matrix_product(std::vector<int> const &A, int M, int N, std::vector<int> const &B, int P, int Q) {
  assert(N == P);

  // AUFGABE 2: DIESE FUNKTION MUSS VOLLSTÄNDIGT WERDEN!
  std::vector<int> matrix_matrix(A.size(), 0);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < Q; j++) {
      matrix_matrix[i * N + j] = dot_product(extract_row(i, A, M, N), extract_column(j, B, P ,Q));
    }
  }
  return matrix_matrix;
  //
}

int main() {
  // Wir deklarieren die Nötigen Vektoren um einen Graph zu laden.
  std::vector<int> vtx_labels, edge_labels, edges;
  // Dann lesen wir den Graph in my_graph.txt aus
  //   und generieren wir die .dot Datei
  // Das ist nur zum Prüfen, ob die Adjacency-Matrix stimmt.
  load_graph("my_graph.txt", vtx_labels, edge_labels, edges);
  graph_to_dot(vtx_labels, edge_labels, edges);
  

  // ??? aufgabe 1
  size_t n_vtcs = vtx_labels.size();
  std::vector<int> adjacency(n_vtcs * n_vtcs);

  assert(edges.size() % 2 == 0);
  int n_vertices = vtx_labels.size();
  int n_edges = edges.size() / 2;

  for (int i = 0; i < n_edges; i++) {
    int src = edges[2 * i];
    int end = edges[2 * i + 1];
    adjacency[n_vertices * src + end] = 1;
  }
  

  // Aufgabe 1:
  //   Deklarieren Sie die Adjacency-Matrix als std::vector<int>
  //     und füllen Sie die wie in der Übung beschrieben ein.
  std::ifstream infile("my_graph.txt");
  int size;
  infile >> size;

  std::vector<int> vertices(size);
  for (int i = 0; i < size; i++){
    infile >> vertices[i];
  }

  int amount_edges;
  infile >> amount_edges;

  std::vector<int> e(amount_edges*2);
  std::vector<int> edg(amount_edges);

  for (int i = 0; i < amount_edges; i++){
    infile >> e[i*2];
    infile >> e[i*2+1];
    infile >> edg[i];
  }
  
  std::vector<int> adjacency_matrix(size * size);
  for (int i = 0; i < e.size(); i += 2) {
      adjacency_matrix[size * e[i] + e[i+1]] = 1;
  }
  
  // ausgabe der matrix
  for (int i = 0; i < adjacency_matrix.size(); i++) {
    if (!(i % 8)) {
      std::cout << std::endl;
    }
    std::cout << adjacency_matrix[i] << "  ";
  }
  std::cout << std::endl << std::endl;

  std::vector<int> step_2_matrix(adjacency_matrix.size(), 0);
  step_2_matrix = matrix_matrix_product(adjacency_matrix, size, size, adjacency_matrix, size, size);

  std::vector<int> step_3_matrix(adjacency_matrix.size(), 0);
  step_3_matrix = matrix_matrix_product(step_2_matrix, size, size, adjacency_matrix, size, size);

  for (int i = 0; i < size; i++) {
    if (step_3_matrix[i*size + i] > 0) {
      std::cout << "Knoten: " << vertices[i] << "\tEs existieret mindestens ein Weg um mit 3 Schritten wieder am Knoten anzukommen!" << std::endl;
    }
  }

  /*
  std::cout << std::endl << std::endl;

  for (int i = 0; i < step_2_matrix.size(); i++) {
    if (!(i % 8)) {
      std::cout << std::endl;
    }
    std::cout << step_2_matrix[i] << "  ";
  }
  
  std::cout << std::endl << std::endl;

  for (int i = 0; i < step_3_matrix.size(); i++) {
    if (!(i % 8)) {
      std::cout << std::endl;
    }
    std::cout << step_3_matrix[i] << "  ";
  }
  */

  
  // Aufgabe 2:
  //   Ergänzen Sie die Funktionen extract_colum, extract_row,
  //     dot_product, und matrix_matrix_product.
  //   Matrix-Matrix Produkt braucht die anderen.

  // Aufgabe 3:
  //   Es gibt eine Beziehung zwischen A*A und mögliche verbindungen zwischen
  //     Knoten. Diese Beziehung geht weiter -- A*A*A hat auch eine Bedeutung.
  //   Geben Sie die Knoten-Labels, die eine Verbindung nach DREI schritten zu
  //   sich selbst haben, auf den Terminal aus.

  return 0;
}
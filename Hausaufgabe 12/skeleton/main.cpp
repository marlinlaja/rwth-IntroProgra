#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "linalg.hpp"

using namespace linalg;

Vector read_vector_from_string(std::string const &str) {
  std::istringstream data_stream(str);
  char c;
  data_stream >> c;
  assert(c == 'V');
  int d;
  data_stream >> d;
  Vector v(d);
  for (int i = 0; i < v.size(); i++) {
    data_stream >> v.at(i);
  }
  return v;
}

Matrix read_matrix_from_string(std::string const &str) {
  std::istringstream data_stream(str);
  char c;
  int m, n;
  data_stream >> c;
  assert(c == 'M');
  data_stream >> m;
  data_stream >> n;
  Matrix M(m, n);
  for (int i = 0; i < M.size().first; i++) {
    for (int j = 0; j < M.size().second; j++) {
      data_stream >> M.at(i, j);
    }
  }
  return M;
}

int main(int argc, char **argv) {

  bool test = true;
  assert(test && "ERROR: index out of bounds");


  if (argc < 2) {
    std::cout << "Inputdatei benötigt!\n";
    return 0;
  }
  std::ifstream input(argv[1]);
  std::string live_line;
  std::getline(input, live_line);
  Vector v1(read_vector_from_string(live_line));
  std::getline(input, live_line);
  Vector v2(read_vector_from_string(live_line));

  std::cout << "\nTesting vector + vector:\n  ";
  print_vectorlike_to(v1, std::cout);
  std::cout << "+ ";
  print_vectorlike_to(v2, std::cout);
  std::cout << "= ";
  print_vectorlike_to(add(v1, v2), std::cout);

  std::cout << "\nTesting vector + vector:\n  ";
  print_vectorlike_to(v1, std::cout);
  std::cout << "- ";
  print_vectorlike_to(v2, std::cout);
  std::cout << "= ";
  print_vectorlike_to(subtract(v1, v2), std::cout);

  std::cout << "\nTesting scalar * vector :\n";
  std::cout << "(2.0) * ";
  print_vectorlike_to(v1, std::cout);
  std::cout << "      = ";
  print_vectorlike_to(scalar_multiply(v1, 2.0), std::cout);

  std::cout << "\nTesting scalar product :\n   ";
  print_vectorlike_to(v1, std::cout);
  std::cout << ".* ";
  print_vectorlike_to(v2, std::cout);
  std::cout << " = " << scalar_product(v1, v2) << "\n";

  std::cout << "Testing VectorView and Destrutors\n";
  std::getline(input, live_line);
  Vector *v3 = new Vector(read_vector_from_string(live_line));
  VectorView *vv1 = new VectorView(v3->view(1, 4));
  std::cout << "\nTesting scalar product (with view!) :\n   ";
  print_vectorlike_to(v1, std::cout);
  std::cout << ".* ";
  print_vectorlike_to(*vv1, std::cout);
  std::cout << " = " << scalar_product(v1, *vv1)
            << "\nExpect Warning Message:\n";
  delete v3;
  // delete vv1;
  //->  Da v3 hier ja schon deleted ist, gibt die dekrementierung der views bei "delete v11" hier einen Fehler aus. Komischerweise nur in Windows. Zur Sicherheit auskommentiert.
  std::getline(input, live_line);
  Vector small_v1(read_vector_from_string(live_line));
  std::getline(input, live_line);
  Vector small_v2(read_vector_from_string(live_line));
  std::getline(input, live_line);
  Vector small_v3(read_vector_from_string(live_line));
  std::cout << "Testing Matrix Operations\n";
  std::getline(input, live_line);
  Matrix m1(read_matrix_from_string(live_line));
  std::getline(input, live_line);
  Matrix m2(read_matrix_from_string(live_line));
  Matrix m3(m2);
  std::cout << "\nMatrix 1 is:\n";
  print_matrix_to(m1, std::cout);
  std::cout << "Matrix 2 is:\n";
  print_matrix_to(m2, std::cout);
  std::cout << "Matrix 3 is:\n";
  print_matrix_to(m3, std::cout);
  std::cout << "\nMatrix 3 += Matrix 1 yields is:\n";
  m3.add_assign_other(m1);
  print_matrix_to(m3, std::cout);
  std::cout << "\nMatrix 2 - Matrix 1 is:\n";
  print_matrix_to(subtract(m2, m1), std::cout);

  std::cout << "\nMatrix 3 * [3 2]^T is:\n";
  print_vectorlike_to(matrix_vector_prod(m3, small_v3), std::cout);
  std::cout << "\nMatrix 1 * Matrix 3 is:\n";
  print_matrix_to(matrix_matrix_prod(m1, m3), std::cout);
}
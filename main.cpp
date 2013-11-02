#include <iostream>
#include "matrix.h"
#include "matrix_discretization.h"
#include "gauss.h"
#include "test.h"

int main(int argc, char** argv)
{
  const int size = 10;
  Matrix<double> matr(size);
  double v[size];
  for (int i = 0; i < size; ++i) {
    v[i] = mf::ucheb(size - 1, mf::uchebNodes<double>(size + 1, i + 1));
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
  discretize(matr, 10);
  gaussScheme(matr, v, size);
  for (int i = 0; i < size; ++i) {
    std::cout << v[i] << " ";
  }
}

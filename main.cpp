#include <iostream>
#include "matrix.h"
#include "gauss.h"
#include "test.h"
#include "discretization.h"
#include "e_core.h"


int main(int argc, char** argv)
{
  crv::Line line({1,1},{2,2});
  std::vector<crv::DiscretizeCurve> curves;
  curves.emplace_back(line, 20, mth::tchebNodes<tps::real>);
  MatrixDiscretization md(curves, 2);
  mtrx::Matrix<tps::complex> matr(md.dimension());
  md.discretize(matr, matr.width(), epl::mdoCore);
  /*const int size = 100;
  mtrx::Matrix<std::complex<double>> matr(size);
  std::complex<double> v[size];
  for (int i = 0; i < size; ++i) {
    v[i] = mth::ucheb(size - 1, mth::uchebNodes<double>(size + 1, i + 1));
    //std::cout << v[i] << " ";
  }
  std::cout << std::endl;
  //discretize(matr, 10);
  std::vector<crv::CurveForDiscretize> cs;
  cs.emplace_back(crv::Line({-1,-1},{1,1}), size);
  hpl::discretize(cs, matr, size);
  gaussScheme(matr, v, size);
  for (int i = 0; i < size; ++i) {
   // std::cout << v[i] << " ";
  }*/



}

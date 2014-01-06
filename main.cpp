#include <iostream>
#include <fstream>
#include "matrix.h"
#include "gauss.h"
#include "test.h"
#include "discretization.h"
#include "e_core.h"
#include "field.h"
#include "field_solver.h"

template <class charT, charT sep>
class punct_facet: public std::numpunct<charT> {
protected:
    charT do_decimal_point() const { return sep; }
};

int main(int argc, char** argv)
{
  crv::Line line({0,1.5},{0,-1.5});
  crv::Line line1({0,-2.5},{0,-3.5});
  crv::Line line2({0,2.5},{0,3.5});
  tps::real wavenumber = 0.69813170079773183076947630739545;
  fld::EPolarizationField field(wavenumber,0);
  std::vector<crv::DiscretizeCurve> curves;
  curves.emplace_back(line, 40, mth::tchebNodes<tps::real>);
  curves.emplace_back(line1, 40, mth::tchebNodes<tps::real>);
  curves.emplace_back(line2, 40, mth::tchebNodes<tps::real>);

  Discretization md(curves, field.clone());
  mtrx::Matrix<tps::complex> matr(md.dimension());
  std::vector<tps::complex> vec(md.dimension());
  md.discretize(matr, matr.width(), epl::mdoCore);
  md.discretize(vec, vec.size());

  gaussScheme(matr,vec,vec.size());

  std::vector<std::vector<std::complex<double>>> currents;
    size_t p = 0;
    for (size_t i = 0; i < curves.size(); i++) {
      std::vector<std::complex<double>>* current =
          new std::vector<std::complex<double>>(curves[i].size());
      for (size_t j = 0; j < curves[i].size(); j++, p++) {
        (*current)[j] = (vec)[p];
      }
      currents.push_back(*current);
    }

    FieldSolver f(curves, currents, wavenumber);
    std::ofstream fout("result.csv");
    for (int i = 0; i < 360; i+=1)
      fout << i<< ";";
    fout <<std::endl;
    fout.imbue(std::locale(fout.getloc(), new punct_facet<char, ','>));
    for (int i = 0; i < 360; i+=1){
      //std::cout <<std::endl<<f.farField(i);

      fout << std::abs(f.farField(i*M_PI/180))<< ";";
    }
    fout.close();

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

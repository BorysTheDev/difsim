#include "discretization.h"

using namespace tps;


MatrixDiscretization::MatrixDiscretization(const DCList& sCurves, real wn)
  : waveNumber(wn), curves(sCurves),  size(0)
{
  for (size_t i = 0; i < sCurves.size(); i++) {
    borders[i].left = size;
    size += sCurves[i].size();
    borders[i].right = size;
  }
  cntr.changeBorder({size});
}





/*
void MatrixDiscretization::fillMatrixBlock(Matrix<tps::complex>& matr,
                                     size_t i, size_t j, const crv::DiscretizeCurve& c1,
                                     const crv::DiscretizeCurve& c2, tps::real waveNumber) {
  if (i != j) {
    //not diagonal blocks
    for (size_t ii = 0; ii < c1.size(); ii++) {
      for (size_t jj = 0; jj < c2.size(); jj++) {
        matr[i + ii][j + jj] = (M_PI / c2.size())
            * h2(waveNumber * dist(c1[ii] ,c2[jj]));
      }
    }
  } else {
    //diagonal block
    for (size_t ii = 0; ii < c1.size(); ii++) {
      for (size_t jj = 0; jj < c1.size(); jj++) {
        tps::complex temp = ii != jj ? h2(waveNumber * dist(c1[ii], c2[jj]))
                                       - epol::asymp(c1[ii].t, c1[jj].t) : epol::lim(c1[ii].d, waveNumber);
        matr[i + ii][j + jj] = (M_PI / c1.size())
            * (temp - tps::complex(0, 2) * epol::Ln(c1[ii].t, c1[jj].t, c1.size())
               / M_PI);
      }
    }
  }
}*/

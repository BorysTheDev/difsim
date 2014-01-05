#ifndef DISCRETIZATION_H_
#define DISCRETIZATION_H_

#include "discretize_curve.h"
#include "types.h"
#include "counter.h"
#include "iostream"

class MatrixDiscretization {
  typedef std::vector<crv::DiscretizeCurve> DCList;

public:
  MatrixDiscretization(const DCList& sCurves, tps::real wn);
  size_t dimension() {return size;}

  template<class Matrix, class Core>
  Matrix& discretize(Matrix&, int, Core&);

private:
  //-----parameters--------------------------
  tps::real waveNumber;
  const DCList& curves;
  //-----types-------------------------------
  typedef utl::Counter<2> Cntr;
  //TODO check maybe left border is enough
  struct Border{ int left, right; };
  //-----auxiliary parameters----------------
  int size;
  Cntr cntr;
  std::vector<Border> borders;
  //-----auxiliary class---------------------
  template<class Matrix, class Core>
  class BlockDiscretizator
  {
  public:
    BlockDiscretizator(MatrixDiscretization& md, Matrix& m, Core& c)
      : md(md), mtrx(m), core(c) {}
    void discretize();

  private:
    Cntr::array curBlock;
    MatrixDiscretization& md;
    Matrix& mtrx;
    Core& core;

    void discretizeBlockLine(int line);
  };
};

template<class Matrix, class Core>
Matrix& MatrixDiscretization::discretize(Matrix& matr, int dim, Core& core) {
  if (dim != size) throw std::logic_error("dimensions are different!");
  BlockDiscretizator<Matrix, Core> discretizator(*this, matr, core);
  discretizator.discretize();
  return matr;
}

template<class Matrix, class Core>
void MatrixDiscretization::BlockDiscretizator<Matrix, Core>::discretize() {
  for(curBlock = md.cntr++; curBlock[1] < (int)md.curves.size(); curBlock = md.cntr++)
  {
    //std::cout<<curBlock[0]<< " - " << curBlock[1] << std::endl;
    for (int i = 0; i < md.curves[curBlock[0]].size(); i++)
      discretizeBlockLine(i);
  }
}

template<class Matrix, class Core>
void MatrixDiscretization::BlockDiscretizator<Matrix, Core>::discretizeBlockLine(int i)
{
  Border& bl = md.borders[curBlock[0]];
  Border& bc = md.borders[curBlock[1]];
  const crv::DiscretizeCurve& c1 = md.curves[curBlock[0]];
  const crv::DiscretizeCurve& c2 = md.curves[curBlock[1]];
  for (int j = 0; j < md.curves[curBlock[1]].size(); j++){
    mtrx[bl.left + i][bc.left + j] = core(c1[i], c2[j],
                                          &c1 == &c2, c2.size(), md.waveNumber);
  }
}


#endif /* DISCRETIZATION_H_ */

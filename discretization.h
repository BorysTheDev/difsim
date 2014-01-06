#ifndef DISCRETIZATION_H_
#define DISCRETIZATION_H_

#include "discretize_curve.h"
#include "field.h"
#include "types.h"
#include "counter.h"
#include "iostream"

class Discretization {
  typedef std::vector<crv::DiscretizeCurve> DCList;
  typedef fld::IncidentField::FieldPtr FieldPtr;
public:
  Discretization(const DCList& sCurves, FieldPtr field);
  size_t dimension() {return size;}

  template<class Matrix, class Core>
  Matrix& discretize(Matrix&, int dim, Core&);

  template<class Vector>
  Vector& discretize(Vector&, int dim);

private:
  //-----parameters--------------------------
  FieldPtr field;
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
    BlockDiscretizator(Discretization& md, Matrix& m, Core& c)
      : md(md), mtrx(m), core(c) {}
    void discretize();

  private:
    Cntr::array curBlock;
    Discretization& md;
    Matrix& mtrx;
    Core& core;

    void discretizeBlockLine(int line);
  };
};

template<class Matrix, class Core>
Matrix& Discretization::discretize(Matrix& matr, int dim, Core& core)
{
  if (dim < size) throw std::logic_error("dimensions are different!");
  BlockDiscretizator<Matrix, Core> discretizator(*this, matr, core);
  discretizator.discretize();
  return matr;
}

template<class Vector>
Vector& Discretization::discretize(Vector& f, int dim)
{
  if (dim < size) throw std::logic_error("dimensions are different!");
  int ii = 0;
  for (size_t i = 0; i < curves.size(); i++) {
    for (size_t j = 0; j < curves[i].size(); j++, ii++)
      f[ii] = -(*field)(curves[i][j].x, curves[i][j].y);
  }
  return f;
}

template<class Matrix, class Core>
void Discretization::BlockDiscretizator<Matrix, Core>::discretize()
{
  for(curBlock = md.cntr++; curBlock[1] < (int)md.curves.size(); curBlock = md.cntr++)
  {
    //std::cout<<curBlock[0]<< " - " << curBlock[1] << std::endl;
    for (int i = 0; i < md.curves[curBlock[0]].size(); i++)
      discretizeBlockLine(i);
  }
}

template<class Matrix, class Core>
void Discretization::BlockDiscretizator<Matrix, Core>::discretizeBlockLine(int i)
{
  Border& bl = md.borders[curBlock[0]];
  Border& bc = md.borders[curBlock[1]];
  const crv::DiscretizeCurve& c1 = md.curves[curBlock[0]];
  const crv::DiscretizeCurve& c2 = md.curves[curBlock[1]];
  for (int j = 0; j < md.curves[curBlock[1]].size(); j++){
    mtrx[bl.left + i][bc.left + j] =
        core(c1[i], c2[j], &c1 == &c2, c2.size(), md.field->waveNumber());
  }
}


#endif /* DISCRETIZATION_H_ */

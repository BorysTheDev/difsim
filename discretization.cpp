#include "discretization.h"

using namespace tps;


MatrixDiscretization::MatrixDiscretization(const DCList& sCurves, real wn)
  : waveNumber(wn), curves(sCurves), size(0), borders(curves.size())
{
  for (size_t i = 0; i < sCurves.size(); i++) {
    borders[i].left = size;
    size += sCurves[i].size();
    borders[i].right = size;
  }
  cntr.changeBorder({(int)curves.size()});
}


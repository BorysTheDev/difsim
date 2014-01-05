#include "discretization.h"

using namespace tps;


Discretization::Discretization(const DCList& sCurves, FieldPtr field)
  : field(field), curves(sCurves), size(0), borders(curves.size())
{
  for (size_t i = 0; i < sCurves.size(); i++) {
    borders[i].left = size;
    size += sCurves[i].size();
    borders[i].right = size;
  }
  cntr.changeBorder({(int)curves.size()});
}


#include "field.h"
namespace fld
{

IncidentField::IncidentField(tps::real waveNumber, tps::real alpha)
  : waveNumber_(waveNumber), alpha_(alpha)
{
}

EPolarizationField::EPolarizationField(tps::real wn, tps::real alpha)
  : IncidentField(wn, alpha)
{

}

tps::complex
EPolarizationField::operator()(tps::real x1, tps::real x2) const
{
  tps::real expArg = (x1 * cos(alpha()) + x2 * sin(alpha())
                      ) * waveNumber();
  return exp(tps::complex(0, -expArg));
}



ProtoPtr<IncidentField> EPolarizationField::clone() const
{
  return new EPolarizationField(waveNumber(), alpha());
}



}

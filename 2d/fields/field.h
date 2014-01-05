#ifndef INCIDENT_FIELD_H_
#define INCIDENT_FIELD_H_
#include <vector>
#include "types.h"
#include "prototype.h"

namespace fld
{
class IncidentField : public Prototype<IncidentField>
{
public:
  typedef ProtoPtr<IncidentField> FieldPtr;

  IncidentField(tps::real waveNumber, tps::real alpha);

  virtual tps::complex operator()(tps::real x1, tps::real x2) const = 0;

  tps::real waveNumber() const {return waveNumber_;}
  tps::real alpha()      const {return alpha_;}

  void setWaveNumber(tps::real wn) {waveNumber_ = wn;}
  void setAlpha(tps::real alpha)   {alpha_ = alpha;}

  virtual ~IncidentField() = default;

protected:
  tps::real waveNumber_;
  tps::real alpha_;
};

//TODO
class FieldsPackage : public IncidentField
{
  FieldsPackage(tps::real wn, tps::real alpha)
    : IncidentField(wn, alpha) {}

private:
  std::vector<FieldPtr> fields;
};


class EPolarizationField: public IncidentField
{
public:
  EPolarizationField(tps::real wn, tps::real alpha);

  tps::complex operator()(tps::real x1, tps::real x2)const override;

  ProtoPtr<IncidentField> clone() const override;
};

}

#endif /* INCIDENT_FIELD_H_ */

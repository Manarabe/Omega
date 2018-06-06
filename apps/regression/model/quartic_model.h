#ifndef REGRESSION_QUARTIC_MODEL_H
#define REGRESSION_QUARTIC_MODEL_H

#include "model.h"
#include <poincare/expression_layout.h>

namespace Regression {

class QuarticModel : public Model {
public:
  using Model::Model;
  static Poincare::ExpressionLayout * Layout();
  double evaluate(double * modelCoefficients, double x) const override;
  double partialDerivate(double * modelCoefficients, int derivateCoefficientIndex, double x) const override;
  double numberOfCoefficients() const override { return 5; }
};

}


#endif
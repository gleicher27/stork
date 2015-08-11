/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "NeutronicSource.h"

/**
 * This function defines the valid parameters for
 * this Kernel and their default values
 */
template<>
InputParameters validParams<NeutronicSource>()
{
  InputParameters params = validParams<EigenKernel>();
  return params;
}


NeutronicSource::NeutronicSource(const InputParameters & parameters) :
    EigenKernel(parameters),
    _nu_sigma_f_xs(getMaterialProperty<Real>("nu_sigma_f_g0"))
{}

Real
NeutronicSource::computeQpResidual()
{
  return -_nu_sigma_f_xs[_qp]*_test[_i][_qp]*_u[_qp];
}

Real
NeutronicSource::computeQpJacobian()
{
  return -_nu_sigma_f_xs[_qp]*_phi[_j][_qp]*_test[_i][_qp];
}

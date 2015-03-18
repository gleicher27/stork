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

#include "NeutronicRemoval.h"

/**
 * This function defines the valid parameters for
 * this Kernel and their default values
 */
template<>
InputParameters validParams<NeutronicRemoval>()
{
  InputParameters params = validParams<Reaction>();
  return params;
}


NeutronicRemoval::NeutronicRemoval(const std::string & name,
                                   InputParameters parameters) :
    Reaction(name,parameters),
    _absorption_xs(getMaterialProperty<Real>("absorption_xs_g0"))
{}

Real
NeutronicRemoval::computeQpResidual()
{
  // We're dereferencing the _diffusivity pointer to get to the
  // material properties vector... which gives us one property
  // value per quadrature point.

  // Also... we're reusing the Removal Kernel's residual
  // so that we don't have to recode that.
  return _absorption_xs[_qp]*Reaction::computeQpResidual();
}

Real
NeutronicRemoval::computeQpJacobian()
{
  // We're dereferencing the _diffusivity pointer to get to the
  // material properties vector... which gives us one property
  // value per quadrature point.

  // Also... we're reusing the Removal Kernel's residual
  // so that we don't have to recode that.
  return _absorption_xs[_qp]*Reaction::computeQpJacobian();
}

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

#include "DiffusionNeutronicsMaterial.h"

template<>
InputParameters validParams<DiffusionNeutronicsMaterial>()
{
  InputParameters params = validParams<Material>();

  // Vectors for Linear Interpolation
  params.addParam<Real>("diffusion_coef",1.0,"The diffusion coefficient");
  params.addParam<Real>("sigma_abs",1.0,"The absorption coefficient");
  params.addParam<Real>("nusigma_xs",1.0,"The multiplication coefficient");
  return params;
}

DiffusionNeutronicsMaterial::DiffusionNeutronicsMaterial(const InputParameters & parameters) :
    Material(parameters),
    _diffusion_coef_value(getParam<Real>("diffusion_coef")),
    _sigma_a_xs(getParam<Real>("sigma_abs")),
    _nu_sigma_f_xs(getParam<Real>("nusigma_xs")),
    _diffusion_coef(declareProperty<Real>("diffusion_coef_g0")),
    _absorption_xs(declareProperty<Real>("absorption_xs_g0")),
    _nu_sigma_f(declareProperty<Real>("nu_sigma_f_g0"))
{}

void
DiffusionNeutronicsMaterial::computeQpProperties()
{
  // We will compute the diffusivity based on the Linear Interpolation of the provided vectors in the z-direction
  _diffusion_coef[_qp] = _diffusion_coef_value;
  _absorption_xs[_qp] = _sigma_a_xs;
  _nu_sigma_f[_qp] = _nu_sigma_f_xs;

}

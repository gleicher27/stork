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

#ifndef DIFFUSIONNEUTRONICSMATERIAL_H
#define DIFFUSIONNEUTRONICSMATERIAL_H

#include "Material.h"

//Forward Declarations
class DiffusionNeutronicsMaterial;

template<>
InputParameters validParams<DiffusionNeutronicsMaterial>();

/**
 * DiffusionNeutronic material class that defines a few properties.
 */
class DiffusionNeutronicsMaterial : public Material
{
public:
  DiffusionNeutronicsMaterial(const std::string & name,
                  InputParameters parameters);

protected:
  virtual void computeQpProperties();

private:
  Real _diffusion_coef_value;
  Real _sigma_a_xs;
  Real _nu_sigma_f_xs;

  /**
   * This is the member reference that will hold the computed values
   * for the Real value property in this class.
   */
  MaterialProperty<Real> & _diffusion_coef;
  MaterialProperty<Real> & _absorption_xs;
  MaterialProperty<Real> & _nu_sigma_f;

};

#endif //DIFFUSIONNEUTRONICSMATERIAL_H

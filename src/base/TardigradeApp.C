#include "TardigradeApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

#include "DiffusionNeutronicsMaterial.h"
#include "NeutronicRemoval.h"
#include "NeutronicDiffusion.h"
#include "NeutronicSource.h"

template<>
InputParameters validParams<TardigradeApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  return params;
}

TardigradeApp::TardigradeApp(const std::string & name, InputParameters parameters) :
    MooseApp(name, parameters)
{
  srand(processor_id());

  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  TardigradeApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  TardigradeApp::associateSyntax(_syntax, _action_factory);
}

TardigradeApp::~TardigradeApp()
{
}

extern "C" void TardigradeApp__registerApps() { TardigradeApp::registerApps(); }
void
TardigradeApp::registerApps()
{
  registerApp(TardigradeApp);
}

void
TardigradeApp::registerObjects(Factory & factory)
{
  
  registerMaterial(DiffusionNeutronicsMaterial);
  registerKernel(NeutronicDiffusion);
  registerKernel(NeutronicRemoval);
  registerKernel(NeutronicSource);
}

void
TardigradeApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}

[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 200
  ny = 10
  xmax = 0.304 # Length of test chamber
  ymax = 0.0257 # Test chamber radius
[]

[Variables]
  [./pressure]
  [../]
  [./temp]
    initial_condition = 300 # Start at room temperature
  [../]
[]

[AuxVariables]
  [./velocity_x]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./velocity_y]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./velocity_z]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[Kernels]
  [./darcy_pressure]
    type = DarcyPressure
    variable = pressure
  [../]
  [./heat_conduction]
    type = HeatConduction
    variable = temp
  [../]
  [./heat_conduction_time_derivative]
    type = HeatConductionTimeDerivative
    variable = temp
  [../]
  [./heat_convection]
    type = DarcyConvection
    variable = temp
    darcy_pressure = pressure
  [../]
[]

[AuxKernels]
  [./velocity_x]
    type = DarcyVelocity
    variable = velocity_x
    component = x
    execute_on = timestep_end
    darcy_pressure = pressure
  [../]
  [./velocity_y]
    type = DarcyVelocity
    variable = velocity_y
    component = y
    execute_on = timestep_end
    darcy_pressure = pressure
  [../]
  [./velocity_z]
    type = DarcyVelocity
    variable = velocity_z
    component = z
    execute_on = timestep_end
    darcy_pressure = pressure
  [../]
[]

[Functions]
  [./inlet_function]
    type = ParsedFunction
    value = 2000*sin(0.466*pi*t) # Inlet signal from Fig. 3
  [../]
  [./outlet_function]
    type = ParsedFunction
    value = 2000*cos(0.466*pi*t) # Outlet signal from Fig. 3
  [../]
[]

[BCs]
  [./inlet]
    type = FunctionDirichletBC
    variable = pressure
    boundary = left
    function = inlet_function
  [../]
  [./outlet]
    type = FunctionDirichletBC
    variable = pressure
    boundary = right
    function = outlet_function
  [../]
  [./inlet_temperature]
    type = DirichletBC
    variable = temp
    boundary = left
    value = 350 # (C)
  [../]
  [./outlet_temperature]
    type = HeatConductionOutflow
    variable = temp
    boundary = right
  [../]
[]

[Materials]
  [./column]
    type = PackedColumn
    block = 0
    ball_radius = 1
  [../]
[]

[Problem]
  type = FEProblem
  coord_type = RZ
  rz_coord_axis = X
[]

[Executioner]
  type = Transient
  num_steps = 300
  dt = 0.1
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  output_initial = true
  exodus = true
  print_perf_log = true
  print_linear_residuals = true
[]

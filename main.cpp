#include <iostream>
#include <BinSim/BinSim.h>

binsim::SimulationParams CreateSimulationParams()
{
  binsim::SimulationParams params;

  params.part.model_file = "data/part.stl";
  params.part.center_of_mass = Eigen::Vector3d(0.012776, -0.283154, 15.027694);
  params.part.mass = 0.5f;
  params.part.resistution = 0.0f;
  params.part.friction = 0.6f;
  params.part.rolling_friction = 0.001f;
  params.part.spinning_friction = 0.001f;

  params.bin.model_file = "data/bin.obj";
  params.bin.center_of_mass = Eigen::Vector3d(0.0, 0.0, 0.0);
  params.bin.mass = 100.0f;
  params.bin.resistution = 0.0f;
  params.bin.friction = 0.6f;
  params.bin.rolling_friction = 0.001f;
  params.bin.spinning_friction = 0.001f;

  return params;
}

int main(int argc, char *argv[])
{
  binsim::EmitterParams emmiter;
  emmiter.spawn_cycles = 5;
  emmiter.spawn_interval = std::chrono::milliseconds(400);

  const auto simulation_params = CreateSimulationParams();
  binsim::Simulation simulation(simulation_params, emmiter);

  size_t last_part_count = 0;
  std::chrono::milliseconds time_lasted{ 0 };
  do
  {
    const std::chrono::milliseconds time_step(2);
    simulation.Step(time_step);
    const auto part_count = simulation.GetPartCount();
    if (part_count != last_part_count)
    {
      std::cout << "Simulation contains " << simulation.GetPartCount() << " parts." << std::endl;
      last_part_count = part_count;
    }
    time_lasted += time_step;
  }
  while (time_lasted < std::chrono::milliseconds(500) || !simulation.HasConverged());

  if (simulation.AreAllPartsInBin())
  {
    std::cout << "All parts are inside the bin." << std::endl;
  }
  else
  {
    std::cout << "Deleting parts that are not inside the bin." << std::endl;
    simulation.DeletePartsNotInBin();
    std::cout << "Left in bin: " << simulation.GetPartCount() << " parts." << std::endl;
  }

  std::cout << "Capturing virtual scan." << std::endl;

  binsim::CaptureParams capture_params;
  capture_params.shader_path = "shaders/";
  capture_params.scanner = binsim::SCANNER_M;
  capture_params.forward = Eigen::Vector3d(0.0, 0.0, -1.0);
  capture_params.up = Eigen::Vector3d(0.0, 1.0, 0.0);
  capture_params.position = Eigen::Vector3d(0.0, 0.0, 1000.0);

  simulation.CaptureAndExportPly("exported.ply", capture_params);

  return 0;
}

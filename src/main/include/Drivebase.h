#pragma once

#include "Vision.h"

#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTable.h>
#include <networktables/DoubleTopic.h>
#include <frc/XboxController.h>
#include <ctre/Phoenix.h>
#include <units/time.h>

#include <iostream>
#include <cmath>
#include <memory>

struct DrivebaseConfig {
  // controller
  frc::XboxController &driver;

  // motor controllers
  TalonSRX &Left1;
  TalonSRX &Left2;
  TalonSRX &Left3;
  TalonSRX &Right1;
  TalonSRX &Right2;
  TalonSRX &Right3;
};

enum DrivebaseState {
  kIdle,
  kTank,
  kVision,
};

class Drivebase {
 public:
   Drivebase(DrivebaseConfig *config);
   Drivebase(DrivebaseConfig *config, Vision *vision);
   ~Drivebase();

   const DrivebaseConfig *GetConfig();
   DrivebaseState GetState();
   Vision *GetVision();

   void SetState(DrivebaseState state);

   void OnStart();
   void OnUpdate(units::second_t dt);

 protected:

 private:
  Vision *_vision = NULL;
  const DrivebaseConfig *_config;
  DrivebaseState _state = kIdle;
  std::shared_ptr<nt::NetworkTable> table;
};


#pragma once

#include "Vision.h"

#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTable.h>
#include <networktables/DoubleTopic.h>

#include <frc/XboxController.h>
#include <frc/DutyCycleEncoder.h>
#include <frc2/command/PIDCommand.h>
#include <ctre/Phoenix.h>

#include <units/length.h>
#include <units/time.h>

#include <iostream>
#include <cmath>
#include <memory>

#define PI = 3.141592553589;

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

  // encoders
  frc::DutyCycleEncoder &Left1Encoder;
  frc::DutyCycleEncoder &Left2Encoder;
  frc::DutyCycleEncoder &Left3Encoder;
  frc::DutyCycleEncoder &Right1Encoder;
  frc::DutyCycleEncoder &Right2Encoder;
  frc::DutyCycleEncoder &Right3Encoder;

  units::meter_t wheelWidth;

  // pid controllers
  frc2::PIDController _velocityPID;
  frc2::PIDController _posePID;
};

enum DrivebaseState {
  kIdle,
  kTank,
  kVision,
  kVelocityPID,
  kPosePID,
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


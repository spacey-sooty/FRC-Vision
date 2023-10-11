#include "Drivebase.h"

Drivebase::Drivebase(DrivebaseConfig *config): _config(config) {}

Drivebase::Drivebase(DrivebaseConfig *config, Vision *vision): _vision(vision), _config(config) {}

Drivebase::~Drivebase() {}

const DrivebaseConfig *Drivebase::GetConfig() {
  return _config;
}

DrivebaseState Drivebase::GetState() {
  return _state;
}

Vision *Drivebase::GetVision() {
  return _vision;
}

void Drivebase::SetState(DrivebaseState state) {
  _state = state;
}

void Drivebase::OnStart() {
  std::cout << "Starting Drivebase" << std::endl;
}

void Drivebase::OnUpdate(units::second_t dt) {
  if (_config->driver.GetXButtonPressed()) {
    SetState(DrivebaseState::kTank);
  }

  if (_config->driver.GetYButtonPressed()) {
    SetState(DrivebaseState::kVision);
  }

  switch(_state) {
    case DrivebaseState::kIdle: {
      // idle state so do nothing
      break;
    }
    case DrivebaseState::kTank: {
      // tank drive state
      double leftSpeed = (std::fabs(_config->driver.GetLeftY()) > 0.02) ? _config->driver.GetLeftY() : 0;
      double rightSpeed = (std::fabs(_config->driver.GetRightY()) > 0.02) ? _config->driver.GetRightY() : 0;
      _config->Left1.Set(ControlMode::PercentOutput, leftSpeed);
      _config->Left2.Set(ControlMode::PercentOutput, leftSpeed);
      _config->Left3.Set(ControlMode::PercentOutput, leftSpeed);
      _config->Right1.Set(ControlMode::PercentOutput, rightSpeed);
      _config->Right2.Set(ControlMode::PercentOutput, rightSpeed);
      _config->Right3.Set(ControlMode::PercentOutput, rightSpeed);
      break;
    }
    case DrivebaseState::kVision: {
      // Vision Tracking State
      break;
    }
  }
}


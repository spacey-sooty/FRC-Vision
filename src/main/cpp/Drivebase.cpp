#include "Drivebase.h"

Drivebase::Drivebase(DrivebaseConfig *config) : _config(config) {
  table = nt::NetworkTableInstance::GetDefault().GetTable("Drivebase");
}

Drivebase::Drivebase(DrivebaseConfig *config, Vision *vision)
    : _vision(vision), _config(config) {}

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
  _config->Left1Encoder.Reset();
  _config->Left2Encoder.Reset();
  _config->Left3Encoder.Reset();
  _config->Right1Encoder.Reset();
  _config->Right2Encoder.Reset();
  _config->Right3Encoder.Reset();
}

void Drivebase::OnUpdate(units::second_t dt) {
  if (_config->driver.GetXButtonPressed()) {
    SetState(DrivebaseState::kTank);
  }

  if (_config->driver.GetYButtonPressed()) {
    SetState(DrivebaseState::kVision);
  }

  if (_config->driver.GetBButtonPressed()) {
    SetState(DrivebaseState::kPosePID);
  }

  if (_config->driver.GetAButtonPressed()) {
    SetState(DrivebaseState::kVelocityPID);
  }

  switch (_state) {
    case DrivebaseState::kIdle: {
      // idle state so do nothing
      break;
    }
    case DrivebaseState::kTank: {
      // tank drive state
      double leftSpeed  = (std::fabs(_config->driver.GetLeftY()) > 0.02)
                              ? _config->driver.GetLeftY()
                              : 0;
      double rightSpeed = (std::fabs(_config->driver.GetRightY()) > 0.02)
                              ? _config->driver.GetRightY()
                              : 0;
      table->PutNumber("Left Speed", leftSpeed);
      table->PutNumber("Right Speed", rightSpeed);
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

      // makes sure vision exists
      if (_vision != NULL) {
      }
      break;
    }
    case DrivebaseState::kPosePID: {
      // Pose PID Control State
      break;
    }
    case DrivebaseState::kVelocityPID: {
      // Velocity PID Control State
      break;
    }
    default: {
      std::cout << "Invalid State" << std::endl;
      break;
    }
  }
}

#pragma once

#include <frc/apriltag/AprilTagFields.h>
#include <frc/apriltag/AprilTagFieldLayout.h>

#include <photonlib/PhotonCamera.h>
#include <photonlib/RobotPoseEstimator.h>

#include <frc/geometry/Transform3d.h>

#include <memory>

std::shared_ptr<frc::AprilTagFieldLayout> Get2023Layout();

struct VisionConfig {
  std::shared_ptr<photonlib::PhotonCamera> camera;
  frc::Transform3d robotToCamera;
  units::radian_t fov;
  std::shared_ptr<frc::AprilTagFieldLayout> layout;
};

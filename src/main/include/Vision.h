#pragma once

#include <frc/apriltag/AprilTagFieldLayout.h>
#include <frc/apriltag/AprilTagFields.h>
#include <frc/geometry/Pose3d.h>
#include <frc/geometry/Transform3d.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/DoubleTopic.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <photonlib/PhotonCamera.h>
#include <photonlib/RobotPoseEstimator.h>
#include <units/time.h>

#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

std::shared_ptr<frc::AprilTagFieldLayout> Get2023Layout();

struct VisionConfig {
  std::shared_ptr<photonlib::PhotonCamera>  camera;
  frc::Transform3d                          robotToCamera;
  units::radian_t                           fov;
  std::shared_ptr<frc::AprilTagFieldLayout> layout;
};

class Vision {
 public:
  Vision(VisionConfig *config);
  ~Vision();

  VisionConfig *GetConfig();

  void OnStart();
  void OnUpdate(units::second_t dt);

  photonlib::PhotonPipelineResult                 GetLatestResult();
  std::span<const photonlib::PhotonTrackedTarget> GetTargets();
  photonlib::PhotonTrackedTarget                  GetBestTarget();
  frc::Pose3d                                     GetPose();
  frc::Transform3d GetPath(photonlib::PhotonTrackedTarget target);

 protected:
 private:
  VisionConfig *_config;
  std::vector<
      std::pair<std::shared_ptr<photonlib::PhotonCamera>, frc::Transform3d>>
      cameras = {std::make_pair(_config->camera, _config->robotToCamera)};
  photonlib::RobotPoseEstimator _estimator = photonlib::RobotPoseEstimator{
      Get2023Layout(), photonlib::CLOSEST_TO_REFERENCE_POSE, cameras};
  std::shared_ptr<nt::NetworkTable> table =
      nt::NetworkTableInstance::GetDefault().GetTable("Vision");
};

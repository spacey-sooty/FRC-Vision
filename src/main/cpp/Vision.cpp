#include "Vision.h"

using namespace std;
using namespace photonlib;
using namespace frc;
using namespace units;

shared_ptr<frc::AprilTagFieldLayout> Get2023Layout() {
  return make_shared<AprilTagFieldLayout>(LoadAprilTagLayoutField(AprilTagField::k2023ChargedUp));
};

Vision::Vision(VisionConfig *config): _config(config) {}

Vision::~Vision() {}

VisionConfig *Vision::GetConfig() {
  return _config;
}

PhotonPipelineResult Vision::GetLatestResult() {
  return _config->camera->GetLatestResult();
}

span<const PhotonTrackedTarget> Vision::GetTargets() {
  return GetLatestResult().GetTargets();
}

PhotonTrackedTarget Vision::GetBestTarget() {
  return GetLatestResult().GetBestTarget();
}

Pose3d Vision::GetPose() {
  return _estimator.Update().first;
}

Transform3d Vision::GetPath(PhotonTrackedTarget target) {
  Transform3d path = target.GetBestCameraToTarget();
  Transform3d offset = _config->robotToCamera;
  return Transform3d{Translation3d{(path.X() - offset.X()), (path.Y() - offset.Y()), (path.Z() - offset.Z())}, path.Rotation()};
}

void Vision::OnStart() {
  cout << "Starting Vision" << endl;
}

void Vision::OnUpdate(second_t dt) {
  Pose3d pose = GetPose();
  frc::SmartDashboard::PutNumber("X", pose.X().value());
  frc::SmartDashboard::PutNumber("Y", pose.Y().value());
  frc::SmartDashboard::PutNumber("Z", pose.Z().value());
  frc::SmartDashboard::PutNumber("Roll", pose.Rotation().X().value());
  frc::SmartDashboard::PutNumber("Pitch", pose.Rotation().Y().value());
  frc::SmartDashboard::PutNumber("Yaw", pose.Rotation().Z().value());
}

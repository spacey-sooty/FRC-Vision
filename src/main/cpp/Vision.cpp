#include "Vision.h"

std::shared_ptr<frc::AprilTagFieldLayout> Get2023Layout() {
  return std::make_shared<frc::AprilTagFieldLayout>(frc::LoadAprilTagLayoutField(frc::AprilTagField::k2023ChargedUp));
};

Vision::Vision(VisionConfig *config): _config(config) {
  table = nt::NetworkTableInstance::GetDefault().GetTable("Vision");
}

Vision::~Vision() {}

VisionConfig *Vision::GetConfig() {
  return _config;
}

photonlib::PhotonPipelineResult Vision::GetLatestResult() {
  return _config->camera->GetLatestResult();
}

std::span<const photonlib::PhotonTrackedTarget> Vision::GetTargets() {
  return GetLatestResult().GetTargets();
}

photonlib::PhotonTrackedTarget Vision::GetBestTarget() {
  return GetLatestResult().GetBestTarget();
}

frc::Pose3d Vision::GetPose() {
  return _estimator.Update().first;
}

frc::Transform3d Vision::GetPath(photonlib::PhotonTrackedTarget target) {
	frc::Transform3d path = target.GetBestCameraToTarget();
	frc::Transform3d offset = _config->robotToCamera;
	return frc::Transform3d{frc::Translation3d{(path.X() - offset.X()), (path.Y() - offset.Y()), (path.Z() - offset.Z())}, path.Rotation()};
}

void Vision::OnStart() {
	std::cout << "Starting Vision" << std::endl;
}

void Vision::OnUpdate(units::second_t dt) {
  frc::Pose3d pose = GetPose();
  table->PutNumber("X", pose.X().value());
  table->PutNumber("Y", pose.Y().value());
  table->PutNumber("Z", pose.Z().value());
  table->PutNumber("Roll", pose.Rotation().X().value());
  table->PutNumber("Pitch", pose.Rotation().Y().value());
  table->PutNumber("Yaw", pose.Rotation().Z().value());
}

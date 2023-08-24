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

frc::Pose3d Vision::GetPose() {
  return _estimator.Update().first;
}

void Vision::OnStart() {
  cout << "Starting Vision" << endl;
}

// TODO periodic logging
void Vision::OnUpdate(second_t dt) {}

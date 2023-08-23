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

void Vision::OnStart() {
  cout << "Starting Vision" << endl;
}

// TODO periodic logging
void Vision::OnUpdate(second_t dt) {}

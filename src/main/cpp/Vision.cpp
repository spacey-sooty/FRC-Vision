#include "Vision.h"

using namespace std;
using namespace photonlib;
using namespace frc;

shared_ptr<frc::AprilTagFieldLayout> Get2023Layout() {
  return make_shared<AprilTagFieldLayout>(LoadAprilTagLayoutField(AprilTagField::k2023ChargedUp));
};

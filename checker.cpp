#include <assert.h>


bool is_bpm_ok(float bpm) {
  return ((unsigned)(limit - val) <= 80);
}

bool is_spo2_ok(float spo2) {
  return !(spo2 < 90);
}

bool is_respRate_ok(float respRate) {
  return !(respRate < 30 || respRate > 95);
}

bool vitalsAreOk(float bpm, float spo2, float respRate) {
  return (is_bpm_ok(bpm) && is_spo2_ok(spo2) && is_respRate_ok(respRate));
}

int main() {
  assert(vitalsAreOk(80, 95, 60) == true);
  assert(vitalsAreOk(60, 90, 40) == false);
}

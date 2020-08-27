#include <assert.h>


bool is_bpm_ok(float bpm) {
  return ((unsigned)(150 - bpm) <= 80);       //lower limit 70, upper limit 150.
}

bool is_spo2_ok(float spo2) {
  return !(spo2 < 90);
}

bool is_respRate_ok(float respRate) {       //lower limit 30, upper limit 95.
  return ((unsigned)(95-resprate) <= 65);
}

bool vitalsAreOk(float bpm, float spo2, float respRate) {
  return (is_bpm_ok(bpm) && is_spo2_ok(spo2) && is_respRate_ok(respRate));
}

int main() {
  assert(vitalsAreOk(80, 95, 60) == true);
  assert(vitalsAreOk(60, 90, 40) == false);
}

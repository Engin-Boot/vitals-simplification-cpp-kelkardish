#include <assert.h>

bool is_vital_normal(float value, int upperLimit, int lowerLimit) {    // (normalRange = upperlimt - value) <= (upperLimit - lowerLimit)
  return ((unsigned)(upperLimit - value) <= (unsigned)(upperLimit - lowerLimit));
}

/*bool is_bpm_ok(float bpm) {
  return ((unsigned)(150 - bpm) <= 80);       //lower limit 70, upper limit 150.
}

bool is_spo2_ok(float spo2) {
  return !(spo2 < 90);
}

bool is_respRate_ok(float respRate) {       //lower limit 30, upper limit 95.
  return ((unsigned)(95-respRate) <= 65);
}*/

bool vitalsAreOk(float bpm, float spo2, float respRate) {
  //return (is_bpm_ok(bpm) && is_spo2_ok(spo2) && is_respRate_ok(respRate));
  return ( is_vital_normal(bpm,150,70) && is_vital_normal(spo2,100,90) && is_vital_normal(respRate(respRate,95,30) );
}

int main() {
  //vitalsAreOk(bpm,spo2,respRate)
  assert(vitalsAreOk(80, 95, 60) == true);        // All Normal
  assert(vitalsAreOk(60, 95, 60) == false);       //AL_bpm, N_sp02, N_resp
  assert(vitalsAreOk(180, 95, 60) == false);      //AH_bpm, N_sp02, N_resp
  assert(vitalsAreOk(80, 95, 22) == false);       //N_bpm,  N_sp02, AL_resp
  assert(vitalsAreOk(80, 95, 98) == false);       //N_bpm,  N_spo2, AH_resp
  assert(vitalsAreOk(80, 89, 60) == false);       //N_bpm,  A_sp02, N_resp
  assert(vitalsAreOk(60, 89, 22) == false);       //All Abnormal Low
  assert(vitalsAreOk(180, 89, 98) == false);      //All Abnormal High
}

#include <assert.h>

bool is_vital_normal(float value, int upperLimit, int lowerLimit) {    // (normalRange = [ 0 , upperLimit-lowerLimit]
  return ((unsigned)(upperLimit - value) <= (unsigned)(upperLimit - lowerLimit));
}

//bpm [70,150], spo2[90,100], respRate[30, 95]
bool vitalsAreOk(float bpm, float spo2, float respRate) {
  return ( is_vital_normal(bpm,150,70) && is_vital_normal(spo2,100,90) && is_vital_normal(respRate,95,30) );
}

int main() {
  /*
  //vitalsAreOk(bpm,spo2,respRate)
  assert(vitalsAreOk(80, 95, 60) == true);        // All Normal
  assert(vitalsAreOk(60, 95, 60) == false);       //AL_bpm, N_sp02, N_resp
  assert(vitalsAreOk(180, 95, 60) == false);      //AH_bpm, N_sp02, N_resp
  assert(vitalsAreOk(80, 95, 22) == false);       //N_bpm,  N_sp02, AL_resp
  assert(vitalsAreOk(80, 95, 98) == false);       //N_bpm,  N_spo2, AH_resp
  assert(vitalsAreOk(80, 89, 60) == false);       //N_bpm,  A_sp02, N_resp
  assert(vitalsAreOk(60, 89, 22) == false);       //All Abnormal Low
  assert(vitalsAreOk(180, 89, 98) == false);      //All Abnormal High
  */
  assert(is_vital_normal(40, 100, 50) == false);
  assert(is_vital_normal(120, 100, 50) == false);
  assert(is_vital_normal(92, 100, 50) == true);
}

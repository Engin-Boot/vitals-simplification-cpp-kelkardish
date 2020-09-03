#include <assert.h>
#include <iostream>

struct Vitals {
	int bedNumber ;
	const char* vitalName;
	int measure;
	int lowerValue;
	int upperValue;
};

class AlertInterface {
public:
	virtual void raiseAlert(int bedNo, const char* vitalName, const char* level) = 0;
};

class AlertWtihSMS : public AlertInterface {
public:
	void raiseAlert(int bedNo, const char* vitalName, const char* level) override {
		std::cout << "SMS:   " << "Bed No: "<<bedNo<< "::"<<vitalName << " " << level << std::endl;
	}
};

class AlertWtihSound : public AlertInterface {
public:
	void raiseAlert(int bedNo, const char* vitalName, const char* level) override {
		std::cout << "Sound: " << "Bed No: " << bedNo << "::" << vitalName << " " << level << std::endl;
	}
};

//class to test both sound and sms alert
class AlertWithSoundandSMS : public AlertInterface {
private:
	AlertWtihSMS alertSMS;
	AlertWtihSound alertSound;
public:
	void raiseAlert(int bedNo, const char* vitalName, const char* level) {
		alertSMS.raiseAlert(bedNo, vitalName, level);
		alertSound.raiseAlert(bedNo, vitalName, level);
	}
};

bool isVitalInRange(Vitals vital, AlertInterface* alerterPtr) {
	if (vital.measure < vital.lowerValue) {
		alerterPtr->raiseAlert(vital.bedNumber, vital.vitalName, "VITAL IS LOW!");
		return false;
	}
	else if (vital.measure > vital.upperValue) {
		alerterPtr->raiseAlert(vital.bedNumber, vital.vitalName, "VITAL IS HIGH!");
		return false;
	}
	return true;
}

bool vitalsAreOk(Vitals* vitalList, int n_Vitals, AlertInterface* alerterPtr) {

	bool flag = true;
	for (int i = 0; i < n_Vitals; i++) {
		flag = flag & isVitalInRange(vitalList[i], alerterPtr);
	}
	return flag;
}

//bpm [70,150], spo2[90,100], respRate[30, 95]
int main() {

	Vitals vital1[] = { {13,"bpm",98,70,150},
			    {13,"spo2",92,90,100},
			    {13,"respRate", 45,30,95} };

	Vitals vital2[] = { {11,"bpm",65,70,150},			//out of range BPM
			    {11,"spo2",92,90,100},
			    {11,"respRate", 45,30,95} };

	Vitals vital3[] = { {7,"bpm",98,70,150},
			    {5,"spo2",85,90,100},			//out of range spo2
			    {3,"respRate", 45,30,95} };

	Vitals vital4[] = { {19,"bpm",98,70,150},
		  	    {19,"spo2",92,90,100},
			    {19,"respRate", 96,30,95} };		//out of range respRate



	AlertWithSoundandSMS awss;
	assert(vitalsAreOk(vital1, 3, &awss) == true);
	assert(vitalsAreOk(vital2, 3, &awss) == false);
	assert(vitalsAreOk(vital3, 3, &awss) == false);
	assert(vitalsAreOk(vital4, 3, &awss) == false);

	assert(isVitalInRange({2, "bpm",155,70,150 }, &awss) == false);
	assert(isVitalInRange({4, "spo2",80,90,100 }, &awss) == false);
	assert(isVitalInRange({6, "respRate",85,30,95 }, &awss) == true);


}

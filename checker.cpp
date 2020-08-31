#include <assert.h>
#include <iostream>

struct Vitals {
	//int bedNumber ;
	const char* vitalName;
	int measure;
	int lowerValue;
	int upperValue;
};

class AlertInterface {
public:
	virtual void raiseAlert(const char* vitalName, const char* level) = 0;
};

class AlertWtihSMS : public AlertInterface {
public:
	void raiseAlert(const char* vitalName, const char* level) override{
		std::cout << "SMS: " << vitalName << " " << level << std::endl;
	}
};

class AlertWtihSound : public AlertInterface {
public:
	void raiseAlert(const char* vitalName, const char* level) override{
		std::cout << "Sound: " << vitalName << " " << level << std::endl;
	}
};

//class to test both sound and sms alert
class AlertWithSoundandSMS : public AlertInterface {
private:
	AlertWtihSMS alertSMS;
	AlertWtihSound alertSound;
public:
	void raiseAlert(const char* vitalName, const char* level) {
		alertSMS.raiseAlert(vitalName, level);
		alertSound.raiseAlert(vitalName, level);
	}
};
bool vitalIsOk(Vitals* vitalList, int n_Vitals, AlertInterface* alerterPtr ) {
	
	for (int i = 0; i < n_Vitals; i++) {
		if (vitalList[i].measure < vitalList[i].lowerValue) {
			alerterPtr->raiseAlert(vitalList[i].vitalName, "VITAL IS LOW!");
			return false;
		}
		else if (vitalList[i].measure > vitalList[i].upperValue) {
			alerterPtr->raiseAlert(vitalList[i].vitalName, "VITAL IS HIGH!");
			return false;
		}
	}
	return true;
}

//bpm [70,150], spo2[90,100], respRate[30, 95]
int main() {
	
	Vitals vital1[] = { {"bpm",98,70,150},
					   {"spo2",92,90,100},
					   {"respRate", 45,30,95} };

	Vitals vital2[] = { {"bpm",65,70,150},			//out of range BPM
					   {"spo2",92,90,100},
					   {"respRate", 45,30,95} };

	Vitals vital3[] = { {"bpm",98,70,150},
					   {"spo2",85,90,100},			//out of range spo2
					   {"respRate", 45,30,95} };

	Vitals vital4[] = { {"bpm",98,70,150},
					   {"spo2",92,90,100},
					   {"respRate", 96,30,95} };	//out of range respRate
	
	//int nVitals = sizeof(vital) / sizeof(Vitals);

	//AlertWtihSMS alertSMS;
	//AlertWtihSound alertSound;
	
	AlertWithSoundandSMS awss;
	assert(vitalIsOk(vital1, 3, &awss) == true);
	assert(vitalIsOk(vital2, 3, &awss) == false);
	assert(vitalIsOk(vital3, 3, &awss) == false);
	assert(vitalIsOk(vital4, 3, &awss) == false);


//	assert(vitalIsOk(vital1, nVitals, &alertSMS) == true);
}

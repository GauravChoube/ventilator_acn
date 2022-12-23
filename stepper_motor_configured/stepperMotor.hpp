
extern int maximumStepOfMotor;

int stepperMotorInit();
int stepperMotorSetStep(int stepValue);

int stepperMotorGetStep( );
int stepperMotordistanceToGo();
int stepperMotorSetSpeed(unsigned int speedValue);
int stepperMotorSetAcceleration(unsigned int accel);
unsigned int stepperMotorGetSpeed( );
void stepperMotorStart();
void stepperMotorStop();
int stepperMotorReset();
int stepperMotorGetTorque();
int stepperMotorSetTorque();
int stepperMotorGetCurrentConsumption();
int stepperMotorGetCurrentVoltage();
int stepperMotorRun();
int stepperMotorSetDelayForStep(unsigned int delayinMicrosecond);
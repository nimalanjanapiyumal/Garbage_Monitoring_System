/*
 * mq2.h
 *
 * Created: 11/4/2022 1:48:55 PM
 *  Author: User
 */ 


#ifndef MQ2_H_
#define MQ2_H_

#define RL_VALUE (10)     //define the load resistance on the board, in kilo ohms
#define RO_CLEAN_AIR_FACTOR (9.83)  //(Sensor resistance in clean air)/RO,which is derived from the chart in datasheet
#define LPG (0)         // Gas identity no.
#define SMOKE (1)

int  GetPercentage(float, float *);
int GetGasPercentage(float , int);
double ReadSensor();
float ResistanceCalculation(int);
float SensorCalibration();




#endif /* MQ2_H_ */
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeMegaPi.h>

double servo_speed=15;
double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
MeSmartServo mysmartservo(PORT5);
float getServoValue(int index, int type)
{
    	if(type==0)
    	{
        		return mysmartservo.getSpeedRequest(index);
    	}
    	else if(type==1)
    	{
        		return mysmartservo.getTempRequest(index);
    	}
    	else if(type==2)
    	{
        		return mysmartservo.getCurrentRequest(index);
    	}
    	else if(type==3)
    	{
        		return mysmartservo.getVoltageRequest(index);
    	}
    	else if(type==4)
    	{
        		return mysmartservo.getAngleRequest(index);
    	}
}

void setup(){
    //Set Pwm 8KHz
    TCCR1A = _BV(WGM10);
    TCCR1B = _BV(CS11) | _BV(WGM12);
    TCCR2A = _BV(WGM21) | _BV(WGM20);
    TCCR2B = _BV(CS21);
    mysmartservo.begin(115200);
    mysmartservo.assignDevIdRequest();
    delay(50);
    mysmartservo.begin(115200);
    mysmartservo.assignDevIdRequest();    mysmartservo.moveTo(1,-45,servo_speed);
}

void loop(){
    if(((getServoValue(1,4))==(-45))){
        mysmartservo.move(1,90,servo_speed);
    }
    if(((getServoValue(1,4))==(45))){
        mysmartservo.move(1,-90,servo_speed);
    }
    Serial.println(getServoValue(1,4));
    _loop();
}

  
void _loop(){
}

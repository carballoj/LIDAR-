#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeMegaPi.h>
#include <LIDARLite.h>

LIDARLite myLidarLite;

MeEncoderOnBoard Encoder_4(SLOT4);

void isr_process_encoder4(void)
{
  if(digitalRead(Encoder_4.getPortB()) == 0)
  {
    Encoder_4.pulsePosMinus();
  }
  else
  {
    Encoder_4.pulsePosPlus();;
  }
}
double rotate_speed=85.0;
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
/*Note!! Might have problem with same serial port 115200*/
void setup()
{
    attachInterrupt(Encoder_4.getIntNum(), isr_process_encoder4, RISING);
    Serial.begin(115200);
  
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
    
    Encoder_4.setPulse(8);
    Encoder_4.setRatio(46.67);
    Encoder_4.setPosPid(1.8,0,1.2);
    Encoder_4.setSpeedPid(0.18,0,0);
}

void loop(){

    Encoder_4.runSpeed(rotate_speed);
    
    if(((getServoValue(1,4))==(-45))){
        mysmartservo.move(1,90,servo_speed);
    }
    if(((getServoValue(1,4))==(45))){
        mysmartservo.move(1,-90,servo_speed);
    }

    Serial.print("Servo Position :");
    Serial.println(getServoValue(1,4));
    Serial.print(" , Encoder Position:");
    Serial.print(Encoder_1.getCurPos());
    delay(500);
    _loop();
}
/*Note!! Might have problem with running different loops (delete Encoder_4.loop(); or have loop twice) */
void loop()
{
  Encoder_4.loop();
}

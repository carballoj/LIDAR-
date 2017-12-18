#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeMegaPi.h>

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
double speed=85.0;

void setup()
{
  attachInterrupt(Encoder_4.getIntNum(), isr_process_encoder4, RISING);
  Serial.begin(115200);
  
  //Set PWM 8KHz
  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(WGM12);

  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS21);

  Encoder_4.setPulse(8);
  Encoder_4.setRatio(46.67);
  Encoder_4.setPosPid(1.8,0,1.2);
  Encoder_4.setSpeedPid(0.18,0,0);
}

void loop(){
    Encoder_4.runSpeed(speed);
    Serial.print("Angular Speed :");
    Serial.print(Encoder_4.getCurrentSpeed());
    Serial.print(" , Angular Position:");
    Serial.print(Encoder_1.getCurPos());
    _delay(0.5);
    _loop();
}

void _delay(float seconds){
    long endTime = millis() + seconds * 1000;
    while(millis() < endTime)_loop();
}

void loop()
{
  Encoder_4.loop();
}

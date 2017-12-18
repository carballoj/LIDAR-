/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * @file    Me_Megapi_encoder_pid_pos.ino
 * @author  MakeBlock
 * @version V1.0.0
 * @date    2016/07/14
 * @brief   Description: this file is sample code for Megapi encoder motor device.
 *
 * Function List:
 *    1. uint8_t MeEncoderOnBoard::getPortB(void);
 *    2. uint8_t MeEncoderOnBoard::getIntNum(void);
 *    3. void MeEncoderOnBoard::pulsePosPlus(void);
 *    4. void MeEncoderOnBoard::pulsePosMinus(void);
 *    5. void MeEncoderOnBoard::setMotorPwm(int pwm);
 *    6. double MeEncoderOnBoard::getCurrentSpeed(void);
 *    7. void MeEncoderOnBoard::setSpeedPid(float p,float i,float d);
 *    8. void MeEncoderOnBoard::setPosPid(float p,float i,float d);
 *    7. void MeEncoderOnBoard::setPosPid(float p,float i,float d);
 *    8. void MeEncoderOnBoard::setPulse(int16_t pulseValue);
 *    9. void MeEncoderOnBoard::setRatio(int16_t RatioValue);
 *    10. void MeEncoderOnBoard::moveTo(long position,float speed,int16_t extId,cb callback);
 *    11. void MeEncoderOnBoard::loop(void);
 *    12. long MeEncoderOnBoard::getCurPos(void);
 *
 * \par History:
 * <pre>
 * <Author>             <Time>        <Version>      <Descr>
 * Mark Yan             2016/07/14    1.0.0          build the new
 * Jorge de Francisco   2017/12/18    2.0.0          adapted
 * </pre>
 */
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

void loop()
{
  Encoder_4.loop();
}

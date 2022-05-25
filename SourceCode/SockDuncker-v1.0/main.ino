#include <SoftwareSerial.h>
#include <EEPROM.h>
#include "State.h"
SoftwareSerial Bluetooth(0, 1);

int recMotor, recAngle;
Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_ver;
Servo wrist_rot;
Servo gripper;

String dataIn;
int index = 1;
_State currState = _State();
_State states[21];
void Go(int motor, int angle);

void setup() {
  Braccio.begin();
  Bluetooth.begin(9600);
  Bluetooth.setTimeout(1);
  Serial.begin(9600);
  setSaves();
  Serial.println("chuvame li se?");
}
void loop() {
  
  if (Bluetooth.available() > 0)
  {
    delay(100);
    dataIn = Bluetooth.readString();
    Serial.println(dataIn);

    if (dataIn.startsWith("ss"))
    {
      currState.velocity = dataIn.substring(2, 4).toInt();
      Serial.println(currState.velocity);
    }
    else if (dataIn.startsWith("s1"))
    {
      Go(1, dataIn.substring(2, dataIn.length()).toInt());
    }
    else if (dataIn.startsWith("s2"))
    {
      Go(2, dataIn.substring(2, dataIn.length()).toInt());
    }
    else if (dataIn.startsWith("s3"))
    {
      Go(3, dataIn.substring(2, dataIn.length()).toInt());
    }
    else if (dataIn.startsWith("s4"))
    {
      Go(4, dataIn.substring(2, dataIn.length()).toInt());
    }
    else if (dataIn.startsWith("s5"))
    {
      Go(5, dataIn.substring(2, dataIn.length()).toInt());
    }
    else if (dataIn.startsWith("s6"))
    {
      Go(6, dataIn.substring(2, dataIn.length()).toInt());
    }

    else if (dataIn.startsWith("save"))
    {
      index = dataIn.substring(5, 7).toInt();
      int temp = 4, br = 5, motor[6];
      for (int i = 4; i < dataIn.length(); i++)
      {
        if (dataIn[i] == ',')
        {
          motor[br] = dataIn.substring(temp, i).toInt();
          temp = i;
          br--;
        }
      }
      states[index].Save(currState.velocity, motor[0], motor[1], motor[2], motor[3], motor[4], motor[5]);
      EEPROM[index*7] = currState.velocity;
      EEPROM[index*7 + 1] = motor[0];
      EEPROM[index*7 + 2] = motor[1];
      EEPROM[index*7 + 3] = motor[2];
      EEPROM[index*7 + 4] = motor[3];
      EEPROM[index*7 + 5] = motor[4];
      EEPROM[index*7 + 6] = motor[5];
      
      index = ++index > 20 ? index = 1 : index;
    }
    else if (dataIn == "reset")
    {
      for (int i = 1; i <= 20; i++) {
        states[i].Reset();
      }

      for(int i = 1; i <= 20; i++) {
        EEPROM[i*7] = 10;
        EEPROM[i*7+1] = 90;
        EEPROM[i*7+2] = 90;
        EEPROM[i*7+3] = 90;
        EEPROM[i*7+4] = 90;
        EEPROM[i*7+5] = 90;
        EEPROM[i*7+6] = 73;
      }
    }
    else if (dataIn.startsWith("run")) {
      index = dataIn.substring(4, 6).toInt();
      for (int i = 1; i <= index; i++) {
        states[i].Run();
      }
    }

    else
    {
      index = dataIn.toInt();
      Serial.println(index);
    }
  }
}

void Go(int motor, int angle) {
  Serial.println(motor);
  Serial.println(angle);
  switch (motor) {
    case 1:
      currState.baseAngle = angle;
      break;
    case 2:
      currState.shoulderAngle = angle;
      break;
    case 3:
      currState.elbowAngle = angle;
      break;
    case 4:
      currState.wristVerAngle = angle;
      break;
    case 5:
      currState.wristRotAngle = angle;
      break;
    case 6:
      currState.gripAngle = angle;
      break;
  }
  currState.Run();
}

void setSaves(){
  for(int i = 1; i <= 20; i++) {
    states[i].velocity = EEPROM[i*7];
    states[i].baseAngle = EEPROM[i*7 + 1];
    states[i].shoulderAngle = EEPROM[i*7 + 2];
    states[i].elbowAngle = EEPROM[i*7 + 3];
    states[i].wristVerAngle = EEPROM[i*7 + 4];
    states[i].wristRotAngle = EEPROM[i*7 + 5];
    states[i].gripAngle = EEPROM[i*7 + 6];
  }
}

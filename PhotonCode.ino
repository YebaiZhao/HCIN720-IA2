/******************************************************************************
Modified from MMA8452Q_Basic.ino
*/
#include "MMA8452-Accelerometer-Library-Spark-Core/MMA8452-Accelerometer-Library-Spark-Core.h" // Includes the SFE_MMA8452Q library

int button1;
int button2;
char publishString[64];
String orient;
MMA8452Q accel;
unsigned long looptime=0;
unsigned long looptime2=0;

void setup()
{
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(D7, OUTPUT);
  Serial.begin(9600);
  Spark.function("led7",ledToggle);
  accel.init(SCALE_2G, ODR_12);
}

void loop()
{
    
    button1=digitalRead(A0);
    button2=digitalRead(A1);
    //digitalWrite(D7,button1);
    if (looptime2+100 < millis()){ ///the local loop

        if (accel.available()){
            accel.read();
            printOrientationFor3D();
            //    Serial.println(); // Print new line every time.
            //sprintf(publishString, "{\"Button1\": %u, \"Ori\": \"%s\", \"Button2\": %u, \"X\": %u, \"Y\": %u, \"Z\": %u}", button1, orient.c_str(), button2, accel.x, accel.y, accel.z);
            sprintf(publishString, "{\"Button1\": %u, \"Ori\": \"%s\", \"Button2\": %u}", button1, orient.c_str(), button2);
            Serial.println(publishString);
            Serial.println(publishString);
        }
        looptime2=millis();
    }    

    
    if (looptime+1000 < millis()){ ///the Cloud Loop

        Spark.publish("Data_2",publishString);
        looptime=millis();
    }
}


void printOrientationFor3D(){
    byte pl = accel.readPL();
    
    switch (pl)
    {
    case PORTRAIT_U:
    //Serial.print("Portrait Up");
    orient="Up";
    //Spark.publish("Orientation","up",60);
    break;
    
    case PORTRAIT_D:
    //Serial.print("Portrait Down");
    orient="Down";
    //Spark.publish("Orientation","donw",60);
    break;
    
    case LANDSCAPE_R:
    //Serial.print("Landscape Right");
    orient="Right";
    //Spark.publish("Orientation","right",60);
    break;
    
    case LANDSCAPE_L:
    //Serial.print("Landscape Left");
    orient="Left";
    //Spark.publish("Orientation","left",60);
    break;
    
    case LOCKOUT:
    //Serial.print("Flat");
    orient="Flat";
    //Spark.publish("Orientation","flat",60);
    break;

  }
}

int ledToggle(String command) {
    unsigned long flashTimer=1024;
    if (command=="flash") {
        
        for( flashTimer; flashTimer>5; flashTimer=flashTimer/2 ){
                digitalWrite(D7,HIGH);
                delay(flashTimer/2);
                digitalWrite(D7,LOW);
                delay(flashTimer/2);
        }
        return 1;
    }
    
    
    else {
        return command.length();
    }
}


unsigned long lastTime = 0UL;
char publishString[40];

void setup() {
}

void loop() {
    unsigned long now = millis();
    //Every 15 seconds publish uptime
    if (now-lastTime>15000UL) {
        lastTime = now;
        // now is in milliseconds
        unsigned nowSec = now/1000UL;
        unsigned sec = nowSec%60;
        unsigned min = (nowSec%3600)/60;
        unsigned hours = (nowSec%86400)/3600;
        sprintf(publishString,"%u:%u:%u",hours,min,sec);
        Spark.publish("Uptime",publishString);
    }
}
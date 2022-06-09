#include <u600.h>

U600 co2Sensor(Serial2, 100);

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Initializing...");
  co2Sensor.init();
  Serial.println("... Initialization completed.");
}

void loop(){
  co2Sensor.read();
  while(co2Sensor.isAvailable()){
    co2_t* co2Packet = co2Sensor.getCo2Reading();
    if(co2Packet != NULL){
      float co2 = co2Sensor.getCo2Concentration(co2Packet);
      Serial.print("CO2: ");
      Serial.println(co2);
      
      if(co2Sensor.isEtCo2(co2Packet)){
        float etCo2 = co2Sensor.getEtCo2(co2Packet);
        Serial.print("ETCO2: ");
        Serial.println(etCo2);
      }
      
      if(co2Sensor.isRespirationRate(co2Packet)){
        float respirationRate = co2Sensor.getRespirationRate(co2Packet);
        Serial.print("Respiration Rate: ");
        Serial.println(respirationRate);
      }
    }
  }
}

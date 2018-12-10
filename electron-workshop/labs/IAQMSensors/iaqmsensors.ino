#include <SensirionSGP30.h>
#include <SHT31.h>

#define SENSOR_CHECK_INTERVAL 60000
#define DUST_SENSOR_PIN D1
#define LIGHT_SENSOR_PIN A0
#define MOTION_SENSOR_PIN D3

SHT31 sht31 = SHT31();
SensirionSGP30 sgp;

int currentTemperature;
int currentHumidity;
int currentTVOC;
int currentCO2eq;
unsigned long duration;
unsigned long lowPulseOccupancy;
float ratio;
float concentration;
double currentLightLevel;
uint32_t lastMotionTime;
unsigned long lastSensorCheck = 0;

void fireSensorEvent() {
  String payload = "{\"temp\":" + String(currentTemperature)
    + ", \"humidity\":" + String(currentHumidity)
    + ", \"tvoc\":" + String(currentTVOC)
    + ", \"co2eq\":" + String(currentCO2eq)
    + ", \"dust\": {\"lpo\":" + String(lowPulseOccupancy)
    + ", \"ratio\":" + String(ratio)
    + ", \"concentration\":" + String(concentration) + "}"
    + ", \"lightLevel\":" + String(currentLightLevel)
    + ", \"lastMotion\":" + String(lastMotionTime)
    + "}";

  Particle.publish("device_sensors", payload, MY_DEVICES);
}

void checkDust() {
  ratio = lowPulseOccupancy/(SENSOR_CHECK_INTERVAL*10.0);
  concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62;

  lowPulseOccupancy = 0;
}

void checkSensors() {
  int temp = round((sht31.getTemperature() * 1.8 + 32.00)*10)/10;
  int humidity = round(sht31.getHumidity()*10)/10;

  if (temp > 0) currentTemperature = temp;
  if (humidity > 0) currentHumidity = humidity;
  if (sgp.IAQmeasure()) {
    currentTVOC = sgp.TVOC;
    currentCO2eq = sgp.eCO2;
  }

  double lightAnalogVal = analogRead(LIGHT_SENSOR_PIN);
  currentLightLevel = map(lightAnalogVal, 0.0, 4095.0, 0.0, 100.0);
}

int checkSensorsHandler(String command) {
  checkSensors();

  return 1;
}

void setup() {
  sht31.begin();
  sgp.begin();

  pinMode(DUST_SENSOR_PIN, INPUT);
  pinMode(LIGHT_SENSOR_PIN, INPUT);
  pinMode(MOTION_SENSOR_PIN, INPUT);

  Particle.variable("tempF", currentTemperature);
  Particle.variable("humidity", currentHumidity);
  Particle.variable("tvoc", currentTVOC);
  Particle.variable("eCO2", currentCO2eq);

  Particle.function("checkSensors", checkSensorsHandler);

  checkSensors();
}

void loop() {
  duration = pulseIn(DUST_SENSOR_PIN, LOW);
  lowPulseOccupancy = lowPulseOccupancy + duration;

  if (lastSensorCheck + SENSOR_CHECK_INTERVAL < millis()) {
    lastSensorCheck = millis();
    checkSensors();

    checkDust();
    fireSensorEvent();
  }

  if (digitalRead(MOTION_SENSOR_PIN)) {
      // Particle.publish("movement_detected", NULL, MY_DEVICES);
      lastMotionTime = Time.now();
  }
}

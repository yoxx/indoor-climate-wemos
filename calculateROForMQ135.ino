// Define input voltage
#define VOLTAGE 3.3
/// The load resistance on the board
#define RLOAD 10.0
/// Calibration resistance at atmospheric CO2 level
#define RZERO 76.63
/// Parameters for calculating ppm of CO2 from sensor resistance
#define MQ135_SCALINGFACTOR 116.6020682
#define MQ135_EXPONENT -2.769034857
#define MQ135_WORLD_CO2 475 // https://www.co2.earth/ or a different CO2 calibrated sensor

void setup() 
{
  Serial.begin(9600);
}
 
void loop() 
{
  // Air Quality
  float analogSensorValue;
  float resistance;
  float CO2_ppm;
  float RO;
  float pow_co2;
  
  // Get the sensor value from the MQ135 sensor
  analogSensorValue = analogRead(A0);
  // Convert the analog value to a digital value 1023 for 5V 4095 for 3.3V
  resistance =  ((4095./(float)analogSensorValue) * VOLTAGE - 1.)*RLOAD;
  Serial.println("Resistance: " + String(resistance));
  // Calculate ppm and do the value times 100 to account for normal values
  RO = (float)(resistance * exp(log(MQ135_SCALINGFACTOR / MQ135_WORLD_CO2) / MQ135_EXPONENT));
  Serial.println("RO: " + String(RO));
  Serial.println("devide: " + String((resistance/RO)));
  pow_co2 = pow((resistance/RO), MQ135_EXPONENT);
    Serial.println("POW: " + String(pow_co2));
  CO2_ppm = (float)MQ135_SCALINGFACTOR * pow((resistance/RO), MQ135_EXPONENT);

  Serial.print(" CO2: ");
  Serial.print((int)CO2_ppm);
  Serial.println("ppm");
  delay(5000);
}

// Define input voltage
#define VOLTAGE 3.3
/// The load resistance on the board
#define RLOAD 10.0
/// Calibration resistance at atmospheric CO2 level
#define RZERO 76.63
/// Parameters for calculating ppm of CO2 from sensor resistance
#define PARA 116.6020682
#define PARB 2.769034857

/// Parameters to model temperature and humidity dependence
#define CORA 0.00035
#define CORB 0.02718
#define CORC 1.39538
#define CORD 0.0018

/// Atmospheric CO2 level for calibration purposes
#define ATMOCO2 397.13

void setup() 
{
  Serial.begin(9600);
}
 
void loop() 
{
  float sensorValue;
  float resistance;
  float ppm;
 
  sensorValue = analogRead(A0);

  resistance =  ((1023./(float)sensorValue) * VOLTAGE - 1.)*RLOAD;
  ppm = PARA * pow((resistance/RZERO), -PARB)*100;

  Serial.print("CO2 val: ");
  Serial.print((int)ppm);
  Serial.println(" ppm");
  
  delay(1000);
}

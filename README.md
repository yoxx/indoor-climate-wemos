# Binnenklimaat met ESP8266
The Space Leiden - Binnenklimaat setup

## Benodigdheden
- [Wemos D1 Mini v3.1.0](https://docs.wemos.cc/en/latest/d1/d1_mini.html)
- [DHT22 Temp and Humidity Sensor](https://www.sparkfun.com/datasheets/Sensors/Temperature/DHT22.pdf)
- [MQ135 Gas sensor](https://www.olimex.com/Products/Components/Sensors/Gas/SNS-MQ135/resources/SNS-MQ135.pdf)

### HowTo
- Code is toegevoegd maar probeer het eerst lekker zelf uit te zoeken! 
- De Wemos D1 mini is programmeerbaar met de Arduino IDE maar kan eventueel ook geprogrammeerd worden met andere talen

## Arduino IDE
- Download -> https://www.arduino.cc/en/main/software
- https://averagemaker.com/2018/03/wemos-d1-mini-setup.html

## Sensoren
- DHT22 -> Food for Thought -> https://chewett.co.uk/blog/1476/using-the-dht22-temperature-sensor-with-a-wemos-d1-mini-esp8266/
- MQ135 -> analog readout -> http://davidegironi.blogspot.com/2014/01/cheap-co2-meter-using-mq135-sensor-with.html

## Workflow
* Zorg dat je de DHT22 werkzaam krijgt en data laat versturen via Serial
* Zorg dat je de MQ135 werkzaam krijgt en data laat versturen via Serial
  * Kalibreer je sensor (voor zover het kan)
* Laat beide sensoren data versturen via Serial
* Connect Met Wifi
* Push je data naar Google sheets!
  1. Create a new sheet with the following headers: Time	Temperature	Humidity	CO2	
  2. Use https://www.hackster.io/thatiotguy/sensor-data-upload-to-google-sheets-through-nodemcu-632358
  3. Use the following code for the script
  4. Deploy as webapp and retrieve your url: (mine) https://script.google.com/macros/s/<YOUR_GS_ID>/exec
  5. Add parameters: https://script.google.com/macros/s/<YOUR_GS_ID>/exec?temperature=22.2&humidity=43.2&ppm=1445
  6. Push data to Sheets using your WEMOS!
  7. Succes now we make graphs

## Optioneel
- Deepsleep en Batterijen -> https://makecademy.com/esp8266-battery

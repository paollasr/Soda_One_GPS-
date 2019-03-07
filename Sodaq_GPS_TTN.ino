//Sodaq One Board - Configuration to send lat and long to TTN

#include <TheThingsNetwork.h>
#include <Arduino.h>
#include <Sodaq_UBlox_GPS.h>


#define MySerial        SERIAL_PORT_MONITOR

void setup()
{
    delay(3000);
    while (!SerialUSB) {
        // Wait for USB to connect
    }

    MySerial.begin(57600);

    MySerial.println("SODAQ LoRaONE test GPS");

    sodaq_gps.init(GPS_ENABLE);
    sodaq_gps.setDiag(MySerial);
}

void loop()
{
  //float latitude and longitude values
  float flat, flon;
  
    MySerial.println("waiting in loop() ...");

    if (sodaq_gps.scan(true))
    {
     
      MySerial.print("Latitude ");
      MySerial.print(sodaq_gps.getLat() == flat, 13);
      MySerial.print("Longitude ");
      MySerial.print(sodaq_gps.getLon() == flon, 13);
      MySerial.print(" Altitude ");
      MySerial.print(sodaq_gps.getAlt(), 1);
      MySerial.print(" and HDOP ");
      MySerial.println(sodaq_gps.getHDOP(), 2);
    }
    delay(60000);


  uint32_t lat = flat * 1000000;
  uint32_t lon = flon * 1000000;

  SerialUSB.println(lat);
  SerialUSB.println(lon);
byte payload[8];
  
  payload[0] = lat >> 24;
  payload[1] = lat >> 16;
  payload[2] = lat >> 8;
  payload[3] = lat;
  
  payload[4] = lon >> 24;
  payload[5] = lon >> 16;
  payload[6] = lon >> 8;
  payload[7] = lon;
  
  ttn.sendBytes(payload, sizeof(payload));

    
}


/*
 * Payload func
 * 
  function Decoder(bytes, port) {
  
  var lat = ((bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3]) / 1000000;
  var lon = ((bytes[4] << 24) | (bytes[5] << 16) | (bytes[6] << 8) | bytes[7]) / 1000000;

  return {
 
    lat: lat,
    lon: lon,
  }
}

/*

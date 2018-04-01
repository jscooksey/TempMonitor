// This #include statement was automatically added by the Particle IDE.
#include <SparkFunMAX17043.h>
#include <Adafruit_DHT.h>

// Name:            Photon Temperature to Azure
// Modified by:     Justin S. Cooksey
// 20180326:        Added battery percentage in to JSON.  No data yet, waiting on sield arival
//                  Also expecting DHT22 for better read, as well as DHT11 is providing no data at this time

#define DHTPIN 2            // DHT11 connected to pin D2  
#define DHTTYPE DHT11		// DHT11 currently   

DHT dht(DHTPIN, DHTTYPE);  

void setup()  
{  
    dht.begin();  
    delay(10000);  
    //lipo.begin();
    //lipo.quickStart();
}  
void loop()  
{  
    char payload[62];
    
    //Maximum delay if using a Free (F1) Azure IoT Hub Instance (8000 request per month) that resets monthly
    delay(652000);  

    // Get data from the sensors    
    float humidity = dht.getHumidity();  
    float temperature = dht.getTempCelcius();  
    //float battery = lipo.getSOC();
    float battery = 95.0; 
     
    // Format JSON string of data to return to Particle via publish command.  This is then hooked to Azure
    snprintf(payload, sizeof(payload), "{\"temperature\":\"%f\",\"humidity\":\"%f\",\"battery\":\"%f\"}",temperature,humidity,battery);  
    Particle.publish("temperature", payload);

}   


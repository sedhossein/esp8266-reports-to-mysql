#include <SPI.h>
#include <ESP8266WiFi.h>

/*
 connection rule = 
      1- black connect to gnd
      2- yellow connect to GPIO0
      3- red connect to Vin 
*/

byte sensorInterrupt = 0; 
byte sensorPin       = 2; // Flow Meter Pin number

float calibrationFactor = 4.5;

unsigned long  month_counter = 0;
unsigned long day_counter = 0;

volatile byte pulseCount;  // Measures flow meter pulses

float flowRate;
double flowMilliLitres;
double totalMilliLitres_perDay;
double totalMilliLitres_perMonth;
double totalMilliLitres;

unsigned long oldTime;

char ssid[] = ""; // WIFI name
char password[] = ""; // WIFI password 
int status = WL_IDLE_STATUS;
WiFiClient client;

char server[] = "XX.XXX.XXX.XXX"; //Server

// ========== Functions ==========
void pulseCounter() // DEBI Frequency
{
  pulseCount++;
}

void setup() 
{
    Serial.begin(115200);
    delay(10); 
    connectWifi();
  
    pinMode(sensorPin, INPUT);
    digitalWrite(sensorPin, HIGH);

    pulseCount        = 0;
    flowRate          = 0.0;
    flowMilliLitres   = 0.0; 
    oldTime           = 0;
    totalMilliLitres_perMonth = 0.0;
    totalMilliLitres_perDay  = 0.0;
    totalMilliLitres = 0.0;

    attachInterrupt(sensorInterrupt, pulseCounter, FALLING); // Setup Interrupt 
}

void connectWifi() // Attempt to connect to wifi network
{
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() 
{
    if((millis() - oldTime) > 1000) // Proccess will be calculate just once in second
    { 
        detachInterrupt(sensorInterrupt);
        flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
        oldTime = millis();
        flowMilliLitres = (flowRate / 60) * 1000;
    
        totalMilliLitres_perDay += flowMilliLitres;
        totalMilliLitres_perMonth += flowMilliLitres;
        totalMilliLitres += flowMilliLitres;
      
        unsigned int frac;
    
        Serial.print("Flow rate: ");
        Serial.print(int(flowRate));
        Serial.print(".");

        frac = (flowRate - int(flowRate)) * 10;
        Serial.print(frac, DEC) ;
        Serial.print(" L/min");

        Serial.print("  Current Liquid Flowing: ");
        Serial.print(flowMilliLitres);
        Serial.print(" mL/Sec");

        Serial.print("  Output Liquid Quantity: ");
        Serial.print(totalMilliLitres);
        Serial.print(" mL\n");
    
        pulseCount = 0;
    
        attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
        ++month_counter;
        ++day_counter;

        String DatatoSend ="";       
      
        DatatoSend += "data=";
        DatatoSend += (totalMilliLitres);
        DatatoSend += "";
        Serial.println("DatatoSend : " + DatatoSend + "\n");

        if(client.connect(server, 80))
        {  
            Serial.println("\nconnected...");
            Serial.println("ARDUINO: forming HTTP request message");
    
            client.print("GET ");
            client.print("/flowMeter.php?"); // server side address
            client.print(DatatoSend);
            client.print(" HTTP/1.1");
            client.print("\r\n");
            client.print("User-Agent: Arduino1\r\n");
            client.print("Content-Type: application/x-www-form-urlencoded\r\n");
            client.print("Connection: Keep-Alive\r\n");
            client.print("\n\n"); 

            Serial.println("ARDUINO: HTTP message sent");
            delay(3000);
            if(client.available())
            {
                Serial.println("ARDUINO: HTTP message received");
                Serial.println("ARDUINO: printing received headers and script response...\n");
      
                while(client.available())
                {
                    char c = client.read();
                    Serial.print(c);
                }
            }
            else
            {
                Serial.println("ARDUINO: no response received / no response received in time");
            }
            client.stop();
        }
        else
        {
            Serial.println("connection failure");
        }

    }

    if(day_counter == 86400)
    {
        Serial.print("  One Day Total Usage =  ");
        Serial.print(totalMilliLitres_perDay);
        Serial.println(" mL");
        day_counter = 0;
        totalMilliLitres_perDay = 0.0;
    }

    if(month_counter == 86400 * month_day)
    {
        Serial.print("  One Month Total Usage =  ");
        Serial.print(totalMilliLitres_perMonth);
        Serial.println(" mL");
        month_counter = 0;
        totalMilliLitres_perMonth = 0.0;
    }
   
}

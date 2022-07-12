#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define API_KEY ""
#define DATABASE_URL ""

FirebaseData JP;

int red = D1;
int green = D2;
int blue = D3;
int i;
int color;
int r = 60;
int g = 0;
int b = 0;
int t=50;
int white = D4;

void setup() 
{
  Serial.begin(115200);
delay(2000);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(DATABASE_URL, API_KEY);
  
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(white,OUTPUT);
 
}

void RGB_color(int red_light_value,int green_light_value,int blue_light_value)
{
  analogWrite(red,red_light_value);
  analogWrite(green,green_light_value);
  analogWrite(blue,blue_light_value);
}

void loop() 
{
  label:
  switch(color)
    {
      case 1:
      digitalWrite(white,LOW);
      RGB_color(255, 0, 0); // Red
      break;
      case 2:
      digitalWrite(white,LOW);
      RGB_color(0, 255, 0); // Green
      break;
      case 3:
      digitalWrite(white,LOW);
      RGB_color(0, 0, 255); // Blue
      break;
      case 4:
      digitalWrite(white,LOW);
      RGB_color(255, 255, 125); // Raspberry
      break;
      case 5:
      digitalWrite(white,LOW);
      RGB_color(0, 255, 255); // Cyan
      break;
      case 6:
      digitalWrite(white,LOW);
      RGB_color(255, 0, 255); // Magenta
      break;
      case 7:
      digitalWrite(white,LOW);
      RGB_color(255, 255, 0); // Yellow
      break;
      case 8:
      digitalWrite(white,LOW);
      RGB_color(255, 255, 255); // White
      break;
      case 9:     //Dancing Mode
      {
        while(1)
        {
            digitalWrite(white,LOW);
            for (/* no initialization */; r>=0, b<60; b++, r--) /*red -> blue*/
            {
            analogWrite(red, r);
            analogWrite(blue, b);
            delay(10);
            }
            
            for (/* no initialization */; b>=0, g<60; g++, b--) /*blue -> green*/
            {
            analogWrite(blue, b);
            analogWrite(green, g);
            delay(10);
            }
  
            for (/* no initialization */; g>=0, r<60; r++, g--) /*green -> red*/
            {
            analogWrite(red, r);
            analogWrite(green, g);
            delay(10);
            }
           Firebase.getInt(JP,"/RGB/Mode",&color);
           if(color!=9)
           {
            goto label;
            }
        }            
      } 
     case 10:      //Gaming Mode
      {
        while(1)
        {
           digitalWrite(white,LOW);
           for (/* no initialization */; r>=0, b<60; b++, r--) /*red -> blue*/
            {
            analogWrite(red, r);
            analogWrite(blue, b);
            delay(100);
            }

            for (/* no initialization */; b>=0, g<60; g++, b--) /*blue -> green*/
            {
            analogWrite(blue, b);
            analogWrite(green, g);
            delay(100);
            }
  
            for (/* no initialization */; g>=0, r<60; r++, g--) /*green -> red*/
            {
            analogWrite(red, r);
            analogWrite(green, g);
            delay(100);
            }
           Firebase.getInt(JP,"/RGB/Mode",&color);
           if(color!=10)
           {
            goto label;
            }
           }
        }

    case 11:     //Night Mode
    digitalWrite(white,LOW);
    RGB_color(0, 20, 20);
    break;  
   
   case 12:             //red-blue
   {
    while(1)
    {
     digitalWrite(white,LOW);
     for(;150<=r<=200, b<150; b++, r--)
     {
      analogWrite(red, r); 
      analogWrite(blue, b); 
      delay(t); 
     }
      for (; b>=0, r<155; r++, b--)
      {
       analogWrite(red, r); 
       analogWrite(blue, b);
       delay(t);
      }
     Firebase.getInt(JP,"/RGB/Mode",&color);
     if(color!=12)
     {goto label;
      }
     }
   }
 
   case 13:      //red-green
   {
    while(1)
    {
    digitalWrite(white,LOW);
    for (; g>=0, r<255; r++, g--)
    {
     analogWrite(red, r); 
     analogWrite(green, g);
     delay(t);
    }
    for(;150<=r<=255, g<150; g++, r--)
    {
      analogWrite(red, r); 
      analogWrite(green, g); 
      delay(t); 
    }
    Firebase.getInt(JP,"/RGB/Mode",&color);
    if(color!=13)
    {
     goto label;
    }
    }
    }
    case 14:      //green-blue
   {
    while(1)
    {
      digitalWrite(white,LOW);
      for(;150<=g<=255, b<150; b++, g--)
      {
       analogWrite(green, g); analogWrite(blue, b); 
       delay(t); 
       }
      for (;150<=b<=0, g<170; g++, b--)
      {
       analogWrite(blue, b); analogWrite(green, g);
       delay(t);
       }
    Firebase.getInt(JP,"/RGB/Mode",&color);
    if(color!=14)
    {
     goto label;
     }
    }
  }
  
    case 15:
    RGB_color(0, 0, 0); //Led off
    digitalWrite(white,LOW);
    break;
 
    case 16:
    RGB_color(0,0,0);
    digitalWrite(white,HIGH);
    break;
    }
  
if(Firebase.ready())
{
  Firebase.getInt(JP,"/RGB/Mode",&color);
  Serial.println(color);
 }
}

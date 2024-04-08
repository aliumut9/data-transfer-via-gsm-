
#include <MAX471.h>
#include <Wire.h>
#include <SoftwareSerial.h>
SoftwareSerial gsm(10, 11);
#define VT_pin A3
#define AT_pin A1
double voltaj;
double amper;
String numara =  "+905306*****";
String _tampon;
char gelen;

void setup()

{
  pinMode(VT_pin, OUTPUT);
  pinMode(AT_pin, OUTPUT);
  
  _tampon.reserve(50);
  delay(1000);
  Serial.begin(115200);
  Serial.println("SİSTEM AÇILDI");
  gsm.begin(115200);
  delay(1000);

}
void loop() 
  Serial.println("GİRİS İCİN TUSLAYINIZ");
  delay(1000);
  gelen = gsm.read(); 
  if (gelen == 'v')
   { 
   Serial.println("ife girdi v");
   olcum_vt();
   }
  }

  void olcum_vt(){
  digitalWrite(A1, HIGH);
  delay(1000);
  digitalWrite(A1, LOW);
  delay(1000);
 
  double at_deger = analogRead(AT_pin);
  double amper_kalibre = 0.65;
  double amper = at_deger * (5.0 / 1023.0) * amper_kalibre * 0.1 ;
Serial.println("AMPER ÖLÇÜLDÜ");
  digitalWrite(A1, HIGH);
  delay(1000);
  digitalWrite(A1, LOW);
  delay(1000);
  
  digitalWrite(A3, HIGH);
  delay(1000);
  digitalWrite(A3, LOW);
  delay(1000);
  double vt_deger = analogRead(VT_pin);//0-1023
  double voltaj_kalibre = 18.6;
  double voltaj = at_deger * (5.0 / 1023.0) * voltaj_kalibre  ; 
Serial.println("VOLTAJ ÖLÇÜLDÜ");
  delay(2000);
  digitalWrite(A3, HIGH);
  delay(2000);
  digitalWrite(A3, LOW);

  Serial.println(String(voltaj));
  Serial.println("V");
  Serial.println(String(amper));
  Serial.println("A");
  
  Serial.println("SMS GONDERE GİRDİ");
  gsm.println("AT+CMGF=1");
  delay(1000);
  gsm.println("AT+CMGS=\"" + numara + "\"\r");
  delay(1000);
  
  String SMS = "VOLTAGE: " + String(voltaj) + "V" "    CURRENT:" + String(amper)+ "A";
  gsm.println(String (SMS));
  delay(100);
  gsm.println((char)26);
  delay(1000);
 
 }

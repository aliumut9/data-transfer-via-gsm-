#include <MAX471.h>
#include <Wire.h>
#include <SoftwareSerial.h>
SoftwareSerial gsm(10, 11);
#define VT_pin A3
#define AT_pin A1
double voltaj;
double amper;
int sayac = 5;
String numara =  "+905306356714";
String _tampon;
void setup()

{
  pinMode(VT_pin, OUTPUT);
  pinMode(AT_pin, OUTPUT);
  
  _tampon.reserve(50);
  delay(5000);
  Serial.begin(115200);
  Serial.println("System Started...");
  gsm.begin(115200);
  delay(1000);
}

void loop() {
  delay(5000);
  sayac++;
  Serial.println(String(sayac));
  if (sayac == 6) {//360 bir saat
    olcum_vt();
    sayac = 0;
  }
}

  void olcum_vt(){
  digitalWrite(A1, HIGH);
  delay(2000);
  digitalWrite(A1, LOW);
  delay(2000);
  double at_deger = analogRead(AT_pin);
  double amper_kalibre = 0.65;
  double amper = at_deger * (5.0 / 1023.0) * amper_kalibre * 0.1 ;

  digitalWrite(A1, HIGH);
  delay(2000);
  digitalWrite(A1, LOW);
  delay(5000);
  digitalWrite(A3, HIGH);
  delay(2000);
  digitalWrite(A3, LOW);
  delay(5000);
  double vt_deger = analogRead(VT_pin);//0-1023
  double voltaj_kalibre = 18.6;
  double voltaj = at_deger * (5.0 / 1023.0) * voltaj_kalibre  ; //0.004
  delay(2000);
  digitalWrite(A3, HIGH);
  delay(2000);
  digitalWrite(A3, LOW);
  Serial.println(String(voltaj));
  Serial.println("V");
  Serial.println(String(amper));
  Serial.println("A")
  gsm.println("AT+CMGF=1");
  delay(1000);
  gsm.println("AT+CMGS=\"" + numara + "\"\r");
  delay(1000);
  
  String SMS = "VOLTAGE: " + String(voltaj) + "V" "    CURRENT:" + String(amper)+ "A";
  gsm.println(SMS);
  delay(100);
  gsm.println((char)26);
  delay(1000);

}

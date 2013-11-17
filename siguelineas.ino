// Sugielineas
// bricolabs.cc


#include <Servo.h> 
 
Servo Rservo;
Servo Lservo;
const int R0 = 78; // 2
const int L0 = 81; // 1
int Rspeed = 10;
int Lspeed = 10;
 
int right = 0;    // variable to store the servo position 
int left = 0;
int origenRight = 0;
int origenLeft = 0;
int umbral = 100;

 
void setup() 
{ 
  Rservo.attach(8);
  Lservo.attach(9);
  Serial.begin(9600);
  
  Rservo.write(R0);
  Lservo.write(L0);
  
  // obtenemos un patrón de luminosidad del fondo
  int repeticiones = 50;
  for (int i = 0; i< repeticiones; i++) 
  {
      origenRight += analogRead(A0);
      origenLeft += analogRead(A1);
      if (i%2 == 0)
      {
        Rservo.write(R0);
        Lservo.write(L0+(Lspeed/2));
      } else {
        Rservo.write(R0+(Lspeed/2));
        Lservo.write(L0);
      }
      delay(20);
  }
  Rservo.write(R0);
  Lservo.write(L0);
  origenRight = origenRight/repeticiones; // media
  origenLeft = origenLeft/repeticiones;
  
  delay(2000);
} 
 
 
void loop() 
{ 
  right = analogRead(A0);
  left = analogRead(A1);
  
  if (origenRight - right > umbral) 
  {
    Rservo.write(R0-Rspeed/2);
    Lservo.write(L0+Lspeed*2);
    Serial.println("Gira a la derecha");
  }
  else if (origenLeft - left > umbral)
  {
    Rservo.write(R0+Rspeed*2);
    Lservo.write(L0-Lspeed/2);
    Serial.println("Gira a la izquierda");
  }
  else
  {
    Rservo.write(R0+Rspeed); 
    Lservo.write(L0+Lspeed); 
    Serial.println("sigue de frente");
  }
} 


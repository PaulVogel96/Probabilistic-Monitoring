#include "StandardCplusplus.h"

int charactersSent;
String satisfyingSequence1 = "XXQPPPPRXX";
String satisfyingSequence2 = "XXXXQRXXXX";
String satisfyingSequence3 = "XPXPXXXRXR";
String satisfyingSequence4 = "XXXXXXXXXX";

void setup() {
  Serial.begin(9600);
  Serial.flush();
  charactersSent = 0;
}

void loop() {
  if (Serial.available()) {
    if(charactersSent <= 1000){
      int r = random(1, 5);
      switch (r)
      {
      case 1:
          Serial.print("XXQPPPPRXX");
          break;
      case 2:
          Serial.print("XXXXQRXXXX");
          break;
      case 3:
          Serial.print("XPXPXXXRXR");
          break;
      case 4:
          Serial.print("XXXXXXXXXX");
          break;
      default:
          break;
      }
      charactersSent+=10;
    }
  }
}
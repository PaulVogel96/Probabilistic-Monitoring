#include <SoftwareSerial.h>
SoftwareSerial link(10, 6);

void setup() {
  link.begin(9600);
}

void loop() {
  link.write('a');
  delay(500);
  link.write('b');
  delay(1000);
}
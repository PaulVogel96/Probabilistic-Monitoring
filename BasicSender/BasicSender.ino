// Uno_UART_sender.ino
#include <SoftwareSerial.h>
SoftwareSerial link(10, 6); // RX not used here, TX = pin 6

void setup() {
  link.begin(9600);
}

void loop() {
  link.write('a');  // send byte 'a'
  delay(500);
  link.write('b');  // send byte 'b'
  delay(1000);
}
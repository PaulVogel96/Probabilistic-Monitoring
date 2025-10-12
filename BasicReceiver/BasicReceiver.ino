// Mega_UART_receiver.ino
void setup() {
  Serial.begin(9600);   // USB serial to PC
  Serial1.begin(9600);  // hardware Serial1 (pins 19 RX1, 18 TX1)
  while (!Serial) {}    // wait for monitor
  Serial.println("Mega UART receiver ready");
}

void loop() {
  if (Serial1.available()) {
    char c = Serial1.read();
    Serial.print("Received: ");
    Serial.println(c);
  }
}

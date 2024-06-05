#include <pio_encoder.h>

double previous_pos = 0;
unsigned long previous_time = 0;
PioEncoder encoder(2);
double v1;
unsigned long interval = 100;

void setup() {
  encoder.begin();
  Serial.begin(115200);
}

void velocity(double current_time) {
  double Position = encoder.getCount(); // Use double for consistency with previous_pos
  v1 = (((Position - previous_pos) * 2 * 3.142 *interval) / 4096.0); // Corrected calculations with floating-point precision
  previous_pos = Position;
  Serial.println(v1);
}

void loop() {
  unsigned long current_time = millis();
  if (current_time - previous_time >= interval) {
    velocity(current_time);
    previous_time = current_time;
  }
}

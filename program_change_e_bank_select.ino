/*IMPLEMENTAÇÃO MIDI DE MUDANÇA DE PROGRAM\VOICE\PRESET E SELEÇÃO DE BANCO MAIS REPRESENTATIVO
  ROBERTO GOMES 31/01/2020
*/
byte program = 0;
byte msb = 0; //CC MSB Bank Select

#define prox 2 //digital pin arduino(preset +)
#define ante 3 //digital pin arduino(preset -)

#define prox_bank 4 //digital pin arduino(bank +)
#define ante_bank 5 //digital pin arduino(bank -)

void setup() {
  Serial.begin(115200);
  pinMode(prox, INPUT_PULLUP);
  pinMode(ante, INPUT_PULLUP);
  pinMode(prox_bank, INPUT_PULLUP);
  pinMode(ante_bank, INPUT_PULLUP);
}
void loop() {
  if (digitalRead(prox) == LOW && program < 127) {
    program++; program_change(0xc0, program); delay(200);
  }
  if (digitalRead(ante) == LOW && program > 0) {
    program--; program_change(0xc0, program); delay(200);
  }
  if (digitalRead(prox_bank ) == LOW && msb < 127) {
    msb++; control_change(0xb0, 0, msb); delay(200);
  }
  if (digitalRead(ante_bank ) == LOW && msb > 0) {
    msb--; control_change(0xb0, 0, msb); delay(200);
  }
}
void program_change(byte Status, byte Data) {
  Serial.write(Status);
  Serial.write(Data);
}
void control_change(byte cc_Status, byte Command, byte Value) {
  Serial.write(cc_Status);
  Serial.write(Command);
  Serial.write(Value);
}

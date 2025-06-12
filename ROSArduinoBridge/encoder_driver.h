/* *************************************************************
   Encoder driver function definitions - by James Nugen
   ************************************************************ */
   
#ifdef ARDUINO_ENC_COUNTER
  // MOTOR LEFT A (A2, A3 → PORTC)
  #define LEFT_ENC_PIN_A PC2
  #define LEFT_ENC_PIN_B PC3

  // MOTOR RIGHT B (D2, D3 → PORTD)
  #define RIGHT_ENC_PIN_A PD2
  #define RIGHT_ENC_PIN_B PD3
#endif

long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();



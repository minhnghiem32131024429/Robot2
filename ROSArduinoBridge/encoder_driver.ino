/* *************************************************************
   Encoder definitions
   
   Add an "#ifdef" block to this file to include support for
   a particular encoder board or library. Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   ************************************************************ */
   
#ifdef USE_BASE

#ifdef ROBOGAIA
  /* The Robogaia Mega Encoder shield */
  #include "MegaEncoderCounter.h"

  /* Create the encoder shield object */
  MegaEncoderCounter encoders = MegaEncoderCounter(4); // Initializes the Mega Encoder Counter in the 4X Count mode
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return encoders.YAxisGetCount();
    else return encoders.XAxisGetCount();
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT) return encoders.YAxisReset();
    else return encoders.XAxisReset();
  }
#elif defined(ARDUINO_ENC_COUNTER)

  volatile long left_enc_pos = 0L;
  volatile long right_enc_pos = 0L;

  // Encoder state lookup table for quadrature decoding
  static const int8_t ENC_STATES [] = {
    0,  1, -1,  0,
   -1,  0,  0,  1,
    1,  0,  0, -1,
    0, -1,  1,  0
  };

  /* Interrupt routine for RIGHT encoder (D2/D3 -> PD2/PD3 -> PIND -> PCINT2_vect) */
  ISR(PCINT2_vect) {
    static uint8_t enc_last_right = 0;
    enc_last_right <<= 2;
    enc_last_right |= (PIND >> 2) & 0x03; // read PD2, PD3 into lower bits
    right_enc_pos -= ENC_STATES[enc_last_right & 0x0F];
  }

  /* Interrupt routine for LEFT encoder (A2/A3 -> PC2/PC3 -> PINC -> PCINT1_vect) */
  ISR(PCINT1_vect) {
    static uint8_t enc_last_left = 0;
    enc_last_left <<= 2;
    enc_last_left |= (PINC >> 2) & 0x03; // read PC2, PC3 into lower bits
    left_enc_pos += ENC_STATES[enc_last_left & 0x0F];
  }

  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return left_enc_pos;
    else return right_enc_pos;
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT) {
      left_enc_pos = 0L;
    } else {
      right_enc_pos = 0L;
    }
  }

#else
  #error A encoder driver must be selected!
#endif

/* Wrap the encoder reset function */
void resetEncoders() {
  resetEncoder(LEFT);
  resetEncoder(RIGHT);
}

#endif


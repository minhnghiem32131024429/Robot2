/***************************************************************
   Motor driver function definitions - by James Nugen
   *************************************************************/

#ifdef L298_MOTOR_DRIVER
  // IN3 MB
  #define LEFT_MOTOR_BACKWARD  6
  // IN4 MB
  #define LEFT_MOTOR_FORWARD   10
  // ENB
  #define LEFT_MOTOR_ENABLE    A1  // Đã chuyển từ D13 sang A1 để nhường SPI
  // IN1 MA
  #define RIGHT_MOTOR_BACKWARD 5
  // IN2 MA
  #define RIGHT_MOTOR_FORWARD  9
  // ENA
  #define RIGHT_MOTOR_ENABLE   12

#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);

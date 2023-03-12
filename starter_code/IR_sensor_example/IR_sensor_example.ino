int ir_left = 13;
int ir_right = 12;

int left_wheel_speed = 0;
int right_wheel_speed = 0;
int left_wheel = 0;
int right_wheel = 0;
int r_in1 = 0;
int r_in2 = 0;
int l_in1 = 0;
int l_in2 = 0;


void setup() {
  // starting up the clock
  Serial.begin(9600);

  // intializing IR sensors
  pinMode(ir_left, INPUT);
  pinMode(ir_right, INPUT);

  // Set all the motor control pins to outputs
	pinMode(left_wheel, OUTPUT);
	pinMode(right_wheel, OUTPUT);
	pinMode(l_in1, OUTPUT);
	pinMode(l_in2, OUTPUT);
	pinMode(r_in1, OUTPUT);
	pinMode(r_in2, OUTPUT);
	
	// Turn off motors - Initial state
  // self note for dicretions: 
	digitalWrite(l_in1, LOW);
	digitalWrite(l_in2, LOW);
	digitalWrite(l_in1, LOW);
	digitalWrite(l_in2, LOW);
}

void initial_startup_test(){
  // function takes in all parameters of wheels and sets the initial speed to ~10%
  // waits for 3 seconds then shuts off the motors
	digitalWrite(l_in1, LOW);
	digitalWrite(l_in2, HIGH);
  digitalWrite(r_in1, LOW);
	digitalWrite(r_in2, HIGH);

  analogWrite(left_wheel, 25);
  analogWrite(right_wheel, 25);

  delay(5000);

  analogWrite(left_wheel, 0);
  analogWrite(right_wheel, 0);
}

void set_motor_speed(int wheel, int target_speed){
  // making sure we dont shoot ourselves 
  analogWrite(wheel, target_speed);
}

int full_speed_fwd(){
  // set motor directions
  // self note for directions: 
	digitalWrite(l_in1, LOW);
	digitalWrite(l_in2, HIGH);
  digitalWrite(r_in1, LOW);
	digitalWrite(r_in2, HIGH);

  // set motor speeds
  set_motor_speed(left_wheel, 255);
  set_motor_speed(right_wheel, 255);

  // record motor speeds
  left_wheel_speed = 255;
  right_wheel_speed = 255;
}

void turn_right(){
  // slow down both motors to 20%
  set_motor_speed(left_wheel, 50);
  set_motor_speed(right_wheel, 50);

  // slow down one side to turn 
  set_motor_speed(right_wheel, 20);
  delay(250);

  // set motors back to 20%
  set_motor_speed(left_wheel, 50);
  set_motor_speed(right_wheel, 50);
  left_wheel_speed = 25;
  right_wheel_speed = 25;
}

void turn_left(){
  // slow down both motors to 20%
  set_motor_speed(left_wheel, 50);
  set_motor_speed(right_wheel, 50);

  // slow down one side to turn 
  set_motor_speed(left_wheel, 20);
  delay(250);

  // set motors back to 20%
  set_motor_speed(left_wheel, 50);
  set_motor_speed(right_wheel, 50);
  left_wheel_speed = 50;
  right_wheel_speed = 50;
}

void stop(){
  set_motor_speed(left_wheel, 0);
  set_motor_speed(right_wheel, 0);
  left_wheel_speed = 0;
  right_wheel_speed = 0;
}


void loop() {
  int ir_left_reading = digitalRead(ir_left);
  int ir_right_reading = digitalRead(ir_right);

  if (ir_left_reading == 0 && ir_right_reading == 0){
    Serial.println("both sensors on white");
    full_speed_fwd();
  }
  else if (ir_left_reading == 1 && ir_right_reading == 0){
    Serial.println("left sensor on black");
    turn_right();
  }
  else if (ir_left_reading == 0 && ir_right_reading == 1){
    Serial.println("right sensor on black");
    turn_left();
  }
  else {
    Serial.println("both sensors on black???");
    stop();
  }
}

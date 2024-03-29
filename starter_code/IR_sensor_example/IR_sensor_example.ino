int ir_left = 12;
int ir_right = 13;

int left_wheel_speed = 0;
int right_wheel_speed = 0;
int left_wheel = 5;
int right_wheel = 6;
int r_in1 = 9;
int r_in2 = 8;
int l_in1 = 3;
int l_in2 = 2;
int count = 0;


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
	digitalWrite(r_in1, LOW);
	digitalWrite(r_in2, LOW);
}

void initial_startup_test(){
  // function takes in all parameters of wheels and sets the initial speed to ~10%
  // waits for 3 seconds then shuts off the motors
	digitalWrite(l_in1, HIGH);
	digitalWrite(l_in2, LOW);
  digitalWrite(r_in1, HIGH);
	digitalWrite(r_in2, LOW);

  analogWrite(left_wheel, 150);
  analogWrite(right_wheel, 150);

  delay(1000);

  analogWrite(left_wheel, 0);
  analogWrite(right_wheel, 0);

  Serial.println("done");
  delay(1000);
  Serial.println("done2");
}

void set_motor_speed(int wheel, int target_speed){
  // making sure we dont shoot ourselves 
	digitalWrite(l_in1, HIGH);
	digitalWrite(l_in2, LOW);
  digitalWrite(r_in1, HIGH);
	digitalWrite(r_in2, LOW);
  analogWrite(wheel, target_speed);
  Serial.println(target_speed);
}

int full_speed_fwd(){
  // set motor directions
  // self note for directions: 
	digitalWrite(l_in1, HIGH);
	digitalWrite(l_in2, LOW);
  digitalWrite(r_in1, HIGH);
	digitalWrite(r_in2, LOW);

  // set motor speeds
  if (count == 0){
  set_motor_speed(left_wheel, 225);
  set_motor_speed(right_wheel, 225);
  count = 1;
  }
  delay(20);
  set_motor_speed(left_wheel, 150);
  set_motor_speed(right_wheel, 150);

  // record motor speeds
  left_wheel_speed = 100;
  right_wheel_speed = 100;
}

void turn_right(){
  // slow down both motors to 20%
  set_motor_speed(left_wheel, 0);
  set_motor_speed(right_wheel, 0);

  if (count == 0){
  set_motor_speed(left_wheel, 225);
  count = 1;
  }
  delay(20);
  set_motor_speed(left_wheel, 150);
  set_motor_speed(right_wheel, 200);
  digitalWrite(r_in1, LOW);
	digitalWrite(r_in2, HIGH);
 

  //set_motor_speed(left_wheel, 150);
  //set_motor_speed(right_wheel, 150);
 // delay(50);


  // slow down one side to turn 
  // set_motor_speed(right_wheel, 100);
  // delay(1000);

  // set motors back to 20%
  // set_motor_speed(left_wheel, 100);
  // set_motor_speed(right_wheel, 100);
}

void turn_left(){
  // slow down both motors to 20%
  set_motor_speed(left_wheel, 0);
  set_motor_speed(right_wheel, 0);
  if (count == 0){
  set_motor_speed(right_wheel, 225);
  count = 1;
  }
  delay(20);
  set_motor_speed(left_wheel, 200);
  set_motor_speed(right_wheel, 150);
  digitalWrite(l_in1, LOW);
	digitalWrite(l_in2, HIGH);
  //set_motor_speed(left_wheel, 150);
  //set_motor_speed(right_wheel, 150);
  //delay(50);

  // slow down one side to turn 
  // set_motor_speed(left_wheel, 100);
  // delay(1000);

  // set motors back to 20%
  // set_motor_speed(left_wheel, 100);
  // set_motor_speed(right_wheel, 100);
  left_wheel_speed = 50;
  right_wheel_speed = 50;
}

void stop(){
  set_motor_speed(left_wheel, 0);
  set_motor_speed(right_wheel, 0);
	digitalWrite(l_in1, LOW);
	digitalWrite(l_in2, LOW);
	digitalWrite(r_in1, LOW);
	digitalWrite(r_in2, LOW);
}

void loop() {
  int ir_left_reading = digitalRead(ir_left);
  int ir_right_reading = digitalRead(ir_right);

  if (ir_left_reading == 0 && ir_right_reading == 0){
    Serial.println("both sensors on white");
    // initial_startup_test();
    full_speed_fwd();
  }
  else if (ir_left_reading == 1 && ir_right_reading == 0){
    // count = 0;
    Serial.println("left sensor on black");
    turn_right();
    count = 0;
  }
  else if (ir_left_reading == 0 && ir_right_reading == 1){
    // count = 0;
    Serial.println("right sensor on black");
    turn_left();
    count = 0;
  }
  else {
    Serial.println("both sensors on black???");
    stop();
    count = 0;
  }
}

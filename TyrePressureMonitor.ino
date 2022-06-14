#define INIT_STATE 0
#define LightOn_STATE 1
#define LightOff_STATE 2

#define frontL_Pressure A0
#define frontR_Pressure A1
#define rearL_Pressure A2
#define rearR_Pressure A3
#define PWM_LIGHT 7

#define Light_ON 255
#define Light_OFF 0

int frontR;
int frontL;
int rearR;
int rearL;
int currentState = 0;

void setup()
{
  currentState = INIT_STATE;
  
  pinMode(PWM_LIGHT, OUTPUT);
  pinMode(frontL_Pressure, INPUT );
  pinMode(frontR_Pressure, INPUT );
  pinMode(rearL_Pressure, INPUT );
  pinMode(rearR_Pressure, INPUT );
  Serial.begin(9600);
  
  currentState = LightOn_STATE;
  
}

void loop()
{
  if (currentState == LightOn_STATE){
    frontR = analogRead(frontR_Pressure);
    frontL = analogRead(frontL_Pressure);
    rearR = analogRead(rearR_Pressure);
    rearL = analogRead(rearL_Pressure);
    analogWrite(PWM_LIGHT,Light_ON);
    
    if ((frontR && frontL && rearR && rearL < 185)
        && (frontR && frontL && rearR && rearL > 165)) {
      
      analogWrite(PWM_LIGHT,Light_OFF);
      currentState = LightOff_STATE;
    }
  }
  
  if (currentState == LightOff_STATE){
    frontR = analogRead(frontR_Pressure);
    frontL = analogRead(frontL_Pressure);
    rearR = analogRead(rearR_Pressure);
    rearL = analogRead(rearL_Pressure);
    analogWrite(PWM_LIGHT,Light_OFF);
    
     if ((frontR || frontL || rearR || rearL > 185)
        || (frontR || frontL || rearR || rearL < 165)) {
      
      analogWrite(PWM_LIGHT,Light_ON);
      currentState = LightOn_STATE;
    }
  } 
}

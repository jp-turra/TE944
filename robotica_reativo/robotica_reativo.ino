/*

  Created by: Felipe Lindo Demais slk

 

  - Definir se o robô terá sensores laterais

  - Adicionar o valor dos pinos

  - Adicionar os valores de K para movimentação

  - Definir tamanho dos corredores

  - Definir o avanço frontal

 

*/

#define SOUND_SPEED_US .0343
#define	RANDOM_MAX 10
//Ponte H

const int DirR1 = 5;

const int DirR2 = 3;

const int PwmR = 7;

const int DirL1 = 2;

const int DirL2 = 4;

const int PwmL = 6;

 

//LDR

const int LdrRF = 0;

const int LdrRB = 0;

const int LdrLF = 0;

const int LdrLB = 0;

 

//Ultrassonico

const int USR_trigger = 0;

const int USR_echo = 0;

const int USL_trigger = 0;

const int USL_echo = 0;

const int USF_trigger = 36;

const int USF_echo = 34;

const int USB_trigger = 13;

const int USB_echo = 12;

 
int Input[8]  = {LdrRF, LdrRB, LdrLF, LdrLB, USR_echo, USL_echo, USF_echo, USB_echo};

int Output[10]  = {DirR1, DirR2, PwmR, DirL1, DirL2, PwmL, USR_trigger, USL_trigger, USF_trigger, USB_trigger};


void setup() {
  Serial.begin(115200);

  for( int i = 0; i < 8; i++){

    pinMode( Input[i], INPUT );

  }

  for( int i = 0; i < 10; i++){

    pinMode( Output[i], OUTPUT );

  }

}

float DistParede = 300;
float DistFrente = 150;

bool once = false;

void loop() {

  DistFrente = GetDistance(USF_trigger, USF_echo);
  
  delay(10);

  if (DistFrente < 20) {
    if (millis() % 2) {
      Giro(0.3, 100);
    }else {
      Giro(0.3, -100);
    }
    
  }else {
    // DistFrente/20
    Motor(0.3, 'F');
  }
  // Linear(220);
  // delay(5000);
  // Motor(0, 'S');
  // delay(5000);

  // if (!once) {
  //   Linear(220);
  //   // Giro(90);
  //   // Motor(1, 'L');
  //   delay(5000);

  //   // Linear(220);
  //   // Giro(-90);
  //   Motor(0, 'S');
  //   once = true;
  // }

  // Giro(90);

  // if ( GetDistance( USF_trigger, USF_echo ) > DistParede){

  //   Linear( DistFrente );

  // }

  // else if( GetDistance( USB_trigger, USB_echo ) > DistParede){

  //   Giro(180);

  //   Linear( DistFrente );

  // }

  // else{

  //   Giro(90);

  //   if ( GetDistance( USF_trigger, USF_echo ) > DistParede){

  //     Linear( DistFrente );

  //   }

  //   else if( GetDistance( USB_trigger, USB_echo ) > DistParede){

  //     Giro(180);

  //     Linear( DistFrente );

  //   }

  // }

}

 

void Linear( float Dist){

  float K = 1000/220; // [ms/mm] // 1000/277

  if      (Dist > 0) { Motor( 1, 'F' ); }

  else if (Dist < 0) { Motor( 1, 'B' ); }

  delay( (int)(K * abs( Dist )) );

  Motor( 0, 'S' );

}

void Giro( float pwm, float ang ){

    float K = 1000/220; // [ms/°]

    if      (ang > 0) { Motor( pwm, 'L' ); }

    else if (ang < 0) { Motor( pwm, 'R' ); }

    delay( (int)(K * abs( ang )) );

    Motor( 0, 'S' );

}

 

//Determina o sentido e intensidade dos motores. PWM = 0-1 e Sentido = 'R', 'L', 'F' e 'B'

void Motor( float PWM, char Sentido){
 

  if (Sentido == 'R' || Sentido == 'L' || Sentido == 'F' || Sentido == 'B'){  

    bool aux = 0;   //Sentido de giro

    bool aux2 = 0;  //Tipo de giro

   

    if (Sentido == 'R' || Sentido == 'F'){ aux = 1; }

    digitalWrite(DirR1, aux);

    digitalWrite(DirR2, !aux);

    if (Sentido == 'F' || Sentido == 'B'){ aux2 = 1; }

    digitalWrite(DirL1, aux ^ aux2);

    digitalWrite(DirL2, !aux ^ aux2);

 

    analogWrite(PwmR, (PWM * 255));

    analogWrite(PwmL, (PWM * 255));

  }

  else{

    analogWrite(PwmR, 0);

    analogWrite(PwmL, 0);

    // Remover depois de arrumar ponte H
    digitalWrite(DirR1, 0);

    digitalWrite(DirR2, 0);

    digitalWrite(DirL1, 0);

    digitalWrite(DirL2, 0);

  }

}

 

float GetDistance( int Trigger, int Echo){
   

    digitalWrite(Trigger, LOW);

    delayMicroseconds(2);

    digitalWrite(Trigger, HIGH);

    delayMicroseconds(15);

    digitalWrite(Trigger, LOW);

    
    float Time = pulseIn(Echo, HIGH); 

    float Distance =  (Time*SOUND_SPEED_US)/2; //Distância [mm]

    return Distance;

}
/*******************************************************************
* read encoder state 
* 
* Action, Back
* 
* 
*
* 
* // Encoder connected ports
* const int ACT_ENCODER = 30; 
* const int A_ENCODER = 33;
* const int B_ENCODER = 32; 
*
********************************************************************
*/ 

void ReadEncoder()
{

  int act_encoder_state=0, a_encoder_state=0, b_encoder_state=0; 
  String rotate="";
 
/*  
if (debug){
  Serial1.println(" run Read Encoder Data ");
   }  
*/  
if (digitalRead(ACT_ENCODER)==LOW){
  act_encoder_state=1;  // action pressed
  main_command=RIGHT_CMD;
  }

if (digitalRead(A_ENCODER)==LOW){
  a_encoder_state=1;
  }
  
if (digitalRead(B_ENCODER)==LOW){
  b_encoder_state=1;
  }
    
 
 if(a_encoder_state==0&&b_encoder_state==1){
   rotate="CW";
   main_command=RIGHT_CMD;
  }
  
   if(a_encoder_state==1&&b_encoder_state==0){
   rotate="CCW";
   main_command=LEFT_CMD;
  }
  
  
/*
if (debug){
  Serial1.println(" Encoder state... ");
  Serial1.println(" ");
  Serial1.print(" Action =  "); 
  Serial1.print(act_encoder_state);
 
 Serial1.print(" A - 33 State =  "); 
  Serial1.print(a_encoder_state);
 
 Serial1.print(" B - 32 State = "); 
  Serial1.print(b_encoder_state);
   Serial1.println(" ");
   
  Serial1.print(rotate);
  
   Serial1.println(" ");
  }  
 */ 
// and cleasr the state


}

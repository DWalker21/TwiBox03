/*******************************************************************
* read encoder state 
* 
* detect rotary direction and assign commands
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

void add_state(int new_state, unsigned char state[])
{
state[1]=state[0];  
state[0]=new_state;
}

int debounceRead(int pin){
  int read_now, read_last;
  while (read_now!=read_last)
    {
    delay(10);
    read_last=read_now;
    read_now=digitalRead(pin);  
    }
}

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
//  if (debounceRead(ACT_ENCODER)==LOW){
  act_encoder_state=1;  // action pressed
  //main_command=RIGHT_CMD;
  }

if (digitalRead(A_ENCODER)==LOW){
//  if (debounceRead(A_ENCODER)==LOW){
  a_encoder_state=1;
  }
  
if (digitalRead(B_ENCODER)==LOW){
  b_encoder_state=1;
  }
    

// in case we have a changes in comparison with prev state     
if ((a_encoder_state!=a_state[0])||(b_encoder_state!=b_state[0])){
  
  // in case we have all channels ==1
  if (a_encoder_state==1&&b_encoder_state==1){
    
    // read previous state 
    if (a_state[0]==1&&b_state[0]==0){
      main_command=LEFT_CMD;
      }
    if (b_state[0]==1&&a_state[0]==0){
      main_command=RIGHT_CMD;
      } 
    }
    
  add_state(a_encoder_state, a_state);
  add_state(b_encoder_state, b_state);
}  

 
 
 
 
 
 
 
 
/*
// first version of reaaaaly stupid code
 if(a_encoder_state==0&&b_encoder_state==1){
   rotate="CW";
   main_command=RIGHT_CMD;
  }
  
   if(a_encoder_state==1&&b_encoder_state==0){
   rotate="CCW";
   main_command=LEFT_CMD;
  }
  
*/  
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

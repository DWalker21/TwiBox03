/*******************************************************************
* read button state 
* Left/Right
* Action, Back
* 
* actions - back are not implemened yet
*
* Control buttons connected to the following Pins (see def.g)
* const int RIGHT_BUTTON_PIN = 41;     // PIN for Right button
* const int LEFT_BUTTON_PIN = 40;      // PIN for Left button 
*
********************************************************************
*/ 

void ReadCommandButtons()
{

if (debug){
  //Serial1.println(" run Read Commands from Buttons ");
  // - disabled as it spams the serial
  }  
  
if (main_command==NO_CMD){
     if (digitalRead(LEFT_BUTTON_PIN)==LOW){
     main_command=LEFT_CMD;
     }
     if (digitalRead(RIGHT_BUTTON_PIN)==LOW){
     main_command=RIGHT_CMD;
     }
  }
if (debug){
  //Serial1.print(" Pressed = ");
  //Serial1.println(main_command);
  // - disabled as it spams the serial
  }  
}



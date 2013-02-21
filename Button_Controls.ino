/*******************************************************************
* read button state 
* Up/Down
* Left/Right
* Action
********************************************************************
*/ 

void ReadCommandButtons()
{

if (debug){
  //Serial1.println(" run Read Commands from Buttons ");
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
  }  
  
}



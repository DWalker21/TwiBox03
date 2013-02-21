/*************************************************************************
*
*  Execute the last command
*/

void ExecuteCommand(){

if (debug)
  {
  //Serial1.println(" run Execute Commands ");
  }     

switch (main_command){
  case LEFT_CMD:{
     //Serial1.println(" LEFT executed ");
     video_message_first-=1;
     break;
     }
  case RIGHT_CMD:{
     //Serial1.println(" RIGHT executed ");
     video_message_first+=1;
     break;
    }  
  } // end switch case

if (video_message_first<=0) {
  video_message_first=0;
  }
  
if (video_message_first>=messages_number) {
  video_message_first=messages_number;
  } 
  
main_command=NO_CMD; // sucessfully executed - clear the command state
}




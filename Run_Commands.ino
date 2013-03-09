/*************************************************************************
*
*  Execute the last command
*/

void ExecuteCommand(){

if (debug){
  //Serial1.println(" run Execute Commands ");
  }     

switch (main_command){
  case LEFT_CMD:{
     video_active_message-=1;
     slide_show=SLD_SHOW_OFF;
     break;
     }
  case RIGHT_CMD:{
     video_active_message+=1;
     slide_show=SLD_SHOW_OFF;
     break;
    }  
   case ACTION_CMD:{
     slide_show=SLD_SHOW_OFF;
     message_scroll=SCROLL_ON;
     break; 
     }  
  } 

if (video_active_message<=0) {
  video_active_message=0;
  }
  
if (video_active_message>=messages_number) {
  video_active_message=messages_number;
  } 
  
main_command=NO_CMD; // sucessfully executed - clear the command state

}




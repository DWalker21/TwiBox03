/*  
*  Twi Box 0.1
*/

#include <LiquidCrystal.h>
#include "def.h"


int debug=1;                       //debug = 1 - start debug output in case we need it

// global variable
String twi_messages[MSGS_NUM];
// Cyclic buffer vars
int message_first, message_last;    // index of the message that was filled in first (oldest one) and last (fresh one)
int messages_number;                // how many messages we have

int video_active_message;           // index of the actual active message from twi messages 

// Read Serial related vars
char msg_buff[5];                   // buffer to read serial
char buff; 
char msg_text_buff[MSG_LEN];       // new string that comming from serial
int msg_lenght;                     // the lenght of the new string 

// base timer loops
uint32_t fast_loop, loop_1, loop_20, loop_600, loop_2000, loop_5000, loop_60sec;
// COMMAND to execute
int main_command;

// Slide Show option
int slide_show;
int message_scroll;

int scroll_shift=0;

/******************************************************************
*
* BEGIN SETUP
*
*******************************************************************
*/

void setup()
{
debug=1; 

pinMode(LEFT_BUTTON_PIN, INPUT);    
pinMode(RIGHT_BUTTON_PIN, INPUT);    

pinMode(ACT_ENCODER, INPUT); 
pinMode(A_ENCODER, INPUT); 
pinMode(B_ENCODER, INPUT); 

Serial2.begin (9600); // serial read #2 (works on MEGA only)
Serial1.begin (9600); // debug serial

LCD_WH1604_init();

main_command=NO_CMD;

// init twi messages cyclic buffer start values
message_first=0;
message_last=0;
messages_number=0;

if (debug){
  messages_number=5; // !!! writing in addition to TEST data !!!
  }

if(debug){
  CreateTestMessages();
  PrintMessages();
  }
  
VideoOutInit();
video_active_message=0;

if (debug){
  Serial2.println(" Ready! Send your data to me! ");
}

// init timer constants
fast_loop=0;
loop_20=0;
loop_600=0;
loop_2000=0;
loop_5000=0;
loop_60sec=0;

slide_show=SLD_SHOW_OFF;
message_scroll=SCROLL_OFF;
}

/******************************************************************
*
* BEGIN MAIN LOOP
*
*******************************************************************
*/

void loop()
{
uint32_t timer = millis();

ReadSerial(); 
ReadCommandButtons();

// run every 1 millisecond
  if ((timer - loop_1) >=10) {
    loop_1=timer;
    ReadEncoder();
    }    


// run every 20 millisecond
  if ((timer - loop_20) >=20) {
    loop_20=timer;
    VideoOut(); 
    }    

// run every 300 millisecond
  if ((timer - loop_600) >=600) {
    loop_600=timer;
    ExecuteCommand();
    }    

// run every 2000 millisecond
  if ((timer - loop_2000) >=2000) {
    loop_2000=timer;
    scroll_one();
    }    


 // run every 5 seconds in case we run SlideShow
  if ((timer - loop_5000) >=10000 && slide_show==SLD_SHOW_ON) {
    loop_5000=timer;
    //lcd.clear();
     video_active_message+=1;  
    if ( video_active_message>messages_number) {
       video_active_message=0;
      }
    }    


//run every 60 sec
  if ((timer-loop_60sec)>=60000){
    loop_60sec=timer;
    slide_show=SLD_SHOW_ON;
  }

delay (10);
 
}

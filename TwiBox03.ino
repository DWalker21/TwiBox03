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
uint32_t fast_loop, loop_20, loop_600 , loop_5000;
// COMMAND to execute
int main_command;

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
loop_5000=0;
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

/* // run every 8 seconds
  if ((timer - loop_5000) >=8000) {
    loop_5000=timer;
    lcd.clear();
    video_message_first+=1;  
    if (video_message_first>messages_number) {
      video_message_first=0;
      }
    }  */  

delay (10);
 
}

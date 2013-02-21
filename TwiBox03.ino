/*  
*  Twi Box 0.1
*/

#include <LiquidCrystal.h>
#include "def.h"


int debug=1; //debug = 1 - start debug output in case we need it

// global variable
String twi_messages[MSGS_NUM];
int message_first, message_last;     // index of the message that was filled in first (oldest one) and last (fresh one)
int messages_number;                 // how many messages we have

int video_message_first, video_message_last; // index from what message till what to display [0..MSGS_NUM]
int active_message; // cursor on the screen associated with one active message

// loop section related vars
char msg_buff[5]; // buffer to read searial
char buff; 
char msg_text_buff[MSG_LEN]; // new string that comming from serial
int msg_lenght; // the lenght of the string 

// base timer loops
uint32_t fast_loop, loop_20, loop_300 , loop_5000;

const int RIGHT_BUTTON_PIN = 41;     // PIN for Right button
const int LEFT_BUTTON_PIN = 40;      // PIN for Left button 

int main_command;

/************************************************************************************************
*
* Custom Fonts
* 
*/
byte TWI_LEFT1[8]={0x1C, 0x11, 0x13, 0x17, 0x13, 0x11, 0x1C, 0x0};
byte TWI_RIGHT1[8]={0x7, 0x11, 0x19, 0x1D, 0x19, 0x11, 0x7, 0x0};
byte TWI_ACT1[8]={0x1b, 0x11, 0x11, 0x15, 0x11, 0x11, 0x1B, 0x0};
byte TWI_BACK1[8]={0x4, 0x8, 0x1F, 0x9, 0x5, 0x1, 0x3, 0x0};

byte TWI_LEFT2[8]={0x1F, 0x10, 0x11, 0x13, 0x17, 0x13, 0x11, 0x10};
byte TWI_RIGHT2[8]={0x1F, 0x1, 0x11, 0x19, 0x1D, 0x19, 0x11, 0x1};
byte TWI_ACT2[8]={0x1f, 0x0, 0x0, 0xE, 0xA, 0xE, 0x0, 0x0};
byte TWI_BACK2[8]={0x1F, 0x0, 0x4, 0x8, 0x1F, 0x9, 0x5, 0x1};






/******************************************************************
*
* BEGIN SETUP
*
*******************************************************************
*/

void setup()
{
fast_loop=0;
loop_20=0;
loop_300=0;
loop_5000=0;

pinMode(LEFT_BUTTON_PIN, INPUT);    
pinMode(RIGHT_BUTTON_PIN, INPUT);    

main_command=NO_CMD;

debug=1;  
Serial2.begin (9600); // serial read #2 (works on MEGA only)
Serial1.begin (9600); // debug serial
LCD_WH1604_init();

// init messages start values
message_first=0;
message_last=0;
messages_number=5;

CreateTestMessages();

VideoOutInit();

PrintMessages();

Serial2.println(" Ready! Send your data to me! ");

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
//VideoOut();
ReadCommandButtons();

// run every 1 millisecond
/*
  if ((timer - fast_loop) >=1) {
    fast_loop=timer;
    ReadSerial(); 
    }    
*/ 
   
// run every 20 millisecond
  if ((timer - loop_20) >=20) {
    loop_20=timer;
    VideoOut(); 
    }    

// run every 300 millisecond
  if ((timer - loop_300) >=600) {
    loop_300=timer;
    ExecuteCommand();
    }    

/*
// rin every 8 seconds
  if ((timer - loop_5000) >=8000) {
    loop_5000=timer;
    lcd.clear();
    video_message_first+=1;  
    if (video_message_first>messages_number) {
      video_message_first=0;
      }
    }    
 */  


delay (10);
 
}

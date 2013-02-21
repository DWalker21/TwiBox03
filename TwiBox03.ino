/*  
*  Twi Box 0.1
*/

#include <LiquidCrystal.h>

#define MSGS_NUM 10
#define MSG_LEN 140

// commands
#define NO_CMD 0
#define LEFT_CMD 1
#define ACTION_CMD 2
#define BACK_CMD 3
#define RIGHT_CMD 4

// global variable
int debug=1; //debug = 1 - start debug output in case we need it

//char twi_messages[MSGS_NUM][MSG_LEN];
String twis_messages[MSGS_NUM];
int message_first, message_last; // index of the message that was filled in first (oldest one) and last (fresh one)
int messages_number; // how many messages we have
int video_views; // how many views till the scrolling text starts
int video_message_first, video_message_last; // index from what message till what to display [0..MSGS_NUM]
int active_message; // cursor on the screen associated with one active message

// loop section related vars
char msg_buff[5]; // buffer to read searial
char buff; 
char msg_text_buff[MSG_LEN]; // new string that comming from serial
int msg_lenght; // the lenght of the string 

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



/************************************************************************************************
*
*  Function initialize the hardware part on LCD
*/

LiquidCrystal lcd(12, 11, 22, 23, 24, 25, 26, 27, 28, 29);

int LCD_WH1604_init()
{
if (debug)
  {
  Serial1.println(" ");
  Serial1.println(" run LCD_WH1604_init ");
  }
  
lcd.begin(16, 4);  
 
return 0;
}

/**********************************************************************************************
*
*  Function fill in test data in the messages array
*/
void CreateTestMessages()
{

twis_messages[0]="Test String 0 - Russian meteorite images caught on dashboard cameras  Google";  
twis_messages[1]="Test String 1 Tesla's Musk Broder Quarrel Echoes Previous Top Gear Fallout  What Really ...";
twis_messages[2]="Test String 2 Trailing Twitter, but Pinterest could soon be second most used social network";
twis_messages[3]="Test String 3 Apple's new iPad ad campaign promotes 300000 apps for everything you love";
twis_messages[4]="Test String 4 Facebook 's VP nearly confirms Facebook is working on auto-play video ads";
twis_messages[5]="Test String 5 Some news string";
//messages_number=5;

if (debug)
  {
  Serial1.println(" run Create Test Messages ");
  }
}

/*********************************************************************************************
*
* function that read serial 
*
*
*/

void ReadSerial(void)
{
int l;

if (Serial2.available()>0)
  {
  // detect MSG
  msg_buff[0]=Serial2.read();
  if (msg_buff[0]=='M')
    {
     msg_buff[1]=Serial2.read(); 
     msg_buff[2]=Serial2.read();
    }  
  if (msg_buff[0]=='M'& msg_buff[1]=='S'&msg_buff[2]=='G')
    {
    // MSG is dtected
     msg_buff[3]=Serial2.read();  //read comma
     msg_buff[4]=Serial2.read();  //read space
     msg_lenght=Serial2.parseInt();  //read lenght of the rest text message
     if (msg_lenght>MSG_LEN) // will read string as long as bytes to store we have
        {
        msg_lenght=MSG_LEN-1;
        }
     msg_buff[4]=Serial2.read();  //read space    
     Serial2.readBytes(msg_text_buff, (msg_lenght-1)); // read the text of the message
     if (debug)
       {
       Serial1.println("MSG is detected");   
       Serial1.print("len = ");  
       Serial1.println(msg_lenght);
       Serial1.println("we have read the string: " );  
       Serial1.println(msg_text_buff);
       }
      TwiMessagesAppend(msg_text_buff); // call smart funtion to add messages
     }  
    
   if (msg_buff[0]=='C')
   {
     msg_buff[1]=Serial2.read(); 
     msg_buff[2]=Serial2.read();
    }  
  if (msg_buff[0]=='C'& msg_buff[1]=='M'&msg_buff[2]=='D')
    {
    // CMD is dtected
    msg_buff[3]=Serial2.read();  //read comma
    msg_buff[4]=Serial2.read();  //read leading space
    msg_buff[5]=Serial2.read();  //read command
    
    if(msg_buff[5]=='l'){
      main_command= main_command=LEFT_CMD;}
      
    if(msg_buff[5]=='r'){
       main_command= main_command=RIGHT_CMD;}  
    }
  } 
 
// and clear the command buffer
for(l=0; l<=5; l++){
  msg_buff[l]=0;
  }  
  
  
}



/********************************************************************************************* 
* 
* function that print out to SERIAL current state with all messages
*
*
*/
void PrintMessages()
{
int i,j;

if (debug)
  {
  Serial1.println(" run Print All Messages, current state is below:\n");
  for (i=0; i<MSGS_NUM; i++)
    {
    Serial1.println(twis_messages[i]);  
    /*  
    for (j=0; j<50; j++)
      {  
      Serial1.write(twis_messages[i][j]); 
      }
    Serial1.write(13); 
    */
    }
  Serial1.println(" ");    
  }    
}


/*****************************************************************************************
*  Init constants to work with video buffer and cursor window
*
*
*/
void VideoOutInit()
{
if (debug)
  {
  Serial1.println(" run Video Out Init ");
  }  

lcd.createChar(0, TWI_LEFT2);
lcd.createChar(1, TWI_RIGHT2);
lcd.createChar(2, TWI_ACT2);
lcd.createChar(3, TWI_BACK2);

video_message_first=0;
video_message_last=1;
video_views=0;

}

/*****************************************************************************************
*
*
* function add additional message to the existed array of twi_messages and do it smart
*/
void TwiMessagesAppend(char new_text[])
{
int j;
  
String new_message=String(new_text);   

if (debug)
  {
  Serial1.println(" run Twi Messages Append ");
  }  
  
twis_messages[message_last]=""; /// clear the place write to
twis_messages[message_last]=new_message;
messages_number=messages_number+1;

if (messages_number<MSGS_NUM) // not complete queee
  {
   message_last=message_last+1; // just add new message
  }

if (messages_number>=MSGS_NUM) // list is FULL and new message come
  {
  message_last=message_last+1;
  message_first=message_first+1;  
  messages_number=MSGS_NUM-1;
  if (message_last>=MSGS_NUM)
    {
    message_last=0;
     }  
    
   if (message_first>=MSGS_NUM)
    {
    message_first=0;
     }  
  }

// and print actual state of messages
PrintMessages();

//VideoOut();

// and clear buffer
for (j=0;j<MSG_LEN;j++)
  {
    msg_text_buff[j]=0;  
  }
//video_views=0;
}

/***************************************************************************************
* function update LCD display completely in according of curretn state with messages, 
* Videowindow and Cursor
*
*/
void VideoOut()
{
  
int scroll_shift=0;
int s;
  
video_views+=1;  

/*
if (debug)
  {
  Serial1.println(" run VideoOut ");
  }    
*/
  lcd.setCursor(0, 0);
  lcd.print(twis_messages[video_message_first].substring(0+scroll_shift,16+scroll_shift));
  lcd.setCursor(0, 1);
  lcd.print(twis_messages[video_message_first].substring(16+scroll_shift,32+scroll_shift));
  lcd.setCursor(0, 2);
  lcd.print(twis_messages[video_message_first].substring(32+scroll_shift,48+scroll_shift));
  lcd.setCursor(0, 3);
  lcd.print(twis_messages[video_message_first].substring(48+scroll_shift,64+scroll_shift));


// and print system information

// for horizontal orientation
lcd.setCursor(12, 3);
//lcd.print(char(60)); //Left

lcd.print(char(0)); // Custom Left

lcd.setCursor(13, 3);
//lcd.print(char(126)); // Action!
lcd.print(char(2)); // Custom Action

lcd.setCursor(14, 3);
//lcd.print(char(217)); // Back
lcd.print(char(3)); // Custom Back

lcd.setCursor(15, 3);
//lcd.print(char(62)); // Right
lcd.print(char(1)); // Custom Right

lcd.setCursor(11, 3);
lcd.print(")"); 

lcd.setCursor(10, 3);
lcd.print(messages_number); 

lcd.setCursor(9, 3);
lcd.print("("); 

lcd.setCursor(8, 3);
lcd.print(video_message_first); 

lcd.setCursor(7, 3);
lcd.print(".");

lcd.setCursor(6, 3);
lcd.print("."); 

/* for vertical right edge orientation
//out cursors
lcd.setCursor(15, 0);
lcd.print(char(217)); // UP

lcd.setCursor(15, 1);
lcd.print(char(126)); //Action! 

lcd.setCursor(15, 2);
lcd.print(char(238)); //Back

lcd.setCursor(15, 3);
lcd.print(char(218)); // Down

*/


// commect actual code
/*

lcd.clear();

if (video_views<50)
  {
  scroll_shift=0;
  }
else
  {
  scroll_shift=(scroll_shift+15)*int((video_views/30));
  }  
   
  if (scroll_shift>=(MSG_LEN-15))
      {
        scroll_shift=MSG_LEN-15;
      } 
 
  Serial1.print(" video_views = ");
  Serial1.println(video_views); 
  
  Serial1.print(" scroll= ");
  Serial1.println(scroll_shift); 
    
  lcd.setCursor(0, 0);
  lcd.print(twis_messages[video_message_first].substring(0+scroll_shift,16+scroll_shift));
  lcd.setCursor(0, 1);
  lcd.print(twis_messages[video_message_first].substring(17+scroll_shift,33+scroll_shift));
  lcd.setCursor(0, 2);
  lcd.print(twis_messages[video_message_first].substring(32+scroll_shift,47+scroll_shift));
  lcd.setCursor(0, 3);
  lcd.print(twis_messages[video_message_first].substring(48+scroll_shift,63+scroll_shift));
 
  
  
//Out String 1
//Out String 2
//Out String 3
//Out String 4

//out cursor position - TBD

if (int(video_views/200)>video_message_first)
 {
  video_message_first+=1;
  video_views=0;
  }
  
*/  
}

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

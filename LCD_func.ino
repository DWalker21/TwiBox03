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
  


/*
if (debug)
  {
  Serial1.println(" run VideoOut ");
  }    
*/
  lcd.setCursor(0, 0);
  lcd.print(twi_messages[video_message_first].substring(0+scroll_shift,16+scroll_shift));
  lcd.setCursor(0, 1);
  lcd.print(twi_messages[video_message_first].substring(16+scroll_shift,32+scroll_shift));
  lcd.setCursor(0, 2);
  lcd.print(twi_messages[video_message_first].substring(32+scroll_shift,48+scroll_shift));
  lcd.setCursor(0, 3);
  lcd.print(twi_messages[video_message_first].substring(48+scroll_shift,64+scroll_shift));


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


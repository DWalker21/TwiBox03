/************************************************************************************************
*
*  Function initialize the hardware part on LCD
*/

LiquidCrystal lcd(12, 11, 22, 23, 24, 25, 26, 27, 28, 29);

int LCD_WH1604_init()
{
if (debug)  {
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
if (debug){
  Serial1.println(" run Video Out Init ");
  }  
  
// Create custom fonts
lcd.createChar(0, TWI_LEFT2);
lcd.createChar(1, TWI_RIGHT2);
lcd.createChar(2, TWI_ACT2);
lcd.createChar(3, TWI_BACK2);

}

/***************************************************************************************
* function update LCD display completely in according of current state with messages, 
* Active_Message
*
*/
void VideoOut()
{
  
int scroll_shift=0;
int s;

// print the Active Message
  lcd.setCursor(0, 0);
  lcd.print(twi_messages[video_active_message].substring(0+scroll_shift,16+scroll_shift));
  lcd.setCursor(0, 1);
  lcd.print(twi_messages[video_active_message].substring(16+scroll_shift,32+scroll_shift));
  lcd.setCursor(0, 2);
  lcd.print(twi_messages[video_active_message].substring(32+scroll_shift,48+scroll_shift));
  lcd.setCursor(0, 3);
  lcd.print(twi_messages[video_active_message].substring(48+scroll_shift,64+scroll_shift));

VideoSystemMenu();

/*
if (debug) {
  Serial1.println(" run VideoOut ");
  }  -  disable as it spams the serial  
*/
}

/****************************************************************************
*
* Print Out system dysplay area
*
*
*/
void VideoSystemMenu(){
// Print out custom controls
lcd.setCursor(12, 3);
lcd.print(char(0)); // Custom Left
lcd.setCursor(13, 3);
lcd.print(char(2)); // Custom Action
lcd.setCursor(14, 3);
lcd.print(char(3)); // Custom Back
lcd.setCursor(15, 3);
lcd.print(char(1)); // Custom Right

// print the number of actual messages in brakes N(of_total)
lcd.setCursor(6, 3);
lcd.print("."); 
lcd.setCursor(7, 3);
lcd.print(".");
lcd.setCursor(8, 3);
lcd.print(video_active_message); 
lcd.setCursor(9, 3);
lcd.print("("); 
lcd.setCursor(10, 3);
lcd.print(messages_number); 
lcd.setCursor(11, 3);
lcd.print(")"); 
  
}

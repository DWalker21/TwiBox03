/**********************************************************************************************
*
*  Function fill in test data in the messages array
*/
void CreateTestMessages()
{

twi_messages[0]="Test String 0 - Russian meteorite images caught on dashboard cameras  Google";  
twi_messages[1]="Test String 1 Tesla's Musk Broder Quarrel Echoes Previous Top Gear Fallout  What Really ...";
twi_messages[2]="Test String 2 Trailing Twitter, but Pinterest could soon be second most used social network";
twi_messages[3]="Test String 3 Apple's new iPad ad campaign promotes 300000 apps for everything you love";
twi_messages[4]="Test String 4 Facebook 's VP nearly confirms Facebook is working on auto-play video ads";
twi_messages[5]="Test String 5 Some news string";
//messages_number=5;

if (debug){
  Serial1.println(" run Create Test Messages ");
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
  for (i=0; i<MSGS_NUM; i++) {
    Serial1.println(twi_messages[i]);  
    /* uncomment here to be byte data 
    for (j=0; j<50; j++) {  
      Serial1.write(twis_messages[i][j]); 
      }
    Serial1.write(13);  */
    }
  Serial1.println(" ");    
  }    
}



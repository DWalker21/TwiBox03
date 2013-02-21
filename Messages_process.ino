/*****************************************************************************************
*
*
* function add additional message to the existed array of twi_messages and do it smart
*/
void TwiMessagesAppend(char new_text[])
{
int j;
  
String new_message=String(new_text);   

if (debug) {
  Serial1.println(" run Twi Messages Append ");
  }  
  
twi_messages[message_last]="";    // clear the place write to
twi_messages[message_last]=new_message;
messages_number=messages_number+1;

if (messages_number<MSGS_NUM){ // not complete cycle here yet
 message_last=message_last+1; // just add new message
 }

if (messages_number>=MSGS_NUM){ // list is FULL and new message came
  message_last=message_last+1;
  message_first=message_first+1;  
  messages_number=MSGS_NUM-1;
  
  if (message_last>=MSGS_NUM){
    message_last=0;
    }  
  if (message_first>=MSGS_NUM){
    message_first=0;
    }  
  }

// print actual state of messages
if (debug) {
  PrintMessages();
  }

// and clear the buffer
for (j=0;j<MSG_LEN;j++){
    msg_text_buff[j]=0;  
    }
}


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





/*****************************************************************
*
* Defines for Twi Box
*
*/


// General defines
#define MSGS_NUM 10
#define MSG_LEN 140

// Define Commands
#define NO_CMD 0
#define LEFT_CMD 1
#define ACTION_CMD 2
#define BACK_CMD 3
#define RIGHT_CMD 4

const int RIGHT_BUTTON_PIN = 41;     // PIN for Right button
const int LEFT_BUTTON_PIN = 40;      // PIN for Left button 

// Encoder connected ports
const int ACT_ENCODER = 32; 
const int A_ENCODER = 35;
const int B_ENCODER = 34; 

// Slide Show options defines
#define SLD_SHOW_OFF 0
#define SLD_SHOW_ON 1

// Messages State defines
#define SHOW_LINE 1 // show line of messages
#define SHOW_MSG 2 // display just active message

// define scrolling option
#define SCROLL_OFF 0
#define SCROLL_ON 1


/*********************

Example code for the Adafruit RGB Character LCD Shield and Library

This code displays text on the shield, and also reads the buttons on the keypad.
When a button is pressed, the backlight changes color.

**********************/

// include the library code:
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

//PARSE STUFF
#include <Parse.h>
#include <Bridge.h>

ParseClient client;

void setup() {
  // Debugging output
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);

  // Print a message to the LCD. We track how long it takes since
  // this library has been optimized a bit and we're proud of it :)
//  int time = millis();
  lcd.print("Time for Quotes!");
//  time = millis() - time;
//  Serial.print("Took "); Serial.print(time); Serial.println(" ms");
  lcd.setBacklight(GREEN);
  
  while(!Serial);
  Serial.println("Before Parse setup");
  
  parseSetup();
  parseRetrieval();
}

void parseSetup()
{
    Serial.println("Parse setup");
  // Initialize Bridge
  Bridge.begin();
  
  // Initialize Parse
  client.begin("OL0i1OhDkRscie1SlaqRinQsn78CwY4gL1vThHaF", "vIuRlq40qlDDCYffI8yeTd7aixpQB4vGVnKYoBKu");
    Serial.println("Parse setup complete");  
}

void parseRetrieval()
{
  Serial.println("Begin Parse retrieval");  
  String quotesArray [] = {};
  
  //Query for Quote objects
  ParseQuery query;
  query.setClassName("Quote");
  query.whereNotEqualTo("text", "foo");
  ParseResponse response = query.send();
   
  int countOfResults = response.count();
  Serial.println(countOfResults);
    
//  for(int i = 0; i < countOfResults; i++)
//  {
////     Serial.println(i);
//     quotesArray[i] = response.getString("text");
//     Serial.println(quotesArray[i]);
//  }
 
//   lcd.print(quotesArray[0]);

  int i = 0;
    
  while(response.nextObject()) 
  {
//    Serial.println(response.getJSONBody());
//    Serial.println(response.getString("text"));     

   quotesArray[i] = response.getString("text");
   Serial.println(quotesArray[i]);
    i++;
  }
  
  lcd.begin(16, 2);
  lcd.print(quotesArray[0]);
  
  response.close(); // Free the resource
    
  Serial.println("Close Parse retrieval");  
}

void displayItemsFromArray(String TheArray[])
{
//   int countOfArray = sizeof(TheArray);
     
//   Serial.println("Should print: ");
   Serial.print(TheArray[0]);
      
//   lcd.print(TheArray[0]);

//   for (int i = 0; i < countOfArray; i++)
//   {
//       TheArray[i]
//   }
}

void loop()
{
}

//uint8_t i=0;
//void loop() {
//  // set the cursor to column 0, line 1
//  // (note: line 1 is the second row, since counting begins with 0):
//  lcd.setCursor(0, 1);
//  // print the number of seconds since reset:
//  lcd.print(millis()/1000);
//
//  uint8_t buttons = lcd.readButtons();
//
//  if (buttons) {
//    lcd.clear();
//    lcd.setCursor(0,0);
//    if (buttons & BUTTON_UP) {
//      lcd.print("UP ");
//      lcd.setBacklight(RED);
//    }
//    if (buttons & BUTTON_DOWN) {
//      lcd.print("DOWN ");
//      lcd.setBacklight(YELLOW);
//    }
//    if (buttons & BUTTON_LEFT) {
//      lcd.print("LEFT ");
//      lcd.setBacklight(GREEN);
//    }
//    if (buttons & BUTTON_RIGHT) {
//      lcd.print("RIGHT ");
//      lcd.setBacklight(TEAL);
//    }
//    if (buttons & BUTTON_SELECT) {
//      lcd.print("SELECT ");
//      lcd.setBacklight(VIOLET);
//    }
//  }
//}

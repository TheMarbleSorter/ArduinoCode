//MarbleSorter_CruzGhasemiJutte_WesleyNedaAlex_WinterSemester 01 aprill 2021
//Source code for the TCS34725 library setup
             // Michael Klements
             // Skittles Colour Sorter
             // 11 January 2019
             // www.the-diy-life.com

//except for the color sensor library all the code is autoral
//there is comments for each code line, except for the delay commands, used only for apropriate time to reliably execute the previous functions


#include <Wire.h>                //Include color sensor 2 channel protocoll
#include "Adafruit_TCS34725.h"   //Include color sensor library
#include <Servo.h>               //Include analog servo library

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);   //Setup the colour sensor through Adafruit library

Servo drop;               //define hatch servo as = drop
Servo drag;               //define transport servo as = drag

const int photocel = 7;   //define pin 7 as photoresistor/part present sensor
const int led = 8;        //define pin 8 as part present pilot led
int photocel_state = 0;   //define reference for state of photocell

void setup()

{
  pinMode(photocel, INPUT);  // IO pin definitions
  pinMode(led, OUTPUT);

  
  drop.attach(12);           //define pin 12 to drop servo
  drag.attach(13);           //define pin 13 to drag servo
  tcs.begin();               //start conection with the color sensor
  drag.write(0);             //move transport to home position
  delay(1000);
  drop.write(90);            //command the hatch to shut
  delay(1000);
}

void loop()

{

photocel_state = digitalRead(photocel); //read part present sensor
  
  if (photocel_state == LOW)              //if voltage input from photocell = low, part is present
                                          //then the whole code below will be executed
                                          //if vin from photocell = high then part is not present
                                          //pilot green led will be off and loop will restart  
  
  {
    
  digitalWrite(led, HIGH);                  //turn on green pilot light  
  
  delay(1000); 
   
  float red, green, blue;                   //define rgb values as floats
  delay(50);
  tcs.setInterrupt(false);                  //turn on color sensor module
  delay(60);                            
  tcs.getRGB(&red, &green, &blue);          //gather rgb values from sensor
  tcs.setInterrupt(true);                   //turn of sensor module
  delay(100);

  drag.write(0);                            //move transport to home position
  delay(1000);

    if ((green>red) && (red>blue))          //if g>r>b then color = yellow
    
    {         
  
    drag.write(35);                         //move transport to yellow drop  

    delay(1000);

    drop.write(0);                          //open the hatch to drop marble
    delay(1000);

    drop.write(90);                         //close the hatch
    delay(1000);

    drag.write(0);                          //transport move back to home position
    delay(1000);

    return;                                 //restart the loop for the next marble

    }


    if (red>=green && red>=blue)             //if red is the greatest output then color = red
    
    {            
      
    drag.write(95);                          //move ransport to red drop

    delay(1000);

    drop.write(0);                           //open hatch to drop marble
    delay(1000);

    drop.write(90);                          //close the hatch
    delay(1000);

    drag.write(0);                           //transport move back to home position
    delay(1000);

    return;                                  //restart loop for the next marble

    }

    if (green>=blue && green>=red)           //if green is the greatest output then color = green
    
    {          

    drag.write(145);                         //move transport to green drop

    delay(1000);

    drop.write(0);                           //open hatch to drop the marble
    delay(1000);

    drop.write(90);                          //close the hatch 
    delay(1000);

    drag.write(0);                           //move transport to home position
    delay(1000);

    return;                                  //restart loop to next marble

    }

    if (blue>=green && blue>=red)            //if blue is the greatest output then color = blue
    
    {          

    drag.write(180);                         //move transport to blue drop

    delay(1000);                             

    drop.write(0);                           //open the hatch to drop marble
    delay(1000);

    drop.write(90);                          //close the hatch
    delay(1000);

    drag.write(0);                           //transport back to home position
    delay(1000);

    return;                                  //restart loop for the next marble

    }
}

else{                                        //negative for the photocell part present sensor if expression  
                           
    digitalWrite(led, LOW);
}

}

/* Flow Meter by Flying Saucer
Serial output also added for testing
a BIG thanks to sekdiy for the library, please go and check his work out

Carefully read the datasheet of whatever sensor you use

*/

#include <FlowMeter.h>  // https://github.com/sekdiy/FlowMeter
#include <LiquidCrystal.h>


// connect a flow meter to an interrupt pin (see notes on your Arduino model for pin numbers, i used YF-S201)

FlowMeter Meter = FlowMeter(2); //data pin of flow meter

//Setting Pins for LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 8, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int obstacleInputPin=10;
int buzzerOutputPin= 13;

int obstacleInput= HIGH; //For Initial No Obstacle Conditin



// set the measurement update period to 1s (1000 ms)
const unsigned long period = 1000;

// define an 'interrupt service handler' (ISR) for every interrupt pin you use

void MeterISR() {
   
    // let our flow meter count the pulses
    Meter.count();
}

void setup() {

pinMode(obstacleInputPin, INPUT);
pinMode(buzzerOutputPin, OUTPUT);


obstacleInput=digitalRead(obstacleInputPin);

  

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("!! Flow Meter !!");
  lcd.setCursor(0,2);
  lcd.print("BY NASS");
  

  // prepare serial communication
    Serial.begin(9600);

    // enable a call to the 'interrupt service handler' (ISR) on every rising edge at the interrupt pin
    // do this setup step for every ISR you have defined, depending on how many interrupts you use
    attachInterrupt(INT0, MeterISR, RISING);

    // sometimes initializing the gear generates some pulses that we should ignore
    Meter.reset();
}

void loop() {
    
    // wait between output updates
    delay(period);


    
    // process the (possibly) counted ticks
    Meter.tick(period);

    lcd.clear();
  
    lcd.setCursor(0,0);
    lcd.print("Rate: ");
    lcd.setCursor(6,0);
    lcd.print(Meter.getCurrentFlowrate());
    lcd.setCursor(11,0);
    lcd.print("L/min");
    
    lcd.setCursor(0,1);
    lcd.print("Volm: ");
    lcd.setCursor(6,1);
    lcd.print(Meter.getTotalVolume());
    lcd.setCursor(11,1);
    lcd.print("L");

    obstacleInput=digitalRead(obstacleInputPin);

if(obstacleInput==LOW){
  digitalWrite(buzzerOutputPin, HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("OVERFLOW!");
  delay(100);
}
else{
 digitalWrite(buzzerOutputPin, LOW);
  
  }
    
    
    // output some measurement result serially
    Serial.println("Currently " + String(Meter.getCurrentFlowrate()) + " l/min, " + String(Meter.getTotalVolume())+ " l total.");


    
}

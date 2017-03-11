#define versie 17.00
/**
  06Mrt 2017 void zonOpOnder()  vervangen door een formule
  11nov 2016 Macros voor de switches in 'Switches.h' opgenomen
  11nov 2016 Version 17 wegens structurele veranderingen
  05nov 2016 E23 verandert in "Deken"
  04nov 2016 RGBstatus toegevoegd
  03nov 2016 IR zendroutine voor NEC toegevoegd voor IR-RGB lamp. codes in RGB_code.h file
  18sep 2016 versie 16, in feite werkcopie
  09jun 2016 void SetToStatus herwerkt met macros
  08jun 2016 Kleine mods om kinderkamer uit te doen gaan
  07jun 2016 Kleine mods rondom alg_status en de resetflagflag toekenning van h,m,mo,s etc hoger in setup. spatie toegevoegd tussen datum en tijd in setup
  05jun 2016 Void resetstatus aangevuld
  05jun 2016 algemeenstatus bit4 gebruikt als flag voor resetten van alle flaggen
  05jun 2016 eerste 3 l_status meer betekenisvolle naam
  30may 2016 renamed  version 15  coz of overhaul of receivers + version check added
  29may 2016 if statement toegevoegd aan "handle_switches()" procedure
  06may 2016 'every 2 hrs'  toegevoegd aan hydro
  06may 2016 printDatum(); tijd();  nu ook in setup ipv Serial.print(now.xxx)
  06may 2016 added HydroFreqStore
  04may 2016 renamed Athomesimulator14 coz of adding "handle_switches()" procedure.28730=>27770 bytes
  03may 2016 code optimalisatie ivm geheugen
  03may 2016 Vijverpomp toegevoegd (EverFlourish 3)
  03may 2016 routine  klok_vooruit() beveiligd tegen overschrijding 60 min grens
  03may 2016 added variable HydroFreq
  20apr 2016 fixed if (h&1==0) into if ((h&1)==0)
  30mrt 2016 hernoemd Athomesimulator13 voor herstrukturering nummering en functies van switches
  27mrt 2016 corrected winter_zomer
  26feb 2016 added Eurodomest2 procedures/ shifted vacation and algemeen status bits
  24feb 2016 fail safe function toegevoegd zet alle lichten weer uit
  12feb 2016 adding 3 eurodomest switches 21,22,23
  12feb 2016 putting  DST on zero position
  29jan 2016 SwitchONtijdlog toegevoegd
  15jan 2016 ifdefs toegevoegd
  28dec 2015 dimmable lamp added
  10dec 2015 IR toegevoegd
  8 dec 2015 dayOfYear toegevoegd
  8 dec 2015 memory opslag nu geconsolideerd
  5 dec 2015 alarm bij lichtwaarneming 's nachts toegevoegd
  9 nov 2015 added updateData() to avoid unnecessary EEPROM writes
********************
  Pin assignments
********************
  pin 1 Rx
  pin 2 Tx
  pin 3 Infraroodzender         OUTPUT  PWM
  pin 4 internal relay pin    OUTPUT      INT0
  pin 5 spare*                              PWM   INT1
  pin 6 spare*                              PWMi
  pin 7 Rf                                       OUTPUT
  pin 8 button                             INPUT
  pin 9 Spare                                PWM
  pin 10 sound In level           INPUT PWM SS
  pin 11 spare                             OUTPUT  PWM MOSI
  pin 12 soundOut Msg              OUTPUT    MISO
  pin 13 buzzer                           OUTPUT    SCK
  pin A0 LDR=A0                           INPUT   Internal Pullup   // D14
  pin A1 Spare-                           currently in use as randomSeed       // D15
  pin A2 NTC                                  INPUT           // D16  Internal Pullup though voltage divider maybe more precise
  pin A3 Spare                            // D17
  pin A4 SDA                                // D18
  pin A5 SCL                                // D19
*************************************************
            EEPROM use  24c32= 4kbyte =4096
            1st 4k=10.000.000 R/W cycles  =500 bytes (512)
            last 28k= 100.000 R/W cycles  =3500 bytes
*************************************************
  0 DST
  1 Huiskamer  --   Eurodomest21
  2 Slaapkamer    Elro1 B
  3 Studeerkamer    Elro1 C
  4 Radio       Blokker 1 voor overdag indien afwezig
  5 Reserved      Blokker 2 tv beneden, niet nodig denk ik beter een fake TV samen met radio
  6 Reserved      Blokker 3
  7 Blaffen     Elro2 1
  8 Kinderkamer   Elro2 2
  9 Hydroponics   EverSwitch 1
  10 lamp achtertuin  EverSwitch 2
  11 Vijverpomp   EverSwitch 3
  12 Fake TV      Eurodomest 1  boven?
  13 Pop        Eurodomest 2
  14 Buitenspot   Eurodomest 3
  15 External Relay Eurodomest 4  Attiny85
  16 Internal Relay
  17 Lamp voortuin  Elro1 A
  18          Eurodomest22
  19          Eurodomest23
  20 vacation
  21 algemeen
  22 dimmerstatus
  //23 hydrofrequency
  24 RGBstatus
  .......
  101-164 Tijd licht aan //baseLightOn=100
  200-230 LDR waarde   //baseLDR=200 //162-192

  240-87 ext temp door de dag //baseExtTemp=240//193-240

  290-337 internal temp door de dag //baseIntTemp=290 // 241-290
  338- lichtwaardes    // 291
  400- Tijd schakelaars aan
  500 hydrofrequency
*****************************
  Chip layout
* ***************************

   +--------+
   |        |
  Rst -+        +- SCL A5
   |        |
  Rx -+        +- SDA A4
     |        |
  Tx -+        +- A3
   |        |
  D2 -+        +- A2
   |        |
  IR -+        +- A1
   |        |
  Re -+        +- LDR
   |        |
  Vcc -+        +- GND
   |        |
  Gnd -+        +- Aref
   |        |
  X0 -+        +- Vcc
   |        |
  X1 -+        +- Buzz
     |        |
  D5 -+        +- SoundOut
   |        |
  D6 -+        +- D11
   |        |
  Rf -+        +- SoundIn
   |        |
  S  -+        +- D9
   |        |
   +--------+


*/
/*
  Switches

*/
//#define RADIO
//#define DEBUG
/*******************************************
// define ownership (and thus configuration)
********************************************/
#define E
//#define H TRUE

//define language (Dutch or English (as default))
#define NL
// define RTC // necessary for EEPROM address/NVR presence
#define DS3231
//#define DS1307 Has NVR
//#define DS3232 Has NVR
/************************************************
            Libraries
    IR libraries én Manchester library
           both use timer2
      VirtualWire uses timer1e
 ************************************************/
#include <Wire.h>
#include "RTClib.h" //  Lady Ada
#include <RemoteSwitch.h> //FuzzyLogic extended lib
#include <IRLib.h> // 
#include "RGB_code.h" // IR codes
#include "zenders.h"  //radiocodes
#include "Switches.h"// macros voor  de remote switches
//#include <EEPROM.h>
//#include <Manchester.h> // non compatible with IR library from Ken Shirrif
//#include <IRremote.h> // Ken Shirriff Have chosen IRlib
//#include <math.h> // for calculations on NTC Steinhart Hart Formula

// manchester conflicts with IR  (Timer)
// http://stackoverflow.com/questions/21069867/why-does-virtualwire-conflicts-with-pwm-signal-in-arduino-atmega328-pin-d10
// http://www.gammon.com.au/forum/?id=11506&reply=2#reply2
/************************************************
            Declarations
 ***********************************************/
ElroAb440Switch ab440Switch(7);
BlokkerSwitch3 blokkerTransmitter(7);// SelectRemote 1728029
EverFlourishSwitch everswitch(7); // EverFlourish EMW203
Ener002Switch enerswitch(7);      // Eurodomest 972080
CnLedDim1Switch ledDimSwitch(7);  // Dimmer
RTC_DS1307 rtc;           // RTC
IRsendRC5 My_sender;        // IRlib
IRsendNEC My_NEC;         // IRLIb
//IRsend irsend;          // replaced
/********************************************
          Arrays
     results => namen
        stat => status Aan/Uit
       maand => namen van maanden
       dagen => namen van dagen
 ********************************************/
#ifdef NL
char *results[] =
{
  "DST", "Huiskamer", "Studeerkamer", "Slaapkamer", "Radio", "Blokker2", "Blokker3", "Blaffen", "Kinderkamer", "Hydro", "Tuinlamp", "Vijver", "Fake TV",
  "Pop", "Spot", "Ext. relais", "Int. Relais",  "Voortuin", "Leeslamp", "Deken", "Vakantie"
};//names array. the char* defines an array of pointers
// Real TV misschien niet nodig
char *stat[] =
{
  "Uit", "Aan"
}; //status array


char *maand[] =
{
  "Januari", "Februari", "Maart", "April", "Mei", "Juni", "Juli", "Augustus", "September", "Oktober", "November", "December"
};

char *dagen[] = {"Zon", "Maan", "Dins", "Woens", "Donder", "Vrij", "Zater" };
#else//-------------------------------------------------------------------------------
char *results[] =
{
  "DST", "Living", "Study", "Bedroom", "Radio", "Blokker2",  "Blokker3", "Bark", "Nursery", "Hydro", "Garden", "Pond", "Fake TV",
  "Doll", "Spot", "Ext. relay", "Int. Relay", "Yard", "bedlamp", "Blanket", "Vacation"
};//names array. the char* defines an array of pointers
// Real TV misschien niet nodig
char *stat[] =
{
  "Off", "On"
}; //status array

char *maand[] =
{
  "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
};

char *dagen[] = {"Sun", "Mon", "Tues", "Wednes", "Thurs", "Fri", "Satur" };
#endif
//char Str4[]=":";
/*******************************************
          Constants
 *******************************************/
const unsigned long BAUD_RATE = 9600;
const byte periode = 30;      // tijd die bijv van zonsondergang wordt afgetrokken
//const byte sensorMin = 40;      // LDR minimum, discovered through experiment
//const int sensorMax = 1012;     // LDR maximum, discovered through experiment
//      Analogue pins
const byte LDRPin = A0;       // Measures light Pullup resistor
const byte NTCpin = A2;       // Measures temperature Pullup resistor
//      Digital pins
const byte IrSendPin = 3;     // Send IR codes
const byte RelayPin = 4;      // Internal Relais
const byte RECV_PIN = 5;      // IR receiver
const byte sparePin1 = 6;     //
const byte RfPin = 7;       // 433 MHz Rx
const byte buttonPin = 8;     // Pushbutton with PullUp resistor
const byte SparePin2 = 9;     // niet nodig
const byte SoundPin = 10;     // input
const byte SparePin3 = 11;      //
const byte soundOut = 12;     // PLAYE(dge)  Edge triggering of voiceboard
const byte buzzPin = 13;      // General purpose signal function
//      Status Addresses in EEPROM
const byte dst = 0;         // DST status address
const byte vacation = 20;     // Vacation status address
const byte algemeen = 21;       // general statusbyte
const byte dimmerstatus = 22;
const byte RGBstatus = 23;
//      Chip and device addresses
const unsigned long euro  = 823148; // base adres eurodomest  : 11001000111101101100
const unsigned long euro2 = 188838; // base address spare set : 00101110000110100110
const unsigned long euro3 = 599252; // base address eurodomestH : 10010010010011010100
const unsigned long cnLed = 208464; //416928; // base address dimmable Lamp  19 ipv 20 bits : 110010111001010000
#ifdef DS1307
const byte chip1 = 0x50;
#else
const byte chip1 = 0x57;      // 0b01010111 EEprom on DS3231 RTC board. On DS1307 EEPROMaddress is 0x50 (80)
#endif
const byte REG_TEMPM = 0x11;    // most significant byte of temperature read in RTC
const byte REG_TEMPL = 0x12;    // most significant byte of temperature read in RTC
const byte DS3231_CONTROL_REG = 0x0E;
const int DS3231_ADDRESS = 0x68;  // DS3231 address
const int wit = 0x3BB40;      // base code for Bell probeer ook 1BB40
const int zwart = 0x3C330;      // base code for Bell  0x3cc30 / 0001 1100 0011 0011 0000
const int baseLightOn = 22;         // base address for storage lightON time // moet 22 worden, eerste log wordt op baseLightOn+1 geschreven 23 is nu RGB status geworden. zou 1 omhoog moeten
const int baseLDR = baseLightOn + 64;   // base address to store Light values at lightOntime
const int baseExtTemp = baseLDR + 33;   // base address to store NTC temperature
const int baseIntTemp = baseExtTemp + 48; // base address to store RTC temperature
const int baseLight = baseIntTemp + 46;   // base address to store hourly light values
const int baseSwitches = baseLight + 22;  //base address to store when any switch was switched ON
const int HydroFreqStore = 500;
//codes for dimmable light
const long dimaddress = 0; //cnLed doet dit all
const byte pwr = 1;
const byte licht = 4;
const byte BrightUp = 5;
const byte BrightDown = 6;
const byte Full = 7;
const byte Half = 8;
const byte Quart = 9;
const byte Mode = 11;
const byte SpeedUp = 13;
const byte SpeedDown = 15;
/*********************************************
    variables for radio
 ******************************************* */
#ifdef RADIO
double frequentie = 96.8; //3fm lopik/eindhoven
/*
  100%NL 94.9;//eindhoven
  Brabant 87.6 fm


*/
unsigned int  frequencyB ;
unsigned char   frequencyH;
unsigned char  frequencyL;
#endif


/******************************************
          Variables
 ******************************************/
int current_time = 0;   // used for  counters
byte light = 140;// bevat de waarde waarop licht moet aangaan
//       Statuses
byte dst_stat = 0;      // 0-Daylight saving status
byte l_status_living = 0;   // 1-huiskamer Elro_Wit1
byte l_status_study = 0;  // 2-study Elro_Wit2
byte l_status_bedroom = 0;  // 3-boven / slaapkamer Elro_Wit3
byte l_status4 = 0;     // 4-Radio Blokker1
byte l_status5 = 0;     // 5-Blokker2 TV beneden
byte l_status6 = 0;     // 6-Blokker3
byte l_status_bark = 0;   // 7-bark ElrobuitenA
byte l_status_nursery = 0;  // 8-kinderkamer ElrobuitenD
byte l_status_h = 0;    // 9-Everswitch1  hydroponicspomp
byte l_status_TuinLamp = 0; // 10-Everswitch2 Tuinlamp/realtv?
byte l_status_pond = 0;   // 11-Everswitch3
byte l_status_TV = 0;     // 12-TV  boven Eurodomest1
byte l_status_pop = 0;    // 13-pop  Eurodomest2
byte l_status_spot = 0;   // 14-Buitenspot  Eurodomest3
byte l_status_tiny = 0;   // 15-External relais
byte l_status_I = 0;      // 16-Internal relais
byte l_status_yard = 0;   // 17-Eurodomest 2A
byte l_status_leeslamp = 0; // 18-Eurodomest 2B
byte l_status_Deken = 0;    // 19-Eurodomest 2C  Deken

// 18 Dimmer
boolean l_status_R1 = LOW;  // 17
boolean l_status_e22 = LOW; // 18
//boolean l_status_Deken = LOW; // 19
byte vac_stat = 0;      // 20 -vacation 0= thuis 1 is weg
byte HydroFreq = 4;       // bepaalt  om de 4 of om de 3 of om de 2 uur

byte g_status = 0;      // gesproken boodschap flag
byte alarmstat = 0;     // alarmstatus
byte t_flag = 0;            // temperature log flag
byte alg_status = 0;    // general status bit, set by byte  bit0=darkbit, bit1=Out-Bit, bit2=safety bit, bit 3 resetbit
boolean knipperstatus = LOW;  // geeft aan of een lamp moet knipperen
boolean dimstatus = LOW;  // status of the dimmable led
//      Settings and  definitions
byte pressLengh = 0;    // lenght button is pressed for
byte longPress = 5;         // number counted in seconds a long press of the button
long previousMillis = 0;  // for switching lights  a few secs without using delay
unsigned long currentMillis = 0;
long interval = 15000;    // 5 sec lamp (slaapkamer) aan *** misschien gewoon een int?
long buzztime = 10000;    // 10 sec buzzer
unsigned long starttime;  // used for several counters to avoid use of delay ()
unsigned long starttime2;
unsigned long starttime3;
byte counter = 0;       // geeft aan dat er een counter voor het alarm loopt
byte counter2 = 0;      // geeft aan dat er een counter voor het slaapkamerlicht loopt
byte counter3 = 0;
byte startminute = 0;   // is used by dimmable LED in the morning
//int poptime = 0;
int incomingByte = 0;   // for Serial Port
// date and time variables
byte m = 0;         // contains the minutes, refreshed each loop
byte h = 0;         // contains the hours, refreshed each loop
byte s = 0;         // contains the seconds, refreshed each loop
byte mo = 0;        // contains the month, refreshes each loop
int j = 0;          // contains the year, refreshed each loop
byte d = 0;         // contains the day (1-31)
byte dag = 0;       // contains day of week (0-6)
int doy;            // day of year
byte random1 = random(5);   // define byte with random value
byte random2 = random(10);
byte random3 = random(15);
//byte random4 = random(20);
//byte random5 = random(25);
byte onder = 0;       // contains hr sunset
byte onderm = 0;      // contains minutes sunset
byte oph = 0;       // contains hr sunrise
byte opm = 0;       // contains minutes sunrise
byte wintertimeday = 25;  // basevalue for day of wintertime start
byte summertimeday = 25;  // basevalue for day of summertime start
//byte dimCmd=0;      // Command sent to dimmer: 1,4,5,6,7,8,9,11,13,15,17

int numberOfItems = ARRAY_SIZE (results);//bevat de grootte van het Array
//-------- for button-----------
int current;        //Current state of the button (LOW is pressed b/c i'm using the pullup resistors
int count;          // How long the button was held (secs)
byte previous = HIGH;   // used in buttonpress
//unsigned long firstTime;  // how long since the button was first pressed
//------------ IR------------
//IRrecv irrecv(RECV_PIN);
//decode_results resultaat;
//------------einde IR------
/*****************************************
        Knipper Class
 * ***************************************/

class  Knipper
{
    char lampNr;
    long OnTime;
    long OffTime;
    boolean lampState;
    unsigned long previousMillis;
  public:
    Knipper(char nr, long on, long off)
    {
      lampNr = nr;
      OnTime = on;
      OffTime = off;
      lampState = true;
      previousMillis = 0;

    }
    void Update()
    {
      unsigned long currentMillis = millis();
      if ((lampState == true) && (currentMillis - previousMillis >= OffTime))
      {
        lampState = false;
        previousMillis = currentMillis;
        ab440Switch.sendSignal(29, lampNr, lampState);
        //  Serial.println("Uit");
        //Serial.print(stat[0]);
      }
      else if ((lampState == false) && (currentMillis - previousMillis >= OnTime))
      {
        lampState = true;
        previousMillis = currentMillis;
        ab440Switch.sendSignal(29, lampNr, lampState);
        //  Serial.println("aan");
        //Serial.print(stat[1]);
      }
    }
    void Stop()
    {
      lampState = false;
      ab440Switch.sendSignal(29, lampNr, lampState);
    }
};

//lamp.Update();
Knipper lamp1('A', 1000, 4000);
Knipper lamp2('C', 1500, 1500);


/******************************************
           SetUp
 *****************************************/
void setup()

{
  Serial.begin(BAUD_RATE);
  //  irrecv.enableIRIn(); // Start the IR receiver
  //----RTC-----
  //  First check if regular arduino or arduino Due
#ifdef AVR
  Wire.begin();
#else
  Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
#endif
  rtc.begin();
  if (! rtc.isrunning())
  {
    Serial.println(F("RTC  NOT running!")); // error message
  }
  // This line sets the RTC with an explicit date & time, for example to set
  // January 30, 2015 at 22:50 pm you would call:
  //rtc.adjust(DateTime(2015, 1, 30, 22, 25, 0));
  //rtc.adjust(DateTime(2016, 5, 3, 22, 12, 0));
  DateTime now = rtc.now();
  DateTime compiled = DateTime(__DATE__, __TIME__);
  if (now.unixtime() < compiled.unixtime())
  {
    Serial.print(F("Current Unix time"));
    Serial.println(now.unixtime());
    Serial.print(F("Compiled Unix time"));
    Serial.println(compiled.unixtime());
    Serial.println(F("RTC is older than compile time! Updating"));
    // following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  rtc.writeSqwPinMode(SquareWave1HZ); // sets the SQW output to 1 Hz, which can be used for a signal function


  /**************************** Set Pins and statusses *******************
             We set the proper pins to input or output
             and write them HIGH or LOW depending on their initial state
   * *********************************************************************/
  //pinMode(13, OUTPUT);
  pinMode(buzzPin, OUTPUT);     // zoemer
  digitalWrite(buzzPin, LOW);     // zoemer uit
  pinMode(RfPin, OUTPUT);       // zender
  pinMode(buttonPin, INPUT_PULLUP); // initialize the pushbutton pin as an input with pullup
  pinMode(soundOut, OUTPUT);      // voor  stem alert
  digitalWrite(soundOut, LOW);    // spraakkaart uit
  pinMode(RelayPin, OUTPUT);      // intern relay
  digitalWrite(RelayPin, LOW);    // intern relay uit
  pinMode(SoundPin, INPUT);       // voor soundlevel // geen pull up
  pinMode(IrSendPin, OUTPUT);     // IR
  digitalWrite(IrSendPin, LOW);   // IR laag
  //pinMode(A0, INPUT_PULLUP);
  pinMode(LDRPin, INPUT_PULLUP);    // value is ca 20k
  //**************************Print Set Up Messages************************


  //DateTime now = rtc.now();
  dag = now.dayOfWeek();
  Weekdag(dag);
  j = now.year();
  mo = now.month();
  d = now.day();
  h = now.hour();
  m = now.minute();
  s = now.second();
  printDatum();
  Serial.print(F(" "));
  tijd();
  /*
    Serial.print(F(" "));
    Serial.print(now.day(), DEC);
    Serial.print("-");
    Serial.print(now.month(), DEC);
    Serial.print(F("-"));
    Serial.print(now.year(), DEC);
    Serial.print(F(" "));
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.println(now.second(), DEC);
  */
  Serial.print(getTemperature());
  Serial.println(" oC");// of gebruik chr248
#ifdef NL
  Serial.print("Dag: ");
#else
  Serial.print("Day: ");
#endif
  Serial.println(now.dayOfYear());
  /*
    j = now.year();
    mo = now.month();
    d = now.day();
    h = now.hour();
    m = now.minute();
    s = now.second();
  */
  randomSeed(analogRead(A1));//make more random
  randomNr();//set up the randomnummers for the first go
  //**********************Read light statusses***************************
  //for (byte j = 1; j < 18; ++j)
  for (byte j = 1; j < numberOfItems + 1; ++j)
  {
    //  Serial.print(j);
    //  Serial.print(F("-"));
    //  Serial.println(readData(chip1, j));
  }


  setToStatus();              // call to a procedure that sets all switches to their EEPROM stored status
  vac_stat = readData(chip1, vacation);   // check if I am on holiday
  light = readData(chip1, 338 + 24);    // waarde waarbij het licht aangaat
  //  updateData(chip1, algemeen, 0);
  alg_status = readData(chip1, algemeen); // algemene status : bit 0= darkbit, bit 1=vakantiebit
  //Serial.println(numberOfItems);

  //Serial.println(alg_status,BIN);
  Serial.print(versie);


}

/********************************************************
                  Loop
 *******************************************************/
void loop()
{

  DateTime now = rtc.now();  //Get the current data
  dag = now.dayOfWeek();
  //onderstaande 2 regels nog vervangen
  //  byte r = zonOnder(now.month()); // benadering van zon onder door het jaar
  //  byte o = zonOp(now.month()); // benadering van zon op door het jaar
  j = now.year();
  mo = now.month();
  d = now.day();
  h = now.hour();
  m = now.minute();
  s = now.second();
  doy = now.dayOfYear();
  zonOpOnder(); // stel de zonsondergang tijden in

  //  int Map(LDRPin);// Read the light value from LDR  Check of dit hier wel nodig is

  //----------------- check  serial input in case of bluetooth-----
  if (Serial.available() > 0)
  {
    incomingByte = Serial.read();
    Serial.println();

    switch (incomingByte)
    {
      case 63://?
        help();
        break;
      case 33: //!
        /*
          Serial.println("Memory dump");
          Serial.println("Flags");
          for(int x = 0; x < baseLightOn; ++x)
          {
            Serial.print(x);
            Serial.print(" ");
            Serial.println(readData(chip1, x));
          }
          Serial.println("baseLightOn");
          for(int x = baseLightOn; x < baseLDR; ++x)
          {
            Serial.print(x);
            Serial.print(" ");
            Serial.println(readData(chip1, x));
          }
          Serial.println("LDR");
          for(int x = baseLDR; x < baseExtTemp; ++x)
          {
            Serial.print(x);
            Serial.print(" ");
            Serial.println(readData(chip1, x));
          }
          Serial.println("Ext temp");
          for(int x = baseExtTemp; x < 270; ++x)
          {
            Serial.print(x);
            Serial.print(" ");
            Serial.println(readData(chip1, x));
          }
          Serial.print("baseLightOn");
          Serial.print(" ");
          Serial.println(baseLightOn);
          Serial.print("baseLDR");
          Serial.print(" ");
          Serial.println(baseLDR);
          Serial.print("baseExtTemp ");
          Serial.println(baseExtTemp);
          Serial.print("baseIntTemp ");
          Serial.println(baseIntTemp);
          Serial.print("baseLight ");
          Serial.println(baseLight);
          Serial.print("baseSwitches ") ;
          Serial.println(baseSwitches) ;
        */
        break;
      case 72://H  of gebruik case 'H':
        livingON();
      //  Blokker1ON();
        break;
      case 104://h
        livingOFF();
      //  Blokker1OFF();
        break;
      case 73://I
        hydroON();
        Serial.print("elke ");
        Serial.print(HydroFreq);
        Serial.print(" uur");
        break;
      case 105://i
        hydroOFF();
        break;
      case 66://B
        bedroomON();
        break;
      case 98://b
        bedroomOFF();
        break;
      case 67: //C
        GardenLampON(); //Tuinlamp
        zendNEC(0xF7C03F);//aan
        zendNEC(0xF7A05F);//groen
        break;
      case 99: //c
        GardenLampOFF();// Tuinlamp
        RGBlampUIT;
        break;
      case 115://s
        CurrentSwitch();
        break;
      case 83 : // S
        CurrentOnSwitch();
        break;
      case 114://r
        resetStatus();
        break;
      case 75: //K
        kinderkamerON();
        break;
      case 107: //k
        kinderkamerOFF();
        break;
      case 76: //L
        studyON();
        break;
      case 108: //l
        studyOFF();
        break;
      case 77:// M
        relaisON();
        break;
      case 109: //m
        relaisOFF();
        break;
      case 37:// %
        if (HydroFreq == 4)
        {
          HydroFreq = 3;
          Serial.println(F("Every 3 hrs"));
          //  updateData(chip1,HydroFreqStore,HydroFreq);
        }
        else if (HydroFreq == 3)
        {
          HydroFreq = 2;
          Serial.println(F("Every 2 hrs"));
          //    updateData(chip1,HydroFreqStore,HydroFreq);
        }
        else
        {
          HydroFreq = 4;
          Serial.println(F("Every 4 hrs"));
          //  updateData(chip1,HydroFreqStore,HydroFreq);
        }
        updateData(chip1, HydroFreqStore, HydroFreq); // maakt niks uit voor geheugen besparing
        break;
      case 79: //O
        spotON();
        break;
      case 111://o
        spotOFF();
        break;
      case 80: //P
        popON();
        break;
      case 112: //p
        popOFF();
        break;
      case 81://Q
        Serial.print(F("donkerwaarde = "));
        Serial.print(sample(LDRPin));
        Serial.print(F(" schakelwaarde = "));
        Serial.println(light);
        printlogLicht();

        break;
      case 82: //R
        zendRC5(0x180C);
        //Serial.print(F("TV uit"));
        arrayprint(12);
        break;
      case 85: //U
        vac_stat = 1;
        updateData(chip1, vacation, 1);
        bitSet(alg_status, 1); // set het vacation bit in algemeen status bit
        updateData(chip1, algemeen, 1);
        //Serial.print(F("Vacation mode ON"));
        arrayprint(vacation);

        break;
      case 117: //u
        vac_stat = 0;
        updateData(chip1, vacation, 0);
        bitClear(alg_status, 1); // clear het vacation bit in algemeen status bit
        //Serial.print(F("Vacation mode OFF"));
        arrayprint(vacation);
        break;
      case 65: //A
        Irelais(1);
        break;
      case 97: //a
        Irelais(0);
        break;
      case 48://0
        EEPROM_Null();
        break;
      case 116://t
        tijd();
        printDatum();
        Serial.print(" DST ");
        Serial.println(stat[(readDST)]);
        //arrayprint(dst);// heeft meer bytes nodig
        break;
      case 84 ://T  2 minuten vooruit
        tijd();
        klok_vooruit(s, m);
        tijd();
        break;
      case 106: //j
        Serial.print("Dag ");
        Serial.print(now.dayOfYear());
        Serial.print(F(" van het jaar. "));
        printDatum();
        Serial.print(" DST ");
        Serial.print(stat[(readDST)]);
        //arrayprint(0);
        Serial.print(F(" v="));
        Serial.println(versie);
        break;
      case 118://v
        digitalWrite(soundOut, HIGH);
        Serial.print(F("Vuil Buiten"));
        digitalWrite(soundOut, LOW);
        break;
      case 87: //W klok1 uur achteruit wintertijd
        winter_zomer(s, m, h, 0);
        break;

      case 119: // w Klok 1 uur vooruit zomertijd
        winter_zomer(s, m, h, 1);
        break;
      case 49://1
        programma(1);
        break;
      case 50://2
        programma(2);
        break;
      case 51://3
        programma(3);
        break;
      case 52://4
        programma(4);
        break;
      case 128: //Ç
        zendRC5(0x1801);//kanaal 1
        break;
      case 129:// ü
        zendRC5(0x1802);
        break;
      case 130:// â
        zendRC5(0x1803);
        break;
      case 131://ä
        zendRC5(0x1804);
        break;
      case 53: //5
        zendRC5(0x1805);// kanaal 5
        break;
      case 54: //6
        zendRC5(0x1806);// kanaal 6
        break;
      case 55: //7
        zendRC5(0x1807);// RTL 7
        break;
      case 56://8
        zendRC5(0x1808);// veronica
        break;
      case 57://9
        zendRC5(0x1809);// kanaal 9=RTL8
        break;
      case 78: //N
        zendRC5(0x1001); // kanaal 11 NET5
        zendRC5(0x1801);
        break;
      case 113: //q
        alarmstat = 1;
        alarm();
        //Serial.print(alarmstat);
        buzzerAAN;
        digitalWrite(buzzPin, HIGH);
        Serial.print(F("buzzeraan"));
        break;
      case 121://y
        alarmstat = 0;
        //Serial.print(alarmstat);
        buzzerUIT;
        //digitalWrite(13,LOW);
        //  led1.Stop();
        //  led2.Stop();
        break;
      case 122: //z  temperature
        convertTemperature();               // convert current temperature into registers
        Serial.print(getTemperature());   // read registers and display the temperature
        Serial.println(" oC ");
        //  delay(50);
        //
        //Serial.println();
        //Serial.println(int(Thermistor(analogRead(NTCpin)))); // Temperatuur gemeten door  NTC
        //  Serial.println(int(THERMISTOR(analogRead(NTCpin))));
        //  Serial.println(int(THERMISTOR(gemiddeld(NTCpin))));//deze
        break;
      case 42: //  *  print lamp aan tijd gebaseerd op zonsondergang

        //Serial.print(results[1]);
        //Serial.print(stat[1]);

        Serial.print(F("Lamp aan om "));
        Serial.print(onder);
        Serial.print(":");
        //  Serial.print(colon);
        //Serial.println(onderm);
        printDigits(onderm);
        break;
      case 64: // @
        randomNr();
        break;
      case 38: // &
        Serial.print(F("lichtschakelwaarde: "));
        Serial.println(light);
        break;
      case 43: //+
        Serial.print(light);
        Serial.print(" => ");
        light = light + 10;
        Serial.println(light);
        updateData(chip1, 338 + 24, light);
        break;
      case 45: //-
        Serial.print(light);
        Serial.print(" => ");
        light = light - 10;
        Serial.print(light);
        updateData(chip1, 338 + 24, light);
        break;
      case 47: // /
        printLog();
        break;
      case 91: // [
        printLogTemp();
        break;
      case 93: // ]
        printLogIntTemp();
        break;
      case 103: //g
        logIntTemp();
        //logTemp(analogRead(NTCpin));
        //  Serial.println(t_flag);
        break;
      case 101://e
        Serial.println(F("Laatste 'aan' tijden"));
        for (byte i = 1; i < numberOfItems; ++i) // 20  vervangen door "numberOfItems"?
        {
          Serial.print(i);
          Serial.print(" - ");
          printlogSwitchOn(i);
          Serial.println();
        }
        break;
      case 100://d
        SelectPlus(wit);// 0x3BB40
        SelectPlus(wit);
        Serial.println(F("Witte bel"));
        break;
      case 68: // D Zwarte bel
        SelectPlus(zwart);// 0x1C330
        Serial.println(F("Zwarte bel"));
        break;

      case 89:// Y
        counter = 1;
        starttime = millis();// can also use now.unixtime()  and use 300 for 5 min
        buzzerAAN;
        break;
      case 69: //E
        //Weekdag2(dag);
        //Serial.println(now.unixtime());
        starttime2 = now.unixtime();
        counter2 = 1;
        break;
      case 60: // <
        zendRC5(0x1021);// channel-
        break;
      case 62: // >
        zendRC5( 0x1020);// channel +
        break;
      case 40: //(
        zendRC5(0x1011);// volume -
        break;
      case 41: //)
        zendRC5(0x1010); //volume +
        break;
      //  case 70://F
      //    Serial.flush();
      //    Serial.write(readDST);
      //    break;
      case 70: //F
        bitSet(alg_status, 2);
        break;
      case 102://f
        bitClear(alg_status, 2);
        break;
      case 120: //x
        setDimmer(BrightUp);
        delay(500);
        setDimmer(Full);
        delay(500);
        setDimmer(Half);
        delay(500);
        setDimmer(Quart);
        break;
      case 36: zendNEC(l_SMOOTH); break; //$
      case 35: zendNEC(l_STROBE); break; //#
      default:
        break;
    }
  }

  if (alarmstat == 1)
  {
    //  led1.Update();
    //  led2.Update();

  }
  //  led4.Start();
  //  led4.Update();
  //---------------einde check serial input
  /*****************************************************
                          Counter
       check if there are any counters active
   * ***************************************************/
   // COUNTER 1
  if (counter == 1)  // zorgt ervoor dat de buzzer niet te lang aanblijft
  {
    if (millis() - starttime > buzztime)
    {
      buzzerUIT;
      //  counter = 0;
    }
    if (millis() - starttime > 3 * buzztime)
    {
      alarmOFF();
    }
  }
  //  COUNTER 2
  if (counter2 == 1) // zet  het slaapkamer licht  's avonds uit een x aantal seconden na de huiskamer
  {
    if (now.unixtime() - starttime2 > (20 + random1))
    {
      bedroomOFF();
      RGBlampUIT;
      counter2 = 0;
    }
  }
  //  COUNTER3
  if (counter3 == 1)  // nog niet gebruikt
  {
    if (now.unixtime() - starttime2 > 20)
    {
      counter3 = 1;//nachtlamp
      RGBlampUIT;
      //digitalWrite(11, LOW);//pin11 is spare
      counter3 = 0;

    }
  }
  /*****************************************************
                             Alarm
   *****************************************************/
  if (digitalRead(SoundPin) == HIGH && counter == 0 && alarmstat == 0)
  {
    //  alarm();
  }

  if (knipperstatus == HIGH)
  {
    lamp1.Update();
    lamp2.Update();
  }
  /****************************************************
                         DST
   * **************************************************/

  if (dag == 0 && mo == 10 && d >= 25 && d <= 31 && h == 3 && readDST == 1)
  {
    winter_zomer(s, m, h, 0);
    wintertimeday = d;
  }
  if (dag == 0 && mo == 3 && d >= 25 && h == 2 && readDST == 0)
  {
    winter_zomer(s, m, h, 1);
    summertimeday = d;
  }
  /****************************************************
       am I on holiday and  is there light?
   * **************************************************/
  // possibly use following:
  /*
     if ((alg_status & 00000011) == 3) // bit 0 en bit 1 gezet
    {
      if (sample(LDRPin) < 200)
      {
        alarm();
      }

    }
  */
  // nog oplossen: als licht beneden eenmaal aan is blijft het alarm
  if ( vac_stat == 1 && alarmstat == 0)
  {
    if ((h > 22 | h < 6) && sample(LDRPin) < 150) // misschien te hoog voor 6 uur
    {
      alarm();
      Serial.print("Alarm!!");
    }
  }
  /*************************************************************
         Log licht en temperature every hour on the hour
   * ***********************************************************/
  if (m == 0 && t_flag == 0)
  {
    //  logTemp(getTemperature());// zolang geen NTC is log niet nodig
    //logTemp(analogRead(NTCpin));
    logIntTemp();
    logLicht();
    t_flag = 1;
  }
  if (m == 2 && t_flag == 1)
  {
    t_flag = 0;
  }
  if (m == 59 && t_flag == 1)
  {
    t_flag = 0;
  }

  /****************************************************
                         MORNING
   ****************************************************/
  if (h == 3 && m == 0 && bitRead(alg_status, 2) == 1 && bitRead(alg_status, 3 == 0))
  {
    bedroomOFF();// ook als licht manueel is aangezet gaat het uit om 3 uur
    bitSet(alg_status, 3);
  }
  if (h == 3 && m == 1 && bitRead(alg_status, 3) == 1)
  {
    bitClear(alg_status, 3);
  }

  // begin with setting  various random numbers
  if (now.hour() == 3 && now.minute() == 0 && now.second() == 55)
  {
    randomNr();
  }


  //  licht langzaam aan
  //  tussen 6 en 7 wordt de dimmer elke 3 min steeds één stap hoger gezet. dat gebeurt op 15 sec na de hele minuut
  //  omdat er op de hele minuut al veel dingen gebeuren 10 stappen
  //  3,6,9,12,15,18,21,24,27,30
  if (h == 6 && mo < 3 && m == 0 && s == 50) // zet eerst op 0
  {
    setDimmer(pwr);
    setDimmer(Quart);
    setDimmer(BrightDown);
    setDimmer(BrightDown);
    setDimmer(BrightDown);
    setDimmer(BrightDown);
  }
  if (h == 6 && mo < 3 && dimstatus == LOW && (m - startminute) == 3 && m <= 31 && s == 15)
  {
    startminute = m;
    setDimmer(BrightUp);
#ifdef DEBUG
    Serial.print("dimmerstart");
#endif
  }
  // zet tussen  6.05 en 6.09 am het licht even aan ... als het donker is en geen weekend
  if (now.hour() == 6 && now.minute() == (5 + random1) && l_status_living == 0 && dag < 6 && dag > 0)
  {
    livingON();

    //Serial.println(F("Vroege  ochtend aan"));
  }



  if (now.hour() == 6 && now.minute() == (10 + random1) && l_status_living == 1 )
  {
    livingOFF();
    
  }

  //zet om 7.25 of later uur am het licht aan... als dat nog niet is gebeurd
  //behalve op zaterdag en zondag en enkel  in sept-feb als het donker is
  // groter of gelijk is gekozen voor het geval er net om 7.25 een manueel licht aan is

  if (h == 7 && m >= 25 && l_status_living == 0 && dag != 6 && dag != 0 && sample(LDRPin) > light && (mo >= 9 || mo <= 2))
  {
    livingON();
   // Blokker1ON();
  }
  //zet om 8 uur am het licht uit... als dat nog niet is gebeurd
  if (now.hour() == 8 && now.minute() == 0 && l_status_living == 1)
  {
    livingOFF();
   // Blokker1OFF;
  }

  // zet in de wintermaanden het licht weer even aan 's morgens
  if (h == 9 && m == 1 + random1 && (now.dayOfYear() > 300 || now.dayOfYear() < 20) && l_status_living == 0)

  {
    livingON();
    //Blokker1ON();
  }
  //en weer uit
  if (h == 10 && m == random1 && l_status_living == 1)
  {
    livingOFF();
   // Blokker1OFF();
  }

/***************************************************
 *     Zet radiogeluid aan                                                                     *
 *     ************************************************/
  #ifdef RADIO
 if (h=9&&m==2+random2){
 radioAAN;
 radio(SKY);
 }
 #endif
  /***************************************************
                    AFTERNOON
   ***************************************************/
  // zet tussen 4 en 7 pm het licht aan ... als het donker is, donkerder dan berekend op basis van zonsondergang/  eigenlijk is dit tussen 15 en 19.59 uur

  if (h >= 15 && h <= 19 && sample(LDRPin) >= light && (mo >= 9 || mo <= 3) && l_status_living == 0)  //nadeel, kunt licht niet uitzetten tussen 3 en 8pm sowieso al verbetering indien  tijd laten lopen tot 'onder en 'onderm'
  {
    livingON();
    //Blokker1ON();
    RGBlampAAN;
    delay(60);
    RGBlampGRN;
    //    Serial.println(" middag aan");
  }

  //zet om r uur pm het licht aan... als dat nog niet is gebeurd (r is even voor zonsondergang) in nov is dit van 16.20 tot 17 uur +
  if (h == onder && m == onderm && l_status_living == 0)

  {
    livingON();
    //Blokker1ON();
  }
  /*****************************************************
                    EVENING
   * ***************************************************/

  //-----------------------Gesproken woord------------
  //                       Geeft een boodschap op woensdag
  //                       8 uur

  if (now.dayOfWeek() == 3 && now.hour() == 20 && now.minute() == 0 && g_status == 0)
  {
    ledblink(2, 200, buzzPin);
    delay(500);
    boodschap();
  }
  if (now.hour() == 20 && now.minute() == 1 && g_status == 1)
  {
    g_status = 0;
  }

  //                       en om half 9

  if (dag == 3 && h == 20 && m == 30 && g_status == 0)
  {
    ledblink(2, 200, buzzPin);
    boodschap();
  }
  if (now.hour() == 20 && now.minute() == 31 && g_status == 1)
  {
    g_status = 0;
  }
  // -------------------- kinderkamer  aan

  if (h == onder && m == onderm + random2 && l_status_nursery == 0)
  {
    kinderkamerON();

  }
  //zet om 21 uur + max16 min pm het licht kinderkamer uit

  if (h == 21 && m == (onderm + random2 + dag)  && l_status_nursery == 1)
  {
    kinderkamerOFF();
    //Serial.print("kinderkamer uit!!!!");
  }
  if (h == 21 && m == (random2 + onderm + dag + 2)  && l_status_nursery == 1) // als er de 1e keer iets tussenkwam (de studeerkamer bijv)
  {
    kinderkamerOFF();  // gaat niet uit
  }


  if (h == 22 && m == (random2)  && l_status_nursery == 1) // als er de 1e keer iets tussenkwam (de studeerkamer bijv)
  {
    kinderkamerOFF();  // gaat niet uit
    //Serial.print("kinderkamer nu uit!!!!");
  }

  //--------------------Fake TV--------------------

  //Zet tussen 7pm en 7.35  pm de (Fake) TV aan
  //if (now.hour() == 19 && now.minute() == (25 + random2) && l_status_TV == 0)
  if (h == 19 && m == (25 + random2) && l_status_TV == 0)
  {
    tvON();
  }
  // zet om 11pm tv voor zekerheid nog even uit voor het geval dit bij het slapengaan niet werd gedaan als bijv
  // de huiskamer eerder werd uitgezet
  if (h == 23 && l_status_TV == 1)
  {
    tvOFF();
  }
  //----------------------- Studeerkamer----------------------------
  //zet tussen 9 en 9.14 uur pm het licht in de studeerkamer aan... als dat nog niet is gebeurd
  if (now.hour() == 21 && now.minute() == (2 * dag) && l_status_study == 0)
  {
    studyON();
  }
  // zet licht in studeerkamer even later weer uit

  if (now.hour() == 21 && now.minute() == (15 + dag) && l_status_study == 1)
  {
    studyOFF();
  }
  if (h==22 &&  m==15  &&  l_status_Deken==0  && vac_stat==0) //alleen aan indien thuis
  {
     DekenSchakel(1);
    }

    if (h==1 && m==5 &&  s>30 ){
    DekenSchakel(0);
    delay(50);
    DekenSchakel(0);
}

   if (h==1 && m==35 &&  s>30 ){
    DekenSchakel(0);
      delay(50);
    DekenSchakel(0);
}
  //------------------------ Slaaptijd---------------------------
  // zet om 22 + ca 25-39 min uur TV en het licht beneden uit en boven aan
  // pas op..als huiskamer al eerder uitgezet, blijft tv aan, dus nog een keer apart
  if (now.hour() == 22 && now.minute() == (35 + random2) && l_status_living == 1)
  {
    GardenLampOFF(); //Tuinlamp
    delay(50);
    YardOFF();// voortuin
    delay(500);
   // RGBlampRED;
    tvOFF();
    delay(1000);
    livingOFF();
   // Blokker1OFF();
   radioUIT;
    delay(1000);
    bedroomON();
    delay(1000);
    leeslampschakel(1);
    starttime2 = now.unixtime();
    //  Serial.println(starttime2);
    counter2 = 1;
    //delay(7000);
    //bedroomOFF();
    bitSet(alg_status, 0); //Set darkbit in alg_status  // gebruik voor nachtlamp
  }
  /************************************************
          's Nachts
   * **********************************************/
   /*
    * //geen idee meer wat dit moest  doen
  if (bitRead(alg_status, 0) == 1 && digitalRead(6) == 1)
  {
    digitalWrite(11, HIGH); // nachtlamp 11 is in middels vijverpomp
  }
  */

if (h==1 && m== random1){
     leeslampschakel(0);
  }
  //zet even na 1 a.m. boven het licht even aan als er niemand is
  if ( h == 1 && m == random3 && l_status_bedroom == 0 && s > 30 && vac_stat == 1)
  {
    bedroomON();
  }
  
  if (h == 1 && m == random3 + 1 && l_status_bedroom == 1)
  {
    bedroomOFF();

  }
/*
  if ( now.hour() == 1 && now.minute() == 17 && l_status_bedroom == 1)
  {
    l_status_bedroom = 0;
    updateData(chip1, 3, 0);
  }
  */

  /*****************************************************
                    ALL DAY
   * ***************************************************/

  //                      blaffen  op oneven uren
  // h & 1 checkt of het LSB '1' (niet nul) is. Dan is het oneven
  if ((h & 1) != 0 && h >= 9 && h <= 19)// op de oneven uren tussen 9 en 19 uur
  {
    if (m == random2 && s == 45 && l_status_bark == 0)
    {
      barkON();// elro 31 A
    }
    if (m == random2 + 1 && l_status_bark == 1)
    {
      barkOFF();
    }
    // if somehow missed:
    if (m == random2 + 3 && l_status_bark == 1)
    {
      barkOFF();
    }
  }

  //-------------------- schakel de hydroponics 6x dag-------------------
  // 0,4,8,12,16,20 uur
  // checkt of een even nummer gedeeld door 2 nog steeds even is. dwz het was deelbaar door 4
  // oneven nummers uitgefilterd in verband met afronding bij delen
  //  beter vervangen door modulo 4..... maar kost 62 meer bytes
  //  EverFlourish A1
  /*
    if ((h & 1) == 0) // is het nummer even? check alleen nodig om fracties te voorkomen
    {
      if(((h / 2) & 1) == 0) // is het als ik het deel door 2 nog steeds even
      {

        //  Serial.print(l_status_h);

        if(m == 0 && s >= 30 && l_status_h == 0)
        {
          hydroON();

        }
        if (m == 2 && l_status_h == 1)
        {
          hydroOFF();
        }
      }
    }
  */
  if (h % HydroFreq == 0)
  {
    if (m == 0 && s >= 30 && l_status_h == 0)
    {
      hydroON();
      //Serial.println("hydro on");
    }
    if (m == 2 && l_status_h == 1)
    {
      hydroOFF();
    }
  }

  // schakel vijver pomp elke 2 uur //op de even uren om 15 over het uur
  if ((h % 2) == 0)
  {
    if (m == 15 && l_status_pond == 0)
    {
      VijverON();
    //  zendNEC(0xF7C03F);//aan
    //  delay(60);
    //  zendNEC(0xF7609F);//blauw
    }
    if (m == 25 && l_status_pond == 1)
    {
      VijverOFF();
     // delay(60);
     // zendNEC(0xF740BF);//off
    //  delay(60);
    //  RGBlampUIT;
  //    delay(60);
    //  RGBlampUIT;
    }
  }


  //-------- POP   beweging  na 3 uur
  if (h >= 15)
  {
    if (m == random2 + h && l_status_pop == 0)
    {
      popON();
    }
    if (m == random2 + h + 1 && l_status_pop == 1)
    {
      popOFF();
    }

    if (m == 58 - (0.5 * h) - random1 && l_status_pop == 0)
    {
      popON();
    }
    if (m == 59 && l_status_pop == 1)
    {
      popOFF();
    }
  }




  //----------------- Tuinlamp--------------------------------------------
  // aan van 5 pm tot 2 am en van 6 am tot 8 am
  //  if (now.hour() == 17 && now.minute() == 0 && l_status_TuinLamp== 0)
  if (h == onder + 1 && m == onderm && l_status_TuinLamp == 0)
  {
    GardenLampON();
    YardON();
  }
  if (now.hour() == 23 && now.minute() == 1 && l_status_TuinLamp == 1)
  {
    GardenLampOFF();// wordt al bij 'slaaptijd'  uitgezet maar hier nog een keer voor de zekerheid
    YardOFF();
  }
  if (now.hour() == 6 && now.minute() == 0 && l_status_TuinLamp == 0)
  {
    //  GardenLampON();
  }
  if (now.hour() == 8 && now.minute() == 1 && l_status_TuinLamp == 1)
  {
    //  GardenLampOFF();
  }
  //------------------Voortuinlamp / Yard  zie bij GardenLamp
  if (h == onder + 1 && m == onderm && l_status_yard == 0)
  {
    //  YardON();
  }

  //--------------einde real TV----------------

  //****************** zet statusflaggen op 0 en schrijf naar EEPROM **************************
  // reset last nights statusflags
  ///// ZOU GECOMBINEERD MOETEN/KUNNEN WORDEN MET ResetStatus()  en met EEPROM0()

  if (now.hour() == 5 && now.minute() == 55 && now.second() >= 59 && bitRead(alg_status, 4) == 0)
  {
    l_status_living = 0;  // 1-Woonkamer Elro
    l_status_study = 0;   // 2-Studeerkamer Elro
    l_status_bedroom = 0;   // 3-Slaapkamer Elro
    l_status4 = 0;      // 4-Blokker1 radio
    l_status5 = 0;      // 5-Blokker2 tvbeneden
    l_status6 = 0;      // 6-Blokker3
    l_status_bark = 0;    // 7-bark ElrobuitenA
    l_status_nursery = 0;   // 8-kamer kinderkamer ElrobuitenD
    l_status_h = 0;     // 9-Everswitch1  hydroponicspomp
    l_status_TuinLamp = 0;  // 10-Everswitch2
    l_status_pond = 0;    // 11-Everswitch3
    l_status_TV = 0;    // 12-TV Eurodomest1
    l_status_pop = 0;     // 13-pop  Eurodomest2
    l_status_spot = 0;    // 14-Buitenspot  Eurodomest3
    l_status_tiny = 0;    // 15 tinyrelais
    l_status_I = 0;     // 16 internalrelais
    l_status_yard = 0;    // 17-Eurodomest 2A
    l_status_leeslamp = 0;    // 18-Eurodomest 2B
    l_status_Deken = 0;   // 19

    bitClear(alg_status, 0);// darkbit gecleared. andere bits blijven staan
    bitSet(alg_status, 4); // zet flag zodat het maar 1x gebeurd. Zet die na 6 uur weer uit
    //  updateData(chip1, algemeen, alg_status); niet echt nodig
    tijd();
    Serial.println(F("Alle licht statussen uit"));

    for (byte i = 1; i < numberOfItems; ++i) //2o vervangen door numberOfItems? of numberOfItems-1?
    {
      updateData(chip1, i, 0);
    }
  }
  if (h == 6 && m == 5 && bitRead(alg_status, 4) == 1)
  {
    bitClear(alg_status, 4); // flag gecleard die de flaggen cleart
  }

  //  leeslampschakel(1);
  //  leeslampschakel(0);
}
//--------------


//----------------- 1. Huiskamer-------------------------
void livingON()
{
  //ab440Switch.sendSignal(29, 'A', true);
  huiskamerAAN; //macro
  l_status_living = 1; //light On
  handle_switches(1, 1);
  //  tijd();
  //  Serial.println(F("Woonkamer aan"));
  //  updateData(chip1, 1, 1);
  //  arrayprint(1);
  //  delay(50);
  //  huiskamerAAN; //macro
  //  logSwitchOn(1);
#ifdef DEBUG
  //  Serial.print("huiskamer aan debug");
#endif
  if (h >= 15 && h <= 22)
  {
    logData();  // sla de aan tijd op dat licht aan ging
  }
}
void livingOFF()
{
  //ab440Switch.sendSignal(29, 'A', false);
  huiskamerUIT; //macro
  l_status_living = 0; //light Off
  handle_switches(1, l_status_living);
  //tijd();
  //Serial.println("Woonkamer uit");
  //  updateData(chip1, 1, 0);
  //  arrayprint(1);
  //  delay(50);
  //ab440Switch.sendSignal(29, 'A', false);
  huiskamerUIT;
#ifdef DEBUG
  //  Serial.print("huiskamer uit debug");
#endif
}
//-------------2. Studeerkamer-----AB440 Switch B---------------------

void studyON()
{
  studyAAN;
  l_status_study = 1; //Study light On
  handle_switches(2, l_status_study);

}
void studyOFF()
{
  studyUIT;
  l_status_study = 0; //light Off
  handle_switches(2, l_status_study);
  studyUIT;
}

void study_handle(boolean schakel) //zou ON en OFF moeten vervangen
{
  if (schakel == 1)
  {
    studyAAN;
    l_status_study = 1;

  }
  else
  {
    studyUIT;
    l_status_study = 2;
  }
  handle_switches(2, l_status_study);
}

//---------------3. Slaapkamer-----------------------
void bedroomON()
{
  bedroomAAN;
  //ab440Switch.sendSignal(29, 'C', true);
  l_status_bedroom = 1; //light On
  handle_switches(3, l_status_bedroom);
  //tijd();
  //Serial.println(F("Slaapkamer aan"));
  //updateData(chip1, 3, 1);
  //arrayprint(3);
  bedroomAAN;
  //logSwitchOn(3);
}
void bedroomOFF()
{
  bedroomUIT;
  //ab440Switch.sendSignal(29, 'C', false);
  l_status_bedroom = 0; //light Off
  handle_switches(3, l_status_bedroom);
  //tijd();
  //Serial.println(F("Slaapkamer uit"));
  //  updateData(chip1, 3, 0);
  //arrayprint(3);
  //ab440Switch.sendSignal(29, 'C', false);
  bedroomUIT;
}
//-------------4. Blokker 1 -----------------------------
void Blokker1ON()
{
  radioAAN;
  l_status4 = 1;
  handle_switches(4, l_status4);
  radioAAN;
}
void Blokker1OFF()
{
  radioUIT;
  l_status4 = 0;
  handle_switches(4, l_status4);
  radioUIT;
}

//-------------5. Blokker 2--------------------------
void Blokker2ON() //tv beneden
{
  blokkerTransmitter.sendSignal(2, true);
  l_status5 = 1;
  handle_switches(5, l_status5);
}
void Blokker2OFF()
{
  blokkerTransmitter.sendSignal(2, false);
  l_status5 = 0;
handle_switches(5,l_status5);
  blokkerTransmitter.sendSignal(2, false);
}
//-------------6. Blokker 3-------------------------------
void Blokker3ON()
{
  blokkerTransmitter.sendSignal(3, true);
  l_status6 = 1;
handle_switches(6,l_status6);
}
void Blokker3OFF()
{
  blokkerTransmitter.sendSignal(3, false);
  l_status6 = 0;
 handle_switches(6,l_status6);
  blokkerTransmitter.sendSignal(3, false);
}
//-------------7. Blaffen--------------------------------
void barkON()
{
  barkAAN;
  l_status_bark = 1; //light On
  handle_switches(7, l_status_bark);
  barkAAN;
}
void barkOFF()
{
  barkUIT;
  l_status_bark = 0; //bark Off
  handle_switches(7, l_status_bark);
  barkUIT;
}
//--------------8. Kinderkamer------------------------
void kinderkamerON()
{
  kinderkamerAAN;
  l_status_nursery = 1;
  handle_switches(8, l_status_nursery);
}
void kinderkamerOFF()
{
  kinderkamerUIT;
  l_status_nursery = 0;
  handle_switches(8, l_status_nursery);
}
//-------------------9. hydroponics------------------------
void hydroON()
{
  hydroAAN;
  //  everswitch.sendSignal('A', 1, true);
  l_status_h = 1;
  //  handle_switches(9, l_status_h);
  tijd();
  Serial.println(F("Irrigatie aan"));
  //updateData(chip1, 9, 1);
  //arrayprint(9);
  logSwitchOn(9);
}
void hydroOFF()
{
  hydroUIT;
  l_status_h = 0;
  tijd();
  Serial.println(F("Irrigatie uit"));
  // updateData(chip1, 9, 0);
  //arrayprint(9);
  hydroUIT;
}
//------------------10. E2-everswitch2-tuinlamp---------------
void GardenLampON()
{
  everswitch.sendSignal('A', 2, true);
  l_status_TuinLamp = 1;
  updateData(chip1, 10, 1);
  handle_switches(10, l_status_TuinLamp);
  everswitch.sendSignal('A', 2, true);
  //  logSwitchOn(10);
}
void GardenLampOFF()
{
  everswitch.sendSignal('A', 2, false);
  l_status_TuinLamp = 0;
  handle_switches(10, l_status_TuinLamp);
  everswitch.sendSignal('A', 2, false);
}
//------------------11. Vijver pomp  (EverFlourish3)-----------------
void VijverON()
{
  vijverAAN;
  l_status_pond = 1;
  handle_switches(11, l_status_pond);
  vijverAAN;

}
void VijverOFF()
{
  vijverUIT;
  l_status_pond = 0;
  handle_switches(11, l_status_pond);
  vijverUIT;
}
//----------------12. TV----------------------------
void tvON()
{
  tvAAN;
  l_status_TV = 1; //TV aan
  handle_switches(12, l_status_TV);
}
void tvOFF()
{
  zendRC5(0x180C); // zet evt ook echte TV af
  tvUIT;
  //  delay(50);
  l_status_TV = 0;
  handle_switches(12, l_status_TV);
 }
//---------------13. Pop------------------
void popON()
{
  popUIT; // Zet eerst uit, voor de zekerheid// helpt niet bij gebufferde voeding
  delay(50);
  popAAN;
  delay(30);
  l_status_pop = 1; //pop aan
  // updateData(chip1, 13, 1);// eigenlijk niet nodig
  //arrayprint(13);
  tijd();
  Serial.println(F("Pop aan"));
  //logSwitchOn(13);
}
void popOFF()
{
  popUIT;
  delay(30);
  l_status_pop = 0;
  // updateData(chip1, 13, 0);
  //arrayprint(13);
  delay(50);
  tijd();
  Serial.println(F("Pop uit"));
  popUIT;
}
//---------------14. Spot---------------
void spotON()
{
  spotAAN;
  delay(30);
  l_status_spot = 1;
  handle_switches(14, l_status_spot);
  spotAAN;
}

void spotOFF()
{
  spotUIT;
  delay(30);
  l_status_spot = 0;
  handle_switches(14, l_status_spot);
  spotUIT;
  delay(50);
}

//----------------15. tiny (extern) Relais-Enerswitch 4---------------------------
void relaisON()
{
  relaisAAN; //macro
  delay(50);
  l_status_tiny = 1; //
  handle_switches(15, l_status_tiny);
}
void relaisOFF()
{
  relaisUIT;
  delay(50);
  l_status_tiny = 0;
  handle_switches(15, l_status_tiny);
}

void setDimmer(byte dimCmd)
{
  ledDimSwitch.sendSignal(dimaddress, dimCmd);
  //Serial.println("dimmer");
}

// ------------------------16. Internal relais-------------------------
void Irelais(byte r)
{
  digitalWrite(RelayPin, r);//pin4
  l_status_I = r;
  handle_switches(16, l_status_I);
}
// ------------------------17. eurodomest 2 1 front yard
void YardON()
{
  YardAAN;
  delay(30);
  l_status_yard = 1;
  handle_switches(17, l_status_yard);
}
void YardOFF()
{
  YardOFF;
  delay(30);
  l_status_yard = 0;
  handle_switches(17, l_status_yard);
}
// ------------------------18. eurodomest 2 2
/*
void leeslampON()
{
  leeslampAAN;
  delay(30);
  l_status_leeslamp = 1;
  handle_switches(18, l_status_leeslamp);
}
void leeslampOFF()

{
  leeslampUIT;
  delay(30);
  l_status_leeslamp = 0;
  handle_switches(18, l_status_leeslamp);
}
*/
void leeslampschakel(boolean schakel)// vervangt bovenstaande 2 procs. saves 34 bytes
{
  if (schakel == 1)
  {
    leeslampAAN;
  }
  else
  {
    leeslampUIT;
  }
  l_status_leeslamp = schakel;
  handle_switches(18, l_status_leeslamp);
}
// ------------------------19. eurodomest 2 3
void DekenON()
{
  DekenAAN;
  delay(30);
  l_status_Deken = 1;
  handle_switches(19, l_status_Deken);
}
void DekenOFF()
{
  DekenUIT;
  delay(30);
  l_status_Deken = 0;
  handle_switches(19, l_status_Deken);
  DekenUIT;
}
void DekenSchakel (boolean schakel)
{
  if (schakel==HIGH){
  DekenAAN;
  }
  else{
    DekenUIT;
  }
  l_status_Deken=schakel;
   handle_switches(19, l_status_Deken);
}

//--------------------------------------------
//                      Various functions
//  Prints the date
void printDatum()
{
  printDigits(d);
  Serial.print("-");
  printDigits(mo);
  Serial.print("-");
  Serial.print(j);
}
// prints the time
void tijd()
{
  printDigits(h);
  Serial.print(":");
  printDigits(m);
  Serial.print(":");
  printDigits(s);
  Serial.print(" ");
}
// activates voice message
void boodschap()
{
  digitalWrite(soundOut, HIGH);
  g_status = 1;
  //Serial.print(F("Vuil buiten zetten"));
  delay(10);
  digitalWrite(soundOut, LOW);
}

//------------Day of week----------------
/*
  byte Weekdag(byte b)
  {
  switch (b)
  {
    case 0:
      Serial.print(F("Zon"));
      break;
    case 1:
      Serial.print(F("Maan"));
      break;
    case 2:
      Serial.print(F("Dins"));
      break;
    case 3:
      Serial.print(F("Woens"));
      break;
    case 4:
      Serial.print(F("Donder"));
      break;
    case 5:
      Serial.print(F("Vrij"));
      break;
    case 6:
      Serial.print(F("Zater"));
      break;
    default:
      Serial.print(F("Controleer Datum"));
      break;
  }
  Serial.print(F("dag"));
  return (b);
  }
*/

void Weekdag(byte b)
{
  Serial.print(dagen[b]);
  Serial.print(F("dag "));
}

int Map(byte sens)
{
  /////
}

byte sample(byte z)
/* This function will read the Pin 'z' 5 times and take an average.
  Afterwards it will be mapped to 8 bits by dividing by 4
  Could ofcourse immediately divided by 20
*/
{
  byte i;
  int sval = 0;
  for (i = 0; i < 5; i++)
  {
    sval = sval + analogRead(z);// sensor on analog pin 'z'
  }
  //sval = sval / 5;    // average
  //sval = sval / 4;    // scale to 8 bits (0 - 255)
  sval = sval / 20;
  return sval;
}

int gemiddeld(byte z)
{
  byte i;
  int sval = 0;
  for (i = 0; i < 5; i++)
  {
    sval = sval + analogRead(z);// sensor on analog pin 'z'
  }
  sval = sval / 5;
  return sval;
}


void writeData(int device, unsigned int addr, byte data)
// writes a byte of data 'data' to the chip at I2C address 'device', in memory location 'addr'
{
  if ( addr > 65535 )// FFFF  grootste 4 bit nummer
    addr = addr | B00001000;

  Wire.beginTransmission(device);
  Wire.write((int)(addr >> 8)); // left-part of pointer address is eigenlijk addr/8
  Wire.write((int)(addr & 0xFF)); // and the right  is addr AND 255
  Wire.write(data);
  Wire.endTransmission();
  delay(10);
}

// Updates data in memory location
void updateData(int device, unsigned int addr, byte data)
{
  if (data != readData(device, addr))
  {
    writeData(device, addr, data);
  }
}

// Reads data from memory location
byte readData(int device, unsigned int add)
// reads a byte of data from memory location 'add' in chip at I2C address 'device'
{
  byte result; // returned value
  Wire.beginTransmission(device); // these three lines set the pointer position in the EEPROM
  Wire.write((int)(add >> 8)); // left-part of pointer address
  Wire.write((int)(add & 0xFF)); // and the right
  Wire.endTransmission();
  Wire.requestFrom(device, 1); // now get the byte of data...
  result = Wire.read();
  return result; // and return it as a result of the function readData
}

//Cuts integer in 2 bytes
void cutInteger(int value) //  nog niet gebruikt

{
  byte bLSB = value & 0xFF;// of gebruik lowByte(value)
  byte bMSB = value >> 8;//of gebruik highByte(value);
}
//Makes integer from two bytes
int combine (byte lsbv, byte msbv)
{
  int value = msbv << 8;
  value = value | lsbv;
  //value= msbv<<8 | lsvb;
  return value;
}

void convertTemperature()
{
  // Set CONV
  uint8_t ctReg = readRegister(DS3231_CONTROL_REG);
  ctReg |= 0b00100000;
  //writeRegister(DS3231_CONTROL_REG,ctReg);
  //wait until CONV is cleared. Indicates new temperature value is available in register.
  do
  {
    //do nothing
  }
  while ((readRegister(DS3231_CONTROL_REG) & 0b00100000) == 0b00100000 );
}

float getTemperature()
//temp3231 = ((((short)tMSB << 8) | (short)tLSB) >> 6) / 4.0;
{
  int   temperatureCelsius;
  float fTemperatureCelsius;

  uint8_t tUBYTE  = readRegister(REG_TEMPM); //Two's complement form
  uint8_t tLRBYTE = readRegister(REG_TEMPL); //Fractional part

  if (tUBYTE & 0b10000000) //check if -ve number
  {
    tUBYTE  ^= 0b11111111;
    tUBYTE  += 0x1;
    fTemperatureCelsius = tUBYTE + ((tLRBYTE >> 6) * 0.25);
    fTemperatureCelsius = fTemperatureCelsius * -1;
  }
  else
  {
    fTemperatureCelsius = tUBYTE + ((tLRBYTE >> 6) * 0.25);
  }

  return (fTemperatureCelsius);

}

//===============================================
// use: Serial.println(int(Thermistor(analogRead(NTCpin))));
//Steinhart Hart
/* double Thermistor(int RawADC)
  {
  double Temp;
  // Temp = log(10000.0*((1024.0/RawADC-1)));
  Temp   = log(10000.0 / (1024.0 / RawADC - 1)); // for pull-up configuration
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp )) * Temp );
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius
  //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  return Temp;
  }*/
//-----------------------------------

double THERMISTOR(int average)
{
  double steinhart;
  average = 1023 / average - 1;
  average = SERIESRESISTOR / average;
  steinhart = average / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert to C
  return steinhart;
}

//================================================
// converts a float temperature to a byte
// format  sign (1 bit) temp (5 bits) fraction(2 bits)
byte floatToByte(float temp2)
{
  double temp = abs(temp2);
  byte sign = 128;
  int heel = int(temp);
  double fractie = temp - heel;
  if (temp2 >= 0)
  {
    sign = 0;
  }
  fractie = (temp - heel);
  fractie = fractie * 100;
  byte fractie2 = 0;
  if (fractie >= 25)
  {
    fractie2 = 1;
  }
  if (fractie >= 50)
  {
    fractie2 = 2;
  }
  if (fractie >= 75)
  {
    fractie2 = 3;
  }
  byte temperatuur = (((heel << 2) | fractie2) | sign);
  return temperatuur;
}


//================================================


void zonOpOnder()
{
 //int sunrise = (392 + 137 * cos((doy + 8 )/ 58.1))-60*dst;
 int sunrise = (392 + 137 * cos((doy + 8 )* 0.017214206))-60*dst;//multiplication faster than division
 int sunset=(1144-170*cos((doy+8)/58.09))-60*dst;
  oph=sunrise/60;
  opm=sunrise%60;
  onder=sunset/60;
  onderm=sunset%60;
 
}

/*
void zonOpOnder() // Stelt in wanneer de zon op en onder gaat
{
  switch (mo)
  {
    case 1: // 16.39-17.15

      onder = 16;
      onderm = 38 + d;
      //------------

      if (d > 16)
      {
        onder = 17;
        onderm = d - 16; //17 jan => 17.01 - 31 jan=> 17.15
      }
      oph = 8;  // zonsopgang

      opm = 50 - d; // 8:49-8
      break;
    case 2:  //17.26-18-20
      onder = 17;
      onderm = 26 + d;
      if (d > 18)
      {
        onder = 18;
        onderm = d - 18;

      }
      oph = 8;
      opm = 21 - d;
      if (d > 14)
        oph = 7;
      opm = 70 - d;
      if (d > 14)
        oph = 7;
      opm = 55 - (2 * (d - 15));
      break;
    case 3: // 18.19-20
      onder = 18;
      onderm = 18 + d;
      if (d > 24)
      {
        onder = 19;
        onderm = d - 24;
      }

      //if(d > 27)
      if (d >= summertimeday)
      {
        onder = 20;
        onderm = 15;
      }

      break;
    case 4:// 20.15-20.53
      onder = 20;
      onderm = d + 14;
      if (d > 15)
      {
        onderm = d + 22;
      }

      break;
    case 5: //21.06-21.51
      onder = 21;
      onderm = d + 5;
      if (d > 15)
      {
        onderm = d + 20;
      }
      break;
    case 6: //21.50
      onder = 21;
      onderm = 50;
      break;
    case 7: // 22.00-21.45
      onder = 22;
      onderm = 0 + random2;
      if (d > 10)
      {
        onder = 21;
        onderm = 50;
      }
      if (d > 19)
      {
        onder = 21;
        onderm = 67 - d;
      }
      break;
    case 8: //21.24-20.29
      onder = 21;
      onderm = 25 - d;
      if (d > 10)
      {
        onderm = 10 + random1;
      }
      if (d > 16)
      {
        onder = 20;
        onderm = 73 - d;
      }
      if (d > 24)
      {
        onderm = 60 - d;
      }
      break;
    case 9: //  20.28-19.20
      if (d <= 13) // deze check niet nodig
      {
        onder = 20;
        onderm = 30 - 2 * d;
      }
      if (d >= 14);
      {
        onder = 19;
        onderm = 63 - d;
      }
      if (d >= 20)
      {
        onder = 19;
        onderm = 51 - d;
      }
      break;
    case 10: //19.16-17.14
      onder = 18;
      //onderm = 44 - d;
      onderm = 76 - 2 * d;
      if (d < 9)
      {
        onder = 19;
        onderm = 18 - 2 * d;
      }
      //  if (d > 24) // dst af in 2015, moet ik nog wijzigen. done
      if (d >= wintertimeday)
      {
        onder = 17;// en onderm is nog steeds 76-2xonderm
      }
      break;
   
    case 11: // 17.00-16.20
      onder = 17;
      onderm = 0  + random2; //0-10 min// of 14-d
      if (d > 10)
      {
        onder = 16;
        onderm = 60 - 2 * (d - 10);
      }
      break;
    

    case 12:// 16.20-16.30
      onder = 16;
      onderm = 20 + random2;
      break;
    default:
      onder = 21;
      break;
  }

  //trek half uur af
  if (onderm >= 30)
  {
    onderm = onderm - 30; //onderm-period
  }
  else
  {
    onder = onder - 1;
    onderm = onderm + 30;//onderm+60-period
  }
  //Serial.print(onderm);
}
*/

//==================================================
//normalize time
//trek periode minuten af
void normalize()
{
  if (onderm >= periode)
  {
    onderm = onderm - periode; //onderm-period
  }
  else
  {
    onder = onder - 1;
    onderm = onderm + 60 - periode;
  }
}

//=================================================

/*
  zon onder
  jan: 16.40-17.25
  feb: 17.25-18.17
  mrt: 18.19-20.12
  apr: 20.13-21
  mei: 21-21.50
  jun: 21.50-22.0
  jul: 22.03-21.32
  aug: 21.30-20.30
  sep: 20.30-19.21
  okt: 19.18-17.14
  nov: 17.12-16.13
  dec: 16.32-16.38
*/

/*
  zon op
  jan: 8:48-8:22
  feb: 8:21-7:27
  mrt: 7:25-7:16
  Apr: 7:14-6:11
  Mei: 6:09-5:26
  jun: 5:25-5:23
  jul: 5:24-6:00
  aug: 6:02-6:50
  sep: 6:52-7:39
  okt: 7:41-8:30-7:33
  nov: 7:35-8:25
  dec: 8:26-8:48
*/


void printDigits(byte digits)
{
  // utility function for digital clock display: prints leading 0

  if (digits < 10)
    Serial.print('0');
  Serial.print(digits, DEC);
}

void CurrentSwitch()   // shows current status of the switches
{
  Serial.println(F("Current SWITCH state:"));
  for (int i = 1; i < 20; ++i) // vervangen door numberOfItems?
  {
    //Serial.print(i);
    printDigits(i);
    Serial.print(" ");
    Serial.print(readData(chip1, i));// prints EEPROM address=content
    Serial.print(" ");
    Serial.print(results[i]); // from names array
    Serial.print(" ");
    Serial.print(stat[(readData(chip1, i))]); // from status array
    if (i <= 19)
    {
      Serial.print(". Last on: ");

      printlogSwitchOn(i);
    }
    Serial.println();
    delay(50);
  }
}

void CurrentOnSwitch()   // shows only statusses that are ON
{
  Serial.println(F("Current SWITCHes that are ON:"));
  for (int i = 1; i < 20; ++i) // vervangen door numberOfItems?
  {
    //Serial.print(i);
    if (readData(chip1, i) == 1)
    {
      printDigits(i);
      Serial.print(" ");
      Serial.print(readData(chip1, i));// prints EEPROM address=content
      Serial.print(" ");
      //  Serial.print(results[i]); // from names array
      //  Serial.print(" ");
      //  Serial.print(stat[(readData(chip1, i))]); // from status array
      arrayprint(i);
      Serial.print(F(" Sinds "));
      printlogSwitchOn(i);
      Serial.println();
      delay(50);

    }
    //else{Serial.println("Alles uit");}
  }
  //toegevoegd 2mei: toont of dst aan of uit is
  // en 7 mei weer weggehaald
  /*
    printDigits(0);
    Serial.print(" ");
    Serial.print(readData(chip1, 0));// prints EEPROM address=content
    Serial.print(" ");
    //  Serial.print(results[0]); // from names array
    //  Serial.print(" ");
    //  Serial.print(stat[(readData(chip1, 0))]);
    arrayprint(0);
    //----------------
  */
}

void setToStatus() // set all switches to their supposed status
{
  tijd();
  Serial.println(F("Set lights according to status"));
  l_status_living = readData(chip1, 1);
  //1 woonkamer
  l_status_study = readData(chip1, 2);
  l_status_bedroom = readData(chip1, 3);
  l_status4 = readData(chip1, 4);       // 4-Radio Blokker1
  l_status5 = readData(chip1, 5);       // 5-Blokker2 TV beneden
  l_status6 = readData(chip1, 6);       // 6-Blokker3
  l_status_bark = readData(chip1, 7);     // 7-bark ElrobuitenA
  l_status_nursery = readData(chip1, 8);    // 8-kinderkamer ElrobuitenD
  l_status_h = readData(chip1, 9);      // 9-Everswitch1  hydroponicspomp
  l_status_TuinLamp = readData(chip1, 10);  // 10-Everswitch2 Tuinlamp/realtv?
  l_status_pond = readData(chip1, 11);    // 11-Everswitch3
  l_status_TV = readData(chip1, 12);      // 12-TV  boven Eurodomest1
  l_status_pop = readData(chip1, 13);     // 13-pop  Eurodomest2
  l_status_spot = readData(chip1, 14);    // 14-Buitenspot  Eurodomest3
  l_status_tiny = readData(chip1, 15);    // 15-External relais
  l_status_I = readData(chip1, 16);       // 16-Internal relais
  l_status_yard = readData(chip1, 17);    // 17-Eurodomest 2A
  l_status_leeslamp = readData(chip1, 18);  // 18-Eurodomest 2B
 // l_status_Deken = readData(chip1, 19);     // 19-Eurodomest 2C
 l_status_Deken=0; // voor veiligheid
  huiskamerStatus; //these are  all '#defines'
  studyStatus;
  bedroomStatus;
  radioStatus;
  TVhStatus;
  Extra2Status; // (6)
  barkStatus;
  kinderkamerStatus;
  hydroStatus;
  TuinLampStatus;
  vijverStatus;  //(11)
  tVStatus;
  popStatus;
  spotStatus;
  relaisStatus;  // (15)
  InternalRelayStatus;
  YardStatus;
  leeslampStatus;
  DekenStatus;
  DekenUIT ; //en nog eens voor de veiligheid
  //---------
  /*
    ab440Switch.sendSignal(29, 'B', readData(chip1, 2));    //2 studeerkamer
    ab440Switch.sendSignal(29, 'C', readData(chip1, 3));    //3 slaapkamer
    blokkerTransmitter.sendSignal(1, readData(chip1, 4));   //4 Radio Blokker
    blokkerTransmitter.sendSignal(2, readData(chip1, 5));   //5 Blokker
    blokkerTransmitter.sendSignal(3, readData(chip1, 6));   //6 Blokker
    ab440Switch.sendSignal(31, 'A', readData(chip1, 7));    //7 blaffen
    ab440Switch.sendSignal(31, 'D', readData(chip1, 8));    //8 kinderkamer
    everswitch.sendSignal('A', 1, readData(chip1, 9));      //9 hydroponics
    everswitch.sendSignal('A', 2, readData(chip1, 10));     //10 everswitch
    everswitch.sendSignal('A', 3, readData(chip1, 11));     //11 everswitch
    enerswitch.sendSignal(euro, 1, readData(chip1, 12));    //12 Fake TV-eurodomest
    delay(50);
    enerswitch.sendSignal(euro, 2, readData(chip1, 13));    //13 Bewegende Pop eurodomest
    delay(50);
    enerswitch.sendSignal(euro, 3, readData(chip1, 14));    //14 Buitenspot Eurodomest
    enerswitch.sendSignal(euro, 4, readData(chip1, 15));    //15 Attiny85Ener
    //Irelais(readData(chip1, 16));             //16 Internal relay
    digitalWrite(4, readData(chip1, 16));
    enerswitch.sendSignal(euro, 1, readData(chip1, 17));    //17
    enerswitch.sendSignal(euro, 2, readData(chip1, 18));    //18
    enerswitch.sendSignal(euro, 3, readData(chip1, 19));    //19
  */
  ledDimSwitch.sendSignal(dimaddress, readData(chip1, dimmerstatus)); //1? Dimmer
  //CurrentOnSwitch(); // laat zien welke switches aan zijn
  HydroFreq = readData(chip1, HydroFreqStore); // leest de irrigatiefrequentie uit de locatie HydroFreqStore
}


void resetStatus() // reset all the statusflags to 0 behalve DST
{
  l_status_living = 0;  // 1-huiskamer Elro_Wit1
  l_status_study = 0;   // 2-study Elro_Wit2
  l_status_bedroom = 0;   // 3-boven  Elro_Wit3
  l_status4 = 0;      // 4-Radio Blokker1
  l_status5 = 0;      // 5-Blokker2
  l_status6 = 0;      // 6-Blokker3
  l_status_bark = 0;    // 7-bark ElrobuitenA
  l_status_nursery = 0;   // 8-kamer kinderkamer ElrobuitenD
  l_status_h = 0;     // 9-Everswitch1  hydroponicspomp
  l_status_TuinLamp = 0;  // 10-Everswitch2
  l_status_pond = 0;    // 11-Everswitch3
  l_status_TV = 0;    // 12-Fake TV Eurodomest1
  l_status_pop = 0;     // 13- pop  Eurodomest2
  l_status_spot = 0;    // 14- Buitenspot  Eurodomest3
  l_status_tiny = 0;    // 15-Laagspanningsrelais Eurodomest4
  l_status_I = 0;     // 16 internal relais
  l_status_yard = 0;    // 17-Elro Wit1
  l_status_leeslamp = 0;    // 18-Eurodomest 2B
  l_status_Deken = 0;   // 19
  l_status_R1 = 0;      //

  //resetStatus = 0;
  Serial.println(F("Statusflaggen op 0"));
}
//  zet  EEPROM flags op 0 // behalve DST
void EEPROM_Null()
{
  for (byte i = 1; i < 20; ++i) //vervang door numberOfItems?
  {
    updateData(chip1, i, 0);
  }
  Serial.println(F("EEPROM op 0"));
}

void randomNr()
//wordt 1x dag aangeroepen om een aantal random nummers te krijgen
{
  random1 = random(5);
  random2 = random(10);
  random3 = random(15);
  //random4 = random(20);
  //  random5 = random(22);
}

// RC5 encoding:
//
// START + TOGGLEBIT + UNITCODE + BUTTONCODE
//
// where:
//   START is a two-bit code, always 11
//   TOGGLEBIT is a one-bit code which toggles on each successive button
//   UNITCODE is a five-bit code specifying the unit being commanded (TV, VCR, etc.)
//   BUTTONCODE is a six-bit code for the button command
//
// Each bit, 0 or 1, is transmitted according to "Manchester" encoding:
//
//   0: MARK followed by SPACE, each of duration irparams.t
//   1: SPACE followed by MARK
//


void klok_vooruit(byte second, byte minute)
{
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  minute = minute + 2;
  if (minute >= 60)
  {
    minute = 59;
  }
  Wire.write(decToBcd(minute)); // set minutes
  Wire.endTransmission();
  Serial.println(F("Klok twee minuten naar voren "));
}

// schakel tussen winter en zomertijd
void winter_zomer(byte second, byte minute, byte hour, byte w) // h  eigenlijk niet nodig
{
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  if (w == 0)
  {
    hour = 2;
    Wire.write(decToBcd(hour));// set hour
    Wire.endTransmission();

    //hour = hour - 1;   // zet op wintertijd

    writeDST;
    //  writeData(chip1,0,dst);
    //  Serial.print("Wintertijd");
  }
  if (w == 1)
  {
    hour = 3;
    Wire.write(decToBcd(hour));// set hour
    Wire.endTransmission();
    //hour = hour + 1;   // zet naar zomertijd
    writeDST;
    //  writeData(chip1,0,dst);
    //  Serial.print("Zomertijd");
  }

  Serial.print("DST set/reset ");
  Serial.println(stat[(readDST)]); // from status array

}

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return ( (val / 10 * 16) + (val % 10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return ( (val / 16 * 10) + (val % 16) );
}

uint8_t readRegister(uint8_t regaddress)
{
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write((byte)regaddress);
  Wire.endTransmission();
  Wire.requestFrom(DS3231_ADDRESS, 1);
  return Wire.read();
}

void alarm()
{
  alarmstat = 1;
  knipperstatus = HIGH;
  starttime = millis();// can also use now.unixtime()  and use 300 for 5 min
  counter = 1; // geeft aan dat de buzzer tijd bijgehouden gaat worden
  //  huiskamerAAN; wordt als knipperlicht geupdate
  buzzerAAN;
  Doorbell;// Wit
  studyAAN;
  bedroomAAN;
  barkAAN;
  //kinderkamerAAN;
  spotAAN;

  //  led1.Update();
  //  led2.Update();
}
void alarmOFF()
{
  knipperstatus = LOW;
  lamp1.Stop();
  huiskamerUIT;
  alarmstat = 0; // geeft aan dat er weer een nieuwe alarmtrigger kan komen
  counter = 0; //  counter wordt gestopt
  buzzerUIT; // zou al uit moeten zijn
  studyUIT;
  bedroomUIT;
  barkUIT;
  huiskamerUIT; // voor de zekerheid
}
void SelectPlus(uint32_t address)
{
  int pulseWidth = 360;     // Pulse breedte in uS
  byte repeat = 16;               // repeat send. Sometimes even 16 is not enough and one needs to enter the procedure twice
  uint32_t databit;
  uint32_t mask = 0x10000;
  uint32_t sendbuff;


  for (byte j = 0; j <= repeat; j++)
  {
    sendbuff = address;
    // send 3 HIGH pulses for syncing
    digitalWrite(RfPin, HIGH);
    delayMicroseconds(pulseWidth * 3);

    // Send command
    for (int i = 0; i < 18; i++)            // 13+4 bits nope
    {
      // read data bit7
      databit = sendbuff & mask;              // Get most left bit
      sendbuff = (sendbuff << 1);               // Shift left

      if (databit != mask)                    // Write 0
      {
        digitalWrite(RfPin, LOW);
        delayMicroseconds(pulseWidth);
        digitalWrite(RfPin, HIGH);
        delayMicroseconds(pulseWidth * 3);
      }
      else                                      // Write 1
      {
        digitalWrite(RfPin, LOW);
        delayMicroseconds(pulseWidth * 3);
        digitalWrite(RfPin, HIGH);
        delayMicroseconds(pulseWidth);
      }
    }
    digitalWrite(RfPin, LOW);
    if (j < repeat)
    {
      delayMicroseconds(pulseWidth * 16);
      // delay between transmits
    }

  }

}


/**************************************
        Logs
 * ************************************/

void logData()
// slaat  tijd licht aan + donkerniveau op
//gebruikt 101-164  en 201-231
{
  //takes 62 bytes
  updateData(chip1, baseLightOn + ((d * 2) - 1), h);//baselight+1 <->
  updateData(chip1, baseLightOn + (d * 2), m);  // baselight+62
  //
  //  Serial.print(baseLightOn);
  //takes 31 bytes
  updateData(chip1, baseLDR + d, sample(LDRPin));// 201-231
}

void printLog() // prints tijd licht aan + donkerniveau
{
  Serial.print(F("Licht aan voor maand "));
  Serial.println(maand[mo - 1]);
  for (byte y = 1; y < 32; y++)
  {
    //Serial.print(y);
    printDigits(y);
    Serial.print(F(" - "));
    byte temp = readData(chip1, baseLightOn + ((y * 2) - 1));
    //Serial.print(temp);
    printDigits(temp);
    Serial.print(F(":"));
    temp = readData(chip1, baseLightOn + (y * 2));
    //Serial.print(temp);
    printDigits(temp);
    Serial.print(" - donker = ");
    temp = readData(chip1, baseLDR + y);
    Serial.print(temp);
    if (y == d)
    {
      Serial.print("*");

    }
    Serial.println("");
    delay(50);
  }
}

void logTemp(int temperatuur) //externaltenp
// slaat temperatuur van NTC op
// gebruikt 241-288
// divide in LSB en MSB
{
  //write MSB
  byte bMSB = temperatuur >> 8;
  updateData(chip1, baseExtTemp + ((h * 2) - 1), bMSB);//241-287
  //write LSB
  byte bLSB = temperatuur & 0xFF;
  updateData(chip1, baseExtTemp + (h * 2), bLSB);//242-288

}
void logLicht()
// slaat lichtwaarde op (byte)
{
  updateData(chip1, baseLight + h, sample(LDRPin));
}
void printlogLicht()
{
  Serial.print(F("Hourly light value "));
  Weekdag(dag);
  Serial.println();
  for (byte y = 0; y < 24; y++)
  {
    printDigits(y);
    Serial.print(F("h "));
    byte lightvalue = readData(chip1, baseLight + y);//339-362
    Serial.print(lightvalue);
    if (y == h)
    {
      Serial.print("*");
    }
    Serial.println("");
    delay(50);
  }
}

void printLogTemp()
{
  Serial.print(F("Hourly Ext. Temp. "));
  Weekdag(dag);
  Serial.println();
  for (byte y = 0; y < 24; y++)
  {
    printDigits(y);
    Serial.print(F("h "));
    byte bMSB = readData(chip1, baseExtTemp + ((y * 2) - 1));
    byte bLSB = readData(chip1, baseExtTemp + (y * 2));
    Serial.print((bMSB << 8) | bLSB);
    Serial.print(" oC");
    if (y == h) // als counter gelijk is aan het uur
    {
      Serial.print("*");
    }
    Serial.println("");
  }
}

void logIntTemp()
{
  uint8_t tUBYTE  = readRegister(REG_TEMPM); //Two's complement form
  updateData(chip1, baseIntTemp + ((h * 2) - 1), tUBYTE);//290-337
  uint8_t tLRBYTE = readRegister(REG_TEMPL); //Fractional part
  updateData(chip1, baseIntTemp + (h * 2), tLRBYTE);//338
  //Serial.print(tUBYTE);
  //Serial.print(" ");
  //Serial.println(tLRBYTE);
}

// slaat de tijd op wanneer een schakelaar aan ging
void logSwitchOn(byte schakelaar)
{

  updateData(chip1, baseSwitches + schakelaar, h);
  updateData(chip1, baseSwitches + 20 + schakelaar, m);
}
//print de opgeslagen tijd
void printlogSwitchOn(byte schakelaar)
{
  if (readData(chip1, baseSwitches + schakelaar) <= 24) // check op geldig getal
  {
    Serial.print(readData(chip1, baseSwitches + schakelaar));
    Serial.print(":");
    printDigits(readData(chip1, baseSwitches + 20 + schakelaar));//minuten
  }
}

/*********************************
    REG_TEMPM bevat SIGN D D D D D D D
  REG_tUBYTE bevat   D D 0 0 0 0 0 0
  Upper 8 bits bevat integer part
  Lowerbyte bevat fractional part in de upper nibble met nauwkeurigheid van 0.25 graad
  0b0001100101 = +25.25°C
  want 00011001 = 25
  0b01 = 1 (*0.25)
  Omdat het laagste byte alleen de hoogste 2 bits gebruikt (hoeft niet verder te tellen dan 3) moet dat 6 bits naar rechts geschoven worden
  bit7 in het hoogste byte geeft het teken aan '1' wil zeggen 'negatief'
  Stel, het is -18 graden :0b11101110  (=238 in twos complement notatie)
  0b11101110 &   0b10000000 => 0b10000000  dus -ve bit gevonden
  0b11101110 XOR 0b11111111 => 0b00010001 (=17)
  17+1= 18
  18*-1 = -18


  /*********************************************************
   Haalt opgeslagen interne temperatuur op
   en print deze
 * *******************************************************/
void printLogIntTemp()
{
  Serial.print(F("Hourly intern temp "));
  Weekdag(dag);
  Serial.println();
  float fTemperatureCelsius;
  for (byte y = 0; y < 24; y++)
  {
    uint8_t tUBYTE  = readData(chip1, 290 + ((y * 2) - 1)); //Two's complement form
    uint8_t tLRBYTE = readData(chip1, 290 + (y * 2)); //Fractional part

    if (tUBYTE & 0b10000000) //check if -ve number leading '1' indicates -ve number
    {
      tUBYTE  ^= 0b11111111;  // assign by bitwise XOR
      tUBYTE  += 0x1; // assign by sum : tUBYTE=tUBYTE+0x1
      fTemperatureCelsius = tUBYTE + ((tLRBYTE >> 6) * 0.25);
      fTemperatureCelsius = fTemperatureCelsius * -1;
    }
    else
    {
      fTemperatureCelsius = tUBYTE + ((tLRBYTE >> 6) * 0.25);
    }
    printDigits(y);
    Serial.print("h ");
    Serial.print(fTemperatureCelsius);
    Serial.print(" oC");
    if (y == h)
    {
      Serial.print("*");
    }
    Serial.println();
  }
}
/********************************************************
   Sends RC5 data to a TV or other device
 * ******************************************************/
void zendRC5(long data)
{
  long previousRC5;
  //  My_sender.send(data); // is al een RC 5 object
  // voor ontvangst RC5: het toggle bit is 0x0800
  // dus  codeValue ^= 0x0800; om dat uit teschakelen dan wel te toggelen
  if (data == previousRC5)
  {
    My_sender.send(data ^ 0x800);
  }
  else
  {
    My_sender.send(data);
  }
  previousRC5 = data;
}
/********************************************************
   Sends NEC data to a TV or other device     (lamp)
 * ******************************************************/
void zendNEC(unsigned long data)
{
  My_NEC.send(data);
}
/**************************************************************
   Prints the inputs the software will react to
 * ************************************************************/

/**************************************************************
    FM-Radio
 *************************************************************/
 #ifdef RADIO
void radio(double frequency) {
  frequencyB = 4 * (frequency * 1000000 + 225000) / 32768; //calculating PLL woord
  frequencyH = frequencyB >> 8;
  frequencyL = frequencyB & 0XFF;
  delay(50);
  Wire.beginTransmission(0x60);   //writing TEA5767
  Wire.write(frequencyH);
  Wire.write(frequencyL);
  Wire.write(0xB0);
  Wire.write(0x10);
  Wire.write(0x00);
  Wire.endTransmission();
}
#endif
void help()
{
  /*
    #ifdef NL
    Serial.println(F("H/h Huiskamer aan/uit"));
    Serial.println(F("B/b Slaapkamer aan/uit"));
    Serial.println(F("K/k Kinderkamer aan/uit"));
    Serial.println(F("L/l Studeerkamer aan/uit"));
    Serial.println(F("M/m Extern relais aan/uit"));

    Serial.println(F("A/a Intern relais aan/uit"));
    Serial.println(F("O/o Spot aan/uit"));
    //delay(100);
    Serial.println(F("P/p Pop aan/uit"));
    Serial.println(F("I/i Irrigatie aan/uit"));
    Serial.println(F("U/u Weg aan/uit"));
    Serial.println(F("D/d Zwarte/Witte bel"));
    Serial.println(F("r reset")) ;
    Serial.println(F("s status")) ;
    Serial.println(F("R TV uit"));
    //delay(100);
    Serial.println(F("T tijd 2 min vooruit"));
    Serial.println(F("t toon tijd"));
    Serial.println(F("v speel boodschap"));
    Serial.println(F("W/w Winter/zomertijd"));
    Serial.println(F("z temperatuur"));
    Serial.println(F("* licht aan tijd"));
    Serial.println(F("+/- donkerwaarde omhoog/omlaag"));
    //delay(100);
    Serial.println(F("/ show licht aan log"));
    Serial.println(F("[ Show Extern temp"));
    Serial.println(F("] Show Intern temp"));
    Serial.println(F("Q Show donker log"));
    Serial.println(F("! Memory Dump"));
    //delay(100);
    Serial.println(F("@ Her-randomiseer"));
    Serial.println(F("0 zet EEPROM op 0"));
    Serial.println(F("1 Program kanaal 1"));
    Serial.println(F("2 Program kanaal 2"));
    Serial.println(F("3 Program kanaal 3"));
    Serial.println(F("4 Program kanaal 4"));
    Serial.println(F("5-9 TV Channels"));
    Serial.println(F("R-TV uit"));
    #else
    Serial.println(F("H/h Living room on/off"));
    Serial.println(F("B/b Bedroom on/off"));
    Serial.println(F("K/k Nursery on/off"));
    Serial.println(F("L/l Study on/off"));
    Serial.println(F("M/m Extern relay on/off"));
    Serial.println(F("A/a Intern relay on/off"));
    Serial.println(F("O/o Spot on/off"));
    //delay(100);
    Serial.println(F("P/p Doll on/off"));
    Serial.println(F("I/i Irrigation on/off"));
    Serial.println(F("U/u Out/in"));
    Serial.println(F("D/d Black/white chime"));
    Serial.println(F("r reset")) ;
    Serial.println(F("s status")) ;
    Serial.println(F("R TV off"));
    //delay(100);
    Serial.println(F("T advance 2min"));
    Serial.println(F("t show time"));
    Serial.println(F("v message"));
    Serial.println(F("W/w Winter/summertime"));
    Serial.println(F("z temperature"));
    Serial.println(F("* light on time"));
    Serial.println(F("+/- darklevel up/down"));
    //delay(100);
    //Serial.println(F("d Doorbel"));
    Serial.println(F("/ show light on"));
    Serial.println(F("[ Show Extern temp"));
    Serial.println(F("] Show Intern temp"));
    Serial.println(F("Q Show darkness"));
    //Serial.println(F("! Memory Dump"));
    //delay(100);
    Serial.println(F("@ Re-randomise"));
    Serial.println(F("0 set EEPROM to 0"));
    Serial.println("1 Program channel 1");
    Serial.println("2 Program channel 2");
    Serial.println("3 Program channel 3");
    Serial.println("4 Program channel 4");
    Serial.println(F("5-9 TV channel"));
    Serial.println(F("R-TV uit"));
    #endif

    /*
    Aa Bb Hh Ii Kk Ll Mm Oo Pp s  r Tt Uu v Ww z  +- / *@ 01234
  */

}
/*************************************************************************
   This function will program an Eurodomest Switch
   Channels 1-4 are implemented
 * ***********************************************************************/

void programma(byte p)// voor het programmeren van de eurodomest
{
  /*
    //  Serial.println("begin programmeren");
    Serial.println(p);
    for(byte i = 1; i < 10; ++i)
    {
    enerswitch.sendSignal(euro2, p, true);
    delay(30);

    }
    Serial.println(F("klaar"));
  */
}
/****************************************************************************
  This function will blink an LED or sound a buzzer a number
  of times for a specific duration
*****************************************************************************/
void ledblink(int times, int lengthms, int pinnum)
{
  for (int x = 0; x < times; x++)
  {
    digitalWrite(pinnum, HIGH);
    delay (lengthms);
    digitalWrite(pinnum, LOW);
    delay(lengthms);
  }
}

/****************************************************************************
    This function will print the state of a switch
    as drawn from the arrays
 * **************************************************************************/

void arrayprint(byte i)
{
  Serial.print(results[i]); // from names array
  Serial.print(" ");
  Serial.print(stat[(readData(chip1, i))]); //fram statusarray
}

/****************************************************************************
    This function takes over commands that were previously issued
    in every  switch function
 * **************************************************************************/
void handle_switches(byte channel, byte state)
{
  delay(30);
  tijd(); // print de tijd
  if (state == 1) //make sure only the ON time is stored
  {
    logSwitchOn(channel); //slaat die tijd op
  }
  updateData(chip1, channel, state); //updates de status in dechip
  arrayprint(channel); // prints de aan boodschap
  delay(30);
  Serial.print("");// om de buffer te pushen
}


/*
  on      6670849 / 0110010111001010000 00001
  light   6670852 / 0110010111001010000 00100
  bright+ 6670853 / 0110010111001010000 00101
  bright- 6670854 / 0110010111001010000 00110
  100%    6670855 / 0110010111001010000 00111
  50%     6670856 / 0110010111001010000 01000
  10%     6670857 / 0110010111001010000 01001
  mode+   6670859 / 0110010111001010000 01011
  mode- 6670865 / 0110010111001010000 10001
  speed-  6670861 / 0110010111001010000 01101
  speed+  6670863 / 0110010111001010000 01111
*/

/*
  0
  1-20- status

  101-164 tijd licht aan //basLightOn 2x31  baselight+1- +62
  LDR value 24   162-192 // baseldr=baselighton+32  24?  LDR+1-LDR+31
  ext temp/dag   24 values baseextemp=baseLDR+32   baseexttemp+1  baseexttemp+62
  int temp 24 valuesbaseinttemp=baseext+50   base-1-base+46
  lichtwaardes  24 baselight=baseInttemp +50  ??  338+0 338+23
  tijdschakelaar aan  48 bytes    baseswitch +1   -  basewitch+20+schakelaar

  dst kan naar boven
  vacation ook
  logData tijd licht aan+ donkerniveau

  baselightOn  =19
  1-> 1 2  --> 20 21
  2-> 3 4
  31->63 64 --> 82 83
  baseLDR  =83   =baseLightOn+64
  1->+1    84
  31->+31  114

  ext temp-baseExttemp  116  =LDR+33
  0-> -1 0     115 116
  1->  1 2
  23->45 46   161 162

  internal temp/day  baseIntTemp  164  =baseExttemp+48
  0-> -1  0   163 164
  1->  1  2
  2->  3  4
  23->45 46   209  210

  lichtwaardes loglicht  baselight   210  =internal+46
  1 -> +1    211
  23->+23    233


  baseswitchon  232  =baselight +22
  1->+1
  s->20+s

  const int baseLightOn = 100;    // 0x64
  //const int baseLDR = 200;      // 0xC8
  const int baseLDR = baseLightOn + 64;
  //const int baseExtTemp = 240;    // 0xF0
  const int baseExtTemp = baseLDR + 33;
  //Fconst int baseIntTemp = 290;   // 0x122
  const int baseIntTemp = baseExtTemp + 48;
  const int baseLight = baseIntTemp + 46
  const int baseSwitches = baselight+22;
*/

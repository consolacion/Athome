/*********************************************
 *          Macros                                                                              *
 *   Using macro's makes it easier to                               *
 *   redefine for other Rf Switches                                  *
 * *******************************************/
#define readDST readData(chip1,dst) // Macro for reading  Daylightsaving time status  '1' in zomer '0' in winter
#define writeDST writeData(chip1,dst,w)  // chip1 adres,EEPROMadres voor dst, waarde

#ifdef H
#define huiskamerAAN blokkerTransmitter.sendSignal(1, true)
#define huiskamerUIT blokkerTransmitter.sendSignal(1, false)
#define huiskamerStatus blokkerTransmitter.sendSignal(1,readData(chip1,1)) //1
#define studyAAN blokkerTransmitter.sendSignal(2, true)
#define studyUIT blokkerTransmitter.sendSignal(2, false)
#define studyStatus blokkerTransmitter.sendSignal(2, readData(chip1, 2)) //2

#define bedroomAAN blokkerTransmitter.sendSignal(3, true)
#define bedroomUIT blokkerTransmitter.sendSignal(3, false)
#define bedroomStatus blokkerTransmitter.sendSignal(3, readData(chip1, 3))

//----------------4. Radio Blokker1   dummy
//#define radioAAN blokkerTransmitter.sendSignal(4, true)
//#define radioUIT blokkerTransmitter.sendSignal(4, false)
#define radioAAN Irelais(1)
#define radioUIT Irelais(0)
//#define radioStatus blokkerTransmitter.sendSignal(4,readData(chip1,4)) //dummy
#define radioStatus  Irelais(readData(chip1,16))

//---------------5. reserved  TV beneden Blokker2 dummy
#define TVhAAN blokkerTransmitter.sendSignal(4, true)
#define TVhUIT blokkerTransmitter.sendSignal(4, false)
#define TVhStatus blokkerTransmitter.sendSignal(4,readData(chip1,5))//5

//---------------6. reserved Blokker3  dummy
#define Extra2AAN blokkerTransmitter.sendSignal(4, true)
#define Extra2UIT blokkerTransmitter.sendSignal(4, false)
#define Extra2Status blokkerTransmitter.sendSignal(4,readData(chip1,6))//6

#else

//-------------  1. Huiskamer AB440--vervangen door Eurodomest set 2 nr 1
#define huiskamer 1
#define huiskamerAAN enerswitch.sendSignal(euro2, 1, true)
#define huiskamerUIT enerswitch.sendSignal(euro2, 1, false)
#define huiskamerStatus enerswitch.sendSignal(euro2,1, readData(chip1,1))

//---------------2. Study AB440
#define study 2
#define studyAAN ab440Switch.sendSignal(29, 'B', true)
#define studyUIT ab440Switch.sendSignal(29, 'B', false)
#define studyStatus ab440Switch.sendSignal(29, 'B', readData(chip1, 2)) //2

//---------------3. Bedroom AB440
#define bedroom 3
#define bedroomAAN ab440Switch.sendSignal(29, 'C', true)
#define bedroomUIT ab440Switch.sendSignal(29, 'C', false)
#define bedroomStatus ab440Switch.sendSignal(29, 'C', readData(chip1, 3))


//----------------4. Radio Blokker1
#define radioAAN blokkerTransmitter.sendSignal(1, true)
#define radioUIT blokkerTransmitter.sendSignal(1, false)
#define radioStatus blokkerTransmitter.sendSignal(1,readData(chip1,4))

//---------------5. reserved  TV beneden Blokker2
#define TVhAAN blokkerTransmitter.sendSignal(2, true)
#define TVhUIT blokkerTransmitter.sendSignal(2, false)
#define TVhStatus blokkerTransmitter.sendSignal(2,readData(chip1,5))//5

//---------------6. reserved Blokker3
#define Extra2AAN blokkerTransmitter.sendSignal(3, true)
#define Extra2UIT blokkerTransmitter.sendSignal(3, false)
#define Extra2Status blokkerTransmitter.sendSignal(3,readData(chip1,6))//6

#endif
//---------------7. Bark AB440 (bruin)
#define barkAAN ab440Switch.sendSignal(31, 'A', true)
#define barkUIT ab440Switch.sendSignal(31, 'A', false)
#define barkStatus ab440Switch.sendSignal(31, 'A', readData(chip1,7))

//---------------8. Kinderkamer AB440 (bruin)
#define kinderkamerAAN  ab440Switch.sendSignal(31, 'D', true)
#define kinderkamerUIT  ab440Switch.sendSignal(31, 'D', false)
#define kinderkamerStatus ab440Switch.sendSignal(31, 'D', readData(chip1, 8))

//---------------9. Hydroponics EverFlourish1
#define hydroAAN everswitch.sendSignal('A', 1, true) //9
#define hydroUIT everswitch.sendSignal('A', 1, false)
#define hydroStatus everswitch.sendSignal('A', 1, readData(chip1,9))

//---------------10. Tuinlamp EverFlourish2
#define TuinLampAAN everswitch.sendSignal('A',2,true) //10
#define TuinLampUIT everswitch.sendSignal('A',2,false)
#define TuinLampStatus everswitch.sendSignal('A', 2, readData(chip1,10))

//---------------11. Vijverpomp EverFlourish3
#define vijverAAN everswitch.sendSignal('A',3,true)//11  EverFlourish3
#define vijverUIT everswitch.sendSignal('A',3,false)
#define vijverStatus everswitch.sendSignal('A', 3, readData(chip1,11))

//---------------12. TV aan Fake tv Eurodomest 1
#define tvAAN enerswitch.sendSignal(euro, 1, true)//12
#define tvUIT enerswitch.sendSignal(euro, 1, false)
#define tVStatus enerswitch.sendSignal(euro,1, readData(chip1,12))

//---------------13. Pop Eurodomest 2
#define popAAN  enerswitch.sendSignal(euro, 2, true)//13   Eurodomest2
#define popUIT  enerswitch.sendSignal(euro, 2, false)
#define popStatus enerswitch.sendSignal(euro,2, readData(chip1,13))

//---------------14. Spot Eurodomest 3
#define spotAAN enerswitch.sendSignal(euro, 3, true)//14
#define spotUIT enerswitch.sendSignal(euro, 3, false)
#define spotStatus enerswitch.sendSignal(euro,3, readData(chip1,14))

//---------------15. Relay Eurodomest 4
#define relaisAAN enerswitch.sendSignal(euro, 4, true) //15
#define relaisUIT enerswitch.sendSignal(euro, 4, false)
#define relaisStatus enerswitch.sendSignal(euro,4, readData(chip1,15))

//               16 internal relay
#define InternalRelayAAN  Irelais(1)
#define InternalRelayUIT  Irelais(0)
#define InternalRelayStatus readData(chip1,16)


//---------------17. Lamp Voortuin Eurodomest 2 1
//#define YardAAN enerswitch.sendSignal(euro2, 1, true) //17
#define YardAAN  ab440Switch.sendSignal(29, 'A', true)
//#define YardUIT enerswitch.sendSignal(euro2, 1, false)
#define YardUIT  ab440Switch.sendSignal(29, 'A', false)
//#define YardStatus enerswitch.sendSignal(euro2,1, readData(chip1,17))
#define YardStatus ab440Switch.sendSignal(29, 'A', 17)

//---------------18.
#define leeslampAAN   enerswitch.sendSignal(euro2, 2, true) //18   Eurodomest2
#define leeslampUIT   enerswitch.sendSignal(euro2, 2, false)
#define leeslampStatus enerswitch.sendSignal(euro2,2, readData(chip1,18))


//---------------19.
#define DekenAAN  enerswitch.sendSignal(euro2, 3, true) //19   Eurodomest2  Deken
#define DekenUIT  enerswitch.sendSignal(euro2, 3, false)
#define DekenStatus enerswitch.sendSignal(euro2,3, readData(chip1,19))

//---------------20. Dimmer
#define dimmer ledDimSwitch.sendSignal(dimaddress,dimCmd)

#define buzzerAAN digitalWrite(buzzPin,HIGH)
#define buzzerUIT digitalWrite(buzzPin,LOW)
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define Doorbell SelectPlus(0x1BB40)

#define THERMISTORNOMINAL 10000
#define TEMPERATURENOMINAL 25
#define BCOEFFICIENT 3950
#define SERIESRESISTOR 10000



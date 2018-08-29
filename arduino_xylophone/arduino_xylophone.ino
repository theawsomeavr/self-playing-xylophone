const int numpins=20;
#include <TimerFive.h>
#include <MIDI.h>
#include <Playtune.h>
MIDI_CREATE_DEFAULT_INSTANCE();
//23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53
int state[numpins];
 int pins[numpins]={53,51,49,47,45,43,41,39,37,35,33,31,29,27,25,23,28,26,24,22};
int notes[numpins]={53,55,57,58,59,60,62,64,65,66,67,69,70,71,72,74,76,77,79,81};
int notes2[numpins]={53,54,56,58,59,60,61,63,65,66,67,68,70,71,72,73,75,77,78,80};
Playtune pt;
void setup() {
   pt.tune_initchan (8);
  for(int a;a!=numpins;a++){
    pinMode(pins[a],1);
  }
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
    Timer5.initialize(500);
  Timer5.attachInterrupt(turnoff);
    MIDI.begin(MIDI_CHANNEL_OMNI); 
  //  Serial.begin(57600);
  // put your setup code here, to run once:

}
void turnoff(void)
{
  for(int a;a!=numpins;a++){
    if (state[a]>0&&state[a]<41) {

 state[a]++;// increase when LED turns on
  }
  if(state[a]>40) {
     digitalWrite(pins[a], 0);
     state[a]=0;
  }
  }
  }
bool chan2;
int b[128];
void startchan(int notaa){
 if(notaa<66){
if(chan2==0&&b[notaa]==0){        
pt.play_note(0,notaa);
b[notaa]=1;
chan2=1;
}}
}
int o=12;
void loop() {
  if(digitalRead(2)==0){o=o+12; delay(200);}
  if(digitalRead(3)==0){o=o-12; delay(200);}
    
  
  if (MIDI.read()&&MIDI.getChannel()!=10)                // Is there a MIDI message incoming ?
    { 
  
     if(MIDI.getType()==0x90){
      for(int a;a!=numpins;a++){ 
 if(MIDI.getData1()==notes[a]+o||MIDI.getData1()==notes2[a]+o){
    digitalWrite(pins[a],1);
     state[a]=1;

 } 
//    for(int a;a!=numpins;a++){

   // }
}
// if(MIDI.getType()<66){
        startchan(MIDI.getData1());
  //   }
    }
       if (MIDI.getType()==0x80)                // Is there a MIDI message incoming ?
    {
       // if(MIDI.getType()<66){
        if(chan2==1&&b[MIDI.getData1()]==1){ 
  
    pt.stop_note(0);  
    b[MIDI.getData1()]=0;
    chan2=0;
        }//}
      }
    }
  
    }

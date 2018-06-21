int data,beepflag=0;
float val=0,multiplier=100,prepos=0,speedmeasured=0;
double presenttime=0,previoustime=0,timetaken=-1;
void setup()
{  
 Serial.begin(9600);
 pinMode(8,OUTPUT);
}
void loop()
{  
  presenttime=millis();
   if(Serial.available())
   {
   data = Serial.read();
    if(data!=46&&data!=13)
    {
    val=val+ (data-48)*multiplier;
    multiplier/=10;
    }
    if( data == 13)
    {
     if(val== 2474)
     {
       Serial.println("NO OBSTACLE DETECTED");
       prepos=0;
       digitalWrite(8,LOW);
     }
     else
     {
       
       timetaken= (presenttime-previoustime)/1000;
       speedmeasured= (prepos-val)/timetaken;
       
        if(prepos!=0)
        { 
         Serial.print("Position");
         Serial.println(val);
         Serial.print("Speed:");
         Serial.println(speedmeasured); 
        }
       prepos=val;
       previoustime=presenttime;
       if(beepflag==1 && (speedmeasured<10 || val>=100))
        {
        digitalWrite(8,LOW);
        Serial.println("No beep");
        beepflag=0;
        delay(50);
        }
       if(speedmeasured>=30 && val<=100)
        {
        digitalWrite(8,HIGH);
        Serial.println("Beep");
        beepflag=1;
        delay(50);
        }
     }
    
    if(abs(speedmeasured)>200 && abs(speedmeasured)<1000)digitalWrite(2,HIGH);
    else digitalWrite(2,LOW);
    
    multiplier=100;
    val=0;
    }
   }
}


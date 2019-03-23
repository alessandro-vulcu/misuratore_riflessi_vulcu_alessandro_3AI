#include <LiquidCrystal.h>
int led = 13;
bool stato_pulsante;
int button = 8;
int buzzer = 10;
double tempo1;
double tempo2;
int t1,t2;
int cas1;
int cas2;
int i = 0;
double time1 = 0;
double time2 = 0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // put your setup code here, to run once:
  inizia_lcd();
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  pinMode(buzzer, OUTPUT);
}

void inizia_lcd(){
  lcd.begin(16,2);
  lcd.print("CLICK THE BUTTON");
  lcd.setCursor(0,1);
  lcd.print("TO START :)");
  loop();
}

void accensione_led(){  
    randomSeed(analogRead(0));
    cas1 = random(1000, 7000);
    delay(cas1);
    digitalWrite(led, HIGH);
    stato_pulsante = 0;
    tempo1 = millis(); //salva dentro una variabile il tempo trascorso dall'accensione dell'Arduino
    
  while(stato_pulsante == LOW){
    stato_pulsante = digitalRead(button);
    if(stato_pulsante == HIGH){
      tempo2 = millis();//salva dentro una seconda variabile il tempo trascorso dall'accensione dell'Arduino
      digitalWrite(led, LOW);
    }
    
    }
    
    time1 = tempo2 - tempo1;
    
    if(time1 > 250){
    lcd.setCursor(0,0);
    lcd.print("Too slow");
    delay(3000);
    lcd.clear();
    stato_pulsante = 0;
    setup();
    }
    else{
      lcd.setCursor(0,0);
      lcd.print(time1/1000);
      lcd.setCursor(4,0);
      lcd.print(" s");//la differenza tra questi due tempi dà il tempo impegato per cliccare il bottone all'accensione del led
      suono_buzzer();
    }
    
}

void suono_buzzer(){
  randomSeed(analogRead(0));
  cas2 = random(1000, 7000);
  delay(cas2);
  stato_pulsante = 0;
  tone(buzzer, 1000);
  tempo1 = millis();
  
  while(stato_pulsante == 0){
    
    stato_pulsante = digitalRead(button);
    if(stato_pulsante == HIGH){
      tempo2 = millis();
      noTone(buzzer);
    }
  }
   time2 = tempo2 - tempo1;
   
   if(time2 > 250){
    lcd.setCursor(0,1);
    lcd.print("Too slow");
    delay(3000);
    lcd.clear();
    stato_pulsante = 0;
    setup();
    
   }
   else{
   lcd.setCursor(0,1);
   lcd.print(time2/1000);
   lcd.setCursor(4,1);
   lcd.print(" s");//la differenza tra questi due tempi dà il tempo impegato per cliccare il bottone al suono del buzzer
   delay(1000);
   }
   
   
   stato_pulsante = 0;
   
   while(stato_pulsante == 0){
    
    stato_pulsante = digitalRead(button);
    if(stato_pulsante == 1){
      stato_pulsante = 0;
      delay(100);
      setup();
    }
   }
   
}
void start(){
  stato_pulsante = 0;
  while(stato_pulsante == 0){
    stato_pulsante = digitalRead(button);
    if(stato_pulsante == 1){
      lcd.clear();
      accensione_led();
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  start();
  setup();
    
  
}

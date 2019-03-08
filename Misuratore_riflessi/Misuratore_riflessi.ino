#include <LiquidCrystal.h>
int led = 13;
bool stato_pulsante;
int button = 8;
int buzzer = 10;
int tempo1;
int tempo2;
int cas1;
int cas2;

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
}

void accensione_led(){
  randomSeed(analogRead(0));
  cas1 = random(1000, 7000);
  delay(cas1);
  stato_pulsante = 0;
  digitalWrite(led, HIGH);
  tempo1 = millis(); //salva dentro una variabile il tempo trascorso dall'accensione dell'Arduino
  
  while(stato_pulsante == 0){
    
    stato_pulsante = digitalRead(button);
    if(stato_pulsante == HIGH){
      tempo2 = millis();//salva dentro una seconda variabile il tempo trascorso dall'accensione dell'Arduino
      digitalWrite(led, LOW);
      
    }
  }
  lcd.setCursor(0,0);
  lcd.print(tempo2 - tempo1);//la differenza tra questi due tempi dà il tempo impegato per cliccare il bottone all'accensione del led
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
  lcd.setCursor(0,1);
  lcd.print(tempo2 - tempo1);//la differenza tra questi due tempi dà il tempo impegato per cliccare il bottone al suono del buzzer
  delay(5000);

}


void loop() {
  // put your main code here, to run repeatedly:
  stato_pulsante = digitalRead(button);
  if(stato_pulsante == 1){
    lcd.clear();
    delay(5000);
  accensione_led();
  suono_buzzer();
  setup();
    
  }
}

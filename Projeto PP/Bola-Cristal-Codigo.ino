#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

#define pinSensor 8
#define pinRSeed A0
#define TX_PIN 4

SoftwareSerial bluetooth(-1, TX_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte leituraSensor = 0;
byte leituraSensorAnt = 0;

int resposta = 0;
unsigned long controleTempo = 0;

void setup() {
  bluetooth.begin(9600);
  lcd.init();
  lcd.backlight();

  lcd.print("Pergunte para   ");
  lcd.setCursor(0, 1);
  lcd.print(" Bola de Cristal");

  pinMode(pinSensor, INPUT_PULLUP);
  pinMode(pinRSeed, INPUT);
  randomSeed(analogRead(pinRSeed));

  bluetooth.println("Fim do Setup");
  bluetooth.println("Pergunte para Bola de Cristal");
}

void loop() {
  leituraSensor = digitalRead(pinSensor);

  if ( leituraSensor != leituraSensorAnt ) {
    if ( leituraSensor == LOW ) {
      lcd.clear();
      lcd.print("A Bola Diz:    ");
      bluetooth.println("A Bola Diz:");
      lcd.setCursor(0, 1);

      delay(500);
      
      resposta = random(8); // Gera uma resposta aleatória de 0 a 7
      controleTempo = millis();

      switch (resposta) {
        case 0: 
          lcd.print("Sim !");
          bluetooth.println("Sim !");
          break;
        
        case 1: 
          lcd.print("Provavelmente !");
          bluetooth.println("Provavelmente !");
          break;
        
        case 2: 
          lcd.print("Certeza !");
          bluetooth.println("Certeza !");
          break;
        
        case 3: 
          lcd.print("Parece bom !");
          bluetooth.println("Parece bom !");
          break;
        
        case 4: 
          lcd.print("Incerto !");
          bluetooth.println("Incerto !");
          break;
        
        case 5: 
          lcd.print("Pergunte de Novo");
          bluetooth.println("Pergunte de Novo");
          break;
        
        case 6: 
          lcd.print("Duvidoso !");
          bluetooth.println("Duvidoso !");
          break;
        
        case 7: 
          lcd.print("Nao !");
          bluetooth.println("Nao !");
          break;
      }
    }
  }

  leituraSensorAnt = leituraSensor;

  if (millis() - controleTempo > 5000) {
    lcd.clear();
    lcd.print("Pergunte para   ");
    lcd.setCursor(0, 1);
    lcd.print(" Bola de Cristal");
    bluetooth.println("Pergunte para Bola de Cristal");
    controleTempo = millis();
  }
}

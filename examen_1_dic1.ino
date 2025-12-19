#define BTN 2
#define BUZZER 6
#define LED_R 9
#define LED_G 10
#define LED_B 11
#define TEMP_PIN A0
#define LDR_PIN A1
#define DEBUG_TEMP
#define DEBUG_LUZ

int modo = 1;
int estadoBtn;
int estadoBtnAnt = HIGH;

int valorTemp;
float temperatura;

int valorLuz;
int luzMapeada;

void setup() {

  pinMode(BTN, INPUT_PULLUP);

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  estadoBtn = digitalRead(BTN);

  if (estadoBtn == LOW && estadoBtnAnt == HIGH) {
    modo++;
    if (modo > 3) {
      modo = 1;
    }
    delay(200);
  }

  estadoBtnAnt = estadoBtn;

  
  if (modo == 1) {

    valorTemp = analogRead(TEMP_PIN);
    temperatura = (valorTemp * 5.0 / 1023.0) * 100;

#ifdef DEBUG_TEMP
    Serial.print("Temperatura: ");
    Serial.println(temperatura);
#endif

    if (temperatura <= 0 || temperatura >= 100) {

      digitalWrite(LED_G, LOW);
      digitalWrite(LED_B, LOW);

      digitalWrite(LED_R, HIGH);
      digitalWrite(BUZZER, HIGH);
      delay(200);
      digitalWrite(LED_R, LOW);
      digitalWrite(BUZZER, LOW);
      delay(200);
    }

    else if (temperatura >= 60 && temperatura <= 80) {

      digitalWrite(LED_R, LOW);
      digitalWrite(LED_B, LOW);
      digitalWrite(LED_G, HIGH);
      digitalWrite(BUZZER, LOW);
    }

    else {

      digitalWrite(LED_R, HIGH);
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_B, LOW);
      digitalWrite(BUZZER, LOW);
    }
  }

 
  else if (modo == 2) {

    valorLuz = analogRead(LDR_PIN);
    luzMapeada = map(valorLuz, 0, 1023, 0, 100);

#ifdef DEBUG_LUZ
    Serial.print("Luz: ");
    Serial.println(luzMapeada);
#endif

    digitalWrite(LED_R, HIGH);

    if (luzMapeada > 50) {
      analogWrite(LED_B, map(luzMapeada, 50, 100, 0, 255));
      analogWrite(LED_G, 0);
    } 
    else {
      analogWrite(LED_G, map(luzMapeada, 0, 50, 255, 0));
      analogWrite(LED_B, 0);
    }

    digitalWrite(BUZZER, LOW);
  }

  
  else if (modo == 3) {

    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
    digitalWrite(BUZZER, LOW);

    valorLuz = analogRead(LDR_PIN);
    luzMapeada = map(valorLuz, 0, 1023, 0, 100);

    valorTemp = analogRead(TEMP_PIN);
    temperatura = (valorTemp * 5.0 / 1023.0) * 100;

    Serial.print("Luz (%): ");
    Serial.print(luzMapeada);
    Serial.print(" | Temp (C): ");
    Serial.println(temperatura);

    delay(500);
  }
}
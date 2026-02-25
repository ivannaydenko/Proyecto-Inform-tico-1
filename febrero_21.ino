#define TRIG 4
#define ECHO 3
#define PIR 2
#define BTN 6
#define BUZZ 5
#define R 9
#define G 11
#define B 10

int estadoSistema = 0;
int ultimoBtn = 0;
long duracion;
int distancia;
int movimiento;

void setup() {

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(PIR, INPUT);
  pinMode(BTN, INPUT_PULLUP);
  pinMode(BUZZ, OUTPUT);

  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  // BOTON
  int lecturaBtn = digitalRead(BTN);

  if (lecturaBtn == LOW && ultimoBtn == HIGH) {
    estadoSistema++;
    if (estadoSistema > 3) {
      estadoSistema = 0;
    }
    delay(250);
  }
  ultimoBtn = lecturaBtn;

  // MEDIR DISTANCIA
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duracion = pulseIn(ECHO, HIGH);
  distancia = duracion * 0.034 / 2;

  movimiento = digitalRead(PIR);

  
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  if (movimiento == HIGH)
    Serial.println("Movimiento");
  else
    Serial.println("Sin movimiento");

  if (estadoSistema == 0)
    Serial.println("Sistema DESACTIVADO");
  else
    Serial.println("Sistema ACTIVADO");

 

  // DESACTIVADO
  if (estadoSistema == 0) {

    analogWrite(R, 0);
    analogWrite(G, 0);
    analogWrite(B, 255);
    digitalWrite(BUZZ, LOW);

    if (movimiento == HIGH) {
      analogWrite(R, 255);
      analogWrite(G, 255);
      analogWrite(B, 0);
      Serial.println("Movimiento detectado con alarma desactivada");
    }
  }

  // MODO 1
  else if (estadoSistema >= 1 && distancia > 200) {

    analogWrite(R, 0);
    analogWrite(G, 255);
    analogWrite(B, 0);
    digitalWrite(BUZZ, LOW);
  }

  // MODO 2
  else if (estadoSistema >= 1 && distancia >= 80 && distancia <= 200) {

    analogWrite(R, 255);
    analogWrite(G, 120);
    analogWrite(B, 0);

    digitalWrite(BUZZ, HIGH);
    delay(200);
    digitalWrite(BUZZ, LOW);
    delay(200);

    Serial.println("Advertencia: objeto aproximandose");
  }

  // MODO 3
  else if (estadoSistema >= 1 && distancia < 80 && movimiento == HIGH) {

    analogWrite(R, 255);
    analogWrite(G, 0);
    analogWrite(B, 0);
    
    
    digitalWrite(BUZZ, HIGH);
    delay(35);
    digitalWrite(BUZZ, LOW);
    delay(35);

    Serial.println("ALARMA CRITICA");
  }

  delay(200);
}

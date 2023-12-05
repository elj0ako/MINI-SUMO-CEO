int pud = A3; // parlante derecha,trigger rigth
int puc = A4;
//int pui A7;
int mud = A2; // microfono derecha,echo right
int muc = A5; 
//int mui A6; 
//conexiones motor
int pwma = 0;
int ain1 = 3; //derecha
int ain2 = 2;
int pwmb = 1;
int bin1 = 6; //izquierda lado de gnd
int bin2 = 7;
//variables calculo ultrasonico
long dd,dc,di;//distancia derecha,central e izquierda respectivamente
long td,tc,ti;//tiempo derecha,central e izquierda
float vel = 0.017;
//CNY70
int lectura_linea_derecha2 = A0;//IO13
int lectura_linea_izquierda2 = A1;//IO27
int llii;
int lldd;

void setup() {
  Serial.begin(9600);
  delay(5000);
  pinMode(pud, OUTPUT);
  pinMode(puc, OUTPUT);
 // pinMode(pui, OUTPUT);
  pinMode(mud, INPUT);
  pinMode(muc, INPUT);
 // pinMode(mui, INPUT);
  pinMode(ain1, OUTPUT);
  pinMode(ain2, OUTPUT);
  pinMode(bin1, OUTPUT);
  pinMode(bin2, OUTPUT);
  pinMode(lectura_linea_derecha2, INPUT);
  pinMode(lectura_linea_izquierda2, INPUT);
}

void loop() {
      llii = digitalRead(lectura_linea_izquierda2); //Sensor de línea izquierdo
      lldd = digitalRead(lectura_linea_derecha2); //Sensor de línea derecho
      //--------------------------------------------------------------------------------------------------------------------------------------------------
      // estrategia basica
      ultrasonicos();
/*
      while(dc>5 && dd>5){
        // derecha(); delayMicroseconds(30);
      reversa();
      }
      if (dd<=5) 
      {        adelante();      }
      else if (dc<=5)//izquierda 
      {  //      izquierda();        delay(100);        adelante();      
      reversa();
      }
*/
      if(dc<=20)
      { adelante();   }
      else
      { vueltas(); 
      delayMicroseconds(10);}
      CNY70();
    
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
//deteccion ultrasonicos
void ultrasonicos() {
  //deteccion objetivo ultrasonico derecho
  digitalWrite(pud, HIGH);
  delayMicroseconds(10);
  digitalWrite(pud, LOW);
  td = pulseIn(mud, HIGH);
  dd = vel * td;
  Serial.println("distancia derecha=");
  Serial.println(dd);
  
  
  //deteccion objetivo ultrasonico central
  digitalWrite(puc, HIGH);
  delayMicroseconds(10);
  digitalWrite(puc, LOW);
  tc = pulseIn(muc, HIGH);
  dc = vel * tc;
  Serial.println("distancia izquierda=");
  Serial.println(dc)
  ;
//delay();probar cual valor utilizar
}
        //--------------------------------------------------------------------------------------------------------------------------------------------------
     //deteccion de lineas
void CNY70() {
      if (llii == 1) {//1== blanco,por lo que si nuestra superfice de pelea es negra usamos 1
        derecha();
        delayMicroseconds(10);
        adelante();
      }
      if (lldd == 1) {//0=negro,por lo que si actualemente queremos evitar que el robot salga del ring usamos esta configuracion de lldd==1
        izquierda();
        delayMicroseconds(10);
        adelante();
      }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
//movimientos

void vueltas(){
  derecha(); }

void adelante() {
  digitalWrite(ain1, HIGH);
  digitalWrite(ain2, LOW);
  digitalWrite(bin1, HIGH);
  digitalWrite(bin2, LOW);
}
//sobre su propio eje
void derecha() {
  digitalWrite(ain1, LOW);
  digitalWrite(ain2, HIGH);
  digitalWrite(bin1, HIGH);
  digitalWrite(bin2, LOW);
}
//sobre su propio eje
void izquierda() {
  digitalWrite(ain1, HIGH);
  digitalWrite(ain2, LOW);
  digitalWrite(bin1, LOW);
  digitalWrite(bin2, HIGH);
}
//marcha atras
void reversa() {
  digitalWrite(ain1, LOW);
  digitalWrite(ain2, HIGH);
  digitalWrite(bin1, LOW);
  digitalWrite(bin2, HIGH);
}

void detener() {
  digitalWrite(ain1, LOW);
  digitalWrite(ain2, LOW);
  digitalWrite(bin1, LOW);
  digitalWrite(bin2, LOW);
}

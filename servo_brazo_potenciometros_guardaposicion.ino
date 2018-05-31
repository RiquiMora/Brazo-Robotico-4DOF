#include <Servo.h>

Servo hombro, brazo, base, garra;

int potpi = 0;
int pot = 1;
int potp = 2;
int po = 3;


int val;    // variable to read the value from the analog pin
int val1;
int val2;
int val3;

const int max_root = 180;
char valores;
String codigo = "";

boolean mode = true;

void setup() {

  
 Serial.begin(9600);
 
 base.attach(11);
 brazo.attach(10);
 hombro.attach(9);
 garra.attach(8);
 
}

void loop() {
 val = analogRead(potpi);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  hombro.write(val);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there


    val1 = analogRead(pot);            // reads the value of the potentiometer (value between 0 and 1023)
  val1 = map(val1, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  brazo.write(val1);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there


    val2 = analogRead(potp);            // reads the value of the potentiometer (value between 0 and 1023)
  val2 = map(val2, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  base.write(val2);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there

    val3 = analogRead(po);            // reads the value of the potentiometer (value between 0 and 1023)
  val3 = map(val3, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  garra.write(val3);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there

  
  String metodo="",init = ""; boolean tipo = false;
  int posicion = 0;

  base.write(60);
  brazo.write(60);
  hombro.write(60);
  garra.write(60);
  
  if(Serial.available() > 0)
  {
    codigo = "";
    while(Serial.available() > 0)
    {  
      valores = Decimal_to_ASCII(Serial.read());
      Serial.print(valores);
      codigo = codigo + valores;          
    }
    delay(2000);
  }

  Serial.println(codigo);
  delay(2000);
  
  for( int i=0; i < codigo.length(); i++)
  {
      if(tipo == false)
      {
        if(codigo.charAt(i) == '(')
        {
           tipo = true;
           continue;
        }
        metodo = metodo + codigo.charAt(i);
      } else
      {
        init = init + codigo.charAt(i);
        if(codigo.charAt(i) == ')')
        {
          continue;
        }else if(codigo.charAt(i) == ';'){
          delay(2000);
          posicion = init.toInt();
          if(metodo == "brazo")
          {
            posicion < 180 ? brazo.write(posicion) : brazo.write(180);
            Serial.println("brazo");
            delay(2000);
          }else if(metodo == "base")
          {
            posicion < max_root ? base.write(posicion) : base.write(180);
            Serial.println("base");
            delay(2000);
          }else if(metodo == "hombro")
          {
            posicion < max_root ? hombro.write(posicion) : hombro.write(180);
            Serial.println("hombro");
            delay(2000);
          }else if(metodo == "garra")
          {
            posicion < max_root ? garra.write(posicion) : garra.write(180);
            Serial.println("garra");
            delay(2000);
          }

          metodo = "";
          tipo =  false;
          init = "";
        }
      }
  }
}

char Decimal_to_ASCII(int entrada){
  char salida=' ';
  switch(entrada){
  case 32: 
  salida=' '; 
  break; 
  case 33: 
  salida='!'; 
  break; 
  case 34: 
  salida='"'; 
  break; 
  case 35: 
  salida='#'; 
  break; 
  case 36: 
  salida='$'; 
  break; 
  case 37: 
  salida='%'; 
  break; 
  case 38: 
  salida='&'; 
  break; 
  case 39: 
  salida=' '; 
  break; 
  case 40: 
  salida='('; 
  break; 
  case 41: 
  salida=')'; 
  break; 
  case 42: 
  salida='*'; 
  break; 
  case 43: 
  salida='+'; 
  break; 
  case 44: 
  salida=','; 
  break; 
  case 45: 
  salida='-'; 
  break; 
  case 46: 
  salida='.'; 
  break; 
  case 47: 
  salida='/'; 
  break; 
  case 48: 
  salida='0'; 
  break; 
  case 49: 
  salida='1'; 
  break; 
  case 50: 
  salida='2'; 
  break; 
  case 51: 
  salida='3'; 
  break; 
  case 52: 
  salida='4'; 
  break; 
  case 53: 
  salida='5'; 
  break; 
  case 54: 
  salida='6'; 
  break; 
  case 55: 
  salida='7'; 
  break; 
  case 56: 
  salida='8'; 
  break; 
  case 57: 
  salida='9'; 
  break; 
  case 58: 
  salida=':'; 
  break; 
  case 59: 
  salida=';'; 
  break; 
  case 60: 
  salida='<'; 
  break; 
  case 61: 
  salida='='; 
  break; 
  case 62: 
  salida='>'; 
  break; 
  case 63: 
  salida='?'; 
  break; 
  case 64: 
  salida='@'; 
  break; 
  case 65: 
  salida='A'; 
  break; 
  case 66: 
  salida='B'; 
  break; 
  case 67: 
  salida='C'; 
  break; 
  case 68: 
  salida='D'; 
  break; 
  case 69: 
  salida='E'; 
  break; 
  case 70: 
  salida='F'; 
  break; 
  case 71: 
  salida='G'; 
  break; 
  case 72: 
  salida='H'; 
  break; 
  case 73: 
  salida='I'; 
  break; 
  case 74: 
  salida='J'; 
  break; 
  case 75: 
  salida='K'; 
  break; 
  case 76: 
  salida='L'; 
  break; 
  case 77: 
  salida='M'; 
  break; 
  case 78: 
  salida='N'; 
  break; 
  case 79: 
  salida='O'; 
  break; 
  case 80: 
  salida='P'; 
  break; 
  case 81: 
  salida='Q'; 
  break; 
  case 82: 
  salida='R'; 
  break; 
  case 83: 
  salida='S'; 
  break; 
  case 84: 
  salida='T'; 
  break; 
  case 85: 
  salida='U'; 
  break; 
  case 86: 
  salida='V'; 
  break; 
  case 87: 
  salida='W'; 
  break; 
  case 88: 
  salida='X'; 
  break; 
  case 89: 
  salida='Y'; 
  break; 
  case 90: 
  salida='Z'; 
  break; 
  case 91: 
  salida='['; 
  break; 
  case 92: 
  salida=' '; 
  break; 
  case 93: 
  salida=']'; 
  break; 
  case 94: 
  salida='^'; 
  break; 
  case 95: 
  salida='_'; 
  break; 
  case 96: 
  salida='`'; 
  break; 
  case 97: 
  salida='a'; 
  break; 
  case 98: 
  salida='b'; 
  break; 
  case 99: 
  salida='c'; 
  break; 
  case 100: 
  salida='d'; 
  break; 
  case 101: 
  salida='e'; 
  break; 
  case 102: 
  salida='f'; 
  break; 
  case 103: 
  salida='g'; 
  break; 
  case 104: 
  salida='h'; 
  break; 
  case 105: 
  salida='i'; 
  break; 
  case 106: 
  salida='j'; 
  break; 
  case 107: 
  salida='k'; 
  break; 
  case 108: 
  salida='l'; 
  break; 
  case 109: 
  salida='m'; 
  break; 
  case 110: 
  salida='n'; 
  break; 
  case 111: 
  salida='o'; 
  break; 
  case 112: 
  salida='p'; 
  break; 
  case 113: 
  salida='q'; 
  break; 
  case 114: 
  salida='r'; 
  break; 
  case 115: 
  salida='s'; 
  break; 
  case 116: 
  salida='t'; 
  break; 
  case 117: 
  salida='u'; 
  break; 
  case 118: 
  salida='v'; 
  break; 
  case 119: 
  salida='w'; 
  break; 
  case 120: 
  salida='x'; 
  break; 
  case 121: 
  salida='y'; 
  break; 
  case 122: 
  salida='z'; 
  break; 
  case 123: 
  salida='{'; 
  break; 
  case 124: 
  salida='|'; 
  break; 
  case 125: 
  salida='}'; 
  break; 
  case 126: 
  salida='~'; 
  break; 
  }
  return salida;
  } 


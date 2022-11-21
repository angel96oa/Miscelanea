#include <SigFox.h>

void setup() {
 Serial.begin(9600);
 SigFox.begin();
 SigFox.debug();

//El bucle iniciará mientras el coche esté funcionando

 float cocheArrancado = 1;

//Declaramos una variable que servirá para comprobar 
//en la estructura de control el nivel de humo, ya
//que en el sistema real este valor vendría dado por
//un detector de humo que actualiza la variable
//de forma constante.

//Dicho detector mide el porcentaje de humos, suponemos 
//que mas de un 40 tendremos problemas
float humos = 66.6;

while(cocheArrancado == 1){
  if(humos>=40){
    Serial.println("Se ha superado el nivel de humos permitido");
  } else {
    //No manda aviso ya que no se ha excedido el nivel de humos
    Serial.println("  ");
  }  
}


 SigFox.beginPacket();
 SigFox.write(humos);
 SigFox.endPacket(true);
}

void loop() {
  while (SigFox.available()) {
  Serial.print("0x");
  Serial.println(SigFox.read(), HEX);
}

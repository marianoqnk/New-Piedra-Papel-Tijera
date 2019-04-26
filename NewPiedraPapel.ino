#include "MTboard.h"
#define TIME_INTERMITENTE 500
#define INTENTOS 10
#define INTENTOS_GANAR 4
#define L_PIEDRA IZQUIERDA
#define L_PAPEL ARRIBA
#define L_TIJERA DERECHA
#define M_PIEDRA 0
#define M_PAPEL 1
#define M_TIJERA 2
int secuencia[INTENTOS];
enum Opciones {piedra, papel, tijera};
enum Resultados {gana, pierde, empata};

MTboard mtBoard;
byte jugadas = 0, ganadas = 0;

void setup() {
  mtBoard.ini();
  randomSeed(analogRead(4));
  mtBoard.textoScroll("Gana 4 veces de 10");
  mtBoard.apagaTodos();
}

void loop() {
  static byte k, jm;
  char txt[6];
  sprintf(txt, "%i/%i", ganadas, jugadas);
  mtBoard.textoScroll(txt);
  pptInicio();
  jm = jugadaMaquina(k, jm);
  k = mtBoard.esperaPulsador(5000);
  mtBoard.drawBitmap(jm + 3);
  mtBoard.fijaLed(k);
  delay(1000);
  byte cj = compruebaJugada(k, jm);
  mtBoard.enciendeTodos();
  if (cj == 0) {
    mtBoard.drawBitmap(ALEGRE);
    ganadas++;
  }
  else if (cj == 1)mtBoard.drawBitmap(TRISTE);
  else mtBoard.drawBitmap(NEUTRAL);
  if (ganadas > INTENTOS_GANAR)hasGanado();
  if (jugadas++ > INTENTOS)
  {
    ganadas = 0;
    jugadas = 0;
    mtBoard.textoScroll("Vuelve a empezar");
  }
  delay(2000);
}

void pptInicio()
{
  mtBoard.apagaTodos();
  mtBoard.drawBitmap(PIEDRA);
  mtBoard.enciendeLed(L_PIEDRA);
  delay(TIME_INTERMITENTE);
  mtBoard.drawBitmap(PAPEL);
  mtBoard.enciendeLed(L_PAPEL);
  delay(TIME_INTERMITENTE);
  mtBoard.drawBitmap(TIJERA);
  mtBoard.enciendeLed(L_TIJERA);
  delay(TIME_INTERMITENTE);
  mtBoard.borrar();
  delay(200);
  mtBoard.apagaTodos();
  delay(200);
}

Opciones jugadaMaquina(byte k, byte jm)
{
  if (jugadas == 0) return (papel); // el primero suele elegir piedra
  if (compruebaJugada(k, jm) == gana)return (k == piedra ? papel : (k == papel ? tijera : piedra)); //si pierde la maquina el no usadoK0JM2 jugada1// K1JM0 Jugada 2 // K2JM1 Jugada 0
  else if (compruebaJugada(k, jm) == 1)return k; //si gana la maquina la del otro jugador
  else return random(3); //empate aleatorio
}

Resultados compruebaJugada(byte k, byte jm)
{
  if ((k == L_PIEDRA && jm == M_TIJERA) || (k == L_PAPEL && jm == M_PIEDRA) || (k == L_TIJERA && jm == M_PAPEL)) return gana; //gana
  else if ((k == L_PIEDRA && jm == M_PAPEL) || (k == L_PAPEL && jm == M_TIJERA) || (k == L_TIJERA && jm == M_PIEDRA)) return pierde;//pierde
  else return empata;//empata
}

inline void hasGanado()  //Funcion cuando has ganado la  partida sonrie y saca coordenadas
{
  mtBoard.drawBitmap(ALEGRE);
  delay(3000);
  mtBoard.textoScroll("Enhorabuena las coordenadas son:");
  while (1)  mtBoard.coordenadasShow();
}

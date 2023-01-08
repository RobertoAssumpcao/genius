#include <Arduino.h>

#define led_vermelho 5
#define led_verde 4
#define led_amarelo 3
#define led_azul 2

int lista_led[] = {led_vermelho, led_verde, led_amarelo, led_azul};

// Inicia as portas dos Leds
void setup_led()
{
  for (int i = 0; i < sizeof(lista_led)/sizeof(int); i++)
  {
    pinMode(lista_led[i], OUTPUT);
  }
}

void pisca_led()
{
  for (int i = 0; i < sizeof(lista_led)/sizeof(int); i++)
  {
      digitalWrite(lista_led[i], 1);
      delay(1000);
      digitalWrite(lista_led[i], 0);
      delay(1000);
  }
}

void setup()
{
  setup_led();
}

void loop()
{
  pisca_led();
}
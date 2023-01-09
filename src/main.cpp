#include <Arduino.h>

// LED
#define led_vermelho 5
#define led_verde 4
#define led_amarelo 3
#define led_azul 2
int lista_led[] = {led_azul, led_amarelo, led_verde, led_vermelho};
// Botao
#define botao_vermelho 13
#define botao_verde 12
#define botao_amarelo 11
#define botao_azul 10
int lista_botao[] = {botao_azul, botao_amarelo, botao_verde, botao_vermelho};

// Inicia as portas dos Leds
void setup_led()
{
  for (int i = 0; i < sizeof(lista_led) / sizeof(int); i++)
  {
    pinMode(lista_led[i], OUTPUT);
  }
}

void pisca_led()
{
}

// Inicia as portas dos botoes
void setup_botao()
{
  for (int i = 0; i < sizeof(lista_botao) / sizeof(int); i++)
  {
    pinMode(lista_botao[i], INPUT_PULLUP);
  }
}

int status_botao()
{
  for (int i = 0; i < sizeof(lista_botao) / sizeof(int); i++)
  {
    if (digitalRead(lista_botao[i]) == 0)
    {
      return lista_led[i];
    }
  }
}

void setup()
{
  Serial.begin(9600);
  setup_led();
  Serial.println("Portas Leds configurada corretamente!");
  setup_botao();
  Serial.println("Portas botões configurado corretamente!");
}

void loop()
{
  pisca_led();
  int estado_botao = status_botao();
  for (int i = 0; i < 4; i++)
  {
    if (estado_botao == lista_led[i])
    {
      digitalWrite(lista_led[0], 1);
    }
    else
    {
      digitalWrite(lista_led[0], 0);
    }
  }

  Serial.println(estado_botao);
}
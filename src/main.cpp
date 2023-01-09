#include <Arduino.h>

// LED
// Azul, Amarelo, Verde, Vermelho.
const int lista_led[] = {2, 3, 4, 5};
// Botao
// Azul, Amarelo, Verde, Vermelho.
const int lista_botao[] = {10, 11, 12, 13};

// Inicia as portas dos Leds
void setup_led()
{
  for (int i = 0; i < sizeof(lista_led) / sizeof(int); i++)
  {
    pinMode(lista_led[i], OUTPUT);
  }
}

// Piscar led conforme o click do botão.
int pisca_led(int porta_led) // valor referente a posição no vetor.
{
  digitalWrite(lista_led[porta_led], 1);
  delay(1000);
  digitalWrite(lista_led[porta_led], 0);
  return porta_led;
}

// Inicia as portas dos botoes
void setup_botao()
{
  for (int i = 0; i < sizeof(lista_botao) / sizeof(int); i++)
  {
    pinMode(lista_botao[i], INPUT_PULLUP);
  }
}

// Verifica se o botão foi apertado ou se está em estado indefinido.
int status_botao()
{
  if (digitalRead(lista_botao[0]) == 0)
  {
    return pisca_led(0);
  }
  else if (digitalRead(lista_botao[1]) == 0)
  {
    return pisca_led(1);
  }
  else if (digitalRead(lista_botao[2]) == 0)
  {
    return pisca_led(2);
  }
  else if (digitalRead(lista_botao[3]) == 0)
  {
    return pisca_led(3);
  }
  else
  {
    return -1;
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
  int botao = status_botao();
}
#include <Arduino.h>

//Pontos / tamanho sequencia.
int pontos = 0;

// LED
// Azul, Amarelo, Verde, Vermelho.
const int lista_led[] = {2, 3, 4, 5};
// Botao
// Azul, Amarelo, Verde, Vermelho.
const int lista_botao[] = {10, 11, 12, 13};

// Inicia as portas dos Leds
void setup_led()
{
  for (unsigned int i = 0; i < sizeof(lista_led) / sizeof(int); i++)
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
  for (unsigned int i = 0; i < sizeof(lista_botao) / sizeof(int); i++)
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

// Pisca os leds de forma aleatoria criando a sequencia.
void leds_aleatorio(int tamanho_sequencia)
{
  int sequencia[tamanho_sequencia];
  for (unsigned int i = 0; i <= sizeof(sequencia) / sizeof(int); i++)
  {
    sequencia[i] = random(lista_led[0], lista_led[3] + 1);
    digitalWrite(sequencia[i], 1);
    delay(1000);
    digitalWrite(sequencia[i], 0);
  }
}

void setup()
{
  randomSeed(analogRead(0)); // Gerar leds aleatorio.
  setup_led();
  Serial.println("Portas Leds configurada corretamente!");
  setup_botao();
  Serial.println("Portas botoes configurado corretamente!");
}


void loop()
{
  leds_aleatorio(pontos);
  //int botao = status_botao();
  //Serial.write(botao);
}
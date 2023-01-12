#include <Arduino.h>

// estado do jogo
enum estados
{
  JOGADA,
  RESPOSTA_JOGADOR,
  GAME_OVER
};

// Estado atual do jogo.
int estado = JOGADA;
// Pontos do jogador.
double pontos = 0.0;

// Tamanho da sequencia de leds.
unsigned int tamanho_sequencia = 1;

// LED Azul, Amarelo, Verde, Vermelho.
const int lista_led[] = {2, 3, 4, 5};

// Botao Azul, Amarelo, Verde, Vermelho.
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
void pisca_led(int porta_led)
{
  digitalWrite(lista_led[porta_led], 1);
  delay(500);
  digitalWrite(lista_led[porta_led], 0);
}

// Inicia as portas dos botoes
void setup_botao()
{
  for (unsigned int i = 0; i < sizeof(lista_botao) / sizeof(int); i++)
  {
    pinMode(lista_botao[i], INPUT_PULLUP);
  }
}

int status_botao()
{
  if (digitalRead(lista_botao[0]) == 0)
  {
    pisca_led(0);
    return lista_led[0];
  }

  if (digitalRead(lista_botao[1]) == 0)
  {
    pisca_led(1);
    return lista_led[1];
  }

  if (digitalRead(lista_botao[2]) == 0)
  {
    pisca_led(2);
    return lista_led[2];
  }

  if (digitalRead(lista_botao[3]) == 0)
  {
    pisca_led(3);
    return lista_led[3];
  }

  return -1;
}

void jogada(unsigned int tamanho_sequencia)
{
  unsigned int sequencia_partida[tamanho_sequencia];

  switch (estado)
  {
  case JOGADA:

    // Gerando sequencia.
    for (unsigned int i = 0; i < sizeof(sequencia_partida) / sizeof(int); i++)
    {
      sequencia_partida[i] = random(lista_led[0], lista_led[3] + 1);
    }

    // Mostrando sequencia ao jogador.
    for (unsigned int i = 0; i < sizeof(sequencia_partida) / sizeof(int); i++)
    {
      digitalWrite(sequencia_partida[i], 1);
      delay(1000);
      digitalWrite(sequencia_partida[i], 0);
      delay(1000);
    }
    estado = RESPOSTA_JOGADOR;
    break;

  case RESPOSTA_JOGADOR:
    status_botao();
    break;

  case GAME_OVER:
    digitalWrite(lista_led[3], 1);
    break;

  default:
    break;
  }
}

void setup()
{
  randomSeed(analogRead(0)); // Gerar leds aleatorio.
  setup_led();
  Serial.println("Portas Leds configurada!");
  setup_botao();
  Serial.println("Portas botoes configurado!");
}

void loop()
{
  jogada(tamanho_sequencia);
}
#include <Arduino.h>

// estado do jogo
enum estados
{
  JOGAR,
  RESPOSTA_JOGADOR
};

// Estado atual do jogo.
int estado = JOGAR;

// Tamanho da sequencia de leds.
int tamanho_sequencia = 1;

int qtd_leds_respondidos = 0;
int tempo_led = 1000;

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

// Inicia as portas dos botoes
void setup_botao()
{
  for (unsigned int i = 0; i < sizeof(lista_botao) / sizeof(int); i++)
  {
    pinMode(lista_botao[i], INPUT_PULLUP);
  }
}

// Piscar led conforme o click do botãoe retorna o led.
int status_botao()
{
  if (digitalRead(lista_botao[0]) == 0)
  {
    digitalWrite(lista_led[0], 1);
    delay(500);
    digitalWrite(lista_led[0], 0);
    delay(500);

    return lista_led[0];
  }

  if (digitalRead(lista_botao[1]) == 0)
  {
    digitalWrite(lista_led[1], 1);
    delay(500);
    digitalWrite(lista_led[1], 0);
    delay(500);

    return lista_led[0];
  }

  if (digitalRead(lista_botao[2]) == 0)
  {
    digitalWrite(lista_led[2], 1);
    delay(500);
    digitalWrite(lista_led[2], 0);
    delay(500);

    return lista_led[0];
  }

  if (digitalRead(lista_botao[3]) == 0)
  {
    digitalWrite(lista_led[3], 1);
    delay(500);
    digitalWrite(lista_led[3], 0);
    delay(400);

    return lista_led[0];
  }

  return -1;
}

void jogada(unsigned int tamanho_s)
{
  int sequencia_partida[tamanho_s];
  int sequencia_jogador[tamanho_s];

  // Altera dificuldade.
  if (tamanho_sequencia % 5 == 0)
  {
    tamanho_sequencia += 2;
  }
  if (tamanho_sequencia % 10 == 0)
  {
    tempo_led -= 50;
  }

  switch (estado)
  {
  case JOGAR:

    // Gerando sequencia.
    for (unsigned int i = 0; i < sizeof(sequencia_partida) / sizeof(int); i++)
    {
      sequencia_partida[i] = random(lista_led[0], lista_led[3] + 1);
    }

    // Mostrando sequencia ao jogador.
    for (unsigned int i = 0; i < sizeof(sequencia_partida) / sizeof(int); i++)
    {
      digitalWrite(sequencia_partida[i], 1);
      delay(tempo_led);
      digitalWrite(sequencia_partida[i], 0);
      delay(1000);
    }
    estado = RESPOSTA_JOGADOR;

    break;

  case RESPOSTA_JOGADOR:
    // Pegando resposta jogador.
    int resposta = status_botao();

    delay(100); // dar tempo de processar o input

    // Aguardando resposta do jogador.
    if (resposta == -1)
    {
      return;
    }
    else
    {
      sequencia_jogador[qtd_leds_respondidos] = resposta;
    }

    // Verificando repostasta jogador.
    if (sequencia_jogador[qtd_leds_respondidos] == sequencia_partida[qtd_leds_respondidos])
    {
      // Verde mostra acerto.
      digitalWrite(lista_led[2], 1);
      delay(2000);
      digitalWrite(lista_led[2], 0);
      delay(3000);
      qtd_leds_respondidos++;
      tamanho_sequencia++;
      estado = JOGAR;
    }
    else
    {
      tamanho_sequencia = 1;
      tempo_led = 1000;
      qtd_leds_respondidos = 0;
      // Vermelho mostra que errou.
      digitalWrite(lista_led[3], 1);
      delay(2000);
      digitalWrite(lista_led[3], 0);
      delay(3000);
      estado = JOGAR;
    }

    break;
  }
}

void setup()
{
  randomSeed(analogRead(0)); // Gerar leds aleatorio.
  setup_led();
  setup_botao();
}

void loop()
{
  jogada(tamanho_sequencia);
}
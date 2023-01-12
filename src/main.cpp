#include <Arduino.h>

// estado do jogo
enum estado
{
  PROXIMA_JOGADA,
  AGUARDANDO_RESPOSTA,
};

// Tamanho da sequencia de leds.
unsigned int tamanho_sequencia = 1;

// LED Azul, Amarelo, Verde, Vermelho.
const int lista_led[] = {2, 3, 4, 5};

// Botao Azul, Amarelo, Verde, Vermelho.
const int lista_botao[] = {10, 11, 12, 13};

// Altera estado do jogo se necessario e retorna o estado atual.
int estado_jogo()
{
  int estado = AGUARDANDO_RESPOSTA;
  return estado;
}

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

  switch (estado_jogo())
  {
  case PROXIMA_JOGADA:
    // Gerando sequencia.
    for (unsigned int i = 0; i <= sizeof(sequencia_partida) / sizeof(int); i++)
    {
      sequencia_partida[i] = random(lista_led[0], lista_led[3] + 1);
    }

    // Mostrando sequencia ao jogador.
    for (unsigned int i = 0; i <= sizeof(sequencia_partida) / sizeof(int); i++)
    {
      digitalWrite(sequencia_partida[i], 1);
      delay(1000);
      digitalWrite(sequencia_partida[i], 0);
    }
    break;

  case AGUARDANDO_RESPOSTA:
    status_botao();
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
  status_botao();
}
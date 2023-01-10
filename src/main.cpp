#include <Arduino.h>

// Tamanho sequencia.
unsigned int tamanho_sequencia = 0;

// Estado do jogo.
int estado_jogo = 1;

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
void pisca_led(int porta_led) // valor referente a posição no vetor.
{
  digitalWrite(lista_led[porta_led], 1);
  delay(1000);
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

void jogada(int tamanho_sequencia)
{
  int sequencia_partida[tamanho_sequencia];
  int sequencia_jogador[tamanho_sequencia];

  switch (estado_jogo)
  {
  case 1:
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
    estado_jogo++;
    break;

  // Verificando escolha jogador.
  case 2:
    // Verifica se o botão foi apertado ou se está em estado indefinido.
    for (unsigned int i = 0; i <= sizeof(sequencia_jogador) / sizeof(int); i++)
    {
      // Verificando led escolhido pelo jogador e salvando na sequencia do jogador.
      int botao_apertado = digitalRead(lista_botao[i]);
      if (botao_apertado == 0)
      {
        sequencia_jogador[i] = botao_apertado;
        pisca_led(i);
      }
      estado_jogo++;
    }
    break;
  case 3:
    for (unsigned int i = 0; i <= sizeof(sequencia_jogador) / sizeof(int); i++)
    {
      // Verificando se a sequencia do jogador é igual a sequencia da partida.
      if (sequencia_partida[i] == sequencia_jogador[i])
      {
        pisca_led(2); // Piscando led verde mostrando que o jogador acertou.
        tamanho_sequencia++;
        estado_jogo = 1;
      }
      else
      {
        pisca_led(3); // Piscando led vermelho mostrando que o jogador errou.
        tamanho_sequencia = 0;
        estado_jogo = 1;
      }
    }
    break;
  default:
    break;
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
  jogada(tamanho_sequencia);
}
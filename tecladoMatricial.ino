#include <Password.h> // Biblioteca utilizada para controle de senha
#include <Keypad.h> // Biblioteca para controle do teclado de matrizes

const byte LINHAS = 4; // Linhas do teclado
const byte COLUNAS = 4; // Colunas do teclado
const int pinoRele = 10;
const int pinoLedVermelho = 11;

Password senha = Password( "1967" ); // Senha utilizada para liberacao

const char TECLAS_MATRIZ[LINHAS][COLUNAS] = { // Matriz de caracteres (mapeamento do teclado)
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

const byte PINOS_LINHAS[LINHAS] = {9, 8, 7, 6}; // Pinos de conexao com as linhas do teclado
const byte PINOS_COLUNAS[COLUNAS] = {5, 4, 3, 2}; // Pinos de conexao com as colunas do teclado

Keypad teclado_personalizado = Keypad(makeKeymap(TECLAS_MATRIZ), PINOS_LINHAS, PINOS_COLUNAS, LINHAS, COLUNAS); // Inicia teclado

void setup() {
  
  Serial.begin(9600); // Inicializa serial monitor


  pinMode(pinoLedVermelho, OUTPUT);
  pinMode(pinoRele, OUTPUT);

  digitalWrite(pinoLedVermelho, LOW);
  digitalWrite(pinoRele, LOW);
}

void loop() {
    
  char leitura_teclas = teclado_personalizado.getKey(); // Atribui a variavel a leitura do teclado
  
  if(leitura_teclas){ // Se alguma tecla foi pressionada

    if(leitura_teclas == 'C'){ // Se a tecla 'C' foi pressionada
      
      if(senha.evaluate()){ // Verifica se a senha digitada esta correta
        
        Serial.println("Senha confirmada!"); // Exibe a mensagem que a senha esta correta
        digitalWrite(pinoRele, HIGH);
        delay(2000);
        digitalWrite(pinoRele, LOW);

      } else { // Caso a senha esteja incorreta
        
        Serial.println("Senha incorreta!"); // Exibe a mensagem que a senha esta errada
        for(int i = 0; i < 5; i++){ // Pisca o LED 5 vezes rapidamente
          digitalWrite(pinoLedVermelho, HIGH);
          delay(50);
          digitalWrite(pinoLedVermelho, LOW);
          delay(50);
          
        }
      }
      
      senha.reset(); // Limpa a variavel senha
      
    } else { // Caso outra tecla tenha sido pressionada
      
      Serial.println(leitura_teclas); // Exibe a tecla pressionada
      senha.append(leitura_teclas); // Salva o valor da tecla pressionada na variavel senha
      
    }
  }

}
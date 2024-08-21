# Mini-Casa-Automatizada
# Mini Casa Automatizada com ESP8266

Este repositório contém o código e as instruções para a construção de uma maquete de uma mini casa automatizada usando o ESP8266. A iluminação dos cômodos pode ser controlada individualmente ou em conjunto via comandos de voz utilizando a assistente virtual Siri.

## 📷 Fotos da Maquete

<img src="CASA.jpeg" alt="Visão Geral da Maquete" width="300"/>
![Circuito e Componentes](Circuito.jpeg)
*Circuito com ESP8266, LEDs e resistores*

## 🛠 Materiais Utilizados

- **ESP8266**
- **LEDs** (para cada cômodo: sala, cozinha, quarto)
- **Resistores** (compatíveis com os LEDs)
- **Fios** para conexão
- **Papelão** para a estrutura da maquete
- **Cola quente** para montagem
- **Decorações variadas** (papel colorido, mini móveis, etc.)

## 📝 Passo a Passo de Construção

### 1. **Construção da Estrutura**
   - A maquete foi construída usando papelão para criar as paredes e divisões dos cômodos.
   - Utilizamos cola quente para fixar as paredes e dar estrutura à casa.
   - A decoração foi feita com papel na cor branca e pequenos itens decorativos parecidos com a grama.

### 2. **Montagem do Circuito**
   - Conecte os LEDs e os resistores aos pinos do ESP8266 conforme o código:
     - **Sala:** GPIO5 (D1)
     - **Cozinha:** GPIO4 (D2)
     - **Quarto:** GPIO2 (D4)
   - Faça as conexões com os fios, garantindo que cada LED tenha um resistor para evitar sobrecarga.

### 3. **Configuração do Software**
   - O código do ESP8266 foi escrito em C++ usando o Arduino IDE.
   - O ESP8266 cria um servidor web que permite o controle das luzes via HTTP.
   - Os comandos podem ser enviados pela Siri, configurada para enviar requisições HTTP ao ESP8266.

## 🔧 Código

O código completo para o ESP8266 está disponível no arquivo [automacao.ino](caminho/para/arquivo.ino).

### **Resumo do Código**
- Configura os pinos dos LEDs como saídas.
- Estabelece uma conexão Wi-Fi usando o WiFiManager.
- Cria um servidor web que processa os comandos para ligar e desligar os LEDs.

## 🚀 Como Usar

1. Carregue o código no seu ESP8266 usando o Arduino IDE.
2. Conecte o ESP8266 à sua rede Wi-Fi.
3. Use a Siri ou um navegador para enviar comandos HTTP e controlar as luzes da mini casa.

## 📄 Licença

Este projeto está licenciado sob os termos da [MIT License](LICENSE).

## 👥 Autores

- **[Seu Nome]**
- **[Nome dos Colaboradores]**



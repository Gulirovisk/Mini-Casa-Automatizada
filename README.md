# Mini-Casa-Automatizada
# Mini Casa Automatizada com ESP8266

Este repositório contém o código e as instruções para a construção de uma maquete de uma mini casa automatizada usando o ESP8266. A iluminação dos cômodos pode ser controlada individualmente ou em conjunto via comandos de voz utilizando a assistente virtual Siri.

## 📷 Fotos da Maquete
*Figura 1: Visão Geral da Mini Casa*

<img src="CASA.jpeg" alt="Visão Geral da Maquete" width="300"/>

*Figura 2: Circuito com ESP8266, LEDs e resistores*

<img src="Circuito.jpeg" alt="Circuito e Componentes" width="300"/>

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

O código completo para o ESP8266 está disponível no arquivo [automacao.ino](Mini-Casa-Automatizada.ino).

### **Resumo do Código**
- Configura os pinos dos LEDs como saídas.
- Estabelece uma conexão Wi-Fi usando o WiFiManager.
- Cria um servidor web que processa os comandos para ligar e desligar os LEDs.

## 🚀 Como Usar

Carregue o Código no ESP8266:

Utilize a Arduino IDE para carregar o código fornecido no ESP8266. Certifique-se de que todas as bibliotecas necessárias estão instaladas e que a placa ESP8266 está selecionada corretamente nas configurações da IDE.
Conecte o ESP8266 à Rede Wi-Fi:

Após carregar o código, o ESP8266 criará uma rede Wi-Fi temporária com o nome "ESP=AUTO" e senha "40028922" (ou conforme configurado no código).
Conecte-se a essa rede Wi-Fi usando seu dispositivo móvel ou computador.
Configuração da Rede Wi-Fi Local:

Uma vez conectado à rede criada pelo ESP8266, você será redirecionado para uma página de configuração onde poderá selecionar a rede Wi-Fi de sua casa ou local de uso.
Após selecionar a rede e inserir a senha, o ESP8266 se conectará automaticamente a essa rede no futuro.
Acesso ao Dispositivo via IP Fixo:

O código já está configurado para atribuir um IP fixo ao ESP8266, 192.168.1.184. Este IP será usado para acessar o dispositivo via navegador ou assistente virtual.
Certifique-se de que o IP 192.168.1.184 não está sendo usado por outro dispositivo na rede para evitar conflitos.
Configuração do Assistente Virtual:

No assistente virtual Siri (ou outro assistente que você deseja utilizar), configure os comandos de voz para enviar requisições HTTP ao IP do ESP8266.
Por exemplo, para ligar a luz da sala, o comando pode enviar uma requisição para http://192.168.1.184/liga_sala. Configure esses comandos conforme sua preferência.
Personalização do Código:

O código é flexível e pode ser adaptado conforme suas necessidades. Você pode alterar os pinos utilizados, adicionar mais LEDs, ou até mesmo integrar outros sensores e atuadores.
Modifique os caminhos dos comandos e a interface web conforme necessário para criar uma experiência de automação personalizada.
Testando e Utilizando:

Após a configuração, você poderá controlar as luzes da mini casa usando seu assistente virtual ou qualquer navegador acessando http://192.168.1.184.
Teste todos os comandos para garantir que estão funcionando conforme esperado e faça ajustes no código, se necessário.
Considerações Finais:

Este projeto pode ser facilmente expandido para controlar outros dispositivos ou sensores. Sinta-se à vontade para explorar e personalizar o código para atender melhor às suas necessidades.
Se houver dúvidas ou problemas, consulte a seção de troubleshooting ou abra um issue neste repositório.

## 📄 Licença

Este projeto está licenciado sob os termos da [MIT License](LICENSE).

## 👥 Autores

- **[Seu Nome]**
- **[Nome dos Colaboradores]**



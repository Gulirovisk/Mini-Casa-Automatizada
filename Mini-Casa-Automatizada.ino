#include <ESP8266WiFi.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

#define LED_SALA_PIN 5     // Definindo o pino do LED da sala como GPIO5
#define LED_COZINHA_PIN 4  // Definindo o pino do LED da cozinha como GPIO4
#define LED_QUARTO_PIN 2   // Definindo o pino do LED do quarto como GPIO2

WiFiServer server(80);

void setup() {
    Serial.begin(115200);
    
    // Define os pinos dos LEDs como saída
    pinMode(LED_SALA_PIN, OUTPUT);
    pinMode(LED_COZINHA_PIN, OUTPUT);
    pinMode(LED_QUARTO_PIN, OUTPUT);
    
    // Os LEDs começarão desligados (LOW) automaticamente
    
    // Definindo um IP fixo para o ESP8266
    IPAddress staticIP(192, 168, 1, 184); // Defina o IP desejado
    IPAddress gateway(192, 168, 1, 1);    // Defina o gateway padrão
    IPAddress subnet(255, 255, 255, 0);   // Defina a máscara de sub-rede
    WiFi.config(staticIP, gateway, subnet); // Aplica as configurações de IP

    // Inicializa o WiFiManager
    WiFiManager wm;
    
    // Tenta conectar automaticamente com as credenciais salvas
    // Se falhar, cria um AP com o nome e senha especificados
    bool res;
    res = wm.autoConnect("ESP=AUTO", "40028922"); // Substitua pelos valores desejados

    if (!res) {
        Serial.println("Falha ao conectar");
        // ESP.restart();  // Reinicia o ESP em caso de falha, se desejado
    } else {
        Serial.println("Conectado ao WiFi");
        Serial.println("Endereço IP: ");
        Serial.println(WiFi.localIP());  // Exibe o IP local atribuído pelo roteador
    }

    server.begin();
}

void loop() {
    // Verifica se ainda está conectado ao WiFi
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Conexão WiFi perdida. Tentando reconectar...");
        // Tenta reconectar ao WiFi
        WiFi.reconnect();
        delay(5000); // Aguarda 5 segundos antes de verificar novamente
        return;
    }

    WiFiClient client = server.available();  // Aguardando por clientes

    if (client) {                     // Se um cliente se conectar
        Serial.println("Novo Cliente.");  // Mensagem no monitor serial
        String currentLine = "";        // String para armazenar dados do cliente
        while (client.connected()) {    // Loop enquanto o cliente estiver conectado
            if (client.available()) {     // Se houver dados do cliente
                char c = client.read();     // Lê um byte
                Serial.write(c);            // Escreve no monitor serial
                if (c == '\n') {            // Se o byte for um caractere de nova linha

                    // Se a linha atual estiver em branco, a solicitação HTTP foi recebida
                    if (currentLine.length() == 0) {
                        // Envia a resposta HTTP
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();

                        client.println("<center>");
                        client.println("<br>");
                        client.println("<a href=\"/liga_sala\"><button>Liga LED Sala</button></a>");
                        client.println("<br>");
                        client.println("<a href=\"/desliga_sala\"><button>Desliga LED Sala</button></a>");
                        client.println("<br>");
                        client.println("<a href=\"/liga_cozinha\"><button>Liga LED Cozinha</button></a>");
                        client.println("<br>");
                        client.println("<a href=\"/desliga_cozinha\"><button>Desliga LED Cozinha</button></a>");
                        client.println("<br>");
                        client.println("<a href=\"/liga_quarto\"><button>Liga LED Quarto</button></a>");
                        client.println("<br>");
                        client.println("<a href=\"/desliga_quarto\"><button>Desliga LED Quarto</button></a>");
                        client.println("<br>");
                        client.println("<a href=\"/liga_tudo\"><button>Liga Todos os LEDs</button></a>");
                        client.println("<br>");
                        client.println("<a href=\"/desliga_tudo\"><button>Desliga Todos os LEDs</button></a>");
                        client.println("<br>");
                        client.println("</center>");

                        // A resposta HTTP termina com uma linha em branco
                        client.println();
                        break;
                    } else {
                        currentLine = "";  // Limpa a linha atual
                    }
                } else if (c != '\r') {  // Se for um caractere diferente de carriage return
                    currentLine += c;      // Adiciona ao final da linha atual
                }

                // Verifica os comandos GET para ligar/desligar os LEDs

                if (currentLine.endsWith("GET /liga_sala")) {
                    digitalWrite(LED_SALA_PIN, HIGH);  // Liga o LED da sala
                }
                if (currentLine.endsWith("GET /desliga_sala")) {
                    digitalWrite(LED_SALA_PIN, LOW);  // Desliga o LED da sala
                }

                if (currentLine.endsWith("GET /liga_cozinha")) {
                    digitalWrite(LED_COZINHA_PIN, HIGH);  // Liga o LED da cozinha
                }
                if (currentLine.endsWith("GET /desliga_cozinha")) {
                    digitalWrite(LED_COZINHA_PIN, LOW);  // Desliga o LED da cozinha
                }

                if (currentLine.endsWith("GET /liga_quarto")) {
                    digitalWrite(LED_QUARTO_PIN, HIGH);  // Liga o LED do quarto
                }
                if (currentLine.endsWith("GET /desliga_quarto")) {
                    digitalWrite(LED_QUARTO_PIN, LOW);  // Desliga o LED do quarto
                }

                // Comandos para ligar/desligar todos os LEDs
                if (currentLine.endsWith("GET /liga_tudo")) {
                    digitalWrite(LED_SALA_PIN, HIGH);     // Liga o LED da sala
                    digitalWrite(LED_COZINHA_PIN, HIGH);  // Liga o LED da cozinha
                    digitalWrite(LED_QUARTO_PIN, HIGH);   // Liga o LED do quarto
                }
                if (currentLine.endsWith("GET /desliga_tudo")) {
                    digitalWrite(LED_SALA_PIN, LOW);     // Desliga o LED da sala
                    digitalWrite(LED_COZINHA_PIN, LOW);  // Desliga o LED da cozinha
                    digitalWrite(LED_QUARTO_PIN, LOW);   // Desliga o LED do quarto
                }
            }
        }
        // Fecha a conexão
        client.stop();
        Serial.println("Cliente desconectado.");
    }
    delay(10);
}

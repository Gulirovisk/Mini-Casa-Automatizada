#include <ESP8266WiFi.h>
#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager

#define LED_SALA_PIN 5
#define LED_COZINHA_PIN 4
#define LED_QUARTO_PIN 2

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  pinMode(LED_SALA_PIN, OUTPUT);
  pinMode(LED_COZINHA_PIN, OUTPUT);
  pinMode(LED_QUARTO_PIN, OUTPUT);

  IPAddress staticIP(192, 168, 1, 184);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.config(staticIP, gateway, subnet);

  WiFiManager wm;
  bool res = wm.autoConnect("ESP=AUTO", "40028922");

  if (!res) {
    Serial.println("Falha ao conectar");
  } else {
    Serial.println("Conectado ao WiFi");
    Serial.println("Endereço IP: ");
    Serial.println(WiFi.localIP());
  }

  server.begin();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Conexão WiFi perdida. Tentando reconectar...");
    WiFi.reconnect();
    delay(5000);
    return;
  }

  WiFiClient client = server.available();

  if (client) {
    Serial.println("Novo Cliente.");
    String currentLine = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        if (c == '\n') {
          if (currentLine.length() == 0) {
            // Envia a página HTML
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            client.println("<center>");
            client.println("<h2>Controle de LEDs</h2><br>");
            client.println("<a href=\"/liga_sala\"><button>Liga LED Sala</button></a><br>");
            client.println("<a href=\"/desliga_sala\"><button>Desliga LED Sala</button></a><br>");
            client.println("<a href=\"/liga_cozinha\"><button>Liga LED Cozinha</button></a><br>");
            client.println("<a href=\"/desliga_cozinha\"><button>Desliga LED Cozinha</button></a><br>");
            client.println("<a href=\"/liga_quarto\"><button>Liga LED Quarto</button></a><br>");
            client.println("<a href=\"/desliga_quarto\"><button>Desliga LED Quarto</button></a><br>");
            client.println("<a href=\"/liga_tudo\"><button>Liga Todos os LEDs</button></a><br>");
            client.println("<a href=\"/desliga_tudo\"><button>Desliga Todos os LEDs</button></a><br>");
            client.println("<hr>");
            client.println("<a href=\"/configurar_wifi\"><button style='background-color:red;color:white;'>Reconfigurar Wi-Fi</button></a>");
            client.println("</center>");

            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        // Comandos para LEDs
        if (currentLine.endsWith("GET /liga_sala")) digitalWrite(LED_SALA_PIN, HIGH);
        if (currentLine.endsWith("GET /desliga_sala")) digitalWrite(LED_SALA_PIN, LOW);

        if (currentLine.endsWith("GET /liga_cozinha")) digitalWrite(LED_COZINHA_PIN, HIGH);
        if (currentLine.endsWith("GET /desliga_cozinha")) digitalWrite(LED_COZINHA_PIN, LOW);

        if (currentLine.endsWith("GET /liga_quarto")) digitalWrite(LED_QUARTO_PIN, HIGH);
        if (currentLine.endsWith("GET /desliga_quarto")) digitalWrite(LED_QUARTO_PIN, LOW);

        if (currentLine.endsWith("GET /liga_tudo")) {
          digitalWrite(LED_SALA_PIN, HIGH);
          digitalWrite(LED_COZINHA_PIN, HIGH);
          digitalWrite(LED_QUARTO_PIN, HIGH);
        }

        if (currentLine.endsWith("GET /desliga_tudo")) {
          digitalWrite(LED_SALA_PIN, LOW);
          digitalWrite(LED_COZINHA_PIN, LOW);
          digitalWrite(LED_QUARTO_PIN, LOW);
        }

        // Comando para apagar Wi-Fi salvo e reiniciar
        if (currentLine.endsWith("GET /configurar_wifi")) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();
          client.println("<html><body><h2>Redefinindo Wi-Fi... Reiniciando.</h2></body></html>");
          client.println();
          delay(2000);

          WiFiManager wm;
          wm.resetSettings();  // ⚠️ Apaga as redes salvas
          delay(1000);

          ESP.restart();  // Reinicia para abrir o portal
        }
      }
    }

    client.stop();
    Serial.println("Cliente desconectado.");
  }

  delay(10);
}

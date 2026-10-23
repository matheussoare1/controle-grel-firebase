#ifndef CONFIG_BLYNK_H
#define CONFIG_BLYNK_H

#include <Arduino.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include "config.h"
#include "ArControle.h"

// ponteiro global para que a macro do Blynk consiga aceder ao ArControle
inline ArControle* arRefBlynk = nullptr;

// essa função é acionada automaticamente sempre que o botão no Blynk (Pino V0) é pressionado
BLYNK_WRITE(V0) {
    int comando = param.asInt();
    
    if (arRefBlynk != nullptr) {
        arRefBlynk->processarComando(comando);
    }
}

class configBlynk {
public:
    void begin(ArControle& arControle) {
        arRefBlynk = &arControle;

        // o blynk que faz a organização WiFi automaticamente

        Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD);
        
        // conectado
    }

    void run() {
        Blynk.run();
    }
};

#endif
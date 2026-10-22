#ifndef CONFIG_FIREBASE_H
#define CONFIG_FIREBASE_H

#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "config.h"
#include "ArControle.h"

class configFirebase{
private:
    inline static FirebaseData stream;
    inline static FirebaseData fbdo;
    inline static FirebaseAuth auth;
    inline static FirebaseConfig config;
    inline static ArControle* arRef = nullptr;

    static void streamCallback(FirebaseStream data){
        if (data.dataType() == "string") {
            String comando = data.stringData();
            
            // comando vai para o ar condicionado
            if (arRef != nullptr) {
                arRef->processarComando(comando);
            }

            // reseta o firebase para "IDLE" para evitar repetições
            Firebase.RTDB.setString(&fbdo, "/comando", "IDLE");
        }
    }

    static void streamTimeoutCallback(bool timeout){
        if (timeout) {
            // vai tentar reconectar
        }
    }

public:
    void begin(ArControle& arControle){
        arRef = &arControle;

        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        Serial.print("Conectando ao Wi-Fi");
        while (WiFi.status() != WL_CONNECTED){
            delay(500);
            Serial.print(".");
        }
        Serial.println(" Conectado!");

        config.api_key = API_KEY;
        config.database_url = FIREBASE_HOST;
        auth.user.email = USER_EMAIL;
        auth.user.password = USER_PASSWORD;

        Firebase.begin(&config, &auth);
        Firebase.reconnectWiFi(true);

        while (auth.token.uid.length() == 0){
            delay(300);
        }

        if (!Firebase.RTDB.beginStream(&stream, "/comando")){
            Serial.printf("Erro no Stream: %s\n", stream.errorReason().c_str());
        }

        Firebase.RTDB.setStreamCallback(&stream, streamCallback, streamTimeoutCallback);
        // ativo!!
    }
};

#endif
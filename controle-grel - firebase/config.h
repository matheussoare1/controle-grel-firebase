#ifndef CONFIG_H
#define CONFIG_H

// wifi
#define WIFI_SSID "NOME_DA_REDE"
#define WIFI_PASSWORD "SENHA_DO_WIFI"

// firebase
#define FIREBASE_HOST "ENDEREÇO_DO_SERVIDOR"
#define API_KEY "CHAVE_DO_SERVIDOR"
#define USER_EMAIL "EMAIL_DO_USUARIO"
#define USER_PASSWORD "SENHA_DO_USUARIO"

// pino led
const int LED_PIN = 13;

// pino botão
const int LIGAR_PIN = 12;
const int DESLIGAR_PIN = 14;

// lembrar de colocar os botões em pull-down

#endif
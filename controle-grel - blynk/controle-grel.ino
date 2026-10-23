#include <Arduino.h>
#include "config.h"
#include "ArControle.h"
#include "configBlynk.h"

// objetvos das classes
ArControle ac(LED_PIN);
configBlynk blynk;

void setup() {
    Serial.begin(115200);

    pinMode(LIGAR_PIN, INPUT);
    pinMode(DESLIGAR_PIN, INPUT);

    ac.begin();

    blynk.begin(ac);
}

void loop() {

    blynk.run(); 

    if(digitalRead(LIGAR_PIN) == 1){
        ac.processarComando(1);
        delay(500);
    }

    if(digitalRead(DESLIGAR_PIN) == 1){
        ac.processarComando(2);
        delay(500);
    }
}
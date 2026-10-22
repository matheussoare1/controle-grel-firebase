#include <Arduino.h>
#include "config.h"
#include "ArControle.h"
#include "configFirebase.h"

// objetvos das classes
ArControle ac(LED_PIN);
configFirebase firebase;

void setup() {
    Serial.begin(115200);

    pinMode(LIGAR_PIN, INPUT);
    pinMode(DESLIGAR_PIN, INPUT);

    ac.begin();

    firebase.begin(ac);
}

void loop() {

    if(digitalRead(LIGAR_PIN) == 1){
        ac.processarComando("MIDEA_ON");
        delay(500);
    }

    if(digitalRead(DESLIGAR_PIN) == 1){
        ac.processarComando("MIDEA_OFF");
        delay(500);
    }
}
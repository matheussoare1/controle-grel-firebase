#ifndef ARCONTROLE_H
#define ARCONTROLE_H

#include <Arduino.h>
#include <IRsend.h>

class ArControle{
private:
    IRsend irsend;

    // protocolo Midea
    const uint64_t MIDEA_LIGAR_22 = 0xB1B5C000004AULL;
    const uint64_t MIDEA_DESLIGAR = 0xB1B57B0000E0ULL;

    // protocolo coolix/springer

    const uint32_t COOLIX_LIGAR_22 = 0xB27BE0;
    const uint32_t COOLIX_DESLIGAR = 0xB27BE0;

    // função que envia os dois sinais

    void enviarUniversal(uint64_t codigoMidea, uint32_t codigoCoolix){
        irsend.sendMidea(codigoMidea);
        delay(500); // tempo de espera para o outro envio
        irsend.sendCoolix(codigoCoolix);
    }

public:
    
    ArControle(int pin) : irsend(pin) {}

    void begin() {
        irsend.begin();
    }

    void processarComando(String comando){
        comando.toUpperCase();
        if (comando == "IDLE" || comando == "") return;

        if (comando == "MIDEA_ON"){
            enviarUniversal(MIDEA_LIGAR_22, COOLIX_LIGAR_22);
            // ligado em 22
        }
        else if (comando == "MIDEA_OFF"){
            enviarUniversal(MIDEA_DESLIGAR, COOLIX_DESLIGAR);
            // desligado
        }
        else {
            // faz nada
        }
    }
};

#endif
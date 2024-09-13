#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <unistd.h>

#define MCP9808_ADDR 0x18
#define MCP9808_REG_TEMP 0x05

int main() {
    int fd;

    // Initialiser I2C
    fd = wiringPiI2CSetup(MCP9808_ADDR);
    if (fd == -1) {
        std::cerr << "Erreur lors de l'initialisation I2C" << std::endl;
        return 1;
    }

    while (true) {
        // Lire la température
        int rawTemp = wiringPiI2CReadReg16(fd, MCP9808_REG_TEMP);
        
        // Convertir la valeur brute en température Celsius
        rawTemp = ((rawTemp & 0x0FFF) / 16.0);
        if (rawTemp & 0x1000) {
            rawTemp -= 256;
        }

        // Afficher la température
        std::cout << "Température : " << rawTemp << " °C" << std::endl;

        // Attendre 1 seconde
        sleep(1);
    }

    return 0;
}
/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"


const int pino_doLedd = 11;
const int pino_do_botaoo = 15;

const int pinos_do_motor[4] = {19, 18, 17, 16};
const int matriz_do_motor[8][4] = {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}
};

void motor_360() {
    for (int i = 0; i < 512; i++) {
        for (int passo = 0; passo < 8; passo++) {
            for (int pino = 0; pino < 4; pino++) {
                gpio_put(pinos_do_motor[pino], matriz_do_motor[passo][pino]);
            }
            sleep_ms(2); 
        }
    }
    
    for (int pin = 0; pin < 4; pin++) gpio_put(pinos_do_motor[pin], 0);
}

int main() {
    stdio_init_all();
    
    sleep_ms(2000);
    
    gpio_init(pino_doLedd);
    gpio_set_dir(pino_doLedd, GPIO_OUT);
    
    gpio_init(pino_do_botaoo);
    gpio_set_dir(pino_do_botaoo, GPIO_IN);
    gpio_pull_up(pino_do_botaoo);
    

    for (int i = 0; i < 4; i++) {
        gpio_init(pinos_do_motor[i]);
        gpio_set_dir(pinos_do_motor[i], GPIO_OUT);
    }

    while (true) {
        if (!gpio_get(pino_do_botaoo)) {
            gpio_put(pino_doLedd, 1);
            motor_360();
            sleep_ms(500);
            gpio_put(pino_doLedd, 0);
        }
        sleep_ms(10);
    }
}
/* 
 * File:   main.h
 * Author: rnd
 *
 * Created on 2024? 9? 18? (?), ?? 12:26
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

#define NUM_LEDS 36
#define COLOR_COUNT 4  
    
typedef struct {
    uint8_t g;
    uint8_t r;
    uint8_t b;
    uint8_t w;
} led_t;

typedef enum {
    INVALID = 0, STANDBY, REACTIVE
} MODES_T;

led_t red = {.r = 100, .g = 0, .b = 0, .w = 0};
led_t green = {.r = 0, .g = 100, .b = 0, .w = 0};
led_t yellow = {.r = 100, .g = 100, .b = 0, .w = 0};
led_t off = {.r = 0, .g = 0, .b = 0, .w = 0};

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */


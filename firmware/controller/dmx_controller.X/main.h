/* 
 * File:   main.h
 * Author: rnd
 *
 * Created on 2024? 9? 18? (?), ?? 12:40
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define NODES 10
#define COLOR_COUNT 4    

#define MAX_SB_VAL 255

typedef struct {
    uint8_t g;
    uint8_t r;
    uint8_t b;
    uint8_t w;
} led_t;

led_t red = {0, 100, 0, 0};
led_t yellow = {100, 100, 0, 0};
led_t green = {100, 0, 0, 0};

typedef enum {INVALID, STANDBY, REACTIVE} MODES_T;

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */


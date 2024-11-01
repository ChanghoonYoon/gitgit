/* 
 * File:   dmx.h
 * Author: rnd
 *
 * Created on September 17, 2024, 10:03 PM
 */

#ifndef DMX_H
#define	DMX_H

#ifdef	__cplusplus
extern "C" {
#endif

void DMX_Initialize(void);
void DMX_sync(void);
void DMX_send_byte(uint8_t data);
void DMX_send_bytes(uint8_t *data, uint8_t len);
void DMX_transsmision(uint8_t start_code, uint8_t *data, uint8_t data_len);


#ifdef	__cplusplus
}
#endif

#endif	/* DMX_H */


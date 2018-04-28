#ifndef USER_API_H
#define USER_API_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "NLMEDE.h"
#include "ZDApp.h"
#include "hal_led.h"
#include "string.h"
#include "user_printf.h"

void user_state_change( afIncomingMSGPacket_t *pkt );
void user_show_info(void);

#ifdef __cplusplus
}
#endif
#endif /* USER_API_H */

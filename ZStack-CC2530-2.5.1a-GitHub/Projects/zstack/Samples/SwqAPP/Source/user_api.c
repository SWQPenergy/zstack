#include "user_api.h"

const uint8* devStates_str[11]=
{
  "HOLD",               // Initialized - not started automatically
  "INIT",               // Initialized - not connected to anything
  "NWK_DISC",           // Discovering PAN's to join
  "NWK_JOINING",        // Joining a PAN
  "NWK_REJOIN",         // ReJoining a PAN", only for end devices
  "END_DEVICE_UNAUTH",  // Joined but not yet authenticated by trust center
  "END_DEVICE",         // Started as device after authentication
  "ROUTER",             // Device joined", authenticated and is a router
  "COORD_STARTING",     // Started as Zigbee Coordinator
  "ZB_COORD",           // Started as Zigbee Coordinator
  "NWK_ORPHAN"          // Device has lost information about its parent..
};
void user_state_change( afIncomingMSGPacket_t *pkt )
{
  printf("Dev_State:%s\r\n",devStates_str[pkt->hdr.status]);

  if     ((devStates_t)(pkt->hdr.status) == DEV_ZB_COORD)  { printf("Coordinator!\r\n"); }
  else if((devStates_t)(pkt->hdr.status) == DEV_ROUTER)    { printf("Router!\r\n");      }
  else if((devStates_t)(pkt->hdr.status) == DEV_END_DEVICE){ printf("EndDevice!\r\n");   }

  if(((devStates_t)(pkt->hdr.status) == DEV_ZB_COORD)
   ||((devStates_t)(pkt->hdr.status) == DEV_ROUTER)
   ||((devStates_t)(pkt->hdr.status) == DEV_END_DEVICE))
  {
    user_show_info();

    HalLedSet (HAL_LED_ALL, HAL_LED_MODE_OFF);
    HalLedBlink ( HAL_LED_ALL, 3, 50, (1000 / 4) );
  }
}
void user_show_info(void)
{
  uint8 *MacAddr  = 0;

  printf("NwkPANID:%04X\r\n",_NIB.nwkPanId);

  NLME_GetCoordExtAddr(MacAddr);
  printf("Fath_Nwk:%04X  ",NLME_GetCoordShortAddr());
  printf("Fath_Mac:%04X%04X%04X%04X\r\n",*((uint16*)(&MacAddr[6])),*((uint16*)(&MacAddr[4])),*((uint16*)(&MacAddr[2])),*((uint16*)(&MacAddr[0])));

  MacAddr = NLME_GetExtAddr();
  printf("Self_Nwk:%04X  ",NLME_GetShortAddr());
  printf("Self_Mac:%04X%04X%04X%04X\r\n",*((uint16*)(&MacAddr[6])),*((uint16*)(&MacAddr[4])),*((uint16*)(&MacAddr[2])),*((uint16*)(&MacAddr[0])));
}

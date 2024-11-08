#include "app.h"
#include "bsp_hcsr04.h"
#include "bsp_relay.h"

typedef struct {
	PresenceSensor_Status presence;
} APP_DATA_Struct;

static APP_DATA_Struct app_data;
void app(){
	app_data.presence = BSP_HCSR04_GetPresence(PRESENCE_CUTOFF);
	if(app_data.presence == Presence){
		BSP_RELAY_ON();
	}
	else{
		BSP_RELAY_OFF();
	}
}

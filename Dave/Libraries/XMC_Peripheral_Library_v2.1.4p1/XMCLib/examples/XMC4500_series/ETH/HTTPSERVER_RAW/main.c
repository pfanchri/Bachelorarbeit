/*
 * main.c
 *
 *  Created on: 2015 Jul 22 14:00:44
 *  Author: ferreije
 */

#include "xmc_gpio.h"
#include "lwip/timers.h"
#include "lwip/netif.h"
#include "lwip/init.h"
#include "netif/etharp.h"
#include "ethernetif.h"
#include "httpserver_raw/httpd.h"

#define LED1 P1_1

/*Static IP ADDRESS*/
#define IP_ADDR0   192
#define IP_ADDR1   168
#define IP_ADDR2   0
#define IP_ADDR3   10

/*NETMASK*/
#define NETMASK_ADDR0   255
#define NETMASK_ADDR1   255
#define NETMASK_ADDR2   255
#define NETMASK_ADDR3   0

/*Gateway Address*/
#define GW_ADDR0   192
#define GW_ADDR1   168
#define GW_ADDR2   0
#define GW_ADDR3   1

struct netif xnetif;

void LWIP_Init(void)
{
  struct ip_addr ipaddr;
  struct ip_addr netmask;
  struct ip_addr gw;

  IP4_ADDR(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
  IP4_ADDR(&netmask, NETMASK_ADDR0, NETMASK_ADDR1 , NETMASK_ADDR2, NETMASK_ADDR3);
  IP4_ADDR(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);

  lwip_init();

  /* - netif_add(struct netif *netif, struct ip_addr *ipaddr,
  struct ip_addr *netmask, struct ip_addr *gw,
  void *state, err_t (* init)(struct netif *netif),
  err_t (* input)(struct pbuf *p, struct netif *netif))

  Adds your network interface to the netif_list. Allocate a struct
  netif and pass a pointer to this structure as the first argument.
  Give pointers to cleared ip_addr structures when using DHCP,
  or fill them with sane numbers otherwise. The state pointer may be NULL.

  The init function pointer must point to a initialization function for
  your ethernet netif interface. The following code illustrates it's use.*/
  netif_add(&xnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &ethernet_input);

  /*  Registers the default network interface.*/
  netif_set_default(&xnetif);

  /* Set Ethernet link flag */
  xnetif.flags |= NETIF_FLAG_LINK_UP;

  /* When the netif is fully configured this function must be called.*/
  netif_set_up(&xnetif);

}

tCGI led_handler_struct;

/* Initialisation of functions to be used with CGi*/
//  CGI handler to switch LED status
const char *led_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) {

  XMC_GPIO_ToggleOutput(LED1);
  return "/index.htm";
}

int led_cgi_init(void)
{
  led_handler_struct.pcCGIName = "/led.html";
  led_handler_struct.pfnCGIHandler = led_handler;
  http_set_cgi_handlers(&led_handler_struct, 1);
  return 0;
}


int main(void)
{
  XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);

  SysTick_Config(SystemCoreClock / 1000);

  LWIP_Init();
  httpd_init();
  led_cgi_init();

  while(1)
  {
    sys_check_timeouts();
  }
}

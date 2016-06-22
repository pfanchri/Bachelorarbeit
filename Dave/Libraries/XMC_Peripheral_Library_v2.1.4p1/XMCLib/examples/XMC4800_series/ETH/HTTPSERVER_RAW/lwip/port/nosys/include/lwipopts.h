#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#ifdef __cplusplus
extern "C" {
#endif

#define NO_SYS                  1
#define LWIP_SOCKET             0
#define LWIP_NETCONN            0

#define MEM_ALIGNMENT           4

#define MEM_SIZE                16 * 1024

#define PBUF_POOL_SIZE          16
#define PBUF_POOL_BUFSIZE       1500

#define LWIP_UDP                1
#define LWIP_TCP                1

#define LWIP_STATS 0

#define CHECKSUM_GEN_IP         0
#define CHECKSUM_GEN_UDP        0
#define CHECKSUM_GEN_TCP        0
#define CHECKSUM_GEN_ICMP       0
#define CHECKSUM_CHECK_IP       0
#define CHECKSUM_CHECK_UDP      0
#define CHECKSUM_CHECK_TCP      0


#ifdef __cplusplus
}
#endif
#endif /* __LWIPOPTS_H__ */


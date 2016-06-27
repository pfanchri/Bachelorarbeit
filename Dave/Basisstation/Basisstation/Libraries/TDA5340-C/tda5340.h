/*
 * TDA5340.c
 *
 *  Created on: 28.01.2015
 *      Author: pflaum
 *      adapt by Pfannenmüller
 */

#define TDA5340_PON_PORT     XMC_GPIO_PORT0
#define TDA5340_PON_PIN      2
#define TDA5340_PP2_PORT     XMC_GPIO_PORT0
#define TDA5340_PP2_PIN      3

#define RX_MODE              RUN_MODE_SLAVE

#define RSSI_SLOPE_VALUE     0xA0
#define RSSI_OFFSET_VALUE    0x00

typedef union {
	uint32_t value;
	uint8_t  bytes[4];
} tda5340_serial_t;

void tda5340_init(uint8_t device_number);
void tda5340_gpio_init(uint8_t device_number);
uint8_t tda5340_transfer(uint8_t device_number, const uint8_t instruction, const uint8_t reg_address, uint8_t data);
uint8_t tda5340_command(uint8_t device_number, const uint8_t instruction, const uint8_t reg_address, uint8_t data);
uint8_t tda5340_fifo_rw(uint8_t device_number, uint8_t wnr, int8_t *data, uint8_t *length);
uint8_t tda5340_transmit(uint8_t device_number, uint8_t config, int8_t *data, uint8_t length);
uint8_t tda5340_receive(uint8_t device_number, int8_t *data, uint8_t *length);
void tda5340_set_mode_and_config(uint8_t device_number, uint8_t mode, uint8_t config);
uint32_t tda5340_interrupt_readout(uint8_t device_number);
uint32_t tda5340_get_serial_number(uint8_t device_number);

#define WRITE_TO_CHIP        0x02
#define READ_FROM_CHIP       0x03
#define WRITE_TO_FIFO        0x06
#define READ_FROM_FIFO       0x04

#define SLEEP_MODE           0x00
#define SELF_POLLING_MODE    0x01
#define RUN_MODE_SLAVE       0x02
#define TRANSMIT_MODE        0x03
#define DEEP_SLEEP_MODE      0x04

#define A_MID0               0x00
#define A_MID1               0x01
#define A_MID2               0x02
#define A_MID3               0x03
#define A_MID4               0x04
#define A_MID5               0x05
#define A_MID6               0x06
#define A_MID7               0x07
#define A_MID8               0x08
#define A_MID9               0x09
#define A_MID10              0x0A
#define A_MID11              0x0B
#define A_MID12              0x0C
#define A_MID13              0x0D
#define A_MID14              0x0E
#define A_MID15              0x0F
#define A_MID16              0x10
#define A_MID17              0x11
#define A_MID18              0x12
#define A_MID19              0x13
#define A_MIDC0              0x14
#define A_MIDC1              0x15
#define A_IF1                0x16
#define A_WUC                0x17
#define A_WUPAT0             0x18
#define A_WUPAT1             0x19
#define A_WUBCNT             0x1A
#define A_WURSSITH1          0x1B
#define A_WURSSIBL1          0x1C
#define A_WURSSIBH1          0x1D
#define A_WURSSITH2          0x1E
#define A_WURSSIBL2          0x1F
#define A_WURSSIBH2          0x20
#define A_WURSSITH3          0x21
#define A_WURSSIBL3          0x22
#define A_WURSSIBH3          0x23
#define A_WURSSITH4          0x24
#define A_WURSSIBL4          0x25
#define A_WURSSIBH4          0x26
#define A_SRTHR              0x27
#define A_SIGDETSAT          0x28
#define A_WULOT              0x29
#define A_SYSRCTO            0x2A
#define A_TOTIM0             0x2B
#define A_TOTIM1             0x2C
#define A_TOTIM_SYNC         0x2D
#define A_TOTIM_TSI          0x2E
#define A_TOTIM_EOM          0x2F
#define A_AFCLIMIT           0x30
#define A_AFCAGCADRD         0x31
#define A_AFCSFCFG           0x32
#define A_AFCKCFG0           0x33
#define A_AFCKCFG1           0x34
#define A_PMFUDSF            0x35
#define A_AGCSFCFG           0x36
#define A_AGCCFG0            0x37
#define A_AGCCFG1            0x38
#define A_AGCTHR             0x39
#define A_DIGRXC             0x3A
#define A_PKBITPOS           0x3B
#define A_PDFMFC             0x3C
#define A_PDECF              0x3D
#define A_PDECSCFSK          0x3E
#define A_PDECSCASK          0x3F
#define A_SRC                0x40
#define A_EXTSLC0            0x41
#define A_EXTSLC1            0x42
#define A_EXTSLC2            0x43
#define A_EXTSLTHR0          0x44
#define A_EXTSLTHR1          0x45
#define A_SIGDET0            0x46
#define A_SIGDET1            0x47
#define A_SIGDETLO           0x48
#define A_SIGDETSEL          0x49
#define A_SIGDETCFG          0x4A
#define A_NDTHRES            0x4B
#define A_NDCONFIG           0x4C
#define A_CDRP               0x4D
#define A_CDRI               0x4E
#define A_CDRCFG0            0x4F
#define A_CDRCFG1            0x50
#define A_TVWIN              0x51
#define A_SLCCFG             0x52
#define A_TSIMODE            0x53
#define A_TSILENA            0x54
#define A_TSILENB            0x55
#define A_TSIGAP             0x56
#define A_TSIPTA0            0x57
#define A_TSIPTA1            0x58
#define A_TSIPTB0            0x59
#define A_TSIPTB1            0x5A
#define A_EOMC               0x5B
#define A_EOMDLEN            0x5C
#define A_EOMDLENP           0x5D
#define A_CHCFG              0x5E
#define A_TXRF               0x5F
#define A_TXCFG              0x60
#define A_TXCHOFFS0          0x61
#define A_TXCHOFFS1          0x62
#define A_TXBDRDIV0          0x63
#define A_TXBDRDIV1          0x64
#define A_TXDSHCFG0          0x65
#define A_TXDSHCFG1          0x66
#define A_TXDSHCFG2          0x67
#define A_TXPOWER0           0x68
#define A_TXPOWER1           0x69
#define A_TXFDEV             0x6A
#define A_PLLINTC1           0x6B
#define A_PLLFRAC0C1         0x6C
#define A_PLLFRAC1C1         0x6D
#define A_PLLFRAC2C1         0x6E
#define A_PLLINTC2           0x6F
#define A_PLLFRAC0C2         0x70
#define A_PLLFRAC1C2         0x71
#define A_PLLFRAC2C2         0x72
#define A_PLLINTC3           0x73
#define A_PLLFRAC0C3         0x74
#define A_PLLFRAC1C3         0x75
#define A_PLLFRAC2C3         0x76
#define A_PLLINTC4           0x77
#define A_PLLFRAC0C4         0x78
#define A_PLLFRAC1C4         0x79
#define A_PLLFRAC2C4         0x7A
#define A_RXPLLBW            0x7B
#define A_TXPLLBW            0x7C
#define A_PLLTST             0x7D
#define A_ANTSW              0x7E
#define A_ADRSFCFG           0x7F
#define A_ADRTCFG0           0x80
#define A_ADRTCFG1           0x81
#define A_ADRTCFG2           0x82
#define A_ADRTHR0            0x83
#define A_ADRTHR1            0x84
#define SFRPAGE              0xA0
#define PPCFG0               0xA1
#define PPCFG1               0xA2
#define PPCFG2               0xA3
#define PPCFG3               0xA4
#define RXRUNCFG0            0xA5
#define RXRUNCFG1            0xA6
#define CLKOUT0              0xA7
#define CLKOUT1              0xA8
#define CLKOUT2              0xA9
#define ANTSW                0xAA
#define RFC                  0xAB
#define BPFCALCFG0           0xAC
#define BPFCALCFG1           0xAD
#define XTALCAL0             0xAE
#define XTALCAL1             0xAF
#define RSSICFG              0xB0
#define ADCINSEL             0xB1
#define RSSIOFFS             0xB2
#define RSSISLOPE            0xB3
#define DELOGSFT             0xB4
#define CDRDRTHRP            0xB5
#define CDRDRTHRN            0xB6
#define IM0                  0xB7
#define IM1                  0xB8
#define IM2                  0xB9
#define SPMIP                0xBA
#define SPMC                 0xBB
#define SPMRT                0xBC
#define SPMOFFT0             0xBD
#define SPMOFFT1             0xBE
#define SPMONTA0             0xBF
#define SPMONTA1             0xC0
#define SPMONTB0             0xC1
#define SPMONTB1             0xC2
#define SPMONTC0             0xC3
#define SPMONTC1             0xC4
#define SPMONTD0             0xC5
#define SPMONTD1             0xC6
#define EXTPCMD              0xC7
#define TXC                  0xC8
#define RXC                  0xC9
#define CMC                  0xCA
#define TXCHNL               0xCB
#define PLLCFG               0xCC
#define VACERRTH             0xCD
#define PRBS                 0xCE
#define TXFIFOAEL            0xCF
#define TXFIFOAFL            0xD0
#define RXFIFOAFL            0xD1
#define PLLSTAT              0xD2
#define IS2                  0xD3
#define IS0                  0xD4
#define IS1                  0xD5
#define RFPLLACC             0xD6
#define RSSIPWU              0xD7
#define RSSIPRX              0xD8
#define RSSIPPL              0xD9
#define PLDLEN               0xDA
#define ADCRESH              0xDB
#define ADCRESL              0xDC
#define AFCOFFSET            0xDD
#define AGCADRR              0xDE
#define SPIAT                0xDF
#define SPIDT                0xE0
#define SPICHKSUM            0xE1
#define SN0                  0xE2
#define SN1                  0xE3
#define SN2                  0xE4
#define SN3                  0xE5
#define CHIPID               0xE6
#define RSSIRX               0xE7
#define RSSIPMF              0xE8
#define SPWR                 0xE9
#define NPWR                 0xEA

#define TDA5340_PON          TDA5340_PON_PORT, TDA5340_PON_PIN

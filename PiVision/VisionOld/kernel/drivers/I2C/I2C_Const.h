#ifndef I2C_CONST_H_
#define I2C_CONST_H_

#define I2C_SUB0            0x44E0B000 // Section 2.1           (Pg  158)
#define I2C_SUB1            0x4802A000 // Section 2.1           (Pg  159)
#define I2C_SUB2            0x4819C000 // Section 2.1           (Pg  160)

#define I2C_REVNB_LO        0x00000000 // Section 21.4.1.1      (Pg 3716)   Revision Number Low
#define I2C_REVNB_HI        0x00000004 // Section 21.4.1.2          Revision Number High
#define I2C_SYSC            0x00000010 // Section 21.4.1.3          System Control
#define I2C_IRQSTATUS_RAW   0x00000024 // Section 21.4.1.4          IRQ Status Raw
#define I2C_IRQSTATUS       0x00000028 // Section 21.4.1.5          IRQ Status Clear
#define I2C_IRQENABLE_SET   0x0000002C // Section 21.4.1.6          IRQ Enable Set
#define I2C_IRQENABLE_CLR   0x00000030 // Section 21.4.1.7          IRQ Enable Clear
#define I2C_WE              0x00000034 // Section 21.4.1.8          Wake Enable
#define I2C_DMARXENABLE_SET 0x00000038 // Section 21.4.1.9          DMA Receiver Enable Set
#define I2C_DMATXENABLE_SET 0x0000003C // Section 21.4.1.10         DMA Transmitter Enable Set
#define I2C_DMARXENABLE_CLR 0x00000040 // Section 21.4.1.11         DMA Receiver Enable Clear
#define I2C_DMATXENABLE_CLR 0x00000044 // Section 21.4.1.12         DMA Transmitter Enable Clear
#define I2C_DMARXWAKE_EN    0x00000048 // Section 21.4.1.13         DMA Receiver Wake Enable
#define I2C_DMATXWAKE_EN    0x0000004C // Section 21.4.1.14         DMA Transmitter Wake Enable
#define I2C_SYSS            0x00000090 // Section 21.4.1.15         System Status
#define I2C_BUF             0x00000094 // Section 21.4.1.16         Buffer
#define I2C_CNT             0x00000098 // Section 21.4.1.17         Count
#define I2C_DATA            0x0000009C // Section 21.4.1.18         Data
#define I2C_CON             0x000000A4 // Section 21.4.1.19         Configuration
#define I2C_OA              0x000000A8 // Section 21.4.1.20         Own Address
#define I2C_SA              0x000000AC // Section 21.4.1.21         Slave Address
#define I2C_PSC             0x000000B0 // Section 21.4.1.22         Pre-Scale Clock
#define I2C_SCLL            0x000000B4 // Section 21.4.1.23         Serial Clock Low
#define I2C_SCLH            0x000000B8 // Section 21.4.1.24         Serial Clock High
#define I2C_SYSTEST         0x000000BC // Section 21.4.1.25         System Test
#define I2C_BUFSTAT         0x000000C0 // Section 21.4.1.26         Buffer Status
#define I2C_OA1             0x000000C4 // Section 21.4.1.27         Own Address 1
#define I2C_OA2             0x000000C8 // Section 21.4.1.28         Own Address 2
#define I2C_OA3             0x000000CC // Section 21.4.1.29         Own Address 3
#define I2C_ACTOA           0x000000D0 // Section 21.4.1.30         Active Own Address
#define I2C_SBLOCK          0x000000D4 // Section 21.4.1.31         Serial Block

#endif

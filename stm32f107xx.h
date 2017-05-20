#ifndef _STM32F107XX_H
#define _STM32F107XX_H

#define HSE_Value       ((uint32_t) 25000000) /* Value of the External oscillator in Hz */
#define HSI_Value       ((uint32_t)  8000000) /* Value of the Internal oscillator in Hz */

// Define the base addresses for peripherals
#define PERIPH_BASE     ((uint32_t) 0x40000000)
#define SRAM_BASE       ((uint32_t) 0x20000000)

#define APB1PERIPH_BASE PERIPH_BASE
#define APB2PERIPH_BASE (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE  (PERIPH_BASE + 0x20000)

#define AFIO_BASE       (APB2PERIPH_BASE + 0x0000) //  AFIO base address is 0x40010000
#define GPIOE_BASE      (APB2PERIPH_BASE + 0x1800) // GPIOE base address is 0x40011800
#define GPIOD_BASE      (APB2PERIPH_BASE + 0x1400) // GPIOD base address is 0x40011400
#define TIM1_BASE       (APB2PERIPH_BASE + 0x2C00) //  TIM1 base address is 0x40012C00
#define RCC_BASE        ( AHBPERIPH_BASE + 0x1000) //   RCC base address is 0x40021000
#define FLASH_BASE      ( AHBPERIPH_BASE + 0x2000) // FLASH base address is 0x40022000

#define STACKINIT       0x2000FF00

/*
 * Register Addresses
 */
typedef struct
{
	uint32_t CRL;      /* GPIO port configuration register low,      Address offset: 0x00 */
	uint32_t CRH;      /* GPIO port configuration register high,     Address offset: 0x04 */
	uint32_t IDR;      /* GPIO port input data register,             Address offset: 0x08 */
	uint32_t ODR;      /* GPIO port output data register,            Address offset: 0x0C */
	uint32_t BSRR;     /* GPIO port bit set/reset register,          Address offset: 0x10 */
	uint32_t BRR;      /* GPIO port bit reset register,              Address offset: 0x14 */
	uint32_t LCKR;     /* GPIO port configuration lock register,     Address offset: 0x18 */
} GPIO_type;

typedef struct
{
	uint32_t CR;       /* RCC clock control register,                Address offset: 0x00 */
	uint32_t CFGR;     /* RCC clock configuration register,          Address offset: 0x04 */
	uint32_t CIR;      /* RCC clock interrupt register,              Address offset: 0x08 */
	uint32_t APB2RSTR; /* RCC APB2 peripheral reset register,        Address offset: 0x0C */
	uint32_t APB1RSTR; /* RCC APB1 peripheral reset register,        Address offset: 0x10 */
	uint32_t AHBENR;   /* RCC AHB peripheral clock enable register,  Address offset: 0x14 */
	uint32_t APB2ENR;  /* RCC APB2 peripheral clock enable register, Address offset: 0x18 */
	uint32_t APB1ENR;  /* RCC APB1 peripheral clock enable register, Address offset: 0x1C */
	uint32_t BDCR;     /* RCC backup domain control register,        Address offset: 0x20 */
	uint32_t CSR;      /* RCC control/status register,               Address offset: 0x24 */
	uint32_t AHBRSTR;  /* RCC AHB peripheral clock reset register,   Address offset: 0x28 */
	uint32_t CFGR2;    /* RCC clock configuration register 2,        Address offset: 0x2C */
} RCC_type;

typedef struct
{
	uint32_t CR1;       /* Address offset: 0x00 */
	uint32_t CR2;       /* Address offset: 0x04 */
	uint32_t SMCR;      /* Address offset: 0x08 */
	uint32_t DIER;      /* Address offset: 0x0C */
	uint32_t SR;        /* Address offset: 0x10 */
	uint32_t EGR;       /* Address offset: 0x14 */
	uint32_t CCMR1;     /* Address offset: 0x18 */
	uint32_t CCMR2;     /* Address offset: 0x1C */
	uint32_t CCER;      /* Address offset: 0x20 */
	uint32_t CNT;       /* Address offset: 0x24 */
	uint32_t PSC;       /* Address offset: 0x28 */
	uint32_t ARR;       /* Address offset: 0x2C */
	uint32_t RES1;      /* Address offset: 0x30 */
	uint32_t CCR1;      /* Address offset: 0x34 */
	uint32_t CCR2;      /* Address offset: 0x38 */
	uint32_t CCR3;      /* Address offset: 0x3C */
	uint32_t CCR4;      /* Address offset: 0x40 */
	uint32_t BDTR;      /* Address offset: 0x44 */
	uint32_t DCR;       /* Address offset: 0x48 */
	uint32_t DMAR;      /* Address offset: 0x4C */
} TIM_type;

typedef struct
{
	uint32_t ACR;
	uint32_t KEYR;
	uint32_t OPTKEYR;
	uint32_t SR;
	uint32_t CR;
	uint32_t AR;
	uint32_t RESERVED;
	uint32_t OBR;
	uint32_t WRPR;
} FLASH_type;

typedef struct
{
	uint32_t EVCR;      /* Address offset: 0x00 */
	uint32_t MAPR;      /* Address offset: 0x04 */
	uint32_t EXTICR1;   /* Address offset: 0x08 */
	uint32_t EXTICR2;   /* Address offset: 0x0C */
	uint32_t EXTICR3;   /* Address offset: 0x10 */
	uint32_t EXTICR4;   /* Address offset: 0x14 */
	uint32_t MAPR2;     /* Address offset: 0x18 */
} AFIO_type;

typedef struct
{
	uint32_t   ISER[8];     /* Address offset: 0x000 - 0x01C */
	uint32_t  RES0[24];     /* Address offset: 0x020 - 0x07C */
	uint32_t   ICER[8];     /* Address offset: 0x080 - 0x09C */
	uint32_t  RES1[24];     /* Address offset: 0x0A0 - 0x0FC */
	uint32_t   ISPR[8];     /* Address offset: 0x100 - 0x11C */
	uint32_t  RES2[24];     /* Address offset: 0x120 - 0x17C */
	uint32_t   ICPR[8];     /* Address offset: 0x180 - 0x19C */
	uint32_t  RES3[24];     /* Address offset: 0x1A0 - 0x1FC */
	uint32_t   IABR[8];     /* Address offset: 0x200 - 0x21C */
	uint32_t  RES4[56];     /* Address offset: 0x220 - 0x2FC */
	uint8_t   IPR[240];     /* Address offset: 0x300 - 0x3EC */
	uint32_t RES5[644];     /* Address offset: 0x3F0 - 0xEFC */
	uint32_t      STIR;     /* Address offset:         0xF00 */
} NVIC_type;

#define AFIO            ((AFIO_type  *)  AFIO_BASE)
#define GPIOE           ((GPIO_type  *) GPIOE_BASE)
#define GPIOD           ((GPIO_type  *) GPIOD_BASE)
#define RCC             ((RCC_type   *)   RCC_BASE)
#define FLASH           ((FLASH_type *) FLASH_BASE)
#define TIM1            ((TIM_type   *)  TIM1_BASE)

#define SET_BIT(REG, BIT)     ((REG) |=  (1 << BIT))
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(1 << BIT))
#define READ_BIT(REG, BIT)    ((REG) &   (1 << BIT))

#endif /* _STM32F107XX_H */

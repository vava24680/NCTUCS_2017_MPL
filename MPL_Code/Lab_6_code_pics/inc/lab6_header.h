#include <stdint.h>
#define     __IO    volatile             /*!< Defines 'read / write' permissions */
typedef struct
{
  __IO uint32_t CR;          /*!< RCC clock control register,                                              Address offset: 0x00 */
  __IO uint32_t ICSCR;       /*!< RCC internal clock sources calibration register,                         Address offset: 0x04 */
  __IO uint32_t CFGR;        /*!< RCC clock configuration register,                                        Address offset: 0x08 */
  __IO uint32_t PLLCFGR;     /*!< RCC system PLL configuration register,                                   Address offset: 0x0C */
  __IO uint32_t PLLSAI1CFGR; /*!< RCC PLL SAI1 configuration register,                                     Address offset: 0x10 */
  __IO uint32_t PLLSAI2CFGR; /*!< RCC PLL SAI2 configuration register,                                     Address offset: 0x14 */
  __IO uint32_t CIER;        /*!< RCC clock interrupt enable register,                                     Address offset: 0x18 */
  __IO uint32_t CIFR;        /*!< RCC clock interrupt flag register,                                       Address offset: 0x1C */
  __IO uint32_t CICR;        /*!< RCC clock interrupt clear register,                                      Address offset: 0x20 */
  uint32_t      RESERVED0;   /*!< Reserved,                                                                Address offset: 0x24 */
  __IO uint32_t AHB1RSTR;    /*!< RCC AHB1 peripheral reset register,                                      Address offset: 0x28 */
  __IO uint32_t AHB2RSTR;    /*!< RCC AHB2 peripheral reset register,                                      Address offset: 0x2C */
  __IO uint32_t AHB3RSTR;    /*!< RCC AHB3 peripheral reset register,                                      Address offset: 0x30 */
  uint32_t      RESERVED1;   /*!< Reserved,                                                                Address offset: 0x34 */
  __IO uint32_t APB1RSTR1;   /*!< RCC APB1 peripheral reset register 1,                                    Address offset: 0x38 */
  __IO uint32_t APB1RSTR2;   /*!< RCC APB1 peripheral reset register 2,                                    Address offset: 0x3C */
  __IO uint32_t APB2RSTR;    /*!< RCC APB2 peripheral reset register,                                      Address offset: 0x40 */
  uint32_t      RESERVED2;   /*!< Reserved,                                                                Address offset: 0x44 */
  __IO uint32_t AHB1ENR;     /*!< RCC AHB1 peripheral clocks enable register,                              Address offset: 0x48 */
  __IO uint32_t AHB2ENR;     /*!< RCC AHB2 peripheral clocks enable register,                              Address offset: 0x4C */
  __IO uint32_t AHB3ENR;     /*!< RCC AHB3 peripheral clocks enable register,                              Address offset: 0x50 */
  uint32_t      RESERVED3;   /*!< Reserved,                                                                Address offset: 0x54 */
  __IO uint32_t APB1ENR1;    /*!< RCC APB1 peripheral clocks enable register 1,                            Address offset: 0x58 */
  __IO uint32_t APB1ENR2;    /*!< RCC APB1 peripheral clocks enable register 2,                            Address offset: 0x5C */
  __IO uint32_t APB2ENR;     /*!< RCC APB2 peripheral clocks enable register,                              Address offset: 0x60 */
  uint32_t      RESERVED4;   /*!< Reserved,                                                                Address offset: 0x64 */
  __IO uint32_t AHB1SMENR;   /*!< RCC AHB1 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x68 */
  __IO uint32_t AHB2SMENR;   /*!< RCC AHB2 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x6C */
  __IO uint32_t AHB3SMENR;   /*!< RCC AHB3 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x70 */
  uint32_t      RESERVED5;   /*!< Reserved,                                                                Address offset: 0x74 */
  __IO uint32_t APB1SMENR1;  /*!< RCC APB1 peripheral clocks enable in sleep mode and stop modes register 1, Address offset: 0x78 */
  __IO uint32_t APB1SMENR2;  /*!< RCC APB1 peripheral clocks enable in sleep mode and stop modes register 2, Address offset: 0x7C */
  __IO uint32_t APB2SMENR;   /*!< RCC APB2 peripheral clocks enable in sleep mode and stop modes register, Address offset: 0x80 */
  uint32_t      RESERVED6;   /*!< Reserved,                                                                Address offset: 0x84 */
  __IO uint32_t CCIPR;       /*!< RCC peripherals independent clock configuration register,                Address offset: 0x88 */
  __IO uint32_t RESERVED7;   /*!< Reserved,                                                                Address offset: 0x8C */
  __IO uint32_t BDCR;        /*!< RCC backup domain control register,                                      Address offset: 0x90 */
  __IO uint32_t CSR;         /*!< RCC clock control & status register,                                     Address offset: 0x94 */
} RCC_TypeDef;

typedef struct
{
  __IO uint32_t MODER;       /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO uint32_t OTYPER;      /*!< GPIO port output type register,        Address offset: 0x04      */
  __IO uint32_t OSPEEDR;     /*!< GPIO port output speed register,       Address offset: 0x08      */
  __IO uint32_t PUPDR;       /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  __IO uint32_t IDR;         /*!< GPIO port input data register,         Address offset: 0x10      */
  __IO uint32_t ODR;         /*!< GPIO port output data register,        Address offset: 0x14      */
  __IO uint32_t BSRR;        /*!< GPIO port bit set/reset  register,     Address offset: 0x18      */
  __IO uint32_t LCKR;        /*!< GPIO port configuration lock register, Address offset: 0x1C      */
  __IO uint32_t AFR[2];      /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
  __IO uint32_t BRR;         /*!< GPIO Bit Reset register,               Address offset: 0x28      */
  __IO uint32_t ASCR;        /*!< GPIO analog switch control register,   Address offset: 0x2C     */

} GPIO_TypeDef;
#define PERIPH_BASE           ((uint32_t)0x40000000U) /*!< Peripheral base address */
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000U)
#define AHB2PERIPH_BASE       (PERIPH_BASE + 0x08000000U)
#define RCC_BASE              (AHB1PERIPH_BASE + 0x1000U)
#define GPIOB_BASE            (AHB2PERIPH_BASE + 0x0400U)


#define RCC                 ((RCC_TypeDef *) RCC_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)

#define RCC_AHB2ENR_GPIOBEN_Pos             (1U)
#define RCC_AHB2ENR_GPIOBEN_Msk             (0x1U << RCC_AHB2ENR_GPIOBEN_Pos)  /*!< 0x00000002 */
#define RCC_AHB2ENR_GPIOBEN                 RCC_AHB2ENR_GPIOBEN_Msk

#define GPIO_Pin_8 8
#define GPIO_Pin_9 9
#define GPIO_Pin_10 10
#define GPIO_Pin_11 11
#define GPIO_Pin_12 12
#define GPIO_Pin_13 13
#define GPIO_Pin_14 (14U)
#define GPIO_Pin_15 (15U)
/******************************************************************************/
/*                                                                            */
/*                       General Purpose IOs (GPIO)                           */
/*                                                                            */
/******************************************************************************/
/******************  Bits definition for GPIO_MODER register  *****************/
#define GPIO_MODER_MODE3_Pos                 (6U)
#define GPIO_MODER_MODE3_Msk                 (0x3U << GPIO_MODER_MODE3_Pos)    /*!< 0x000000C0 */
#define GPIO_MODER_MODE3                     GPIO_MODER_MODE3_Msk
#define GPIO_MODER_MODE3_0                   (0x1U << GPIO_MODER_MODE3_Pos)    /*!< 0x00000040 */
#define GPIO_MODER_MODE3_1                   (0x2U << GPIO_MODER_MODE3_Pos)    /*!< 0x00000080 */
#define GPIO_MODER_MODE4_Pos                 (8U)
#define GPIO_MODER_MODE4_Msk                 (0x3U << GPIO_MODER_MODE4_Pos)    /*!< 0x00000300 */
#define GPIO_MODER_MODE4                     GPIO_MODER_MODE4_Msk
#define GPIO_MODER_MODE4_0                   (0x1U << GPIO_MODER_MODE4_Pos)    /*!< 0x00000100 */
#define GPIO_MODER_MODE4_1                   (0x2U << GPIO_MODER_MODE4_Pos)    /*!< 0x00000200 */
#define GPIO_MODER_MODE5_Pos                 (10U)
#define GPIO_MODER_MODE5_Msk                 (0x3U << GPIO_MODER_MODE5_Pos)    /*!< 0x00000C00 */
#define GPIO_MODER_MODE5                     GPIO_MODER_MODE5_Msk
#define GPIO_MODER_MODE5_0                   (0x1U << GPIO_MODER_MODE5_Pos)    /*!< 0x00000400 */
#define GPIO_MODER_MODE5_1                   (0x2U << GPIO_MODER_MODE5_Pos)    /*!< 0x00000800 */
#define GPIO_MODER_MODE8_Pos                 (16U)
#define GPIO_MODER_MODE8_Msk                 (0x3U << GPIO_MODER_MODE8_Pos)    /*!< 0x00030000 */
#define GPIO_MODER_MODE8                     GPIO_MODER_MODE8_Msk
#define GPIO_MODER_MODE8_0                   (0x1U << GPIO_MODER_MODE8_Pos)    /*!< 0x00010000 */
#define GPIO_MODER_MODE8_1                   (0x2U << GPIO_MODER_MODE8_Pos)    /*!< 0x00020000 */
#define GPIO_MODER_MODE9_Pos                 (18U)
#define GPIO_MODER_MODE9_Msk                 (0x3U << GPIO_MODER_MODE9_Pos)    /*!< 0x000C0000 */
#define GPIO_MODER_MODE9                     GPIO_MODER_MODE9_Msk
#define GPIO_MODER_MODE9_0                   (0x1U << GPIO_MODER_MODE9_Pos)    /*!< 0x00040000 */
#define GPIO_MODER_MODE9_1                   (0x2U << GPIO_MODER_MODE9_Pos)    /*!< 0x00080000 */
#define GPIO_MODER_MODE10_Pos                (20U)
#define GPIO_MODER_MODE10_Msk                (0x3U << GPIO_MODER_MODE10_Pos)   /*!< 0x00300000 */
#define GPIO_MODER_MODE10                    GPIO_MODER_MODE10_Msk
#define GPIO_MODER_MODE10_0                  (0x1U << GPIO_MODER_MODE10_Pos)   /*!< 0x00100000 */
#define GPIO_MODER_MODE10_1                  (0x2U << GPIO_MODER_MODE10_Pos)   /*!< 0x00200000 */
#define GPIO_MODER_MODE11_Pos                (22U)
#define GPIO_MODER_MODE11_Msk                (0x3U << GPIO_MODER_MODE11_Pos)   /*!< 0x00C00000 */
#define GPIO_MODER_MODE11                    GPIO_MODER_MODE11_Msk
#define GPIO_MODER_MODE11_0                  (0x1U << GPIO_MODER_MODE11_Pos)   /*!< 0x00400000 */
#define GPIO_MODER_MODE11_1                  (0x2U << GPIO_MODER_MODE11_Pos)   /*!< 0x00800000 */
#define GPIO_MODER_MODE12_Pos                (24U)
#define GPIO_MODER_MODE12_Msk                (0x3U << GPIO_MODER_MODE12_Pos)   /*!< 0x03000000 */
#define GPIO_MODER_MODE12                    GPIO_MODER_MODE12_Msk
#define GPIO_MODER_MODE12_0                  (0x1U << GPIO_MODER_MODE12_Pos)   /*!< 0x01000000 */
#define GPIO_MODER_MODE12_1                  (0x2U << GPIO_MODER_MODE12_Pos)   /*!< 0x02000000 */
#define GPIO_MODER_MODE13_Pos                (26U)
#define GPIO_MODER_MODE13_Msk                (0x3U << GPIO_MODER_MODE13_Pos)   /*!< 0x0C000000 */
#define GPIO_MODER_MODE13                    GPIO_MODER_MODE13_Msk
#define GPIO_MODER_MODE13_0                  (0x1U << GPIO_MODER_MODE13_Pos)   /*!< 0x04000000 */
#define GPIO_MODER_MODE13_1                  (0x2U << GPIO_MODER_MODE13_Pos)   /*!< 0x08000000 */
#define GPIO_MODER_MODE14_Pos                (28U)
#define GPIO_MODER_MODE14_Msk                (0x3U << GPIO_MODER_MODE14_Pos)   /*!< 0x30000000 */
#define GPIO_MODER_MODE14                    GPIO_MODER_MODE14_Msk
#define GPIO_MODER_MODE14_0                  (0x1U << GPIO_MODER_MODE14_Pos)   /*!< 0x10000000 */
#define GPIO_MODER_MODE14_1                  (0x2U << GPIO_MODER_MODE14_Pos)   /*!< 0x20000000 */
#define GPIO_MODER_MODE15_Pos                (30U)
#define GPIO_MODER_MODE15_Msk                (0x3U << GPIO_MODER_MODE15_Pos)   /*!< 0xC0000000 */
#define GPIO_MODER_MODE15                    GPIO_MODER_MODE15_Msk
#define GPIO_MODER_MODE15_0                  (0x1U << GPIO_MODER_MODE15_Pos)   /*!< 0x40000000 */
#define GPIO_MODER_MODE15_1                  (0x2U << GPIO_MODER_MODE15_Pos)   /*!< 0x80000000 */


#define GPIO_OSPEEDR_OSPEED3_Pos             (6U)
#define GPIO_OSPEEDR_OSPEED3_Msk             (0x3U << GPIO_OSPEEDR_OSPEED3_Pos) /*!< 0x000000C0 */
#define GPIO_OSPEEDR_OSPEED3                 GPIO_OSPEEDR_OSPEED3_Msk
#define GPIO_OSPEEDR_OSPEED3_0               (0x1U << GPIO_OSPEEDR_OSPEED3_Pos) /*!< 0x00000040 */
#define GPIO_OSPEEDR_OSPEED3_1               (0x2U << GPIO_OSPEEDR_OSPEED3_Pos) /*!< 0x00000080 */
#define GPIO_OSPEEDR_OSPEED4_Pos             (8U)
#define GPIO_OSPEEDR_OSPEED4_Msk             (0x3U << GPIO_OSPEEDR_OSPEED4_Pos) /*!< 0x00000300 */
#define GPIO_OSPEEDR_OSPEED4                 GPIO_OSPEEDR_OSPEED4_Msk
#define GPIO_OSPEEDR_OSPEED4_0               (0x1U << GPIO_OSPEEDR_OSPEED4_Pos) /*!< 0x00000100 */
#define GPIO_OSPEEDR_OSPEED4_1               (0x2U << GPIO_OSPEEDR_OSPEED4_Pos) /*!< 0x00000200 */
#define GPIO_OSPEEDR_OSPEED5_Pos             (10U)
#define GPIO_OSPEEDR_OSPEED5_Msk             (0x3U << GPIO_OSPEEDR_OSPEED5_Pos) /*!< 0x00000C00 */
#define GPIO_OSPEEDR_OSPEED5                 GPIO_OSPEEDR_OSPEED5_Msk
#define GPIO_OSPEEDR_OSPEED5_0               (0x1U << GPIO_OSPEEDR_OSPEED5_Pos) /*!< 0x00000400 */
#define GPIO_OSPEEDR_OSPEED5_1               (0x2U << GPIO_OSPEEDR_OSPEED5_Pos) /*!< 0x00000800 */
#define GPIO_OSPEEDR_OSPEED8_Pos             (16U)
#define GPIO_OSPEEDR_OSPEED8_Msk             (0x3U << GPIO_OSPEEDR_OSPEED8_Pos) /*!< 0x00030000 */
#define GPIO_OSPEEDR_OSPEED8                 GPIO_OSPEEDR_OSPEED8_Msk
#define GPIO_OSPEEDR_OSPEED8_0               (0x1U << GPIO_OSPEEDR_OSPEED8_Pos) /*!< 0x00010000 */
#define GPIO_OSPEEDR_OSPEED8_1               (0x2U << GPIO_OSPEEDR_OSPEED8_Pos) /*!< 0x00020000 */
#define GPIO_OSPEEDR_OSPEED9_Pos             (18U)
#define GPIO_OSPEEDR_OSPEED9_Msk             (0x3U << GPIO_OSPEEDR_OSPEED9_Pos) /*!< 0x000C0000 */
#define GPIO_OSPEEDR_OSPEED9                 GPIO_OSPEEDR_OSPEED9_Msk
#define GPIO_OSPEEDR_OSPEED9_0               (0x1U << GPIO_OSPEEDR_OSPEED9_Pos) /*!< 0x00040000 */
#define GPIO_OSPEEDR_OSPEED9_1               (0x2U << GPIO_OSPEEDR_OSPEED9_Pos) /*!< 0x00080000 */
#define GPIO_OSPEEDR_OSPEED10_Pos            (20U)
#define GPIO_OSPEEDR_OSPEED10_Msk            (0x3U << GPIO_OSPEEDR_OSPEED10_Pos) /*!< 0x00300000 */
#define GPIO_OSPEEDR_OSPEED10                GPIO_OSPEEDR_OSPEED10_Msk
#define GPIO_OSPEEDR_OSPEED10_0              (0x1U << GPIO_OSPEEDR_OSPEED10_Pos) /*!< 0x00100000 */
#define GPIO_OSPEEDR_OSPEED10_1              (0x2U << GPIO_OSPEEDR_OSPEED10_Pos) /*!< 0x00200000 */
#define GPIO_OSPEEDR_OSPEED11_Pos            (22U)
#define GPIO_OSPEEDR_OSPEED11_Msk            (0x3U << GPIO_OSPEEDR_OSPEED11_Pos) /*!< 0x00C00000 */
#define GPIO_OSPEEDR_OSPEED11                GPIO_OSPEEDR_OSPEED11_Msk
#define GPIO_OSPEEDR_OSPEED11_0              (0x1U << GPIO_OSPEEDR_OSPEED11_Pos) /*!< 0x00400000 */
#define GPIO_OSPEEDR_OSPEED11_1              (0x2U << GPIO_OSPEEDR_OSPEED11_Pos) /*!< 0x00800000 */

#define GPIO_PUPDR_PUPD12_Pos                (24U)
#define GPIO_PUPDR_PUPD12_Msk                (0x3U << GPIO_PUPDR_PUPD12_Pos)   /*!< 0x03000000 */
#define GPIO_PUPDR_PUPD12                    GPIO_PUPDR_PUPD12_Msk
#define GPIO_PUPDR_PUPD12_0                  (0x1U << GPIO_PUPDR_PUPD12_Pos)   /*!< 0x01000000 */
#define GPIO_PUPDR_PUPD12_1                  (0x2U << GPIO_PUPDR_PUPD12_Pos)   /*!< 0x02000000 */
#define GPIO_PUPDR_PUPD13_Pos                (26U)
#define GPIO_PUPDR_PUPD13_Msk                (0x3U << GPIO_PUPDR_PUPD13_Pos)   /*!< 0x0C000000 */
#define GPIO_PUPDR_PUPD13                    GPIO_PUPDR_PUPD13_Msk
#define GPIO_PUPDR_PUPD13_0                  (0x1U << GPIO_PUPDR_PUPD13_Pos)   /*!< 0x04000000 */
#define GPIO_PUPDR_PUPD13_1                  (0x2U << GPIO_PUPDR_PUPD13_Pos)   /*!< 0x08000000 */
#define GPIO_PUPDR_PUPD14_Pos                (28U)
#define GPIO_PUPDR_PUPD14_Msk                (0x3U << GPIO_PUPDR_PUPD14_Pos)   /*!< 0x30000000 */
#define GPIO_PUPDR_PUPD14                    GPIO_PUPDR_PUPD14_Msk
#define GPIO_PUPDR_PUPD14_0                  (0x1U << GPIO_PUPDR_PUPD14_Pos)   /*!< 0x10000000 */
#define GPIO_PUPDR_PUPD14_1                  (0x2U << GPIO_PUPDR_PUPD14_Pos)   /*!< 0x20000000 */
#define GPIO_PUPDR_PUPD15_Pos                (30U)
#define GPIO_PUPDR_PUPD15_Msk                (0x3U << GPIO_PUPDR_PUPD15_Pos)   /*!< 0xC0000000 */
#define GPIO_PUPDR_PUPD15                    GPIO_PUPDR_PUPD15_Msk
#define GPIO_PUPDR_PUPD15_0                  (0x1U << GPIO_PUPDR_PUPD15_Pos)   /*!< 0x40000000 */
#define GPIO_PUPDR_PUPD15_1                  (0x2U << GPIO_PUPDR_PUPD15_Pos)   /*!< 0x80000000 */

#define GPIO_IDR_ID11_Pos                    (11U)
#define GPIO_IDR_ID11_Msk                    (0x1U << GPIO_IDR_ID11_Pos)       /*!< 0x00000800 */
#define GPIO_IDR_ID11                        GPIO_IDR_ID11_Msk
#define GPIO_IDR_ID12_Pos                    (12U)
#define GPIO_IDR_ID12_Msk                    (0x1U << GPIO_IDR_ID12_Pos)       /*!< 0x00001000 */
#define GPIO_IDR_ID12                        GPIO_IDR_ID12_Msk
#define GPIO_IDR_ID13_Pos                    (13U)
#define GPIO_IDR_ID13_Msk                    (0x1U << GPIO_IDR_ID13_Pos)       /*!< 0x00002000 */
#define GPIO_IDR_ID13                        GPIO_IDR_ID13_Msk
#define GPIO_IDR_ID14_Pos                    (14U)
#define GPIO_IDR_ID14_Msk                    (0x1U << GPIO_IDR_ID14_Pos)       /*!< 0x00004000 */
#define GPIO_IDR_ID14                        GPIO_IDR_ID14_Msk
#define GPIO_IDR_ID15_Pos                    (15U)
#define GPIO_IDR_ID15_Msk                    (0x1U << GPIO_IDR_ID15_Pos)       /*!< 0x00008000 */
#define GPIO_IDR_ID15                        GPIO_IDR_ID15_Msk
#define GPIO_IDR_IDR_12                     GPIO_IDR_ID12
#define GPIO_IDR_IDR_13                     GPIO_IDR_ID13
#define GPIO_IDR_IDR_14                     GPIO_IDR_ID14
#define GPIO_IDR_IDR_15                     GPIO_IDR_ID15

#define GPIO_ODR_OD3_Pos                     (3U)
#define GPIO_ODR_OD3_Msk                     (0x1U << GPIO_ODR_OD3_Pos)        /*!< 0x00000008 */
#define GPIO_ODR_OD3                         GPIO_ODR_OD3_Msk
#define GPIO_ODR_OD4_Pos                     (4U)
#define GPIO_ODR_OD4_Msk                     (0x1U << GPIO_ODR_OD4_Pos)        /*!< 0x00000010 */
#define GPIO_ODR_OD4                         GPIO_ODR_OD4_Msk
#define GPIO_ODR_OD5_Pos                     (5U)
#define GPIO_ODR_OD5_Msk                     (0x1U << GPIO_ODR_OD5_Pos)        /*!< 0x00000020 */
#define GPIO_ODR_OD5                         GPIO_ODR_OD5_Msk
#define GPIO_ODR_OD8_Pos                     (8U)
#define GPIO_ODR_OD8_Msk                     (0x1U << GPIO_ODR_OD8_Pos)        /*!< 0x00000100 */
#define GPIO_ODR_OD8                         GPIO_ODR_OD8_Msk
#define GPIO_ODR_OD9_Pos                     (9U)
#define GPIO_ODR_OD9_Msk                     (0x1U << GPIO_ODR_OD9_Pos)        /*!< 0x00000200 */
#define GPIO_ODR_OD9                         GPIO_ODR_OD9_Msk
#define GPIO_ODR_OD10_Pos                    (10U)
#define GPIO_ODR_OD10_Msk                    (0x1U << GPIO_ODR_OD10_Pos)       /*!< 0x00000400 */
#define GPIO_ODR_OD10                        GPIO_ODR_OD10_Msk
#define GPIO_ODR_OD11_Pos                    (11U)
#define GPIO_ODR_OD11_Msk                    (0x1U << GPIO_ODR_OD11_Pos)       /*!< 0x00000800 */
#define GPIO_ODR_OD11                        GPIO_ODR_OD11_Msk

#define GPIO_BSRR_BS8_Pos                    (8U)
#define GPIO_BSRR_BS8_Msk                    (0x1U << GPIO_BSRR_BS8_Pos)       /*!< 0x00000100 */
#define GPIO_BSRR_BS8                        GPIO_BSRR_BS8_Msk
#define GPIO_BSRR_BS9_Pos                    (9U)
#define GPIO_BSRR_BS9_Msk                    (0x1U << GPIO_BSRR_BS9_Pos)       /*!< 0x00000200 */
#define GPIO_BSRR_BS9                        GPIO_BSRR_BS9_Msk
#define GPIO_BSRR_BS10_Pos                   (10U)
#define GPIO_BSRR_BS10_Msk                   (0x1U << GPIO_BSRR_BS10_Pos)      /*!< 0x00000400 */
#define GPIO_BSRR_BS10                       GPIO_BSRR_BS10_Msk
#define GPIO_BSRR_BS11_Pos                   (11U)
#define GPIO_BSRR_BS11_Msk                   (0x1U << GPIO_BSRR_BS11_Pos)      /*!< 0x00000800 */
#define GPIO_BSRR_BS11                       GPIO_BSRR_BS11_Msk

#define GPIO_BRR_BR8_Pos                     (8U)
#define GPIO_BRR_BR8_Msk                     (0x1U << GPIO_BRR_BR8_Pos)        /*!< 0x00000100 */
#define GPIO_BRR_BR8                         GPIO_BRR_BR8_Msk
#define GPIO_BRR_BR9_Pos                     (9U)
#define GPIO_BRR_BR9_Msk                     (0x1U << GPIO_BRR_BR9_Pos)        /*!< 0x00000200 */
#define GPIO_BRR_BR9                         GPIO_BRR_BR9_Msk
#define GPIO_BRR_BR10_Pos                    (10U)
#define GPIO_BRR_BR10_Msk                    (0x1U << GPIO_BRR_BR10_Pos)       /*!< 0x00000400 */
#define GPIO_BRR_BR10                        GPIO_BRR_BR10_Msk
#define GPIO_BRR_BR11_Pos                    (11U)
#define GPIO_BRR_BR11_Msk                    (0x1U << GPIO_BRR_BR11_Pos)       /*!< 0x00000800 */
#define GPIO_BRR_BR11                        GPIO_BRR_BR11_Msk

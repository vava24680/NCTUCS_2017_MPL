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

typedef struct
{
  __IO uint32_t CR1;         /*!< TIM control register 1,                   Address offset: 0x00 */
  __IO uint32_t CR2;         /*!< TIM control register 2,                   Address offset: 0x04 */
  __IO uint32_t SMCR;        /*!< TIM slave mode control register,          Address offset: 0x08 */
  __IO uint32_t DIER;        /*!< TIM DMA/interrupt enable register,        Address offset: 0x0C */
  __IO uint32_t SR;          /*!< TIM status register,                      Address offset: 0x10 */
  __IO uint32_t EGR;         /*!< TIM event generation register,            Address offset: 0x14 */
  __IO uint32_t CCMR1;       /*!< TIM capture/compare mode register 1,      Address offset: 0x18 */
  __IO uint32_t CCMR2;       /*!< TIM capture/compare mode register 2,      Address offset: 0x1C */
  __IO uint32_t CCER;        /*!< TIM capture/compare enable register,      Address offset: 0x20 */
  __IO uint32_t CNT;         /*!< TIM counter register,                     Address offset: 0x24 */
  __IO uint32_t PSC;         /*!< TIM prescaler,                            Address offset: 0x28 */
  __IO uint32_t ARR;         /*!< TIM auto-reload register,                 Address offset: 0x2C */
  __IO uint32_t RCR;         /*!< TIM repetition counter register,          Address offset: 0x30 */
  __IO uint32_t CCR1;        /*!< TIM capture/compare register 1,           Address offset: 0x34 */
  __IO uint32_t CCR2;        /*!< TIM capture/compare register 2,           Address offset: 0x38 */
  __IO uint32_t CCR3;        /*!< TIM capture/compare register 3,           Address offset: 0x3C */
  __IO uint32_t CCR4;        /*!< TIM capture/compare register 4,           Address offset: 0x40 */
  __IO uint32_t BDTR;        /*!< TIM break and dead-time register,         Address offset: 0x44 */
  __IO uint32_t DCR;         /*!< TIM DMA control register,                 Address offset: 0x48 */
  __IO uint32_t DMAR;        /*!< TIM DMA address for full transfer,        Address offset: 0x4C */
  __IO uint32_t OR1;         /*!< TIM option register 1,                    Address offset: 0x50 */
  __IO uint32_t CCMR3;       /*!< TIM capture/compare mode register 3,      Address offset: 0x54 */
  __IO uint32_t CCR5;        /*!< TIM capture/compare register5,            Address offset: 0x58 */
  __IO uint32_t CCR6;        /*!< TIM capture/compare register6,            Address offset: 0x5C */
  __IO uint32_t OR2;         /*!< TIM option register 2,                    Address offset: 0x60 */
  __IO uint32_t OR3;         /*!< TIM option register 3,                    Address offset: 0x64 */
} TIM_TypeDef;

#define PERIPH_BASE           ((uint32_t)0x40000000U) /*!< Peripheral base address */
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000U)
#define AHB2PERIPH_BASE       (PERIPH_BASE + 0x08000000U)
#define APB1PERIPH_BASE        PERIPH_BASE
#define RCC_BASE              (AHB1PERIPH_BASE + 0x1000U)
#define GPIOB_BASE            (AHB2PERIPH_BASE + 0x0400U)
#define GPIOC_BASE            (AHB2PERIPH_BASE + 0x0800U)
#define TIM2_BASE             (APB1PERIPH_BASE + 0x0000U)

#define RCC                 ((RCC_TypeDef *) RCC_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define TIM2                ((TIM_TypeDef *) TIM2_BASE)

#define RCC_CR_MSIRDY_Pos                   (1U)
#define RCC_CR_MSIRDY_Msk                   (0x1U << RCC_CR_MSIRDY_Pos)        /*!< 0x00000002 */
#define RCC_CR_MSIRDY                       RCC_CR_MSIRDY_Msk                  /*!< Internal Multi Speed oscillator (MSI) clock ready flag */


#define RCC_CR_PLLON_Pos                    (24U)
#define RCC_CR_PLLON_Msk                    (0x1U << RCC_CR_PLLON_Pos)         /*!< 0x01000000 */
#define RCC_CR_PLLON                        RCC_CR_PLLON_Msk                   /*!< System PLL clock enable */
#define RCC_CR_PLLRDY_Pos                   (25U)
#define RCC_CR_PLLRDY_Msk                   (0x1U << RCC_CR_PLLRDY_Pos)        /*!< 0x02000000 */
#define RCC_CR_PLLRDY                       RCC_CR_PLLRDY_Msk                  /*!< System PLL clock ready */

#define RCC_CFGR_SW_Pos                     (0U)
#define RCC_CFGR_SW_Msk                     (0x3U << RCC_CFGR_SW_Pos)          /*!< 0x00000003 */
#define RCC_CFGR_SW                         RCC_CFGR_SW_Msk                    /*!< SW[1:0] bits (System clock Switch)*/
#define RCC_CFGR_SW_PLL                     (0x00000003U)                      /*!< PLL selection as system clock */

#define RCC_AHB2ENR_GPIOBEN_Pos             (1U)
#define RCC_AHB2ENR_GPIOBEN_Msk             (0x1U << RCC_AHB2ENR_GPIOBEN_Pos)  /*!< 0x00000002 */
#define RCC_AHB2ENR_GPIOBEN                 RCC_AHB2ENR_GPIOBEN_Msk
#define RCC_AHB2ENR_GPIOCEN_Pos             (2U)
#define RCC_AHB2ENR_GPIOCEN_Msk             (0x1U << RCC_AHB2ENR_GPIOCEN_Pos)  /*!< 0x00000004 */
#define RCC_AHB2ENR_GPIOCEN                 RCC_AHB2ENR_GPIOCEN_Msk


#define RCC_PLLCFGR_PLLN_Pos                (8U)
#define RCC_PLLCFGR_PLLN_Msk                (0x7FU << RCC_PLLCFGR_PLLN_Pos)    /*!< 0x00007F00 */
#define RCC_PLLCFGR_PLLN                    RCC_PLLCFGR_PLLN_Msk
#define RCC_PLLCFGR_PLLM_Pos                (4U)
#define RCC_PLLCFGR_PLLM_Msk                (0x7U << RCC_PLLCFGR_PLLM_Pos)     /*!< 0x00000070 */
#define RCC_PLLCFGR_PLLM                    RCC_PLLCFGR_PLLM_Msk
#define RCC_PLLCFGR_PLLR_Pos                (25U)
#define RCC_PLLCFGR_PLLR_Msk                (0x3U << RCC_PLLCFGR_PLLR_Pos)     /*!< 0x06000000 */
#define RCC_PLLCFGR_PLLR                    RCC_PLLCFGR_PLLR_Msk

#define RCC_PLLCFGR_PLLREN_Pos              (24U)
#define RCC_PLLCFGR_PLLREN_Msk              (0x1U << RCC_PLLCFGR_PLLREN_Pos)   /*!< 0x01000000 */
#define RCC_PLLCFGR_PLLREN                  RCC_PLLCFGR_PLLREN_Msk
#define RCC_PLLCFGR_PLLPEN_Pos              (16U)
#define RCC_PLLCFGR_PLLPEN_Msk              (0x1U << RCC_PLLCFGR_PLLPEN_Pos)   /*!< 0x00010000 */
#define RCC_PLLCFGR_PLLPEN                  RCC_PLLCFGR_PLLPEN_Msk
#define RCC_PLLCFGR_PLLQEN_Pos              (20U)
#define RCC_PLLCFGR_PLLQEN_Msk              (0x1U << RCC_PLLCFGR_PLLQEN_Pos)   /*!< 0x00100000 */
#define RCC_PLLCFGR_PLLQEN                  RCC_PLLCFGR_PLLQEN_Msk
#define RCC_PLLCFGR_PLLSRC_MSI_Pos          (0U)
#define RCC_PLLCFGR_PLLSRC_MSI_Msk          (0x1U << RCC_PLLCFGR_PLLSRC_MSI_Pos) /*!< 0x00000001 */
#define RCC_PLLCFGR_PLLSRC_MSI              RCC_PLLCFGR_PLLSRC_MSI_Msk         /*!< MSI oscillator source clock*/

#define RCC_APB1ENR1_TIM2EN_Pos             (0U)
#define RCC_APB1ENR1_TIM2EN_Msk             (0x1U << RCC_APB1ENR1_TIM2EN_Pos)  /*!< 0x00000001 */
#define RCC_APB1ENR1_TIM2EN                 RCC_APB1ENR1_TIM2EN_Msk

#define TIM_CR1_CEN_Pos           (0U)
#define TIM_CR1_CEN_Msk           (0x1U << TIM_CR1_CEN_Pos)                    /*!< 0x00000001 */
#define TIM_CR1_CEN               TIM_CR1_CEN_Msk                              /*!<Counter enable */
#define TIM_CR1_DIR_Pos           (4U)
#define TIM_CR1_DIR_Msk           (0x1U << TIM_CR1_DIR_Pos)                    /*!< 0x00000010 */
#define TIM_CR1_DIR               TIM_CR1_DIR_Msk                              /*!<Direction */
#define TIM_CNT_CNT_Pos           (0U)
#define TIM_CNT_CNT_Msk           (0xFFFFFFFFU << TIM_CNT_CNT_Pos)             /*!< 0xFFFFFFFF */
#define TIM_CNT_CNT               TIM_CNT_CNT_Msk                              /*!<Counter Value */
#define TIM_PSC_PSC_Pos           (0U)
#define TIM_PSC_PSC_Msk           (0xFFFFU << TIM_PSC_PSC_Pos)                 /*!< 0x0000FFFF */
#define TIM_PSC_PSC               TIM_PSC_PSC_Msk                              /*!<Prescaler Value */
#define TIM_ARR_ARR_Pos           (0U)
#define TIM_ARR_ARR_Msk           (0xFFFFFFFFU << TIM_ARR_ARR_Pos)             /*!< 0xFFFFFFFF */
#define TIM_ARR_ARR               TIM_ARR_ARR_Msk                              /*!<Actual auto-reload Value */
#define TIM_EGR_UG_Pos            (0U)
#define TIM_EGR_UG_Msk            (0x1U << TIM_EGR_UG_Pos)                     /*!< 0x00000001 */
#define TIM_EGR_UG                TIM_EGR_UG_Msk                               /*!<Update Generation */
#define TIM_SR_UIF_Pos            (0U)
#define TIM_SR_UIF_Msk            (0x1U << TIM_SR_UIF_Pos)                     /*!< 0x00000001 */
#define TIM_SR_UIF                TIM_SR_UIF_Msk                               /*!<Update interrupt Flag */

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
#define GPIO_MODER_MODE13_Pos                (26U)
#define GPIO_MODER_MODE13_Msk                (0x3U << GPIO_MODER_MODE13_Pos)   /*!< 0x0C000000 */
#define GPIO_MODER_MODE13                    GPIO_MODER_MODE13_Msk
#define GPIO_MODER_MODE13_0                  (0x1U << GPIO_MODER_MODE13_Pos)   /*!< 0x04000000 */
#define GPIO_MODER_MODE13_1                  (0x2U << GPIO_MODER_MODE13_Pos)   /*!< 0x08000000 */

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

#define GPIO_PUPDR_PUPD13_Pos                (26U)
#define GPIO_PUPDR_PUPD13_Msk                (0x3U << GPIO_PUPDR_PUPD13_Pos)   /*!< 0x0C000000 */
#define GPIO_PUPDR_PUPD13                    GPIO_PUPDR_PUPD13_Msk
#define GPIO_PUPDR_PUPD13_0                  (0x1U << GPIO_PUPDR_PUPD13_Pos)   /*!< 0x04000000 */
#define GPIO_PUPDR_PUPD13_1                  (0x2U << GPIO_PUPDR_PUPD13_Pos)   /*!< 0x08000000 */

#define GPIO_ODR_OD3_Pos                     (3U)
#define GPIO_ODR_OD3_Msk                     (0x1U << GPIO_ODR_OD3_Pos)        /*!< 0x00000008 */
#define GPIO_ODR_OD3                         GPIO_ODR_OD3_Msk
#define GPIO_ODR_OD4_Pos                     (4U)
#define GPIO_ODR_OD4_Msk                     (0x1U << GPIO_ODR_OD4_Pos)        /*!< 0x00000010 */
#define GPIO_ODR_OD4                         GPIO_ODR_OD4_Msk
#define GPIO_ODR_OD5_Pos                     (5U)
#define GPIO_ODR_OD5_Msk                     (0x1U << GPIO_ODR_OD5_Pos)        /*!< 0x00000020 */
#define GPIO_ODR_OD5                         GPIO_ODR_OD5_Msk

#define GPIO_BSRR_BS3_Pos                    (3U)
#define GPIO_BSRR_BS3_Msk                    (0x1U << GPIO_BSRR_BS3_Pos)       /*!< 0x00000008 */
#define GPIO_BSRR_BS3                        GPIO_BSRR_BS3_Msk
#define GPIO_BSRR_BS4_Pos                    (4U)
#define GPIO_BSRR_BS4_Msk                    (0x1U << GPIO_BSRR_BS4_Pos)       /*!< 0x00000010 */
#define GPIO_BSRR_BS4                        GPIO_BSRR_BS4_Msk
#define GPIO_BSRR_BS5_Pos                    (5U)
#define GPIO_BSRR_BS5_Msk                    (0x1U << GPIO_BSRR_BS5_Pos)       /*!< 0x00000020 */
#define GPIO_BSRR_BS5                        GPIO_BSRR_BS5_Msk

#define GPIO_BRR_BR3_Pos                     (3U)
#define GPIO_BRR_BR3_Msk                     (0x1U << GPIO_BRR_BR3_Pos)        /*!< 0x00000008 */
#define GPIO_BRR_BR3                         GPIO_BRR_BR3_Msk
#define GPIO_BRR_BR4_Pos                     (4U)
#define GPIO_BRR_BR4_Msk                     (0x1U << GPIO_BRR_BR4_Pos)        /*!< 0x00000010 */
#define GPIO_BRR_BR4                         GPIO_BRR_BR4_Msk
#define GPIO_BRR_BR5_Pos                     (5U)
#define GPIO_BRR_BR5_Msk                     (0x1U << GPIO_BRR_BR5_Pos)        /*!< 0x00000020 */
#define GPIO_BRR_BR5                         GPIO_BRR_BR5_Msk
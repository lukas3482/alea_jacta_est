#include "rand.h"

#define RNG_BASE 0x60026000
#define RNG_DATA_REG_OFFSET 0xB0

#define LOWPOWER_MGR_BASE 0x60008000
#define RTC_CNTL_CLK_CONF_REG 0x70
#define RTC_CNTL_DIG_FOSC_EN_BIT 10
#define RTC_CNTL_DIG_FOSC_EN (0x1 << RTC_CNTL_DIG_FOSC_EN_BIT)

volatile uint32_t* pRngDataReg = (volatile uint32_t*) (RNG_BASE | RNG_DATA_REG_OFFSET);
volatile uint32_t* pRtcCntlClkConfReg = (volatile uint32_t*) (LOWPOWER_MGR_BASE | RTC_CNTL_CLK_CONF_REG);

uint32_t nextRand() {
    return *pRngDataReg;
}

void switchOnRtc20MClk() {
    *pRtcCntlClkConfReg |= RTC_CNTL_DIG_FOSC_EN;
}

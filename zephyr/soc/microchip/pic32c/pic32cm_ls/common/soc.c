/*
 * Copyright (c) 2026 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file soc.c
 * @brief Microchip PIC32CM LS00 family initialization code
 */

#include <zephyr/devicetree.h>
#include <soc.h>

#define SRAM0_NODE DT_CHOSEN(zephyr_sram)
#define SRAM0_BASE DT_REG_ADDR(SRAM0_NODE)
#define SRAM0_SIZE DT_REG_SIZE(SRAM0_NODE)

#define TIMEOUT_CYCLES 10000U

/**
 * @brief Configure system clocks for 48 MHz operation via FDPLL96M (1 MHz ref -> 48 MHz).
 */
void pic32cm_ls_clock_init(void)
{
	/* 1. Flash wait states: 2 wait states for 48 MHz operation at PL2 */
	NVMCTRL_REGS->NVMCTRL_CTRLB = (NVMCTRL_REGS->NVMCTRL_CTRLB & ~NVMCTRL_CTRLB_RWS_Msk) | NVMCTRL_CTRLB_RWS(2);

	/* 2. Switch Power Manager to Performance Level 2 (PL2) */
	PM_REGS->PM_PLCFG = PM_PLCFG_PLSEL_PL2;
	for (volatile uint32_t t = 0; t < TIMEOUT_CYCLES; t++) {
		if (PM_REGS->PM_INTFLAG & PM_INTFLAG_PLRDY_Msk) {
			break;
		}
	}

	/* 3. Configure and enable OSC16M at 16 MHz (ONDEMAND = 0) */
	OSCCTRL_REGS->OSCCTRL_OSC16MCTRL = OSCCTRL_OSC16MCTRL_FSEL_16MHZ | OSCCTRL_OSC16MCTRL_ENABLE(1);
	for (volatile uint32_t t = 0; t < TIMEOUT_CYCLES; t++) {
		if (OSCCTRL_REGS->OSCCTRL_STATUS & OSCCTRL_STATUS_OSC16MRDY_Msk) {
			break;
		}
	}

	/* 4. Configure GCLK1 to divide 16 MHz by 16 => 1.0 MHz reference for FDPLL */
	GCLK_REGS->GCLK_GENCTRL[1] = GCLK_GENCTRL_SRC_OSC16M | GCLK_GENCTRL_DIV(16) | GCLK_GENCTRL_GENEN(1);
	for (volatile uint32_t t = 0; t < TIMEOUT_CYCLES; t++) {
		if (!(GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL1_Msk)) {
			break;
		}
	}

	/* 5. Connect GCLK1 (1.0 MHz) to FDPLL peripheral channel (Channel 0) */
	GCLK_REGS->GCLK_PCHCTRL[OSCCTRL_GCLK_ID_FDPLL] = GCLK_PCHCTRL_GEN_GCLK1 | GCLK_PCHCTRL_CHEN(1);
	for (volatile uint32_t t = 0; t < TIMEOUT_CYCLES; t++) {
		if (GCLK_REGS->GCLK_PCHCTRL[OSCCTRL_GCLK_ID_FDPLL] & GCLK_PCHCTRL_CHEN_Msk) {
			break;
		}
	}

	/* 6. Configure FDPLL Reference to GCLK */
	OSCCTRL_REGS->OSCCTRL_DPLLCTRLB = OSCCTRL_DPLLCTRLB_REFCLK_GCLK | OSCCTRL_DPLLCTRLB_LTIME_DEFAULT;

	/* 7. Configure FDPLL Multiplier: 1.0 MHz * (47 + 1) = 48.0 MHz */
	OSCCTRL_REGS->OSCCTRL_DPLLRATIO = OSCCTRL_DPLLRATIO_LDR(47);
	for (volatile uint32_t t = 0; t < TIMEOUT_CYCLES; t++) {
		if (!(OSCCTRL_REGS->OSCCTRL_DPLLSYNCBUSY & OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Msk)) {
			break;
		}
	}

	/* 8. Enable FDPLL with ONDEMAND = 0 */
	OSCCTRL_REGS->OSCCTRL_DPLLCTRLA = OSCCTRL_DPLLCTRLA_ENABLE(1);
	for (volatile uint32_t t = 0; t < TIMEOUT_CYCLES; t++) {
		if (!(OSCCTRL_REGS->OSCCTRL_DPLLSYNCBUSY & OSCCTRL_DPLLSYNCBUSY_ENABLE_Msk)) {
			break;
		}
	}

	/* 9. Wait for FDPLL Lock and Clock Ready */
	for (volatile uint32_t t = 0; t < TIMEOUT_CYCLES; t++) {
		if ((OSCCTRL_REGS->OSCCTRL_DPLLSTATUS & (OSCCTRL_DPLLSTATUS_LOCK_Msk | OSCCTRL_DPLLSTATUS_CLKRDY_Msk)) ==
		    (OSCCTRL_DPLLSTATUS_LOCK_Msk | OSCCTRL_DPLLSTATUS_CLKRDY_Msk)) {
			break;
		}
	}

	/* 10. Switch GCLK0 to FDPLL96M (48 MHz) */
	GCLK_REGS->GCLK_GENCTRL[0] = GCLK_GENCTRL_SRC_FDPLL96M | GCLK_GENCTRL_GENEN(1);
	for (volatile uint32_t t = 0; t < TIMEOUT_CYCLES; t++) {
		if (!(GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL0_Msk)) {
			break;
		}
	}

	/* 11. Ensure CPU divisor is 1 */
	MCLK_REGS->MCLK_CPUDIV = MCLK_CPUDIV_CPUDIV_DIV1;
 	/* 12. Enable SERCOM3 & SERCOM0 Bus Clock in MCLK APBC */
	MCLK_REGS->MCLK_APBCMASK |= MCLK_APBCMASK_SERCOM0_Msk | MCLK_APBCMASK_SERCOM3_Msk;

	/* 13. Route GCLK0 (48 MHz) to SERCOM3 Core Clock (Channel 20) & SERCOM0 (Channel 17) */
	GCLK_REGS->GCLK_PCHCTRL[17] = GCLK_PCHCTRL_GEN_GCLK0 | GCLK_PCHCTRL_CHEN(1);
	GCLK_REGS->GCLK_PCHCTRL[20] = GCLK_PCHCTRL_GEN_GCLK0 | GCLK_PCHCTRL_CHEN(1);
		
}

/**
 * @brief Reset hook to run SoC-specific initialization.
 *
 * Clears SRAM with 16-bit Thumb stm instruction, then calls clock initialization.
 */
void __attribute__((naked)) soc_reset_hook(void)
{
	__asm__ volatile(
		"ldr r0, =%0\n"
		"ldr r1, =%1\n"
		"movs r2, #0\n"
		"1:\n"
		"stm r0!, {r2}\n"
		"cmp r0, r1\n"
		"bne 1b\n"
		"push {r4, lr}\n"
		"bl pic32cm_ls_clock_init\n"
		"pop {r4, pc}\n"
		:
		: "i"(SRAM0_BASE), "i"(SRAM0_BASE + SRAM0_SIZE)
		: "r0", "r1", "r2", "memory"
	);
}

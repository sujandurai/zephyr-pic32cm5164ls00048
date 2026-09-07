/*
 * Copyright (c) 2026 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_SOC_MICROCHIP_PIC32CM_LS00_H_
#define ZEPHYR_SOC_MICROCHIP_PIC32CM_LS00_H_

#ifndef _ASMLANGUAGE

#include <zephyr/types.h>

/* CMSIS device feature definitions are now provided by the DFP header */

#if defined(CONFIG_SOC_PIC32CM5164LS00048)
#include <pic32cm5164ls00048.h>
#else
#error "Library does not support the specified device."
#endif


#include <pic32cm_ls.h>

#endif /* _ASMLANGUAGE */

#endif /* ZEPHYR_SOC_MICROCHIP_PIC32CM_LS00_H_ */

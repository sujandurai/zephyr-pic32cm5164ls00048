# Copyright (c) 2026 Microchip Technology Inc.
#
# SPDX-License-Identifier: Apache-2.0

add_subdirectory(common)

zephyr_include_directories(${SOC_SERIES})
zephyr_include_directories(${ZEPHYR_HAL_MICROCHIP_MODULE_DIR}/packs/pic32c/pic32cm_ls/${SOC_SERIES}/include)

zephyr_library_sources(${SOC_SERIES}/soc.c)

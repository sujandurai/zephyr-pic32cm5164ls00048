# Copyright (c) 2026 Microchip Technology Inc.
#
# SPDX-License-Identifier: Apache-2.0

add_subdirectory(common)

zephyr_include_directories(${SOC_SERIES})

zephyr_include_directories(
    ${ZEPHYR_BASE}/../modules/hal/microchip/packs/pic32c/pic32cm_ls/pic32cm_ls00/include/pio
    ${ZEPHYR_BASE}/../modules/hal/microchip/packs/pic32c/pic32cm_ls/pic32cm_ls00/include/component
    ${ZEPHYR_BASE}/../modules/hal/microchip/packs/pic32c/pic32cm_ls/pic32cm_ls00/include/instance
)

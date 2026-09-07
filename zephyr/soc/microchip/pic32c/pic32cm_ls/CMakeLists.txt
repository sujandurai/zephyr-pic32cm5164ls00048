# Copyright (c) 2026 Microchip Technology Inc.
#
# SPDX-License-Identifier: Apache-2.0

add_subdirectory(common)

zephyr_include_directories(${SOC_SERIES})

zephyr_library_sources(${SOC_SERIES}/soc.c)

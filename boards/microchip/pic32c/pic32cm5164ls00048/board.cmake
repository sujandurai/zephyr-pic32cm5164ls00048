# Copyright (c) 2026 Microchip Technology Inc.
# SPDX-License-Identifier: Apache-2.0

board_runner_args(pyocd "--target=cortex_m" "--frequency=4000")
board_runner_args(openocd "--config=interface/cmsis-dap.cfg" "--config=target/atsaml1x.cfg")

include(${ZEPHYR_BASE}/boards/common/pyocd.board.cmake)
include(${ZEPHYR_BASE}/boards/common/openocd.board.cmake)

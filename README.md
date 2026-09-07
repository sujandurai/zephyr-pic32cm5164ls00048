# Zephyr RTOS Port for Microchip PIC32CM5164LS00048 (PIC32CM LS00 Curiosity Nano)

This repository contains the complete Zephyr RTOS port, board support, SoC definitions, peripheral drivers, sample applications, and documentation for the **Microchip PIC32CM5164LS00048** (ARM Cortex-M23) microcontroller on the **PIC32CM LS00 Curiosity Nano** evaluation kit.

---

## 📌 Features & Implementation Details

- **Core**: ARM Cortex-M23 @ 48 MHz via FDPLL96M (16 MHz OSC16M divided to 1.0 MHz reference $\times 48$).
- **Memory**: 512 KB Flash, 64 KB SRAM (with Thumb SRAM ECC reset initialization).
- **Peripherals Supported**:
  - GPIO (PORTA, PORTB) with Pinmux configuration
  - SERCOM0 & SERCOM3 (UART / Console)
  - SERCOM I2C & SPI
  - Power Manager (PM) Performance Level 2 (PL2) and NVMCTRL 2 wait states
- **Board Target**: `pic32cm_ls00_cnano`

---

## 📁 Repository Structure

```
├── port/                               # Direct port source files
│   ├── boards/pic32cm_ls00_cnano/      # Board DTS, defconfig, yaml, Kconfig
│   ├── soc/pic32cm_ls/                 # SoC initialization, clock setup (soc.c), Kconfig
│   ├── dts/pic32cm_ls/                 # Device Tree bindings (.dtsi)
│   └── hal_microchip_packs/            # Microchip DFP headers and CMakeLists
├── docs/                               # Technical reports, datasheets, comparison charts
│   ├── GC00_vs_LS00_Complete_Comparison.pdf
│   ├── PIC32CM5164LS00048_Zephyr_Porting_Technical_Doc.pdf
│   └── PIC32CM-LE00-LS00-LS60-Family-Data-Sheet-DS60001615.pdf
├── led_test/                           # Basic LED blinking test project
├── direct_pb02_test/                   # Direct PB02 pin toggle test
├── gpio_test/                          # GPIO input/output test application
├── i2c_project/                        # I2C peripheral test application
├── pir_project/                        # PIR motion sensor application
├── different_tasks/                    # Multithreaded Zephyr RTOS tasks example
├── project1/                           # Sample Zephyr application 1
├── Project2/                           # Sample Zephyr application 2
├── pwm/                                # PWM peripheral test
├── zephy_hml/                          # HTML documentation and preview
├── download_dfp.sh                     # Script to download Microchip DFP pack
├── generate_pdf_report.py              # Script to generate PDF porting report
└── zephyr/                             # Zephyr RTOS fork tree
```

---

## 🚀 Getting Started

### 1. Build an Application
To build a sample application (e.g. `led_test`):
```bash
cd /home/sujan/zephyrproject/led_test
west build -b pic32cm_ls00_cnano . -p
```

### 2. Flash to the Target Board
Using Microchip EDBG / Curiosity Nano onboard debugger:
```bash
west flash
```
Or directly using `edbg`:
```bash
edbg -b -t pic32cm_ls00 -pv -f build/zephyr/zephyr.bin
```

---

## 📄 Documentation & Reports
- [Complete GC00 vs LS00 Comparison Report](docs/GC00_vs_LS00_Complete_Comparison.pdf)
- [PIC32CM5164LS00048 Technical Porting Guide](docs/PIC32CM5164LS00048_Zephyr_Porting_Technical_Doc.pdf)
- [Interactive Porting Charts HTML](PIC32CM5164LS00048_Zephyr_Porting_Charts.html)

---

## 👤 Author
**Sujan D** - [GitHub Profile](https://github.com/sujandurai)

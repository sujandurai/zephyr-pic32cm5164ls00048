#!/bin/bash
# Download and extract the PIC32CM-LS DFP pack since the sandbox network is unreachable

set -e

WORK_DIR="/home/sujan/zephyrproject/tmp_pack"
DEST_DIR="/home/sujan/zephyrproject/modules/hal/microchip/packs/pic32c/pic32cm_ls/pic32cm_ls00/include"

mkdir -p "$WORK_DIR"
cd "$WORK_DIR"

echo "Downloading PIC32CM-LS DFP using Python..."
python3 -c "import urllib.request; urllib.request.urlretrieve('https://packs.download.microchip.com/Microchip.PIC32CM-LS_DFP.1.3.278.atpack', 'Microchip.PIC32CM-LS_DFP.1.3.278.atpack')"

echo "Extracting..."
unzip -q Microchip.PIC32CM-LS_DFP.1.3.278.atpack -d dfp_extracted

echo "Copying component and instance headers to hal_microchip..."
mkdir -p "$DEST_DIR"
cp -r dfp_extracted/saml11/include/component "$DEST_DIR/"
cp -r dfp_extracted/saml11/include/instance "$DEST_DIR/"

echo "Done! The real CMSIS headers are now in place."

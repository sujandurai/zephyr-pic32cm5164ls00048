config SOC_FAMILY_MICROCHIP_PIC32CM_LS00
	bool

config SOC_FAMILY
	default "microchip_pic32cm_ls00" if SOC_FAMILY_MICROCHIP_PIC32CM_LS00

rsource "*/Kconfig.soc"

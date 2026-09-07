from pyocd.core.helpers import ConnectHelper
import time

with ConnectHelper.session_with_chosen_probe(target_override="cortex_m") as session:
    t = session.target
    t.halt()
    t.write32(0x44800008, 0x8000)   # DIRSET: pin15 -> output
    t.write8(0x4480004f, 0x00)      # PINCFG: pin15 -> plain GPIO
    while True:
        t.write32(0x44800018, 0x8000)  # OUTSET: pin15 high
        time.sleep(0.5)
        t.write32(0x44800014, 0x8000)  # OUTCLR: pin15 low
        time.sleep(0.5)

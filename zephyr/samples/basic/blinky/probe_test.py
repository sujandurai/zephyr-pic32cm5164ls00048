from pyocd.core.helpers import ConnectHelper

with ConnectHelper.session_with_chosen_probe(target_override="cortex_m") as session:
    t = session.target
    t.halt()
    print("DIR :", hex(t.read32(0x44800000)))
    print("OUT :", hex(t.read32(0x44800010)))
    print("IN  :", hex(t.read32(0x44800020)))
    print("writing OUTSET with 0x0 (sets nothing, changes no pin)...")
    t.write32(0x44800018, 0x00000000)
    print("OUTSET write succeeded with a zero value")

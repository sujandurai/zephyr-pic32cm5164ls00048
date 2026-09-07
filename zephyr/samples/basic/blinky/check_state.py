from pyocd.core.helpers import ConnectHelper

with ConnectHelper.session_with_chosen_probe(target_override="cortex_m") as session:
    t = session.target
    t.halt()
    dscsr = t.read32(0xE000EE08)
    print("DSCSR:", hex(dscsr), " CDS(secure)=", (dscsr >> 16) & 1)
    dir_val = t.read32(0x44800000)
    print("PORTA DIR:", hex(dir_val))

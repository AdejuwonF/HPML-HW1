import matplotlib.pyplot as plt
import numpy as np


results = {
    "dp1 small": (2125606528, 8.502426),
    "dp1 large": (2130603776.000000 , 8.522415),
    "dp2 small": (7666349360.387095, 30.665397),
    "dp2 large": (4414528260.431974, 17.658113),
    "dp3 large": (12763953725.842808 , 51.055815),
    "dp3 small": (60867596288.000000 , 243.470385),
    "dp4 small": (7958973.152227303, 0.03183589260890921),
    "dp4 large": (7907670.219652294, 0.03163068087860918),
    "dp5 large": (2125245088.5938237, 8.500980354375296),
    "dp5 small": (2118608563.2152393, 8.474434252860958)
}

peak_flops = 200
peak_bandwidth = 30
peak_intensity = 200/30
plt.rcParams["figure.figsize"] = (10, 6)

plt.plot([0, peak_intensity], [0, peak_flops], label="DRAM 30 GB(s)")
plt.vlines([peak_intensity], [0], [peak_flops], label="Peak Intensity", linestyles="--")
plt.plot([peak_intensity, 10], [peak_flops, peak_flops], label="CPU 300 FLOP(s)")

for key, value in results.items():
    plt.plot((value[0]/1000000000.0) / value[1], (value[0]/1000000000.0), marker='o', linestyle="",  label=key)
    print((value[0]/1000000000.0) / value[1])

plt.xscale("log")
plt.yscale("log")
plt.legend()
plt.show()
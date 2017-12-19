# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\qureshis\Documents\CE 4950\attep5000\networking-project\networking.cydsn\networking.cyprj
# Date: Tue, 12 Dec 2017 19:23:32 GMT
#set_units -time ns
create_clock -name {CyILO} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {clock_1} -source [get_pins {ClockBlock/clk_sync}] -edges {1 241 481} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {Clock_3} -source [get_pins {ClockBlock/clk_sync}] -edges {1 321 641} -nominal_period 13333.333333333332 [list [get_pins {ClockBlock/dclk_glb_1}]]


# Component constraints for C:\Users\qureshis\Documents\CE 4950\attep5000\networking-project\networking.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\qureshis\Documents\CE 4950\attep5000\networking-project\networking.cydsn\networking.cyprj
# Date: Tue, 12 Dec 2017 19:23:29 GMT
# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\Spitfire54444444\Dropbox\Projets\Wavelab Technologies Inc\RnD\Projets\Auto Shut-OFF\Auto-Shut-OFF\Auto Shut-OFF_SOIC16.cydsn\Auto Shut-OFF_SOIC16.cyprj
# Date: Tue, 06 Dec 2016 09:53:06 GMT
#set_units -time ns
create_clock -name {PWM_CLOCK(FFB)} -period 83.333333333333329 -waveform {0 41.6666666666667} [list [get_pins {ClockBlock/ff_div_3}]]
create_clock -name {I2C_SCBCLK(FFB)} -period 583.33333333333326 -waveform {0 291.666666666667} [list [get_pins {ClockBlock/ff_div_0}]]
create_clock -name {CyILO} -period 25000 -waveform {0 12500} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFCLK} -period 25000 -waveform {0 12500} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFCLK} -period 83.333333333333329 -waveform {0 41.6666666666667} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySYSCLK} -period 83.333333333333329 -waveform {0 41.6666666666667} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {PWM_CLOCK} -source [get_pins {ClockBlock/hfclk}] -edges {1 2 3} [list]
create_generated_clock -name {I2C_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 7 13} -nominal_period 583.33333333333326 [list]


# Component constraints for C:\Users\Spitfire54444444\Dropbox\Projets\Wavelab Technologies Inc\RnD\Projets\Auto Shut-OFF\Auto-Shut-OFF\Auto Shut-OFF_SOIC16.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\Spitfire54444444\Dropbox\Projets\Wavelab Technologies Inc\RnD\Projets\Auto Shut-OFF\Auto-Shut-OFF\Auto Shut-OFF_SOIC16.cydsn\Auto Shut-OFF_SOIC16.cyprj
# Date: Tue, 06 Dec 2016 09:53:06 GMT

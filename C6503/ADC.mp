NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0014   0002 =      2. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0014  __idata_start
       0016  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0016   0220 =    544. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       000B  __start
       000B  __text_start
       002C  _exit
       002D  _delay_us
       0035  _port_init
       003A  _adc_init
       0044  _adc_isr
       005D  _init_devices
       0066  _main
       00AA  div32u
       00AC  mod32u
       00B0  div32s
       00B2  mod32s
       00DD  long_div_prolog
       00F0  long_div_epilog
       00FF  tst_R16_R19
       0104  tst_R24_R27
       0109  neg_R24_R27
       0112  neg32
       011B  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0002 =      2. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  ADC.c:LASTADCVAL
       0060  __data_start
       0062  __data_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0014 =     20. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\iccv7avr\lib\crtAVR.o	[ crtavr.s ]
ADC.o	[ ADC.c ]
<library>	[ div32.s, lneg.s ]

User Global Definitions

ram_end = 0x9f
hwstk_size = 0x1e

User Base Address Definitions

func_lit = 0x14
data = 0x60
eeprom:0.128


EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "IOT with a soft toch: Sound sensor"
Date "21/11/2019"
Rev ""
Comp "KU Leuven"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L SoundModulev2-rescue:VesperVM1010-vespervm1010 MK1
U 1 1 5D9B52DE
P 2800 3150
F 0 "MK1" H 2750 4250 60  0000 C CNN
F 1 "VesperVM1010" H 2800 4150 60  0000 C CNN
F 2 "vesper_vm1010:VESPER_VM1010" H 2800 3150 60  0001 C CNN
F 3 "" H 2800 3150 60  0001 C CNN
	1    2800 3150
	1    0    0    -1  
$EndComp
Text GLabel 3300 2600 2    50   Input ~ 0
GND
Text GLabel 2250 3050 0    50   Input ~ 0
GND
Text GLabel 3500 3050 2    50   Input ~ 0
mode
Text GLabel 4150 2900 2    50   Input ~ 0
VDDsensor
Wire Wire Line
	2250 2600 2250 2350
$Comp
L Device:C C3
U 1 1 5D9B9382
P 4700 2350
F 0 "C3" V 4448 2350 50  0000 C CNN
F 1 "47n" V 4539 2350 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4738 2200 50  0001 C CNN
F 3 "~" H 4700 2350 50  0001 C CNN
	1    4700 2350
	0    1    1    0   
$EndComp
Wire Wire Line
	4850 2350 5150 2350
$Comp
L Device:R R5
U 1 1 5D9B9389
P 5150 2500
F 0 "R5" H 5220 2546 50  0000 L CNN
F 1 "120k" H 5220 2455 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5080 2500 50  0001 C CNN
F 3 "~" H 5150 2500 50  0001 C CNN
	1    5150 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 2350 4550 2350
Wire Wire Line
	3300 2900 4000 2900
Wire Wire Line
	4000 2900 4000 3050
Connection ~ 4000 2900
$Comp
L Device:C C2
U 1 1 5D9BCC4D
P 4000 3200
F 0 "C2" H 4115 3246 50  0000 L CNN
F 1 "100 nF" H 4115 3155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4038 3050 50  0001 C CNN
F 3 "~" H 4000 3200 50  0001 C CNN
	1    4000 3200
	1    0    0    -1  
$EndComp
Text GLabel 4000 3350 3    50   Input ~ 0
GND
Connection ~ 5150 2350
$Comp
L Device:R R7
U 1 1 5D9BE525
P 6250 2850
F 0 "R7" V 6150 2850 50  0000 C CNN
F 1 "18k" V 6050 2850 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6180 2850 50  0001 C CNN
F 3 "~" H 6250 2850 50  0001 C CNN
	1    6250 2850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5150 2350 6550 2350
$Comp
L SoundModulev2-rescue:TLV341A-tlv341a U2
U 1 1 5D9BB2DF
P 6700 3250
F 0 "U2" H 6950 3897 60  0000 C CNN
F 1 "TLV341A" H 6950 3791 60  0000 C CNN
F 2 "tlv341-sot-23-6:TLV341 SOT-23-6" H 6700 3250 60  0001 C CNN
F 3 "" H 6700 3250 60  0001 C CNN
	1    6700 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 2100 7350 2100
Wire Wire Line
	7400 2100 7400 2150
Wire Wire Line
	7350 2100 7350 1700
Connection ~ 7350 2100
Wire Wire Line
	7350 2100 7400 2100
Text GLabel 7750 1700 2    50   Input ~ 0
VDDAMP
$Comp
L Device:C C5
U 1 1 5D9DA2FA
P 7650 1850
F 0 "C5" H 7765 1896 50  0000 L CNN
F 1 "100 nF" H 7765 1805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7688 1700 50  0001 C CNN
F 3 "~" H 7650 1850 50  0001 C CNN
	1    7650 1850
	1    0    0    -1  
$EndComp
Connection ~ 7650 1700
Wire Wire Line
	7650 1700 7750 1700
Text GLabel 7650 2000 3    50   Input ~ 0
GND
Wire Wire Line
	7350 1700 7650 1700
Wire Wire Line
	6550 2850 6450 2850
Wire Wire Line
	6450 2850 6450 3550
Connection ~ 6450 2850
Wire Wire Line
	6450 2850 6400 2850
$Comp
L Device:R R10
U 1 1 5D9E687B
P 7100 3550
F 0 "R10" V 6893 3550 50  0000 C CNN
F 1 "560k" V 6984 3550 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7030 3550 50  0001 C CNN
F 3 "~" H 7100 3550 50  0001 C CNN
	1    7100 3550
	0    1    1    0   
$EndComp
Wire Wire Line
	6950 3550 6450 3550
Wire Wire Line
	8050 3550 8050 2600
Wire Wire Line
	7250 3550 8050 3550
Text GLabel 7300 3100 3    50   Input ~ 0
GND
Wire Wire Line
	11050 2300 11050 1800
Text GLabel 11050 1650 1    50   Input ~ 0
VDDAMP
Wire Wire Line
	11050 1800 10850 1800
Connection ~ 11050 1800
Wire Wire Line
	11050 1800 11050 1650
$Comp
L Device:C C11
U 1 1 5D9F666D
P 10700 1800
F 0 "C11" V 10448 1800 50  0000 C CNN
F 1 "100 nF" V 10539 1800 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 10738 1650 50  0001 C CNN
F 3 "~" H 10700 1800 50  0001 C CNN
	1    10700 1800
	0    1    1    0   
$EndComp
Text GLabel 10550 1800 0    50   Input ~ 0
GND
Wire Wire Line
	10250 2600 9950 2600
$Comp
L Device:R R13
U 1 1 5D9F6675
P 9750 2600
F 0 "R13" V 9543 2600 50  0000 C CNN
F 1 "10k" V 9634 2600 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 9680 2600 50  0001 C CNN
F 3 "~" H 9750 2600 50  0001 C CNN
	1    9750 2600
	0    1    1    0   
$EndComp
$Comp
L Device:R R12
U 1 1 5D9F667B
P 9250 2600
F 0 "R12" V 9043 2600 50  0000 C CNN
F 1 "10k" V 9134 2600 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 9180 2600 50  0001 C CNN
F 3 "~" H 9250 2600 50  0001 C CNN
	1    9250 2600
	0    1    1    0   
$EndComp
Wire Wire Line
	9400 2600 9500 2600
$Comp
L Device:C C9
U 1 1 5D9F6682
P 9500 1850
F 0 "C9" H 9615 1896 50  0000 L CNN
F 1 "2.2 nF" H 9615 1805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9538 1700 50  0001 C CNN
F 3 "~" H 9500 1850 50  0001 C CNN
	1    9500 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 2600 9500 2000
Connection ~ 9500 2600
Wire Wire Line
	9500 2600 9600 2600
Text GLabel 11000 3350 3    50   Input ~ 0
GND
$Comp
L Device:R R15
U 1 1 5D9F6693
P 10600 3650
F 0 "R15" V 10393 3650 50  0000 C CNN
F 1 "1k" V 10484 3650 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 10530 3650 50  0001 C CNN
F 3 "~" H 10600 3650 50  0001 C CNN
	1    10600 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	10250 3650 10250 3950
$Comp
L Device:R R14
U 1 1 5D9F669E
P 10250 4100
F 0 "R14" H 10320 4146 50  0000 L CNN
F 1 "2.7k" H 10320 4055 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 10180 4100 50  0001 C CNN
F 3 "~" H 10250 4100 50  0001 C CNN
	1    10250 4100
	1    0    0    -1  
$EndComp
Text GLabel 12900 2850 2    50   Input ~ 0
Vanalog
Text GLabel 3250 7900 0    50   Input ~ 0
3V3
Text GLabel 3250 8000 0    50   Input ~ 0
GND
Text GLabel 3750 7900 2    50   Input ~ 0
SDA
Text GLabel 3750 8000 2    50   Input ~ 0
SCL
Text GLabel 3250 8100 0    50   Input ~ 0
INT
Text GLabel 850  6100 0    50   Input ~ 0
3V3
$Comp
L Device:C C1
U 1 1 5D9FC984
P 950 6250
F 0 "C1" H 1065 6296 50  0000 L CNN
F 1 "100 nF" H 1065 6205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 988 6100 50  0001 C CNN
F 3 "~" H 950 6250 50  0001 C CNN
	1    950  6250
	1    0    0    -1  
$EndComp
Text GLabel 950  6400 3    50   Input ~ 0
GND
Wire Wire Line
	850  6100 950  6100
Text GLabel 3050 6100 2    50   Input ~ 0
GND
$Comp
L Connector_Generic:Conn_01x06 J1
U 1 1 5DA00DCE
P 1200 7900
F 0 "J1" H 1280 7892 50  0000 L CNN
F 1 "ProgramPic" H 1000 7500 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 1200 7900 50  0001 C CNN
F 3 "~" H 1200 7900 50  0001 C CNN
	1    1200 7900
	1    0    0    -1  
$EndComp
Text GLabel 1000 7700 0    50   Input ~ 0
MCLR
Text GLabel 1550 6400 0    50   Input ~ 0
MCLR
Text GLabel 1000 7800 0    50   Input ~ 0
3V3
Text GLabel 1000 7900 0    50   Input ~ 0
GND
Text GLabel 1000 8000 0    50   Input ~ 0
ICSPDAT
Text GLabel 3050 6200 2    50   Input ~ 0
ICSPDAT
Text GLabel 1000 8100 0    50   Input ~ 0
ICSPCLK
Text GLabel 3050 6300 2    50   Input ~ 0
ICSPCLK
NoConn ~ 1000 8200
Text GLabel 3050 6900 2    50   Input ~ 0
SDA
Text GLabel 1850 7000 0    50   Input ~ 0
SCL
$Comp
L Device:C C10
U 1 1 5D9DD76E
P 9950 2750
F 0 "C10" H 10065 2796 50  0000 L CNN
F 1 "2.2 nF" H 10065 2705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9988 2600 50  0001 C CNN
F 3 "~" H 9950 2750 50  0001 C CNN
	1    9950 2750
	1    0    0    -1  
$EndComp
Connection ~ 9950 2600
Wire Wire Line
	9950 2600 9900 2600
Text GLabel 3050 6600 2    50   Input ~ 0
Vanalog
Text GLabel 1850 6900 0    50   Input ~ 0
INT
Wire Wire Line
	1550 6400 1600 6400
$Comp
L Device:R R4
U 1 1 5D9E656F
P 1600 6250
F 0 "R4" H 1670 6296 50  0000 L CNN
F 1 "10k" H 1670 6205 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1530 6250 50  0001 C CNN
F 3 "~" H 1600 6250 50  0001 C CNN
	1    1600 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 6100 1850 6100
Connection ~ 1600 6400
Wire Wire Line
	1600 6400 1850 6400
$Comp
L SoundModulev2-rescue:TLV341A-tlv341a U4
U 1 1 5D9ED282
P 10400 3500
F 0 "U4" H 11450 4550 60  0000 L CNN
F 1 "TLV341A" H 11400 4400 60  0000 L CNN
F 2 "tlv341-sot-23-6:TLV341 SOT-23-6" H 10400 3500 60  0001 C CNN
F 3 "" H 10400 3500 60  0001 C CNN
	1    10400 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	10250 3100 10250 3650
Wire Wire Line
	10250 3650 10450 3650
Connection ~ 10250 3650
Wire Wire Line
	11750 2850 11750 3650
Wire Wire Line
	10750 3650 11750 3650
Connection ~ 11750 2850
Wire Wire Line
	11000 2350 11000 2300
Wire Wire Line
	11000 2300 11050 2300
Wire Wire Line
	11100 2300 11100 2400
Wire Wire Line
	11100 2300 11050 2300
Connection ~ 11050 2300
NoConn ~ 1850 6200
NoConn ~ 1850 6300
Text GLabel 3050 6500 2    50   Input ~ 0
VDDsensor
$Comp
L SoundModulev2-rescue:PIC16F18446-PIC16F18446SSOP20pin U1
U 1 1 5DA0439B
P 2450 6400
F 0 "U1" H 2450 6965 50  0000 C CNN
F 1 "PIC16F18446" H 2450 6874 50  0000 C CNN
F 2 "PIC16F18446SSOPPIN:PIC16F18446SSOP20PIN" H 2400 6400 50  0001 C CNN
F 3 "" H 2400 6400 50  0001 C CNN
	1    2450 6400
	1    0    0    -1  
$EndComp
Text GLabel 1850 6700 0    50   Input ~ 0
mode
Wire Wire Line
	11750 1100 9500 1100
Wire Wire Line
	9500 1100 9500 1700
Wire Wire Line
	11750 1100 11750 2850
Wire Wire Line
	12900 2850 12700 2850
$Comp
L Connector_Generic:Conn_01x01 J7
U 1 1 5DAE528D
P 12700 2650
F 0 "J7" V 12664 2562 50  0000 R CNN
F 1 "VanalogTestPin" V 12573 2562 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 12700 2650 50  0001 C CNN
F 3 "~" H 12700 2650 50  0001 C CNN
	1    12700 2650
	0    -1   -1   0   
$EndComp
Connection ~ 12700 2850
Wire Wire Line
	3300 3050 3350 3050
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5DAE92D9
P 3400 3050
F 0 "#FLG01" H 3400 3125 50  0001 C CNN
F 1 "PWR_FLAG" H 3400 3223 50  0000 C CNN
F 2 "" H 3400 3050 50  0001 C CNN
F 3 "~" H 3400 3050 50  0001 C CNN
	1    3400 3050
	-1   0    0    1   
$EndComp
Connection ~ 3400 3050
Wire Wire Line
	3400 3050 3500 3050
Wire Wire Line
	5300 6800 5300 7000
$Comp
L Device:LED D1
U 1 1 5DB0D289
P 5300 7150
F 0 "D1" V 5339 7033 50  0000 R CNN
F 1 "LED" V 5248 7033 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5300 7150 50  0001 C CNN
F 3 "~" H 5300 7150 50  0001 C CNN
	1    5300 7150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R6
U 1 1 5DB0DF3B
P 5300 7450
F 0 "R6" H 5370 7496 50  0000 L CNN
F 1 "470" H 5370 7405 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5230 7450 50  0001 C CNN
F 3 "~" H 5300 7450 50  0001 C CNN
	1    5300 7450
	1    0    0    -1  
$EndComp
Text GLabel 5300 7600 3    50   Input ~ 0
GND
Text GLabel 5300 6800 1    50   Input ~ 0
LEDdebug
Text GLabel 3050 7000 2    50   Input ~ 0
LEDdebug
NoConn ~ 3750 8100
$Comp
L Connector_Generic:Conn_02x03_Top_Bottom J5
U 1 1 5DCA8361
P 3450 8000
F 0 "J5" H 3500 8317 50  0000 C CNN
F 1 "Conn_02x03_Top_Bottom" H 3500 8226 50  0000 C CNN
F 2 "ConnectorHorizontalPcb:ConnectorHorizontalPcb" H 3450 8000 50  0001 C CNN
F 3 "~" H 3450 8000 50  0001 C CNN
	1    3450 8000
	1    0    0    -1  
$EndComp
Wire Notes Line
	2550 7350 2550 8600
Text Notes 800  7550 0    79   ~ 0
Pickit program connector
Text Notes 2900 7550 0    79   ~ 0
Motherboard connector\n
Wire Wire Line
	950  6100 1600 6100
Connection ~ 950  6100
Connection ~ 1600 6100
Wire Notes Line
	4500 5400 4500 8600
Text Notes 2050 5600 0    79   ~ 0
PIC16F18446
Wire Notes Line
	6100 5400 6100 8600
Text Notes 5050 5800 0    79   ~ 0
Debug led
Text Notes 3750 1900 0    79   ~ 0
Analog sound sense circuit
$Comp
L Connector_Generic:Conn_01x06 J3
U 1 1 5DE210CD
P 2050 7900
F 0 "J3" H 2130 7892 50  0000 L CNN
F 1 "ProgramPic" H 1850 7500 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 2050 7900 50  0001 C CNN
F 3 "~" H 2050 7900 50  0001 C CNN
	1    2050 7900
	1    0    0    -1  
$EndComp
Text GLabel 1850 7700 0    50   Input ~ 0
MCLR
Text GLabel 1850 7800 0    50   Input ~ 0
3V3
Text GLabel 1850 7900 0    50   Input ~ 0
GND
Text GLabel 1850 8000 0    50   Input ~ 0
ICSPDAT
Text GLabel 1850 8100 0    50   Input ~ 0
ICSPCLK
NoConn ~ 1850 8200
$Comp
L SoundModulev2-rescue:TLV341A-tlv341a U3
U 1 1 5E8C4531
P 7450 8050
F 0 "U3" H 8844 8753 60  0000 L CNN
F 1 "TLV341A" H 8844 8647 60  0000 L CNN
F 2 "tlv341-sot-23-6:TLV341 SOT-23-6" H 7450 8050 60  0001 C CNN
F 3 "" H 7450 8050 60  0001 C CNN
	1    7450 8050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 5E8C510E
P 6450 6900
F 0 "R8" H 6520 6946 50  0000 L CNN
F 1 "10k" H 6520 6855 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6380 6900 50  0001 C CNN
F 3 "~" H 6450 6900 50  0001 C CNN
	1    6450 6900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 5E8C57F3
P 6450 7400
F 0 "R9" H 6520 7446 50  0000 L CNN
F 1 "10k" H 6520 7355 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6380 7400 50  0001 C CNN
F 3 "~" H 6450 7400 50  0001 C CNN
	1    6450 7400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 7050 6450 7150
Text GLabel 6450 7550 3    79   Input ~ 0
GND
Text GLabel 6450 6750 1    50   Input ~ 0
VDDBIAS
Wire Wire Line
	6450 7150 6850 7150
Connection ~ 6450 7150
Wire Wire Line
	6450 7150 6450 7250
Wire Wire Line
	8050 6900 8050 6800
Wire Wire Line
	8050 6800 8100 6800
Wire Wire Line
	8150 6800 8150 6950
Connection ~ 8100 6800
Wire Wire Line
	8100 6800 8150 6800
Text GLabel 8100 6350 1    50   Input ~ 0
VDDBIASAMP
Wire Wire Line
	7150 7650 7150 8250
Wire Wire Line
	7150 8250 8900 8250
Wire Wire Line
	8900 8250 8900 7400
Wire Wire Line
	8900 7400 8800 7400
Wire Wire Line
	7150 7650 7300 7650
Wire Wire Line
	8900 7400 9150 7400
Connection ~ 8900 7400
Text GLabel 8050 7900 3    79   Input ~ 0
GND
Text GLabel 9350 7400 2    79   Input ~ 0
biasvoltage
Wire Wire Line
	8100 6350 8100 6650
$Comp
L Device:C C6
U 1 1 5E8D06FC
P 8250 6650
F 0 "C6" V 7998 6650 50  0000 C CNN
F 1 "100 nF" V 8089 6650 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8288 6500 50  0001 C CNN
F 3 "~" H 8250 6650 50  0001 C CNN
	1    8250 6650
	0    1    1    0   
$EndComp
Connection ~ 8100 6650
Wire Wire Line
	8100 6650 8100 6800
Text GLabel 8400 6650 2    79   Input ~ 0
GND
Text GLabel 5150 2650 3    79   Input ~ 0
biasvoltage
Text GLabel 6100 2850 0    79   Input ~ 0
biasvoltage
$Comp
L Device:C C7
U 1 1 5E8D26CC
P 8400 2600
F 0 "C7" V 8148 2600 50  0000 C CNN
F 1 "47n" V 8239 2600 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8438 2450 50  0001 C CNN
F 3 "~" H 8400 2600 50  0001 C CNN
	1    8400 2600
	0    1    1    0   
$EndComp
$Comp
L Device:R R11
U 1 1 5E8D26D2
P 8850 2750
F 0 "R11" H 8920 2796 50  0000 L CNN
F 1 "120k" H 8920 2705 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 8780 2750 50  0001 C CNN
F 3 "~" H 8850 2750 50  0001 C CNN
	1    8850 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 2600 8250 2600
Connection ~ 8050 2600
Wire Wire Line
	8550 2600 8850 2600
Wire Wire Line
	8850 2600 9100 2600
Connection ~ 8850 2600
$Comp
L Device:C C12
U 1 1 5E8DC842
P 11900 2850
F 0 "C12" V 11648 2850 50  0000 C CNN
F 1 "47n" V 11739 2850 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 11938 2700 50  0001 C CNN
F 3 "~" H 11900 2850 50  0001 C CNN
	1    11900 2850
	0    1    1    0   
$EndComp
$Comp
L Device:R R16
U 1 1 5E8DC848
P 12350 3000
F 0 "R16" H 12420 3046 50  0000 L CNN
F 1 "120k" H 12420 2955 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 12280 3000 50  0001 C CNN
F 3 "~" H 12350 3000 50  0001 C CNN
	1    12350 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	12050 2850 12350 2850
Wire Wire Line
	12350 2850 12700 2850
Connection ~ 12350 2850
Text GLabel 8850 2900 3    79   Input ~ 0
biasvoltage
Text GLabel 9950 2900 3    79   Input ~ 0
biasvoltage
Text GLabel 10250 4250 3    79   Input ~ 0
biasvoltage
Text GLabel 12350 3150 3    79   Input ~ 0
biasvoltage
Text GLabel 3750 2750 2    50   Input ~ 0
dout
Text GLabel 1850 6800 0    50   Input ~ 0
dout
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5E938882
P 3700 2750
F 0 "#FLG02" H 3700 2825 50  0001 C CNN
F 1 "PWR_FLAG" H 3700 2923 50  0000 C CNN
F 2 "" H 3700 2750 50  0001 C CNN
F 3 "~" H 3700 2750 50  0001 C CNN
	1    3700 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 2750 3700 2750
Wire Wire Line
	3700 2750 3600 2750
Connection ~ 3700 2750
Wire Notes Line
	450  7350 4500 7350
Wire Notes Line
	10200 5400 10200 8600
Wire Notes Line
	13550 500  450  500 
Wire Notes Line
	450  5400 13550 5400
Text Notes 7850 5800 0    79   ~ 0
Bias voltage
Text Notes 2650 4850 0    79   ~ 0
possible to change value by means of jumpers\npossible values: \n18k: 65 dB\n50k: 72 dB\n100k: 78 dB\nOPEN: 89 dB
Text Notes 6300 8450 0    79   ~ 0
een cap van 10 µF parallel met r9
Text Notes 10200 8600 1    79   ~ 0
een cap van 10 µF aan pin 4 van tlv
$Comp
L Device:C C4
U 1 1 5F32765A
P 6850 7400
F 0 "C4" H 6965 7446 50  0000 L CNN
F 1 "10 uF" H 6965 7355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6888 7250 50  0001 C CNN
F 3 "~" H 6850 7400 50  0001 C CNN
	1    6850 7400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 7250 6850 7150
Connection ~ 6850 7150
Wire Wire Line
	6850 7150 7300 7150
Text GLabel 6850 7550 3    79   Input ~ 0
GND
$Comp
L Device:C C8
U 1 1 5F32AADF
P 9150 7750
F 0 "C8" H 9265 7796 50  0000 L CNN
F 1 "10 uF" H 9265 7705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9188 7600 50  0001 C CNN
F 3 "~" H 9150 7750 50  0001 C CNN
	1    9150 7750
	1    0    0    -1  
$EndComp
Text GLabel 9150 7900 3    79   Input ~ 0
GND
Wire Wire Line
	9150 7600 9150 7400
Connection ~ 9150 7400
Wire Wire Line
	9150 7400 9350 7400
Text GLabel 3050 6700 2    50   Input ~ 0
VDDBIAS
Text GLabel 1850 6600 0    50   Input ~ 0
VDDAMP
$Comp
L Connector_Generic:Conn_01x01 J4
U 1 1 5F33104B
P 3350 3250
F 0 "J4" V 3222 3330 50  0000 L CNN
F 1 "Conn_01x01" V 3313 3330 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3350 3250 50  0001 C CNN
F 3 "~" H 3350 3250 50  0001 C CNN
	1    3350 3250
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J6
U 1 1 5F3339A4
P 3600 2550
F 0 "J6" V 3564 2462 50  0000 R CNN
F 1 "Conn_01x01" V 3473 2462 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3600 2550 50  0001 C CNN
F 3 "~" H 3600 2550 50  0001 C CNN
	1    3600 2550
	0    -1   -1   0   
$EndComp
Connection ~ 3600 2750
Wire Wire Line
	3600 2750 3300 2750
Wire Wire Line
	4000 2900 4150 2900
Text GLabel 3050 6800 2    50   Input ~ 0
VDDBIASAMP
Connection ~ 3350 3050
Wire Wire Line
	3350 3050 3400 3050
$Comp
L SamacSys_Parts:TS5A2066DCUR IC1
U 1 1 5F977482
P 11250 6700
F 0 "IC1" H 11250 6850 50  0000 C CNN
F 1 "TS5A2066DCUR" H 11150 6750 50  0000 C CNN
F 2 "SamacSys_Parts:SOP50P310X90-8N" H 12200 6800 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/ts5a2066.pdf" H 12200 6700 50  0001 L CNN
F 4 "TEXAS INSTRUMENTS - TS5A2066DCUR - IC, ANLG SW 10R DUAL SPST 8VSSOP" H 12200 6600 50  0001 L CNN "Description"
F 5 "0.9" H 12200 6500 50  0001 L CNN "Height"
F 6 "595-TS5A2066DCUR" H 12200 6400 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=595-TS5A2066DCUR" H 12200 6300 50  0001 L CNN "Mouser Price/Stock"
F 8 "Texas Instruments" H 12200 6200 50  0001 L CNN "Manufacturer_Name"
F 9 "TS5A2066DCUR" H 12200 6100 50  0001 L CNN "Manufacturer_Part_Number"
	1    11250 6700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5F9819CA
P 11750 7750
F 0 "R2" V 11543 7750 50  0000 C CNN
F 1 "36k" V 11634 7750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 11680 7750 50  0001 C CNN
F 3 "~" H 11750 7750 50  0001 C CNN
	1    11750 7750
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R1
U 1 1 5F984028
P 11750 6150
F 0 "R1" V 11543 6150 50  0000 C CNN
F 1 "36k" V 11634 6150 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 11680 6150 50  0001 C CNN
F 3 "~" H 11750 6150 50  0001 C CNN
	1    11750 6150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R17
U 1 1 5F98658B
P 12400 7750
F 0 "R17" V 12193 7750 50  0000 C CNN
F 1 "9k" V 12284 7750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 12330 7750 50  0001 C CNN
F 3 "~" H 12400 7750 50  0001 C CNN
	1    12400 7750
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R3
U 1 1 5F988A2A
P 12400 6150
F 0 "R3" V 12193 6150 50  0000 C CNN
F 1 "9k" V 12284 6150 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 12330 6150 50  0001 C CNN
F 3 "~" H 12400 6150 50  0001 C CNN
	1    12400 6150
	0    -1   -1   0   
$EndComp
Text GLabel 12700 7150 3    50   Input ~ 0
GND
Wire Wire Line
	12700 6850 12700 6750
Text GLabel 12700 6700 1    50   Input ~ 0
3V3
$Comp
L Device:C C13
U 1 1 5F98CA75
P 12700 7000
F 0 "C13" H 12815 7046 50  0000 L CNN
F 1 "100 nF" H 12815 6955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 12738 6850 50  0001 C CNN
F 3 "~" H 12700 7000 50  0001 C CNN
	1    12700 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	11550 7450 11550 7750
Wire Wire Line
	11550 7750 11600 7750
Wire Wire Line
	11950 7450 11950 7750
Wire Wire Line
	11950 7750 11900 7750
Wire Wire Line
	11950 7750 12250 7750
Connection ~ 11950 7750
Text Notes 12650 8000 0    79   ~ 0
GA2\n
Text Notes 12700 6050 0    79   ~ 0
GA1\n
Wire Wire Line
	12400 6900 12400 6750
Wire Wire Line
	12400 6750 12700 6750
Connection ~ 12700 6750
Wire Wire Line
	12700 6750 12700 6700
Wire Wire Line
	12400 7100 12400 7150
Wire Wire Line
	12400 7150 12700 7150
Wire Wire Line
	11600 6150 11550 6150
Wire Wire Line
	11550 6150 11550 6500
Wire Wire Line
	11950 6500 11950 6150
Wire Wire Line
	11900 6150 11950 6150
Connection ~ 11950 6150
Wire Wire Line
	11950 6150 12250 6150
Text Notes 10700 7300 0    79   ~ 0
To µC
Text GLabel 2250 2750 0    50   Input ~ 0
GA2
Text GLabel 2250 2900 0    50   Input ~ 0
GA1
Wire Wire Line
	12550 6150 12700 6150
Wire Wire Line
	12550 7750 12750 7750
Text GLabel 12750 7750 2    50   Input ~ 0
GA2
Text GLabel 12700 6150 2    50   Input ~ 0
GA1
Wire Notes Line
	450  8600 13550 8600
Wire Notes Line
	13550 500  13550 8600
Text Notes 10950 5800 0    79   ~ 0
Threshold set by resistor values\n
Text GLabel 3050 6400 2    50   Input ~ 0
THRESHOLD1
Text GLabel 1850 6500 0    50   Input ~ 0
THRESHOLD2
Text GLabel 11050 7050 0    50   Input ~ 0
THRESHOLD1
Text GLabel 11050 6900 0    50   Input ~ 0
THRESHOLD2
$Comp
L Device:R R18
U 1 1 5FAC9C8E
P 1350 3600
F 0 "R18" V 1143 3600 50  0000 C CNN
F 1 "500k" V 1234 3600 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1280 3600 50  0001 C CNN
F 3 "~" H 1350 3600 50  0001 C CNN
	1    1350 3600
	-1   0    0    1   
$EndComp
Text GLabel 1350 3450 1    50   Input ~ 0
dout
Text GLabel 1350 3750 3    50   Input ~ 0
VDDsensor
Text Notes 1100 3200 0    50   ~ 0
Pullup on DOUT
Text Notes 6300 5600 0    79   ~ 0
200ms to charge RC circuit
$EndSCHEMATC

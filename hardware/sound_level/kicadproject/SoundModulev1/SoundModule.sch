EESchema Schematic File Version 4
LIBS:SoundModule-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
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
L vespervm1010:VesperVM1010 MK1
U 1 1 5D9B52DE
P 1300 3050
F 0 "MK1" H 1250 4150 60  0000 C CNN
F 1 "VesperVM1010" H 1300 4050 60  0000 C CNN
F 2 "vesper_vm1010:VESPER_VM1010" H 1300 3050 60  0001 C CNN
F 3 "" H 1300 3050 60  0001 C CNN
	1    1300 3050
	1    0    0    -1  
$EndComp
Text GLabel 1800 2500 2    50   Input ~ 0
GND
Text GLabel 750  2950 0    50   Input ~ 0
GND
NoConn ~ 750  2650
NoConn ~ 750  2800
NoConn ~ 1800 2650
Text GLabel 2000 2950 2    50   Input ~ 0
mode
Text GLabel 2650 2800 2    50   Input ~ 0
VDDsensor
Wire Wire Line
	750  2500 750  2250
$Comp
L Device:C C3
U 1 1 5D9B9382
P 3200 2250
F 0 "C3" V 2948 2250 50  0000 C CNN
F 1 "47n" V 3039 2250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3238 2100 50  0001 C CNN
F 3 "~" H 3200 2250 50  0001 C CNN
	1    3200 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	3350 2250 3650 2250
$Comp
L Device:R R2
U 1 1 5D9B9389
P 3650 2400
F 0 "R2" H 3720 2446 50  0000 L CNN
F 1 "120k" H 3720 2355 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3580 2400 50  0001 C CNN
F 3 "~" H 3650 2400 50  0001 C CNN
	1    3650 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	750  2250 3050 2250
Wire Wire Line
	1800 2800 2500 2800
Wire Wire Line
	2500 2800 2500 2950
Connection ~ 2500 2800
Wire Wire Line
	2500 2800 2650 2800
$Comp
L Device:C C2
U 1 1 5D9BCC4D
P 2500 3100
F 0 "C2" H 2615 3146 50  0000 L CNN
F 1 "100 nF" H 2615 3055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2538 2950 50  0001 C CNN
F 3 "~" H 2500 3100 50  0001 C CNN
	1    2500 3100
	1    0    0    -1  
$EndComp
Text GLabel 3650 2550 3    50   Input ~ 0
GND
Text GLabel 2500 3250 3    50   Input ~ 0
GND
Connection ~ 3650 2250
Text GLabel 4600 2750 0    50   Input ~ 0
GND
$Comp
L Device:R R3
U 1 1 5D9BE525
P 4750 2750
F 0 "R3" V 4650 2750 50  0000 C CNN
F 1 "18k" V 4550 2750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4680 2750 50  0001 C CNN
F 3 "~" H 4750 2750 50  0001 C CNN
	1    4750 2750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3650 2250 5050 2250
$Comp
L tlv341a:TLV341A U2
U 1 1 5D9BB2DF
P 5200 3150
F 0 "U2" H 5450 3797 60  0000 C CNN
F 1 "TLV341A" H 5450 3691 60  0000 C CNN
F 2 "tlv341-sot-23-6:TLV341 SOT-23-6" H 5200 3150 60  0001 C CNN
F 3 "" H 5200 3150 60  0001 C CNN
	1    5200 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 2000 5850 2000
Wire Wire Line
	5900 2000 5900 2050
Wire Wire Line
	5850 2000 5850 1600
Connection ~ 5850 2000
Wire Wire Line
	5850 2000 5900 2000
Text GLabel 6250 1600 2    50   Input ~ 0
VDDsensor
$Comp
L Device:C C4
U 1 1 5D9DA2FA
P 6150 1750
F 0 "C4" H 6265 1796 50  0000 L CNN
F 1 "100 nF" H 6265 1705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6188 1600 50  0001 C CNN
F 3 "~" H 6150 1750 50  0001 C CNN
	1    6150 1750
	1    0    0    -1  
$EndComp
Connection ~ 6150 1600
Wire Wire Line
	6150 1600 6250 1600
Text GLabel 6150 1900 3    50   Input ~ 0
GND
Wire Wire Line
	5850 1600 6150 1600
Wire Wire Line
	5050 2750 4950 2750
Wire Wire Line
	4950 2750 4950 3450
Connection ~ 4950 2750
Wire Wire Line
	4950 2750 4900 2750
$Comp
L Device:R R5
U 1 1 5D9E687B
P 5600 3450
F 0 "R5" V 5393 3450 50  0000 C CNN
F 1 "560k" V 5484 3450 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5530 3450 50  0001 C CNN
F 3 "~" H 5600 3450 50  0001 C CNN
	1    5600 3450
	0    1    1    0   
$EndComp
Wire Wire Line
	5450 3450 4950 3450
Wire Wire Line
	6550 3450 6550 2500
Wire Wire Line
	5750 3450 6550 3450
Text GLabel 5800 3000 3    50   Input ~ 0
GND
Wire Wire Line
	9550 2200 9550 1700
Text GLabel 9550 1550 1    50   Input ~ 0
VDDsensor
Wire Wire Line
	9550 1700 9350 1700
Connection ~ 9550 1700
Wire Wire Line
	9550 1700 9550 1550
$Comp
L Device:C C7
U 1 1 5D9F666D
P 9200 1700
F 0 "C7" V 8948 1700 50  0000 C CNN
F 1 "100 nF" V 9039 1700 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9238 1550 50  0001 C CNN
F 3 "~" H 9200 1700 50  0001 C CNN
	1    9200 1700
	0    1    1    0   
$EndComp
Text GLabel 9050 1700 0    50   Input ~ 0
GND
Wire Wire Line
	8750 2500 8450 2500
$Comp
L Device:R R7
U 1 1 5D9F6675
P 8250 2500
F 0 "R7" V 8043 2500 50  0000 C CNN
F 1 "10k" V 8134 2500 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 8180 2500 50  0001 C CNN
F 3 "~" H 8250 2500 50  0001 C CNN
	1    8250 2500
	0    1    1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 5D9F667B
P 7750 2500
F 0 "R6" V 7543 2500 50  0000 C CNN
F 1 "10k" V 7634 2500 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7680 2500 50  0001 C CNN
F 3 "~" H 7750 2500 50  0001 C CNN
	1    7750 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	7900 2500 8000 2500
$Comp
L Device:C C5
U 1 1 5D9F6682
P 8000 1750
F 0 "C5" H 8115 1796 50  0000 L CNN
F 1 "2.2 nF" H 8115 1705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8038 1600 50  0001 C CNN
F 3 "~" H 8000 1750 50  0001 C CNN
	1    8000 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 2500 8000 1900
Connection ~ 8000 2500
Wire Wire Line
	8000 2500 8100 2500
Text GLabel 9500 3250 3    50   Input ~ 0
GND
$Comp
L Device:R R9
U 1 1 5D9F6693
P 9100 3550
F 0 "R9" V 8893 3550 50  0000 C CNN
F 1 "1k" V 8984 3550 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 9030 3550 50  0001 C CNN
F 3 "~" H 9100 3550 50  0001 C CNN
	1    9100 3550
	0    1    1    0   
$EndComp
Wire Wire Line
	8750 3550 8750 3850
$Comp
L Device:R R8
U 1 1 5D9F669E
P 8750 4000
F 0 "R8" H 8820 4046 50  0000 L CNN
F 1 "2.7k" H 8820 3955 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 8680 4000 50  0001 C CNN
F 3 "~" H 8750 4000 50  0001 C CNN
	1    8750 4000
	1    0    0    -1  
$EndComp
Text GLabel 8750 4150 3    50   Input ~ 0
GND
Wire Wire Line
	6550 2500 7600 2500
Connection ~ 6550 2500
Text GLabel 10700 2750 2    50   Input ~ 0
Vanalog
Text GLabel 3150 7050 0    50   Input ~ 0
3V3
Text GLabel 3150 7150 0    50   Input ~ 0
GND
Text GLabel 3650 7050 2    50   Input ~ 0
SDA
Text GLabel 3650 7150 2    50   Input ~ 0
SCL
Text GLabel 3150 7250 0    50   Input ~ 0
INT
Text GLabel 750  5250 0    50   Input ~ 0
3V3
$Comp
L Device:C C1
U 1 1 5D9FC984
P 850 5400
F 0 "C1" H 965 5446 50  0000 L CNN
F 1 "100 nF" H 965 5355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 888 5250 50  0001 C CNN
F 3 "~" H 850 5400 50  0001 C CNN
	1    850  5400
	1    0    0    -1  
$EndComp
Text GLabel 850  5550 3    50   Input ~ 0
GND
Wire Wire Line
	750  5250 850  5250
Text GLabel 2950 5250 2    50   Input ~ 0
GND
$Comp
L Connector_Generic:Conn_01x06 J1
U 1 1 5DA00DCE
P 1100 7050
F 0 "J1" H 1180 7042 50  0000 L CNN
F 1 "ProgramPic" H 900 6650 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 1100 7050 50  0001 C CNN
F 3 "~" H 1100 7050 50  0001 C CNN
	1    1100 7050
	1    0    0    -1  
$EndComp
Text GLabel 900  6850 0    50   Input ~ 0
MCLR
Text GLabel 1450 5550 0    50   Input ~ 0
MCLR
Text GLabel 900  6950 0    50   Input ~ 0
3V3
Text GLabel 900  7050 0    50   Input ~ 0
GND
Text GLabel 900  7150 0    50   Input ~ 0
ICSPDAT
Text GLabel 2950 5350 2    50   Input ~ 0
ICSPDAT
Text GLabel 900  7250 0    50   Input ~ 0
ICSPCLK
Text GLabel 2950 5450 2    50   Input ~ 0
ICSPCLK
NoConn ~ 900  7350
Text GLabel 2950 6050 2    50   Input ~ 0
SDA
Text GLabel 1750 6150 0    50   Input ~ 0
SCL
$Comp
L Device:C C6
U 1 1 5D9DD76E
P 8450 2650
F 0 "C6" H 8565 2696 50  0000 L CNN
F 1 "2.2 nF" H 8565 2605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8488 2500 50  0001 C CNN
F 3 "~" H 8450 2650 50  0001 C CNN
	1    8450 2650
	1    0    0    -1  
$EndComp
Connection ~ 8450 2500
Wire Wire Line
	8450 2500 8400 2500
Text GLabel 8450 2800 3    50   Input ~ 0
GND
Text GLabel 2950 5750 2    50   Input ~ 0
Vanalog
Text GLabel 1750 6050 0    50   Input ~ 0
INT
Wire Wire Line
	1450 5550 1500 5550
$Comp
L Device:R R1
U 1 1 5D9E656F
P 1500 5400
F 0 "R1" H 1570 5446 50  0000 L CNN
F 1 "10k" H 1570 5355 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1430 5400 50  0001 C CNN
F 3 "~" H 1500 5400 50  0001 C CNN
	1    1500 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 5250 1750 5250
Connection ~ 1500 5550
Wire Wire Line
	1500 5550 1750 5550
$Comp
L tlv341a:TLV341A U3
U 1 1 5D9ED282
P 8900 3400
F 0 "U3" H 9950 4450 60  0000 L CNN
F 1 "TLV341A" H 9900 4300 60  0000 L CNN
F 2 "tlv341-sot-23-6:TLV341 SOT-23-6" H 8900 3400 60  0001 C CNN
F 3 "" H 8900 3400 60  0001 C CNN
	1    8900 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 3000 8750 3550
Wire Wire Line
	8750 3550 8950 3550
Connection ~ 8750 3550
Wire Wire Line
	10250 2750 10250 3550
Wire Wire Line
	9250 3550 10250 3550
Connection ~ 10250 2750
Wire Wire Line
	9500 2250 9500 2200
Wire Wire Line
	9500 2200 9550 2200
Wire Wire Line
	9600 2200 9600 2300
Wire Wire Line
	9600 2200 9550 2200
Connection ~ 9550 2200
NoConn ~ 2950 5950
NoConn ~ 2950 5550
NoConn ~ 1750 5350
NoConn ~ 1750 5450
NoConn ~ 1750 5650
NoConn ~ 1750 5750
Text GLabel 2950 5650 2    50   Input ~ 0
VDDsensor
$Comp
L PIC16F18446SSOP20pin:PIC16F18446 U1
U 1 1 5DA0439B
P 2350 5550
F 0 "U1" H 2350 6115 50  0000 C CNN
F 1 "PIC16F18446" H 2350 6024 50  0000 C CNN
F 2 "PIC16F18446SSOPPIN:PIC16F18446SSOP20PIN" H 2300 5550 50  0001 C CNN
F 3 "" H 2300 5550 50  0001 C CNN
	1    2350 5550
	1    0    0    -1  
$EndComp
NoConn ~ 2950 5850
Text GLabel 1200 5850 0    50   Input ~ 0
mode
Wire Wire Line
	10250 1000 8000 1000
Wire Wire Line
	8000 1000 8000 1600
Wire Wire Line
	10250 1000 10250 2750
Wire Wire Line
	10700 2750 10500 2750
Wire Wire Line
	1200 5850 1750 5850
$Comp
L Connector_Generic:Conn_01x01 J4
U 1 1 5DAE528D
P 10500 2550
F 0 "J4" V 10464 2462 50  0000 R CNN
F 1 "VanalogTestPin" V 10373 2462 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 10500 2550 50  0001 C CNN
F 3 "~" H 10500 2550 50  0001 C CNN
	1    10500 2550
	0    -1   -1   0   
$EndComp
Connection ~ 10500 2750
Wire Wire Line
	10500 2750 10250 2750
Wire Wire Line
	1800 2950 1900 2950
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5DAE92D9
P 1900 2950
F 0 "#FLG01" H 1900 3025 50  0001 C CNN
F 1 "PWR_FLAG" H 1900 3123 50  0000 C CNN
F 2 "" H 1900 2950 50  0001 C CNN
F 3 "~" H 1900 2950 50  0001 C CNN
	1    1900 2950
	-1   0    0    1   
$EndComp
Connection ~ 1900 2950
Wire Wire Line
	1900 2950 2000 2950
NoConn ~ 1750 5950
Wire Wire Line
	5200 5950 5200 6150
$Comp
L Device:LED D1
U 1 1 5DB0D289
P 5200 6300
F 0 "D1" V 5239 6183 50  0000 R CNN
F 1 "LED" V 5148 6183 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5200 6300 50  0001 C CNN
F 3 "~" H 5200 6300 50  0001 C CNN
	1    5200 6300
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R4
U 1 1 5DB0DF3B
P 5200 6600
F 0 "R4" H 5270 6646 50  0000 L CNN
F 1 "470" H 5270 6555 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5130 6600 50  0001 C CNN
F 3 "~" H 5200 6600 50  0001 C CNN
	1    5200 6600
	1    0    0    -1  
$EndComp
Text GLabel 5200 6750 3    50   Input ~ 0
GND
Text GLabel 5200 5950 1    50   Input ~ 0
LEDdebug
Text GLabel 2950 6150 2    50   Input ~ 0
LEDdebug
NoConn ~ 3650 7250
$Comp
L Connector_Generic:Conn_02x03_Top_Bottom J3
U 1 1 5DCA8361
P 3350 7150
F 0 "J3" H 3400 7467 50  0000 C CNN
F 1 "Conn_02x03_Top_Bottom" H 3400 7376 50  0000 C CNN
F 2 "ConnectorHorizontalPcb:ConnectorHorizontalPcb" H 3350 7150 50  0001 C CNN
F 3 "~" H 3350 7150 50  0001 C CNN
	1    3350 7150
	1    0    0    -1  
$EndComp
Wire Notes Line
	500  500  500  7750
Wire Notes Line
	500  7750 6950 7750
Wire Notes Line
	6950 7750 6950 6500
Wire Notes Line
	6950 6500 11200 6500
Wire Notes Line
	11200 6500 11200 500 
Wire Notes Line
	11200 500  500  500 
Wire Notes Line
	2450 6500 2450 7750
Wire Notes Line
	500  6500 4400 6500
Text Notes 700  6700 0    79   ~ 0
Pickit program connector
Text Notes 2800 6700 0    79   ~ 0
Motherboard connector\n
Wire Wire Line
	850  5250 1500 5250
Connection ~ 850  5250
Connection ~ 1500 5250
Wire Notes Line
	4400 4550 4400 7750
Text Notes 1950 4750 0    79   ~ 0
PIC16F18446
Wire Notes Line
	6000 4550 6000 7750
Text Notes 4950 4950 0    79   ~ 0
Debug led
Wire Notes Line
	500  4550 11200 4550
Text Notes 1400 850  0    79   ~ 0
Analog sound sense circuit
$Comp
L Connector_Generic:Conn_01x06 J2
U 1 1 5DE210CD
P 1950 7050
F 0 "J2" H 2030 7042 50  0000 L CNN
F 1 "ProgramPic" H 1750 6650 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 1950 7050 50  0001 C CNN
F 3 "~" H 1950 7050 50  0001 C CNN
	1    1950 7050
	1    0    0    -1  
$EndComp
Text GLabel 1750 6850 0    50   Input ~ 0
MCLR
Text GLabel 1750 6950 0    50   Input ~ 0
3V3
Text GLabel 1750 7050 0    50   Input ~ 0
GND
Text GLabel 1750 7150 0    50   Input ~ 0
ICSPDAT
Text GLabel 1750 7250 0    50   Input ~ 0
ICSPCLK
NoConn ~ 1750 7350
$EndSCHEMATC

EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 2400 1050 1    50   Input ~ 0
BAT+
Text GLabel 2300 1200 1    50   Input ~ 0
VSTOR
$Comp
L Battery_Management:BQ25570 U2
U 1 1 5EDE08E4
P 2300 1900
F 0 "U2" H 2600 1050 50  0000 C CNN
F 1 "BQ25570" H 2600 1150 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-20-1EP_3.5x3.5mm_P0.5mm_EP2x2mm" H 2300 1700 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/bq25570.pdf" H 2700 3100 50  0001 C CNN
	1    2300 1900
	1    0    0    -1  
$EndComp
Text GLabel 850  3050 1    50   Input ~ 0
VSTOR
$Comp
L Device:C CSTOR1
U 1 1 5EDE6006
P 650 3300
F 0 "CSTOR1" H 765 3346 50  0000 L CNN
F 1 "4.7 uF" H 765 3255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 688 3150 50  0001 C CNN
F 3 "~" H 650 3300 50  0001 C CNN
	1    650  3300
	1    0    0    -1  
$EndComp
$Comp
L Device:C CBYP1
U 1 1 5EDE66C7
P 1100 3300
F 0 "CBYP1" H 1215 3346 50  0000 L CNN
F 1 "10 nF" H 1215 3255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1138 3150 50  0001 C CNN
F 3 "~" H 1100 3300 50  0001 C CNN
	1    1100 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	650  3150 850  3150
Wire Wire Line
	650  3450 850  3450
Text GLabel 850  3500 3    50   Input ~ 0
GND
Wire Wire Line
	850  3500 850  3450
Connection ~ 850  3450
Wire Wire Line
	850  3450 1100 3450
Wire Wire Line
	850  3050 850  3150
Connection ~ 850  3150
Wire Wire Line
	850  3150 1100 3150
$Comp
L Device:L L1
U 1 1 5EDE7A03
P 1300 1400
F 0 "L1" V 1119 1400 50  0000 C CNN
F 1 "22 uH" V 1210 1400 50  0000 C CNN
F 2 "inductor_744031220_22uH:Inductor_744031220_22uH" H 1300 1400 50  0001 C CNN
F 3 "~" H 1300 1400 50  0001 C CNN
	1    1300 1400
	0    1    1    0   
$EndComp
Wire Wire Line
	1450 1400 1700 1400
Wire Wire Line
	2200 1200 2200 1050
Wire Wire Line
	2200 1050 1800 1050
Wire Wire Line
	1050 1050 1050 1400
Wire Wire Line
	1050 1400 900  1400
Connection ~ 1050 1400
Text GLabel 900  1400 0    50   Input ~ 0
SOL+
$Comp
L Device:C CIN1
U 1 1 5EDE97C6
P 1100 1550
F 0 "CIN1" H 1215 1596 50  0000 L CNN
F 1 "4.7 uF" H 1215 1505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1138 1400 50  0001 C CNN
F 3 "~" H 1100 1550 50  0001 C CNN
	1    1100 1550
	1    0    0    -1  
$EndComp
Text GLabel 1100 1700 3    50   Input ~ 0
GND
Text GLabel 1700 1800 0    50   Input ~ 0
VSTOR
Text GLabel 2300 2600 3    50   Input ~ 0
GND
$Comp
L Device:C CREF1
U 1 1 5EDEB4AF
P 1400 2550
F 0 "CREF1" H 1515 2596 50  0000 L CNN
F 1 "10 nF" H 1515 2505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1438 2400 50  0001 C CNN
F 3 "~" H 1400 2550 50  0001 C CNN
	1    1400 2550
	1    0    0    -1  
$EndComp
Text GLabel 1400 2700 3    50   Input ~ 0
GND
Wire Wire Line
	1400 2400 1700 2400
$Comp
L Device:L L2
U 1 1 5EDEDC2A
P 4000 1400
F 0 "L2" V 3819 1400 50  0000 C CNN
F 1 "10 uH" V 3910 1400 50  0000 C CNN
F 2 "Inductor_744029100_10uH:Inductor_744029100_10uH" H 4000 1400 50  0001 C CNN
F 3 "~" H 4000 1400 50  0001 C CNN
	1    4000 1400
	0    1    1    0   
$EndComp
Wire Wire Line
	4150 1600 4150 1400
$Comp
L Device:C COUT1
U 1 1 5EDEE5E4
P 4150 1750
F 0 "COUT1" H 4265 1796 50  0000 L CNN
F 1 "22 uF" H 4265 1705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4188 1600 50  0001 C CNN
F 3 "~" H 4150 1750 50  0001 C CNN
	1    4150 1750
	1    0    0    -1  
$EndComp
Connection ~ 4150 1600
Text GLabel 4150 1900 3    50   Input ~ 0
GND
Text GLabel 900  2000 0    50   Input ~ 0
VUSB
Text GLabel 1700 2100 0    50   Input ~ 0
VSTOR
$Comp
L Device:R ROV1
U 1 1 5EDF021A
P 3500 2450
F 0 "ROV1" H 3570 2496 50  0000 L CNN
F 1 "7.32 M" H 3570 2405 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3430 2450 50  0001 C CNN
F 3 "~" H 3500 2450 50  0001 C CNN
	1    3500 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:R ROK1
U 1 1 5EDF088F
P 3950 2450
F 0 "ROK1" H 4020 2496 50  0000 L CNN
F 1 "1.9 M" H 4020 2405 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3880 2450 50  0001 C CNN
F 3 "~" H 3950 2450 50  0001 C CNN
	1    3950 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:R ROV2
U 1 1 5EDF0B8E
P 3500 2850
F 0 "ROV2" H 3570 2896 50  0000 L CNN
F 1 "5.61 M" H 3570 2805 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3430 2850 50  0001 C CNN
F 3 "~" H 3500 2850 50  0001 C CNN
	1    3500 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:R ROK2
U 1 1 5EDF1096
P 3950 2850
F 0 "ROK2" H 4020 2896 50  0000 L CNN
F 1 "5.49 M" H 4020 2805 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3880 2850 50  0001 C CNN
F 3 "~" H 3950 2850 50  0001 C CNN
	1    3950 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 2000 3500 2000
Wire Wire Line
	3500 2000 3500 2300
Text GLabel 3500 3000 3    50   Input ~ 0
GND
$Comp
L Device:R ROK3
U 1 1 5EDF2C3E
P 3950 3250
F 0 "ROK3" H 4020 3296 50  0000 L CNN
F 1 "5.62M" H 4020 3205 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3880 3250 50  0001 C CNN
F 3 "~" H 3950 3250 50  0001 C CNN
	1    3950 3250
	1    0    0    -1  
$EndComp
Text GLabel 3950 3400 3    50   Input ~ 0
GND
Wire Wire Line
	3950 2600 3950 2700
Wire Wire Line
	3950 3000 3950 3100
Wire Wire Line
	3950 2300 4600 2300
Connection ~ 3950 2300
$Comp
L Device:R ROUT1
U 1 1 5EDF4059
P 4600 2450
F 0 "ROUT1" H 4670 2496 50  0000 L CNN
F 1 "8.25 M" H 4670 2405 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4530 2450 50  0001 C CNN
F 3 "~" H 4600 2450 50  0001 C CNN
	1    4600 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:R ROUT2
U 1 1 5EDF4212
P 4600 2850
F 0 "ROUT2" H 4670 2896 50  0000 L CNN
F 1 "4.75 M" H 4670 2805 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4530 2850 50  0001 C CNN
F 3 "~" H 4600 2850 50  0001 C CNN
	1    4600 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 2600 4600 2700
Text GLabel 4600 3000 3    50   Input ~ 0
GND
Text GLabel 2900 2100 2    50   Input ~ 0
HYST
Text GLabel 3950 2650 2    50   Input ~ 0
HYST
Text GLabel 2900 2200 2    50   Input ~ 0
PROG
Text GLabel 3950 3050 2    50   Input ~ 0
PROG
Wire Wire Line
	3500 2600 3500 2650
Wire Wire Line
	2900 2300 3350 2300
Wire Wire Line
	3350 2300 3350 2650
Wire Wire Line
	3350 2650 3500 2650
Connection ~ 3500 2650
Wire Wire Line
	3500 2650 3500 2700
Text GLabel 4600 2650 2    50   Input ~ 0
SET
Text GLabel 2900 2400 2    50   Input ~ 0
SET
Wire Wire Line
	3500 2300 3950 2300
Connection ~ 3500 2300
Text GLabel 2900 1800 2    50   Input ~ 0
VBAT_OK_TO_MCU
Wire Wire Line
	2900 1400 3850 1400
Wire Wire Line
	2900 1600 3850 1600
$Comp
L Power_module_v1-rescue:PIC16F18446-PIC16F18446SSOP20pin U4
U 1 1 5EDFC64B
P 8350 2600
F 0 "U4" H 8350 3165 50  0000 C CNN
F 1 "PIC16F18446" H 8350 3074 50  0000 C CNN
F 2 "PIC16F18446SSOPPIN:PIC16F18446SSOP20PIN" H 8300 2600 50  0001 C CNN
F 3 "" H 8300 2600 50  0001 C CNN
	1    8350 2600
	1    0    0    -1  
$EndComp
Text Notes 2000 3700 0    50   ~ 0
USB charger IC
$Comp
L Connector:USB_B_Micro J3
U 1 1 5EE0210B
P 10100 3050
F 0 "J3" H 10157 3517 50  0000 C CNN
F 1 "USB_B_Micro" H 10157 3426 50  0000 C CNN
F 2 "USB_Micro:USB_Micro" H 10250 3000 50  0001 C CNN
F 3 "~" H 10250 3000 50  0001 C CNN
	1    10100 3050
	1    0    0    -1  
$EndComp
NoConn ~ 10400 3050
NoConn ~ 10400 3150
NoConn ~ 10400 3250
NoConn ~ 10000 3450
Text GLabel 10100 3450 3    50   Input ~ 0
GND
Text GLabel 10400 2850 2    50   Input ~ 0
VUSB
Text GLabel 800  4150 0    50   Input ~ 0
VUSB
$Comp
L Device:C C1
U 1 1 5EE0A419
P 850 4300
F 0 "C1" H 965 4346 50  0000 L CNN
F 1 "1 uF" H 965 4255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 888 4150 50  0001 C CNN
F 3 "~" H 850 4300 50  0001 C CNN
	1    850  4300
	1    0    0    -1  
$EndComp
Text GLabel 850  4450 3    50   Input ~ 0
GND
Wire Wire Line
	800  4150 850  4150
Connection ~ 850  4150
Text GLabel 1950 4350 0    50   Input ~ 0
GND
Wire Wire Line
	850  4150 1950 4150
Wire Wire Line
	1950 4250 1250 4250
$Comp
L Device:R R2
U 1 1 5EE0EFAB
P 1250 4400
F 0 "R2" H 1320 4446 50  0000 L CNN
F 1 "1k" H 1320 4355 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1180 4400 50  0001 C CNN
F 3 "~" H 1250 4400 50  0001 C CNN
	1    1250 4400
	1    0    0    -1  
$EndComp
Text GLabel 1250 4550 3    50   Input ~ 0
GND
$Comp
L Device:R R3
U 1 1 5EE1009C
P 1500 4600
F 0 "R3" H 1570 4646 50  0000 L CNN
F 1 "2k" H 1570 4555 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1430 4600 50  0001 C CNN
F 3 "~" H 1500 4600 50  0001 C CNN
	1    1500 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 4450 1950 4450
Text GLabel 1500 4750 3    50   Input ~ 0
GND
NoConn ~ 2850 4550
$Comp
L Device:R R6
U 1 1 5EE1198D
P 3350 4400
F 0 "R6" H 3420 4446 50  0000 L CNN
F 1 "10k" H 3420 4355 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3280 4400 50  0001 C CNN
F 3 "~" H 3350 4400 50  0001 C CNN
	1    3350 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 4250 3350 4250
Text GLabel 3350 4550 3    50   Input ~ 0
GND
$Comp
L Device:C C4
U 1 1 5EE132FA
P 3800 4300
F 0 "C4" H 3915 4346 50  0000 L CNN
F 1 "1 uF" H 3915 4255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3838 4150 50  0001 C CNN
F 3 "~" H 3800 4300 50  0001 C CNN
	1    3800 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 4150 3800 4150
Wire Wire Line
	3800 4150 3950 4150
Connection ~ 3800 4150
Text GLabel 3800 4450 3    50   Input ~ 0
GND
Text GLabel 3950 4150 2    50   Input ~ 0
BAT+
$Comp
L Device:LED D1
U 1 1 5EE159F7
P 1950 4900
F 0 "D1" V 1897 4978 50  0000 L CNN
F 1 "LED" V 1988 4978 50  0000 L CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1950 4900 50  0001 C CNN
F 3 "~" H 1950 4900 50  0001 C CNN
	1    1950 4900
	0    1    1    0   
$EndComp
Wire Wire Line
	1950 4550 1950 4750
$Comp
L Device:R R4
U 1 1 5EE1732A
P 1950 5200
F 0 "R4" H 2020 5246 50  0000 L CNN
F 1 "1.5k" H 2020 5155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1880 5200 50  0001 C CNN
F 3 "~" H 1950 5200 50  0001 C CNN
	1    1950 5200
	1    0    0    -1  
$EndComp
Text GLabel 1950 5350 3    50   Input ~ 0
BAT+
Wire Wire Line
	2850 4350 3150 4350
Wire Wire Line
	3150 4350 3150 4750
$Comp
L Device:LED D2
U 1 1 5EE1A8AA
P 3150 4900
F 0 "D2" V 3097 4978 50  0000 L CNN
F 1 "LED" V 3188 4978 50  0000 L CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3150 4900 50  0001 C CNN
F 3 "~" H 3150 4900 50  0001 C CNN
	1    3150 4900
	0    1    1    0   
$EndComp
$Comp
L Device:R R5
U 1 1 5EE1A8B0
P 3150 5200
F 0 "R5" H 3220 5246 50  0000 L CNN
F 1 "1.5k" H 3220 5155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3080 5200 50  0001 C CNN
F 3 "~" H 3150 5200 50  0001 C CNN
	1    3150 5200
	1    0    0    -1  
$EndComp
Text GLabel 3150 5350 3    50   Input ~ 0
BAT+
Text GLabel 2850 4450 2    50   Input ~ 0
GND
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 5EE288FF
P 1000 650
F 0 "J1" H 1080 642 50  0000 L CNN
F 1 "Conn_01x02" H 1080 551 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 1000 650 50  0001 C CNN
F 3 "~" H 1000 650 50  0001 C CNN
	1    1000 650 
	1    0    0    -1  
$EndComp
Text GLabel 800  650  0    50   Input ~ 0
SOL+
Text GLabel 800  750  0    50   Input ~ 0
GND
$Comp
L Device:LED D3
U 1 1 5EE2BEC6
P 7950 4750
F 0 "D3" V 7989 4633 50  0000 R CNN
F 1 "LED" V 7898 4633 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7950 4750 50  0001 C CNN
F 3 "~" H 7950 4750 50  0001 C CNN
	1    7950 4750
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R14
U 1 1 5EE2CDB8
P 7950 5050
F 0 "R14" H 8020 5096 50  0000 L CNN
F 1 "470" H 8020 5005 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7880 5050 50  0001 C CNN
F 3 "~" H 7950 5050 50  0001 C CNN
	1    7950 5050
	1    0    0    -1  
$EndComp
Text GLabel 7950 5200 3    50   Input ~ 0
GND
Text GLabel 7950 4600 1    50   Input ~ 0
LED0
Text GLabel 8950 3200 2    50   Input ~ 0
LED0
Text GLabel 6800 5800 2    50   Input ~ 0
3V3
Text GLabel 8350 4600 1    50   Input ~ 0
LED1
$Comp
L Device:LED D4
U 1 1 5EE343C4
P 8350 4750
F 0 "D4" V 8389 4633 50  0000 R CNN
F 1 "LED" V 8298 4633 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8350 4750 50  0001 C CNN
F 3 "~" H 8350 4750 50  0001 C CNN
	1    8350 4750
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R15
U 1 1 5EE343CA
P 8350 5050
F 0 "R15" H 8420 5096 50  0000 L CNN
F 1 "470" H 8420 5005 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 8280 5050 50  0001 C CNN
F 3 "~" H 8350 5050 50  0001 C CNN
	1    8350 5050
	1    0    0    -1  
$EndComp
Text GLabel 8350 5200 3    50   Input ~ 0
GND
Text GLabel 8950 2800 2    50   Input ~ 0
LED1
Text GLabel 9150 2300 2    50   Input ~ 0
GND
$Comp
L Device:C C14
U 1 1 5EE39906
P 8350 1750
F 0 "C14" V 8098 1750 50  0000 C CNN
F 1 "100 nF" V 8189 1750 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8388 1600 50  0001 C CNN
F 3 "~" H 8350 1750 50  0001 C CNN
	1    8350 1750
	0    1    1    0   
$EndComp
Wire Wire Line
	7750 2300 7700 2300
Wire Wire Line
	7700 2300 7700 1750
Wire Wire Line
	7700 1750 8200 1750
Wire Wire Line
	8500 1750 9000 1750
Wire Wire Line
	9000 1750 9000 2300
Wire Wire Line
	9000 2300 8950 2300
Wire Wire Line
	9000 2300 9150 2300
Connection ~ 9000 2300
$Comp
L Connector_Generic:Conn_01x02 J4
U 1 1 5EE3DD3A
P 10100 4000
F 0 "J4" H 10180 3992 50  0000 L CNN
F 1 "Conn_01x02_battery" H 10180 3901 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 10100 4000 50  0001 C CNN
F 3 "~" H 10100 4000 50  0001 C CNN
	1    10100 4000
	1    0    0    -1  
$EndComp
Text GLabel 9900 4000 0    50   Input ~ 0
BAT+
Text GLabel 9900 4100 0    50   Input ~ 0
GND
$Comp
L Connector_Generic:Conn_02x03_Top_Bottom J2
U 1 1 5EE439E6
P 10000 6150
F 0 "J2" H 10050 6467 50  0000 C CNN
F 1 "Conn_02x03_motherboardconn" H 10050 6376 50  0000 C CNN
F 2 "ConnectorHorizontalPcb:ConnectorHorizontalPcb" H 10000 6150 50  0001 C CNN
F 3 "~" H 10000 6150 50  0001 C CNN
	1    10000 6150
	1    0    0    -1  
$EndComp
Text GLabel 10300 6250 2    50   Input ~ 0
3V3
Text GLabel 9800 6150 0    50   Input ~ 0
GND
Text GLabel 9800 6250 0    50   Input ~ 0
INT
Text GLabel 10300 6050 2    50   Input ~ 0
SDA
Text GLabel 10300 6150 2    50   Input ~ 0
SCL
Text GLabel 4150 1500 2    50   Input ~ 0
3V3BUCK
$Comp
L Power_module_v1-rescue:TPS22860-TPS22860 S3
U 1 1 5EE49BD8
P 5950 4000
F 0 "S3" H 6200 4475 50  0000 C CNN
F 1 "TPS22860" H 6200 4384 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6_Handsoldering" H 5950 4000 50  0001 C CNN
F 3 "" H 5950 4000 50  0001 C CNN
	1    5950 4000
	1    0    0    -1  
$EndComp
$Comp
L Power_module_v1-rescue:TPS22860-TPS22860 S2
U 1 1 5EE4AA8C
P 5900 5850
F 0 "S2" H 6150 6325 50  0000 C CNN
F 1 "TPS22860" H 6150 6234 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6_Handsoldering" H 5900 5850 50  0001 C CNN
F 3 "" H 5900 5850 50  0001 C CNN
	1    5900 5850
	1    0    0    -1  
$EndComp
NoConn ~ 5800 5800
NoConn ~ 5850 3950
Text GLabel 6850 3900 2    50   Input ~ 0
BAT+
Wire Wire Line
	5200 3750 5200 4200
$Comp
L Device:R R9
U 1 1 5EE4FD9F
P 5200 4350
F 0 "R9" H 5270 4396 50  0000 L CNN
F 1 "10k" H 5270 4305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5130 4350 50  0001 C CNN
F 3 "~" H 5200 4350 50  0001 C CNN
	1    5200 4350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R10
U 1 1 5EE503F3
P 5200 4800
F 0 "R10" H 5270 4846 50  0000 L CNN
F 1 "8.2k" H 5270 4755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5130 4800 50  0001 C CNN
F 3 "~" H 5200 4800 50  0001 C CNN
	1    5200 4800
	1    0    0    -1  
$EndComp
Text GLabel 5200 4950 3    50   Input ~ 0
GND
Text GLabel 5850 3850 0    50   Input ~ 0
GND
Wire Wire Line
	5200 4500 5200 4650
Text GLabel 5200 4550 2    50   Input ~ 0
BAT_VOLTAGE
Text GLabel 7750 2800 0    50   Input ~ 0
BAT_VOLTAGE
Wire Wire Line
	6550 3850 6550 3900
Wire Wire Line
	6550 3900 6700 3900
Connection ~ 6550 3900
Wire Wire Line
	6550 3900 6550 3950
$Comp
L Device:C C12
U 1 1 5EE548FE
P 6700 4050
F 0 "C12" H 6815 4096 50  0000 L CNN
F 1 "1 uF" H 6815 4005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6738 3900 50  0001 C CNN
F 3 "~" H 6700 4050 50  0001 C CNN
	1    6700 4050
	1    0    0    -1  
$EndComp
Connection ~ 6700 3900
Wire Wire Line
	6700 3900 6850 3900
Text GLabel 6700 4200 3    50   Input ~ 0
GND
Text GLabel 7750 3000 0    50   Input ~ 0
BAT_MEAS_EN
Text GLabel 7400 3750 2    50   Input ~ 0
BAT_MEAS_EN
Wire Wire Line
	5100 5600 5100 6050
$Comp
L Device:R R7
U 1 1 5EE5A834
P 5100 6200
F 0 "R7" H 5170 6246 50  0000 L CNN
F 1 "10k" H 5170 6155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5030 6200 50  0001 C CNN
F 3 "~" H 5100 6200 50  0001 C CNN
	1    5100 6200
	1    0    0    -1  
$EndComp
Text GLabel 5100 6800 3    50   Input ~ 0
GND
Wire Wire Line
	5100 6350 5100 6500
Text GLabel 5100 6400 2    50   Input ~ 0
LDR_VOLTAGE
Text GLabel 7750 2900 0    50   Input ~ 0
LDR_VOLTAGE
Text GLabel 9250 2700 2    50   Input ~ 0
LDR_MEAS_EN
Text GLabel 7250 5600 2    50   Input ~ 0
LDR_MEAS_EN
Wire Wire Line
	6500 5800 6650 5800
$Comp
L Device:C C11
U 1 1 5EE5C853
P 6650 5950
F 0 "C11" H 6765 5996 50  0000 L CNN
F 1 "1 uF" H 6765 5905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6688 5800 50  0001 C CNN
F 3 "~" H 6650 5950 50  0001 C CNN
	1    6650 5950
	1    0    0    -1  
$EndComp
Connection ~ 6650 5800
Wire Wire Line
	6650 5800 6800 5800
Text GLabel 6650 6100 3    50   Input ~ 0
GND
Wire Wire Line
	6500 5700 6500 5800
Connection ~ 6500 5800
Text GLabel 5800 5700 0    50   Input ~ 0
GND
Text GLabel 8950 2400 2    50   Input ~ 0
ICSPDAT
Text GLabel 8950 2500 2    50   Input ~ 0
ICSPCLK
Text GLabel 6950 2500 1    50   Input ~ 0
MCLR
Wire Wire Line
	7750 2600 7500 2600
$Comp
L Device:R R13
U 1 1 5EE62880
P 7500 2450
F 0 "R13" H 7570 2496 50  0000 L CNN
F 1 "10k" H 7570 2405 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7430 2450 50  0001 C CNN
F 3 "~" H 7500 2450 50  0001 C CNN
	1    7500 2450
	1    0    0    -1  
$EndComp
Connection ~ 7500 2600
Wire Wire Line
	7500 2300 7700 2300
Connection ~ 7700 2300
NoConn ~ 7750 2400
NoConn ~ 7750 2500
NoConn ~ 8950 3000
NoConn ~ 8950 2900
NoConn ~ 8950 2600
$Comp
L Connector_Generic:Conn_01x06 J6
U 1 1 5EE6D381
P 10100 5250
F 0 "J6" H 10180 5242 50  0000 L CNN
F 1 "Conn_01x06_programmer" H 10180 5151 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 10100 5250 50  0001 C CNN
F 3 "~" H 10100 5250 50  0001 C CNN
	1    10100 5250
	1    0    0    -1  
$EndComp
Text GLabel 9900 5050 0    50   Input ~ 0
MCLR
Text GLabel 9900 5150 0    50   Input ~ 0
3V3
Text GLabel 9900 5350 0    50   Input ~ 0
ICSPDAT
Text GLabel 9900 5450 0    50   Input ~ 0
ICSPCLK
Text GLabel 9900 5250 0    50   Input ~ 0
GND
NoConn ~ 9900 5550
$Comp
L Connector_Generic:Conn_01x06 J5
U 1 1 5EE73010
P 10100 4600
F 0 "J5" H 10180 4592 50  0000 L CNN
F 1 "Conn_01x06_programmer" H 10180 4501 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 10100 4600 50  0001 C CNN
F 3 "~" H 10100 4600 50  0001 C CNN
	1    10100 4600
	1    0    0    -1  
$EndComp
Text GLabel 9900 4400 0    50   Input ~ 0
MCLR
Text GLabel 9900 4500 0    50   Input ~ 0
3V3
Text GLabel 9900 4700 0    50   Input ~ 0
ICSPDAT
Text GLabel 9900 4800 0    50   Input ~ 0
ICSPCLK
Text GLabel 9900 4600 0    50   Input ~ 0
GND
NoConn ~ 9900 4900
$Comp
L Device:C C13
U 1 1 5EE87F8E
P 8350 1350
F 0 "C13" V 8098 1350 50  0000 C CNN
F 1 "10 uF" V 8189 1350 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8388 1200 50  0001 C CNN
F 3 "~" H 8350 1350 50  0001 C CNN
	1    8350 1350
	0    1    1    0   
$EndComp
Wire Wire Line
	7700 1350 8200 1350
Wire Wire Line
	8500 1350 9000 1350
Wire Wire Line
	9000 1350 9000 1750
Connection ~ 9000 1750
Wire Wire Line
	7700 1350 7700 1750
Connection ~ 7700 1750
Wire Wire Line
	1050 1400 1100 1400
Connection ~ 1100 1400
Wire Wire Line
	1100 1400 1150 1400
Wire Wire Line
	1700 2000 1000 2000
$Comp
L Device:R R1
U 1 1 5EE8E638
P 1000 2150
F 0 "R1" H 1070 2196 50  0000 L CNN
F 1 "10k" H 1070 2105 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 930 2150 50  0001 C CNN
F 3 "~" H 1000 2150 50  0001 C CNN
	1    1000 2150
	1    0    0    -1  
$EndComp
Connection ~ 1000 2000
Wire Wire Line
	1000 2000 900  2000
Text GLabel 1000 2300 3    50   Input ~ 0
GND
Text GLabel 7350 2300 0    50   Input ~ 0
3V3
Wire Wire Line
	7500 2300 7350 2300
Connection ~ 7500 2300
Wire Wire Line
	6550 3750 6650 3750
$Comp
L power:PWR_FLAG #FLG03
U 1 1 5EE987AC
P 6650 3750
F 0 "#FLG03" H 6650 3825 50  0001 C CNN
F 1 "PWR_FLAG" H 6650 3923 50  0000 C CNN
F 2 "" H 6650 3750 50  0001 C CNN
F 3 "~" H 6650 3750 50  0001 C CNN
	1    6650 3750
	1    0    0    -1  
$EndComp
Connection ~ 6650 3750
Wire Wire Line
	2400 1050 2400 1150
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5EE9AD75
P 2400 1150
F 0 "#FLG02" H 2400 1225 50  0001 C CNN
F 1 "PWR_FLAG" V 2400 1278 50  0000 L CNN
F 2 "" H 2400 1150 50  0001 C CNN
F 3 "~" H 2400 1150 50  0001 C CNN
	1    2400 1150
	0    1    1    0   
$EndComp
Connection ~ 2400 1150
Wire Wire Line
	2400 1150 2400 1200
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5EEA609F
P 1800 1050
F 0 "#FLG01" H 1800 1125 50  0001 C CNN
F 1 "PWR_FLAG" H 1800 1223 50  0000 C CNN
F 2 "" H 1800 1050 50  0001 C CNN
F 3 "~" H 1800 1050 50  0001 C CNN
	1    1800 1050
	1    0    0    -1  
$EndComp
Connection ~ 1800 1050
Wire Wire Line
	1800 1050 1050 1050
Text GLabel 8950 3100 2    50   Input ~ 0
SDA
Text GLabel 7750 3200 0    50   Input ~ 0
SCL
Text GLabel 7750 3100 0    50   Input ~ 0
INT
Wire Wire Line
	9200 2700 8950 2700
Wire Wire Line
	9200 2700 9250 2700
Connection ~ 9200 2700
$Comp
L power:PWR_FLAG #FLG04
U 1 1 5EE9D631
P 9200 2700
F 0 "#FLG04" H 9200 2775 50  0001 C CNN
F 1 "PWR_FLAG" H 9200 2873 50  0000 C CNN
F 2 "" H 9200 2700 50  0001 C CNN
F 3 "~" H 9200 2700 50  0001 C CNN
	1    9200 2700
	1    0    0    -1  
$EndComp
$Comp
L Power_module_v1-rescue:TPS705-tps7a05 U3
U 1 1 5EEB36FB
P 2550 6450
F 0 "U3" H 2775 6915 50  0000 C CNN
F 1 "TPS705" H 2775 6824 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5_HandSoldering" H 2550 6650 50  0001 C CNN
F 3 "" H 2550 6650 50  0001 C CNN
	1    2550 6450
	1    0    0    -1  
$EndComp
Text GLabel 1350 6250 0    50   Input ~ 0
BAT+
$Comp
L Jumper:SolderJumper_2_Open JP1
U 1 1 5EEB4D01
P 1500 6250
F 0 "JP1" H 1500 6455 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 1500 6364 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 1500 6250 50  0001 C CNN
F 3 "~" H 1500 6250 50  0001 C CNN
	1    1500 6250
	1    0    0    -1  
$EndComp
Text GLabel 2350 6350 0    50   Input ~ 0
GND
Wire Wire Line
	2000 6250 2000 6450
Wire Wire Line
	2000 6450 2350 6450
Connection ~ 2000 6250
Wire Wire Line
	2000 6250 2350 6250
$Comp
L Device:C C2
U 1 1 5EEBDE16
P 1700 6400
F 0 "C2" H 1815 6446 50  0000 L CNN
F 1 "1 uF" H 1815 6355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1738 6250 50  0001 C CNN
F 3 "~" H 1700 6400 50  0001 C CNN
	1    1700 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 6250 1700 6250
Connection ~ 1700 6250
Wire Wire Line
	1700 6250 2000 6250
Text GLabel 1700 6550 3    50   Input ~ 0
GND
NoConn ~ 3200 6450
Text GLabel 4050 6250 2    50   Input ~ 0
3V3
$Comp
L Jumper:SolderJumper_2_Open JP2
U 1 1 5EEC77AE
P 3900 6250
F 0 "JP2" H 3900 6050 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 3850 6150 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 3900 6250 50  0001 C CNN
F 3 "~" H 3900 6250 50  0001 C CNN
	1    3900 6250
	-1   0    0    1   
$EndComp
Wire Wire Line
	3200 6250 3550 6250
$Comp
L Device:C C3
U 1 1 5EECC235
P 3550 6450
F 0 "C3" H 3665 6496 50  0000 L CNN
F 1 "1 uF" H 3665 6405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3588 6300 50  0001 C CNN
F 3 "~" H 3550 6450 50  0001 C CNN
	1    3550 6450
	1    0    0    -1  
$EndComp
Text GLabel 3550 6600 3    50   Input ~ 0
GND
Wire Wire Line
	3550 6300 3550 6250
Connection ~ 3550 6250
Wire Wire Line
	3550 6250 3750 6250
Text GLabel 2400 4000 1    50   Input ~ 0
GND
$Comp
L Power_module_v1-rescue:BQ24040-BQ24040 U1
U 1 1 5EDFFF7A
P 2050 4550
F 0 "U1" H 2700 5150 50  0000 C CNN
F 1 "BQ24040" H 2700 5250 50  0000 C CNN
F 2 "BQ24040:BQ24040" H 2050 4550 50  0001 C CNN
F 3 "" H 2050 4550 50  0001 C CNN
	1    2050 4550
	1    0    0    -1  
$EndComp
Text Notes 2000 7400 0    50   ~ 0
Gebruik ldo ipv buck converter van solar charger\ndeze zorgt sporadisch voor een spanningsval dat niet gunstig is voor het circuit
Text GLabel 6350 1100 2    50   Input ~ 0
VBAT_OK_TO_MCU
$Comp
L Power_module_v1-rescue:TPS22860-TPS22860 S1
U 1 1 5F35450B
P 5750 1350
F 0 "S1" H 6000 1825 50  0000 C CNN
F 1 "TPS22860" H 6000 1734 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6_Handsoldering" H 5750 1350 50  0001 C CNN
F 3 "" H 5750 1350 50  0001 C CNN
	1    5750 1350
	1    0    0    -1  
$EndComp
Text GLabel 5650 1200 0    50   Input ~ 0
GND
NoConn ~ 5650 1300
$Comp
L Device:C C10
U 1 1 5F357778
P 6350 1450
F 0 "C10" H 6465 1496 50  0000 L CNN
F 1 "1 uF" H 6465 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6388 1300 50  0001 C CNN
F 3 "~" H 6350 1450 50  0001 C CNN
	1    6350 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 1200 6350 1300
Connection ~ 6350 1300
Text GLabel 6350 1600 3    50   Input ~ 0
GND
Text GLabel 6350 1250 2    50   Input ~ 0
3V3BUCK
Text GLabel 4800 1100 0    50   Input ~ 0
3V3
NoConn ~ 7750 2700
$Comp
L Device:C C5
U 1 1 5F361D8E
P 3850 1750
F 0 "C5" H 3965 1796 50  0000 L CNN
F 1 "470 uF" H 3965 1705 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 3888 1600 50  0001 C CNN
F 3 "~" H 3850 1750 50  0001 C CNN
	1    3850 1750
	1    0    0    -1  
$EndComp
Connection ~ 3850 1600
Wire Wire Line
	3850 1600 4150 1600
Text GLabel 3850 1900 3    50   Input ~ 0
GND
$Comp
L Device:C C6
U 1 1 5F36379B
P 4900 1350
F 0 "C6" H 5015 1396 50  0000 L CNN
F 1 "470 uF" H 5015 1305 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 4938 1200 50  0001 C CNN
F 3 "~" H 4900 1350 50  0001 C CNN
	1    4900 1350
	1    0    0    -1  
$EndComp
Text GLabel 4900 1500 3    50   Input ~ 0
GND
Wire Wire Line
	4800 1100 4900 1100
Wire Wire Line
	4900 1200 4900 1100
Connection ~ 4900 1100
Wire Wire Line
	6650 3750 7250 3750
$Comp
L Device:R R12
U 1 1 5F370B3A
P 7250 3900
F 0 "R12" H 7320 3946 50  0000 L CNN
F 1 "10k" H 7320 3855 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7180 3900 50  0001 C CNN
F 3 "~" H 7250 3900 50  0001 C CNN
	1    7250 3900
	1    0    0    -1  
$EndComp
Connection ~ 7250 3750
Wire Wire Line
	7250 3750 7400 3750
Text GLabel 7250 4050 3    50   Input ~ 0
GND
$Comp
L Device:R R11
U 1 1 5F372BE5
P 7200 5800
F 0 "R11" H 7270 5846 50  0000 L CNN
F 1 "10k" H 7270 5755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7130 5800 50  0001 C CNN
F 3 "~" H 7200 5800 50  0001 C CNN
	1    7200 5800
	1    0    0    -1  
$EndComp
Text GLabel 7200 5950 3    50   Input ~ 0
GND
Wire Wire Line
	7250 5600 7200 5600
Wire Wire Line
	7200 5650 7200 5600
Connection ~ 7200 5600
Wire Wire Line
	7200 5600 6500 5600
Wire Wire Line
	5200 3750 5400 3750
$Comp
L Device:C C9
U 1 1 5F3817DD
P 5400 3900
F 0 "C9" H 5515 3946 50  0000 L CNN
F 1 "1 uF" H 5515 3855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5438 3750 50  0001 C CNN
F 3 "~" H 5400 3900 50  0001 C CNN
	1    5400 3900
	1    0    0    -1  
$EndComp
Text GLabel 5400 4050 3    50   Input ~ 0
GND
Wire Wire Line
	5100 5600 5350 5600
$Comp
L Device:C C8
U 1 1 5F389DF9
P 5350 5750
F 0 "C8" H 5465 5796 50  0000 L CNN
F 1 "1 uF" H 5465 5705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5388 5600 50  0001 C CNN
F 3 "~" H 5350 5750 50  0001 C CNN
	1    5350 5750
	1    0    0    -1  
$EndComp
Text GLabel 5350 5900 3    50   Input ~ 0
GND
$Comp
L Device:C C7
U 1 1 5F38FE5B
P 5150 1250
F 0 "C7" H 5265 1296 50  0000 L CNN
F 1 "1 uF" H 5265 1205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5188 1100 50  0001 C CNN
F 3 "~" H 5150 1250 50  0001 C CNN
	1    5150 1250
	1    0    0    -1  
$EndComp
Text GLabel 5150 1400 3    50   Input ~ 0
GND
Wire Wire Line
	4900 1100 5150 1100
Connection ~ 5150 1100
Wire Wire Line
	5150 1100 5650 1100
Connection ~ 5350 5600
Wire Wire Line
	5350 5600 5800 5600
Connection ~ 5400 3750
Wire Wire Line
	5400 3750 5850 3750
NoConn ~ 9800 6050
$Comp
L Switch:SW_Push SW1
U 1 1 5F430BA9
P 6450 2600
F 0 "SW1" H 6450 2885 50  0000 C CNN
F 1 "SW_Push" H 6450 2794 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm_H7.3mm" H 6450 2800 50  0001 C CNN
F 3 "~" H 6450 2800 50  0001 C CNN
	1    6450 2600
	1    0    0    -1  
$EndComp
Text GLabel 6250 2600 0    50   Input ~ 0
GND
Wire Wire Line
	6650 2600 6950 2600
Wire Wire Line
	6950 2500 6950 2600
Connection ~ 6950 2600
Wire Wire Line
	6950 2600 7500 2600
$Comp
L Sensor_Optical:LDR03 R8
U 1 1 5F3A3DD1
P 5100 6650
F 0 "R8" H 5170 6696 50  0000 L CNN
F 1 "LDR03" H 5170 6605 50  0000 L CNN
F 2 "OptoDevice:R_LDR_5.1x4.3mm_P3.4mm_Vertical" V 5275 6650 50  0001 C CNN
F 3 "http://www.elektronica-componenten.nl/WebRoot/StoreNL/Shops/61422969/54F1/BA0C/C664/31B9/2173/C0A8/2AB9/2AEF/LDR03IMP.pdf" H 5100 6600 50  0001 C CNN
	1    5100 6650
	1    0    0    -1  
$EndComp
$EndSCHEMATC

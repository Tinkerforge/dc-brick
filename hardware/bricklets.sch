EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 5
Title ""
Date "14 jan 2013"
Rev "1.0"
Comp "Tinkerforge GmbH"
Comment1 "Licensed under CERN OHL v.1.1"
Comment2 "Copyright (©) 2011, B.Nordmeyer <bastian@tinkerforge.com>"
Comment3 ""
Comment4 ""
$EndDescr
NoConn ~ 3250 3250
NoConn ~ 3150 3250
Wire Wire Line
	3350 2850 3350 2750
Connection ~ 3150 2750
Wire Wire Line
	3150 2850 3150 2750
Wire Wire Line
	7800 2350 7800 2450
Wire Wire Line
	7500 2650 7500 2550
Wire Wire Line
	7500 2550 7800 2550
Wire Wire Line
	7800 4400 7600 4400
Wire Wire Line
	7600 4400 7600 4100
Wire Wire Line
	7550 4750 7550 4700
Wire Wire Line
	7550 4700 7800 4700
Connection ~ 5000 3600
Wire Wire Line
	5000 2750 5000 3600
Connection ~ 4900 3700
Wire Wire Line
	4900 4600 4900 3700
Wire Wire Line
	6550 3350 7800 3350
Wire Wire Line
	6550 3150 7800 3150
Wire Wire Line
	7800 5100 6550 5100
Wire Wire Line
	7800 4900 6550 4900
Connection ~ 3350 3700
Wire Wire Line
	3350 3250 3350 3700
Connection ~ 3200 2750
Wire Wire Line
	3200 2650 3200 2750
Wire Wire Line
	5000 3600 3050 3600
Wire Wire Line
	4900 4600 7800 4600
Wire Wire Line
	4900 2850 7800 2850
Wire Wire Line
	8250 5300 8250 5250
Wire Wire Line
	8250 3550 8250 3500
Wire Wire Line
	5000 2750 7800 2750
Wire Wire Line
	5000 4500 7800 4500
Wire Wire Line
	4900 3700 3350 3700
Wire Wire Line
	3350 2750 3250 2750
Wire Wire Line
	3050 3250 3050 3600
Connection ~ 3050 3600
Wire Wire Line
	7800 4800 6550 4800
Wire Wire Line
	7800 5000 6550 5000
Wire Wire Line
	6550 3050 7800 3050
Wire Wire Line
	6550 3250 7800 3250
Wire Wire Line
	7800 2950 7350 2950
Wire Wire Line
	7350 2950 7350 2650
Wire Wire Line
	7800 4300 7500 4300
Wire Wire Line
	7500 4300 7500 4400
Wire Wire Line
	7800 4100 7800 4200
Wire Wire Line
	7600 2350 7600 2650
Wire Wire Line
	7600 2650 7800 2650
Wire Wire Line
	3050 2750 3050 2850
Wire Wire Line
	3250 2850 3250 2750
Connection ~ 3250 2750
$Comp
L tinkerforge:R_PACK4 RP4
U 1 1 4D9DB274
P 3400 3050
F 0 "RP4" H 3400 3500 40  0000 C CNN
F 1 "1k" H 3400 3000 40  0000 C CNN
F 2 "4X0402" H 3400 3050 60  0001 C CNN
F 3 "" H 3400 3050 60  0001 C CNN
	1    3400 3050
	0    -1   1    0   
$EndComp
$Comp
L tinkerforge:GND #PWR025
U 1 1 4D0FDD4E
P 7550 4750
F 0 "#PWR025" H 7550 4750 30  0001 C CNN
F 1 "GND" H 7550 4680 30  0001 C CNN
F 2 "" H 7550 4750 60  0001 C CNN
F 3 "" H 7550 4750 60  0001 C CNN
	1    7550 4750
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:3V3 #PWR026
U 1 1 4D0FDD41
P 7350 2650
F 0 "#PWR026" H 7350 2750 40  0001 C CNN
F 1 "3V3" H 7350 2775 40  0000 C CNN
F 2 "" H 7350 2650 60  0001 C CNN
F 3 "" H 7350 2650 60  0001 C CNN
	1    7350 2650
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:3V3 #PWR027
U 1 1 4CAC8AB4
P 3200 2650
F 0 "#PWR027" H 3200 2750 40  0001 C CNN
F 1 "3V3" H 3200 2775 40  0000 C CNN
F 2 "" H 3200 2650 60  0001 C CNN
F 3 "" H 3200 2650 60  0001 C CNN
	1    3200 2650
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:+5V #PWR028
U 1 1 4CAC88B4
P 7800 2350
F 0 "#PWR028" H 7800 2440 20  0001 C CNN
F 1 "+5V" H 7800 2440 30  0000 C CNN
F 2 "" H 7800 2350 60  0001 C CNN
F 3 "" H 7800 2350 60  0001 C CNN
	1    7800 2350
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:+5V #PWR029
U 1 1 4CAC88AE
P 7800 4100
F 0 "#PWR029" H 7800 4190 20  0001 C CNN
F 1 "+5V" H 7800 4190 30  0000 C CNN
F 2 "" H 7800 4100 60  0001 C CNN
F 3 "" H 7800 4100 60  0001 C CNN
	1    7800 4100
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:3V3 #PWR030
U 1 1 4CAC87D9
P 7600 4100
F 0 "#PWR030" H 7600 4200 40  0001 C CNN
F 1 "3V3" H 7600 4225 40  0000 C CNN
F 2 "" H 7600 4100 60  0001 C CNN
F 3 "" H 7600 4100 60  0001 C CNN
	1    7600 4100
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:3V3 #PWR031
U 1 1 4CAC87D4
P 7600 2350
F 0 "#PWR031" H 7600 2450 40  0001 C CNN
F 1 "3V3" H 7600 2475 40  0000 C CNN
F 2 "" H 7600 2350 60  0001 C CNN
F 3 "" H 7600 2350 60  0001 C CNN
	1    7600 2350
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR032
U 1 1 4CAC87AD
P 7500 2650
F 0 "#PWR032" H 7500 2650 30  0001 C CNN
F 1 "GND" H 7500 2580 30  0001 C CNN
F 2 "" H 7500 2650 60  0001 C CNN
F 3 "" H 7500 2650 60  0001 C CNN
	1    7500 2650
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR033
U 1 1 4CAC87A9
P 7500 4400
F 0 "#PWR033" H 7500 4400 30  0001 C CNN
F 1 "GND" H 7500 4330 30  0001 C CNN
F 2 "" H 7500 4400 60  0001 C CNN
F 3 "" H 7500 4400 60  0001 C CNN
	1    7500 4400
	1    0    0    -1  
$EndComp
Text GLabel 6550 4900 0    60   Input ~ 0
BRICKLET-IO1_1/DA1
Text GLabel 6550 3150 0    60   Input ~ 0
BRICKLET-IO0_1/DA0
Text GLabel 6550 3350 0    60   Input ~ 0
BRICKLET-IO0_3
Text GLabel 6550 5100 0    60   Input ~ 0
BRICKLET-IO1_3
Text GLabel 6550 5000 0    60   Input ~ 0
BRICKLET-IO1_2/PWM1
Text GLabel 6550 3250 0    60   Input ~ 0
BRICKLET-IO0_2/PWM0
Text GLabel 6550 4800 0    60   Input ~ 0
BRICKLET-IO1_0/AD1
Text GLabel 6550 3050 0    60   Input ~ 0
BRICKLET-IO0_0/AD0
Text GLabel 2450 3600 0    60   Input ~ 0
BRICKLET-I2C-SCL
Text GLabel 2450 3700 0    60   Input ~ 0
BRICKLET-I2C-SDA
$Comp
L tinkerforge:GND #PWR034
U 1 1 4CAC33F4
P 8250 5300
F 0 "#PWR034" H 8250 5300 30  0001 C CNN
F 1 "GND" H 8250 5230 30  0001 C CNN
F 2 "" H 8250 5300 60  0001 C CNN
F 3 "" H 8250 5300 60  0001 C CNN
	1    8250 5300
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR035
U 1 1 4CAC33ED
P 8250 3550
F 0 "#PWR035" H 8250 3550 30  0001 C CNN
F 1 "GND" H 8250 3480 30  0001 C CNN
F 2 "" H 8250 3550 60  0001 C CNN
F 3 "" H 8250 3550 60  0001 C CNN
	1    8250 3550
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:CON-SENSOR P4
U 1 1 4CAC3392
P 8250 4650
F 0 "P4" H 8000 5200 60  0000 C CNN
F 1 "CON-SENSOR" V 8450 4650 60  0000 C CNN
F 2 "CON-SENSOR" H 8250 4650 60  0001 C CNN
F 3 "" H 8250 4650 60  0001 C CNN
	1    8250 4650
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:CON-SENSOR P3
U 1 1 4CAC338E
P 8250 2900
F 0 "P3" H 8000 3450 60  0000 C CNN
F 1 "CON-SENSOR" V 8450 2900 60  0000 C CNN
F 2 "CON-SENSOR" H 8250 2900 60  0001 C CNN
F 3 "" H 8250 2900 60  0001 C CNN
	1    8250 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 2750 3050 2750
Wire Wire Line
	5000 3600 5000 4500
Wire Wire Line
	4900 3700 4900 2850
Wire Wire Line
	3350 3700 2450 3700
Wire Wire Line
	3200 2750 3150 2750
Wire Wire Line
	3050 3600 2450 3600
Wire Wire Line
	3250 2750 3200 2750
$EndSCHEMATC

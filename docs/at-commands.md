---
title: AT Commands
---


## Ping (get motherboard ID)
### Command
```
AT+PNG?
```

### Response
```
+PNG: <motherboard-id>
```

### Description
Ping the motherboard. The motherboard will respond with its motherboard ID This is a sixteen bit unsigned identifier. The ID is sent as a 4-digit hex string in ASCII format.


### Example
```
Command>  AT+PNG?
Response> +PNG: 474F
The board has id 0x474F
```

## List sensors
Command
AT+LS?
Response
+LS: {<sensor1> <sensor2> ...}
Description
List the sensors that are connected to the motherboard. The motherboard will respond with a space-separated list of sensors. When no sensors are connected this list is empty. The <sensorX> field is sent as a 4-digit hex string in ASCII format. The first 2 digits are the sensors’ ID The last 2 digits are the sensors’ type. For a list of supported sensor types, see TODO.
Based on the sensor type, the UI can determine what metrics are supported.
Example
Command>  AT+LS?
Response> +LS: 0168 0221
Two sensors are connected. Sensor 0x01 has type 0x68, sensor 0x02 has type 0x21.
Check poll interval
Command
AT+POL?<sensor-id> <metric>
Response
+POL: <poll-interval>
Description
Check the poll interval (Explain what this is? Here? Somewhere else?) that is used to check a sensors’ readings. The <poll-interval> is returned as a decimal string. When an invalid sensor ID or metric is specified, <poll-interval> is an empty string.
Example
Command>  AT+POL?01 2
Response> +POL: 300
Request poll interval for sensor 0x01, metric 2. Current setting is 300 seconds, i.e., every 5 minutes.
Set poll interval
Command
AT+POL=<sensor-id> <metric> <poll-interval>
Response
OK | ERROR
Description
Set the poll interval for the sensor with ID <sensor-id>. The <sensor-id> field is a 2-digit hex string. The <poll-interval> formatted as a decimal string. When the poll interval is changed successfully, the motherboard responds with OK. Otherwise, e.g., when an invalid sensor ID is specified, the response is ERROR.
Bedenkingen geof (maar moet dat hier)?
•	Minimum poll interval: 5 minutes? (Not enforced yet in software).
•	Maximum value 65535 (approx.. 18 hours).
•	A poll interval of 0 will be treated as “never poll”, sensor will operate threshold-based.
Example
Command>  AT+POL=01 1 600
Response> OK
Set poll interval for sensor 0x01, metric 1 to 600 seconds, i.e., every 10 minutes.
Check the threshold settings
Command
AT+TH?<sensor-id> <metric>
Response
+TH: <thresholds-enabled> <threshold-level-low> <threshold-level-high>
Description
Check the threshold settings for the sensor with ID <sensor-id> (opnieuw: waar leggen we thresholds uit?). The <sensor-id> field is a 2-digit hex string. The <thresholds-enabled> field will be either ‘0’ (not enabled) or ‘1’ (enabled). Both <threshold-level-low> and <threshold-level-high> are decimal strings (between 0 and 65535).  When an invalid sensor ID is specified, only +TH: is returned.
Example
Command>  AT+TH?=02 1
Response> +TH: 1 100 5000
Check the threshold settings for sensor 0x02, metric 1. Thresholds are enabled with threshold-level-low = 100 and threshold-level-high = 5000.

General remarks section? Misschien aan’t begin.
Sensor id, sensor type and motherboard id -> hex string with fixed size
Poll interval, threshold levels and metric specifiers all decimals (ascii string).

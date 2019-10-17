---
layout: default
title: Set poll interval
parent: AT Commands
has_toc: true
nav_order: 4
---

## Check the threshold settings

### Command
```
AT+TH?<sensor-id> <metric>
```

### Response
```
+TH: <thresholds-enabled> <threshold-level-low> <threshold-level-high>
```

### Description
Check the threshold settings for the sensor with ID <sensor-id> (opnieuw: waar leggen we thresholds uit?). The <sensor-id> field is a 2-digit hex string. The <thresholds-enabled> field will be either ‘0’ (not enabled) or ‘1’ (enabled). Both <threshold-level-low> and <threshold-level-high> are decimal strings (between 0 and 65535).  When an invalid sensor ID is specified, only +TH: is returned.

### Example
```
Command>  AT+TH?=02 1
Response> +TH: 1 100 5000
```

Check the threshold settings for sensor 0x02, metric 1. Thresholds are enabled with threshold-level-low = 100 and threshold-level-high = 5000.


---
layout: default
title: Check poll interval
parent: AT Commands
has_toc: true
---

## Check poll interval

### Command
```
AT+POL?<sensor-id> <metric>
```

### Response
```
+POL: <poll-interval>
```

### Description
Check the poll interval (Explain what this is? Here? Somewhere else?) that is used to check a sensors’ readings. The <poll-interval> is returned as a decimal string. When an invalid sensor ID or metric is specified, <poll-interval> is an empty string.

### Example
```
Command>  AT+POL?01 2
Response> +POL: 300
```
Request poll interval for sensor 0x01, metric 2. Current setting is 300 seconds, i.e., every 5 minutes.

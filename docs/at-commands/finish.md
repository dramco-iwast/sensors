---
layout: default
title: Close
parent: AT Commands
has_toc: true
nav_order: 6
---

## Close
### Command
```
AT+CLS
```

### Response
```
OK | ERROR
```

### Description
Close the configuration context.
The motherboard will stop listening to serial communication, enabling to enter a low power state.
It will push the updated configurations to all connected sensors.

### Example
```
Command>  AT+CLS
Response> OK
No errors occured.
```

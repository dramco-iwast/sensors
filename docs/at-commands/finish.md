---
layout: default
title: Finish
parent: AT Commands
has_toc: true
nav_order: 6
---

## Finish
### Command
```
AT+FIN
```

### Response
```
OK | ERROR
```

### Description
Close the configuration context.
The motherboard will stop listening to serial communication, enabling to enter a low power state.
It will store the updated configurations to non-volatile memory.

### Example
```
Command>  AT+FIN
Response> OK
No errors occured.
```

### Name
Use After Free

### Description
In `resize.c:87`, `img->px` pointer is freed twice, causing a use after free bug

### Affected Lines
In `resize.c:87` 

### Expected vs Observed
Expected the `error_memory` control block to free `img->px` and `img`. Observed that it tries to free `img->px` twice. 

### Steps to Reproduce
Although unable to exploit the bug, I think that the way to reach the `error_memory` block and to cause a memory error is to run several processes in parallel, each allocating some memory in heap. The bug will then be triggered when some processes have allocated all the heap memory, and there is a remaining process that tries to allocate more heap memory, causing the `malloc` in `resize.c:38` to return NULL

#### Command

```
No specific command to trigger this bug
```
#### Proof-of-Concept Input (if needed)

### Suggested Fix Description
In the error memory block free `img->px` and then `img`
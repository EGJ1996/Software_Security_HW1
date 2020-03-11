### Name
Use After Free

### Description
In `solid.c:47-49`, curly brackets are missing in the if condition, which causes the palette pointer to be always freed, and then used in the lines 64-67.
When accessed later in our program,  palette will not contain the rgb values assigned in lines 64-67, but some random values. 

### Affected Lines
In `solid.c:64-67`, `solid.c:49` 

### Expected vs Observed
Expected to free palette only if `height` < 0 or `end_ptr` is not NULL. Observed that the palette pointer is always freed, causing a use after free bug

### Steps to Reproduce
The bug is independent of the input

#### Command
```
./solid test.png 10 10 ff0000
```
#### Proof-of-Concept Input (if needed)

### Suggested Fix Description
Only free palette if  `height` < 0 or `end_ptr` is not NULL. In `solid.c:47-49` use curly brackets in the if condition to ensure that the `free(palette)` statement is included in the if clause
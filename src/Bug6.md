### Name
Buffer Overflow

### Description
In `filter.c:177-179`, we are using the function strcpy to copy the value of the arguments to the corresponding char arrays. However, strcpy does not have any restriction on the number of characters being copied, so if the size of the array is 256 character, but we try to copy more than 256 characters, strcpy will just overwrite the next memory address with the remaining characters. In our case, the command array sits just before the `ebp` register. In order to prevent buffer overflows, gcc adds a stack canary between ebp and the command, and checks whether the canary value was modified to detect buffer overflows. By inspection, I found that the stack canary is 8 bytes long. Hence, if we write more than 256(size of the array) + 8(size of the stack canary) to the command array, we will overflow the buffer and get a stack smashed error. 

### Affected Lines
In `filter.c:179` 

### Expected vs Observed
Expected to write at most characters to the command array. Observed that if more than 256 were provided as input, strcpy will just overwrite the next memory address

### Steps to Reproduce
Create an input image using the following command:
```
./checkerboard check.png 10 10 1 ff0000 00ff00
```
Call filter with a command greater than 264 characters

#### Command

```
./filter check.png out.png AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
```
#### Proof-of-Concept Input (if needed)
(attached:check.png)

### Suggested Fix Description
Use strncpy to limit the number of copied characters to the size of the array
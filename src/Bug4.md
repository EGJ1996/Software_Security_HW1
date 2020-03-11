### Name
Use After Free

### Description

Description: In `filter.c`, the `negative` filter uses `get_pixel` function, which returns a pointer to a `struct pixel` that is created in the function. Givv
This pointer is uninitialized, and it does not point to any memory location, so attempting to access this pointer later in `filter_negative function` will cause a bug.

### Affected Lines
In `filter.c:102` 

### Expected vs Observed
Expected the `get_pixel` function to return a valid pointer to `struct pixel`. Observed that it returns an invalid pointer.

### Steps to Reproduce
Generate input image using the following command:
```
./checkerboard check.png 10 10 2 ff0000
```
Apply the negative filter to the input image with an arbitrary `alpha` value

#### Command

```
./filter check.png negative_check.png negative
```
#### Proof-of-Concept Input (if needed)
(attached:check.png)

### Suggested Fix Description
Initialize the `px` pointer by allocating memory of size `struct pixel` in the heap using `malloc`, and return a pointer to the allocated memory
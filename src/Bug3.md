### Name
Type Confusion

### Description

In `filter.c`, the `filter_transparency` function, converts the `void* transparency` pointer to a `uint8_t*` pointer, and then dereferences the pointer to obtain the value of alpha.  However, in the `filter.c:207-222`, we see that in the case of the alpha filter, which calls the `filter_transparency` function, the argument assigned to the filter is an array of double `weights`. When the conversion is done in `filter.c:132`, the first element of the weights array, which is a pointer of type double with value 0.2125, is converted to a pointer of type uint8_t with value 51. In this case alpha always takes a value of 51.

### Affected Lines
In `filter.c:221`

### Expected vs Observed
Expected the `filter_transparency` function to take the value of `alpha` that is passed as an argument to the filter command. Observed that the value of alpha is assigned from the first element of the `weights` array, and always takes a value of 51.

### Steps to Reproduce]
Generate an input image using the following command:
```
./checkerboard check.png 10 10 2 ff0000
```
Apply the alpha filter to the input image

#### Command
 
```
./filter check.png check_alpha.png alpha 1.5
```
#### Proof-of-Concept Input (if needed)
(attached:check.png)

### Suggested Fix Description
In `filter.c:221`, assign `fil.arg = &alpha`
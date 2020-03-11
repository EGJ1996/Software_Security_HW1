### Name
Out-of-Bounds Read/Write

### Description
In `resize.c:34-35` , we are assigning to `new_width` and `new_height`  the rounded values of `factor * img->size_x` and `factor * img->size_y` respectively,each converted to unsigned integers. When the value of `round(factor*img->size_x)` or `round(factor*img->size_y)` exceeds 4294967295(this is the value for `UINT_MAX` in my machine), the value of `new_width` or `new_height` will overflow to 0, which is the minimum value of an unsigned integer. However, in the lines 58-59, `y` and `x` are upper bounded by `round(factor*img->size_y)` and `round(factor*img->size_x)` respectively. Note that the round method returns a double, and the maximum value of a double data type is much larger than the maximum value of the unsigned data type (179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.0 vs 4294967295 in my machine). Hence, we may overflow `new_width` and `new_height` in lines 34-35, but `y` and `x` in lines 58-59 may still want to access the memory that would have been allocated if no overflow occurred, causing an out-of-bound read/write. 
Similar problem to the above is caused when calling `malloc(new_width * new_height * sizeof(struct pixel))`. If the argument of the malloc function is greater than `LONG_MAX`, it will overflow to `new_width * new_height * sizeof(struct pixel)` - `LONG_MAX`. Hence, malloc will allocate less than `new_width * new_height * sizeof(struct pixel)`, while the loops in lines 58-59 will iterate up to `new_width - 1`, `new_height - 1`, causing an out-of-bounds read/write. 
The same out-of-bounds bug is also caused by the round operator in `resize.c:58` and `resize.c:59` For example, if we are rescaling a 10 by 10 image with a scaling factor of 1.26, the `new_width` and `new_height` will be truncated to 12. Meanwhile, the round operator in `resize.c:58` and `resize.c:59` will round `factor*img->size_x` and `factor * img->size_y` to 13, and the loops in the lines 58 and 59 will iterate until 12, which is out of the bounds of the image (valid indices in this case for width and height range from 0 to 11).

### Affected Lines
In `resize.c:66`, `resize.c:34-35`, `resize.c:58-59`

### Expected vs Observed
Expected loop to iterate only through the correctly allocated memory. Observed that the nested loops in `resize.c:58-59` iterate through unallocated memory in case of an overflow. Also, when `new_width * new_height * sizeof(struct pixel)` does not overflow, the nested loops in `resize.c:58-59` will still exceed the image bounds by 1 when `floor(alpha)` != `round(alpha)`

### Steps to Reproduce
Generate an input image using the command below:
```
./checkerboard check.png 10 10 2 ff0000
```
Call `resize_image` with a factor `alpha` such that `floor(alpha)` != `round(alpha)`

Call `resize_image` with a very large rescaling factor that will cause an overflow in  `new_width` and `new_height`

#### Command

```
./resize_image check.png res_check.png 100000000000000000000000000000000000000000000000
./resize_image check.png resized_check.png 1.26
```
#### Proof-of-Concept Input (if needed)
(attached:check.png)

### Suggested Fix Description
Fix by checking each dimension, `new_width` and `new_height` for overflow, and checking whether `new_img->px` is properly allocated in the heap, i.e., `new_width * new_height * sizeof(struct pixel)` does not exceed `UINT_MAX`. Also fix by first rounding the new image_size and then casting it to unsigned, so that the decimal part is not truncated
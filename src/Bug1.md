### Name
Out-of-Bounds Write

### Description
Description: In `checkerboard.c`, when the size of the square divides the size of the checkerboard, in the nested loops in the lines 99-120, `(height+square_width-1)/square_width = height/square_width and (width + square_width-1)/square_width = width/square_width`, which will be integers in both cases. Hence, the i and j variables will be upper bounded by `(height/square_width - 1)` and `(width/square_width - 1)` respectively. This means that the `square_top_left_y` and `square_top_left_x` will be upper bounded `by height - square_width` and `width - square_width`. The `x` and `y` variables are upper bounded by `square_width - 1`. Hence, the `square_top_left_y + y` and `square_top_left_x + x` are upper bounded `by height - 1` and `width - 1`, which are perfectly within bounds. In case the `square_width` is not a multiple of either height or width, an out-of-bound read bug will occur. Consider the case when square_width is not a multiples of width. Same reasoning follows for the case when square_width is not a multiple of height. In this case `(width + square_width - 1)/square_width = ceil(width/square_width)`. The variable `j` will be upper bounded by `ceil(width/square_width)-1`. Hence the variable `square_top_left_x` will be upper bounded by `ceil(width/square_width) * square_width - square_width`. The variable x is upper bounded by `square_width - 1`. Hence the variable `square_top_left_x + x` will be upper bounded by `ceil(width/square_width) - 1`, which is larger than `width - 1`, causing an out-of-bounds write. The same out-of-bounds error happens when `square_width` is greater than `min(width, height)`. In this case, since `x` and `y` go from 0 to `square_width - 1` and `square_height - 1` respectively, `square_top_left_x + x` will be greater than `width - 1` when `square_width` > `width` and `square_top_left_y + y` will be greater than `height - 1` when `square_width` > `height`.
The out-of-bounds read/write bug in `checkerboard.c:112-115` could also be caused by when the `width and height` arguments are such that `height * width * sizeof(struct pixel)` are larger than `LONG_MAX`, causing the `malloc` in line 87 to allocate less memory than requested. When this happens, the nested loops in `checkerboard.c:99-100` assume that the full requested memory was allocated, hence causing an out-of-bounds read/write in lines 112-115. 

### Affected Lines
In `checkerboard.c:112-115`, `checkerboard:87`

### Expected vs Observed
Expected the parts of the square outside the checkerboard to be cut. Observed that the program was trying to access the parts of the squares outside the checkerboard.

### Steps to Reproduce
The above bugs can be reproduced by inputting a `square_width` that is larger than `min(width,height)`, or a `square_width` that does not divide `height` or `width`, or by providing as inputs `width` and `height` such that `width * height * sizeof(struct pixel)` is larger than `LONG_MAX`.

#### Command

```
./checkerboard check.png 10 8 4 ff0000 00ff00
./checkerboard check.png 5 5 10 ff0000 00ff00
./checkerboard check.png 9223372036854775807 9223372036854775807 3 ff0000 00ff00
```
#### Proof-of-Concept Input (if needed)

### Suggested Fix Description
Check that `square_width` divides `width` and `height`, and it is less than `min(width,height)`. Also, check that `width * height * sizeof(struct pixel)` < `LONG_MAX` before allocating the heap memory in `checkerboard.c:87`
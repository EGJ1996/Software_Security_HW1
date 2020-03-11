### Name
Out-of-Bounds Write

### Description

In `rect.c`, the loops in the lines 60,61 iterate up to `width` and `height`, causing out-of-bounds write. They should iterate up to `width-1` and ` height-1` respectively


### Affected Lines
In `rect.c:60`, `rect.c:61` 

### Expected vs Observed
Expected loop to iterate until the bounds of the image. Observed that the loop exceeds the bounds by 1.

### Steps to Reproduce
Generate an input image using the command below:
```
./checkerboard check.png 10 10 2 ff0000
```
Call the rect command with `top_left_x` < `width`, `bottom_right_x` > `top_left_x` and `bottom_right_x` < `width`, `top_left_y` < `height`,  `bottom_right_y > top_left_y` and `bottom_right_y` < `height` 

#### Command

```
./rect check.png rect_check.png 3 3 5 5 0000ff
```
#### Proof-of-Concept Input (if needed)
(attached:check.png)

### Suggested Fix Description
Bounding the loops in `rect.c:60-61` by width-1 and height-1 respectively
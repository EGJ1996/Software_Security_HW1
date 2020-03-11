### Name
Out-of-Bounds Write

### Description

In  `circle.c` , if the x-coordinate of the center is smaller than the radius, then `center_x - radius` will be negative, and if `center_x + radius` is greater than the width of the image `center_x + radius` will be out of the image bounds. Same goes for the y-coordinate of the center. Although C might allow the usage of negative indices, as array accesses are interpreted as pointer additions, the memory accessed in the case of negative indices will contain an invalid value.


### Affected Lines
In `circle.c:49-59`, `circle.c:70-80` 

### Expected vs Observed
Expected the parts of the circle outside the image boundaries to be cut. Observed that the program was trying to access the parts of the circle outside the image boundaries.

### Steps to Reproduce
First generate a png file using the checkerboard or solid command. In my example I have generated a png file using checkerboard as below:
```
./checkerboard check.png 10 10 1 ff0000 00ff00
```
Calling circle with arguments such that `center_x - radius` < 0, or `center_y - radius` < 0, or `center_x + radius` > `width`, or `center_y + radius` > `height` will cause the bug.

#### Command

```
./circle check.png  circle_check.png 2 2 10 ff0000
```
#### Proof-of-Concept Input (if needed)
(attached:check.png)

### Suggested Fix Description
Limit access to within the image bounds. Fix implemented in the `circle.c:48-50`,`circle.c:74-76`

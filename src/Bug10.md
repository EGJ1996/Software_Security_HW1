### Name
Out-of-Bounds Read/Write

### Description
In `solid.c:75`, we are allocating in the heap a memory of size `malloc(new_width * new_height * sizeof(struct pixel))` for the px pointer. If the argument of the malloc function is greater than `LONG_MAX`, it will overflow to `new_width * new_height * sizeof(struct pixel)` - `LONG_MAX`. Hence, malloc will allocate less than `new_width * new_height * sizeof(struct pixel)`, while the loops in lines 92-95 will iterate up to `new_width - 1`, `new_height - 1`, causing an out-of-bounds read/write.

### Affected Lines
In `solid.c:92-95` 

### Expected vs Observed
Expected solid to throw a memory error when the user asks for too much memory to be allocated. Observed that when `new_width * new_height * sizeof(struct_pixel)` overflows, `malloc` will allocate less memory than required, but it will then behave as though the full memory was allocated 

### Steps to Reproduce
Provide `width` and `height` arguments such that `width * height * sizeof(struct pixel)` will be larger than `LONG_MAX`

#### Command
```
./solid solid.png 9223372036854775807 9223372036854775807 ff0000
```

#### Proof-of-Concept Input (if needed)

### Suggested Fix Description
Before allocating the memory in `solid.c:75`, check whether `width * height * sizeof(struct pixel)` exceeds `LONG_MAX`. If that is the case, throw a memory error
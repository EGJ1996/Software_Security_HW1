### Name
Command Injection

### Description
In `solid.c:121`, `strncat` concatenates the output name, provided as argument by the user, with the command `stat -c`. In line 122, the system function is called with argument `stat -c output_name`.The system function in C can be quite dangerous if not checked for command injection, because it passes the command argument to the host environment to be executed and returns after the command has been completed. Hence, if we pass a malicious output name, `test.png; rm *` for example, the host environment will execute 2 sepearate commands, `stat -c test.png` and `rm *` which, beside displaying statistics for the test.png file, will also delete all the files in the current directory.

### Affected Lines
In `solid.c:120-122` 

### Expected vs Observed
Expected to print the size of the output file. Observed that any other command following the output_name can be executed.

### Steps to Reproduce
Call `solid` with the name of the file followed by semicolon and an arbitrary command 

#### Command

```
./solid "check.png;ls" 10 10 ff0000
```
#### Proof-of-Concept Input (if needed)
(attached:check.png)

### Suggested Fix Description
 Avoid calling the system function. Replace the call to the `system` function with a call to stat, which expects as arguments the path to the file whose properties will be read, and a pointer to a `struct stat`, where all the file properties will be dumped. This function acts as a usual C function, and it does not call any commands in the host environment
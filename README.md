# 42-get_next_line

## Description

This project is about creating a function that reads a file line by line. The goal of this project is to learn how to manage file descriptors, buffers, and memory allocation.

The function is prototyped as follows:
```c
int get_next_line(int fd);
```

The mandatory part has the following constraints:
- Repeated calls to the function should read the text file pointed to by the file descriptor, one line at a time.
- Should return the line that was read. If there is nothing else to read or if an error occurred, it should return NULL.
- The line read should include the newline character unless it is the end of the file.
- Must work with different buffer sizes. (Compile with -D BUFFER_SIZE=n)
- Should be able to read from a file and from the standard input.
- No memory leaks.

The bonus part of the project has the following constraints:
- The function should be able to manage multiple file descriptors.
- Only one static variable is allowed.

# get_next_line 📖

## Description 📜
The get_next_line function reads one line from the file descriptor `fd` each time it is called. The function returns a pointer to a string containing the line that was read, without the newline character \n. The function returns NULL when the end of file is reached or an error occurs. The function uses a static variable to store the remaining characters from the previous call, if any.

## Technologies & Concepts 🛠️
- Dynamic memory allocation
- Static Variables
- File Descriptors
- Function `read()`
- Macros(object-like macros, more specifically)

## Source Code Structure 📂
* **`get_next_line.c`** - implementation of functions with other static functions to auxiliate.
* **`get_next_line.h`** - header file.
* **`get_next_line_utils.c`** - auxiliary functions replicated from `libft`(subject requirement, we couldn't use our lib)
* **`*_bonus.c`** - implementation of get_next_line reading from multiple fd.

## Instructions ⚙️
- Run this command on your terminal to compile the  main function. (make sure you uncomment it!)
```bash
gcc get_next_line_utils.c get_next_line.c get_next_line.h -o get_next_line
```
You can also run with the flag `-D BUFFER_SIZE=42` with 42 being whateaver number you want, otherwise the BUFFER_SIZE can be altered in the header file.

Then, run  `./get_next line <file>` to see it happening.

*To the bonus version you should do the same steps above adding the `_bonus` to the files and then running `./get_next line <file> <file2>`

## Used Tests 🧪
- [Francinette](https://github.com/xicodomingues/francinette)

## Grade: 125 / 100 🏅
The project includes a bonus version of get_next_line, which can read from multiple file descriptors at the same time.

## Useful Links 🔗
- [Object-like Macros - GCC](https://gcc.gnu.org/onlinedocs/cpp/Object-like-Macros.html)
- [Static Variables in C – GeeksforGeeks](https://www.geeksforgeeks.org/c/static-variables-in-c/)
- [Memory Allocation](https://www.geeksforgeeks.org/c/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/)

## License 📜
This project was developed for academic purposes at 42, but feel free to use it as reference or inspiration.
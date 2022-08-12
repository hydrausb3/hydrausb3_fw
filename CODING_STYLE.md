Coding rules
==================
* Use standard types from stdbool.h/stdint.h => uint8_t/uint16_t/uint32_t ...
* Avoid any memory allocation like `malloc()/free()` (if required a dedicated memory allocator shall be used)
* All string functions that do not take an explicit buffer size argument are forbidden.
  * This includes but is not limited to `strcpy()`, `sprintf()`, etc.
* Use of C string manipulation functions with an explicit size, such as `snprintf()`, is acceptable.
* Field width specifiers are required on all `sscanf()` calls that write to strings. For example, %30s rather than %s.
* Avoid big stack usage (as the stack is very limited)
* Do not use reserved keywords for files (like CON, PRN, AUX, NUL, COM1, COM2, COM3, COM4, COM5, COM6, COM7, COM8, COM9, LPT1, LPT2, LPT3, LPT4, LPT5, LPT6, LPT7, LPT8, and LPT9) This is documented on: https://docs.microsoft.com/en-us/windows/desktop/FileIO/naming-a-file

C code conventions
==================
When writing new C code, please adhere to the following conventions.

Coding Style of the project: Linux Kernel coding style see: https://www.kernel.org/doc/html/latest/process/coding-style.html
- **Do not** apply following kernel.org coding-styles (see below coding style with AStyle):
  - `1) Indentation`
  - `2) Breaking long lines and strings`
  - `3) Placing Braces and Spaces`

### Configuration of coding style with AStyle

Can be also done automatically with open source tool AStyle: http://astyle.sourceforge.net/

With following syntax (Linux):
```
cd ~\hydrausb3_fw
astyle-T --indent-switches --style=bsd --lineend=linux --recursive *.c *.h
```

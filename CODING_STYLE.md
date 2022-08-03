Coding rules
==================
* Use types from stdint.h => uint8_t/uint16_t/uint32_t ...
* Avoid any malloc
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

With following syntax: `astyle -T --indent-switches --style=bsd --lineend=linux my_c_file.c`

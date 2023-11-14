#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>

int _printf(const char *format, ...);
int handle_specifier(const char **ptr, va_list args);
int print_int(int n);
int print_binary(unsigned int n);
int print_unsigned(unsigned int n);
int print_octal(unsigned int n);
int print_hex(unsigned int n, int uppercase);
int print_custom_string(char *str);
int print_pointer(void *ptr);
int print_reversed(char *str);
int print_rot13(char *str);
int _putchar(char c);
int _puts(char *str);

#endif /* MAIN_H */


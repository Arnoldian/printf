#include "main.h"
#include <stdarg.h>
#include <unistd.h>

#define BUFFER_SIZE 20

/**
 * write_char - Helper func to write a char
 * @c: Char to write
 * Return: Num of chars written
 */
int write_char(int c) {
    return write(1, &c, 1);
}

/**
 * write_str - Helper func to write a str with precision
 * @str: Str to write
 * @precision: Max chars to write
 * Return: Num of chars written
 */

int write_str(char *str, int precision) {
    int count = 0;
    while (*str && count < precision)
        write(1, str++, 1), count++;
    return count;
}

/**
 * write_int - Helper func to write an int
 * @n: Int to write
 * Return: Number of chars written
 */

int write_int(int n) {
    char buffer[BUFFER_SIZE];
    int i = 0;

    if (n < 0) write_char('-'), n = -n;
    if (n == 0) return write_char('0');

    while (n != 0) buffer[i++] = '0' + n % 10, n /= 10;

    while (--i >= 0) write(1, &buffer[i], 1);
    return i;
}

/**
 * _printf - Custom printf func
 * @format: Format str
 * Return: Number of chars printed (excl null byte)
 */

int _printf(const char *format, ...) {
    va_list args;
    int count = 0, int_arg;
    char *str_arg;

    va_start(args, format);

    for (; *format; ++format) {
        if (*format != '%') {
            write_char(*format);
            count++;
        } else {
            format++;
            switch (*format) {
            case 'c':
                count += write_char(va_arg(args, int));
                break;
            case 's':
                str_arg = va_arg(args, char *);
                count += write_str(str_arg ? str_arg : "(null)");
                break;
            case '%':
                count += write_char('%');
                break;
            case 'd': case 'i':
                int_arg = va_arg(args, int);
                count += write_int(int_arg);
                break;
            default:
                write_char('%');
                write_char(*format);
                count += 2;
            }
        }
    }

    va_end(args);
    return count;
}


#include "main.h"
#include <stdarg.h>
#include <unistd.h>

int write_str(char *str);
int write_int(int n);
int _strlen(char *s);
char *itoa(int n, char *buffer);
char *reverse_str(char *str);

/**
 * _printf - Custom printf func
 * @format: Format string
 * Return: Number of chars printed (excl null byte)
 */

int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    const char *ptr;

    va_start(args, format);

    for (ptr = format; *ptr != '\0'; ptr++)
    {
        if (*ptr != '%')
        {
            write(1, ptr, 1);
            count++;
        }
        else
        {
            ptr++; /* Move to the character after '%' */
            switch (*ptr)
            {
                case 'c':
                    count += write(1, &va_arg(args, int), 1);
                    break;
                case 's':
                    count += write_str(va_arg(args, char *));
                    break;
                case '%':
                    count += write(1, "%", 1);
                    break;
                case 'd':
                case 'i':
                    count += write_int(va_arg(args, int));
                    break;
                default:
                    write(1, "%", 1);
                    write(1, &(*ptr), 1);
                    count += 2;
            }
        }
    }

    va_end(args);

    return count;
}

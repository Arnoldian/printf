#include "main.h"
#include <stdarg.h>
#include <unistd.h>

/**
 * _printf - Custom printf function
 * @format: Format string
 * Return: Number of characters printed (excluding null byte)
 */
int _printf(const char *format, ...)
{
    va_list args_list;
    int count = 0;
    const char *ptr;

    va_start(args_list, format);

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
                    count += write(1, va_arg(args_list, int), 1);
                    break;
                case 's':
                    count += write(1, va_arg(args_list, char *), 1);
                    break;
                case '%':
                    count += write(1, "%", 1);
                    break;
                case 'd':
                case 'i':
                    count += write(1, va_arg(args_list, int), 1);
                    break;
                default:
                    write(1, "%", 1);
                    write(1, &(*ptr), 1);
                    count += 2;
            }
        }
    }

    va_end(args_list);

    return (count);
}


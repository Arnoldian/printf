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
    va_list args;
    int count = 0;
    const char *ptr;

    va_start(args, format);

    for (ptr = format; *ptr != '\0'; ptr++)
    {
        if (*ptr != '%')
        {
            write(1, ptr, 1);  // write character to stdout
            count++;
        }
        else
        {
            ptr++; // Move past '%'

            switch (*ptr)
            {
            case 'c':
                count += write_char(va_arg(args, int));
                break;
            case 's':
                count += write_str(va_arg(args, char *));
                break;
            case '%':
                write(1, "%", 1);
                count++;
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

/**
 * write_char - Helper function to write a character
 * @c: Character to write
 * Return: Number of characters written
 */

int write_char(int c)
{
    write(1, &c, 1);
    return 1;
}

/**
 * write_str - Helper function to write a string
 * @str: String to write
 * Return: Number of characters written
 */

int write_str(char *str)
{
    if (str == NULL)
        str = "(null)";

    write(1, str, _strlen(str));
    return _strlen(str);
}

/**
 * write_int - Helper function to write an integer
 * @n: Integer to write
 * Return: Number of characters written
 */

int write_int(int n)
{
    char buffer[20];
    int i = 0;

    if (n < 0)
    {
        write_char('-');
        n = -n;
    }

    if (n == 0)
    {
        write_char('0');
        return 1;
    }

    while (n != 0)
    {
        buffer[i++] = '0' + n % 10;
        n /= 10;
    }

    while (--i >= 0)
        write(1, &buffer[i], 1);

    return i;
}

/**
 * _strlen - Helper function to calculate string length
 * @str: Input string
 * Return: Length of the string
 */

int _strlen(char *str)
{
    int len = 0;
    while (*str)
    {
        len++;
        str++;
    }
    return len;
}


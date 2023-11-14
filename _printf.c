#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * _printf - Custom printf function
 * @format: Format str with conversion specifiers
 * @...: Var num of args for conversion specifiers
 * Return: Num of chars printed (excl null byte)
 */

int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    const char *ptr;

    va_start(args, format);

    for (ptr = format; *ptr != '\0'; ptr++)
    {
        if (*ptr == '%')
        {
            ptr++; /* Move past '%' */
            count += handle_specifier(&ptr, args);
        }
        else
        {
            _putchar(*ptr);
            count++;
        }
    }

    va_end(args);
    return count;
}

/**
 * handle_specifier - Handle conversion specifiers
 * @ptr: Ptr to the format str after '%'
 * @args: Var arguments list
 * Return: Num of chars printed for the specifier
 */

int handle_specifier(const char **ptr, va_list args)
{
    int count = 0;
    char specifier = **ptr;

    switch (specifier)
    {
    case 'c':
        count += _putchar(va_arg(args, int));
        break;

    case 's':
        count += _puts(va_arg(args, char *));
        break;

    case '%':
        count += _putchar('%');
        break;

    case 'd':
    case 'i':
        count += print_int(va_arg(args, int));
        break;

    case 'b':
        count += print_binary(va_arg(args, unsigned int));
        break;

    case 'u':
        count += print_unsigned(va_arg(args, unsigned int));
        break;

    case 'o':
        count += print_octal(va_arg(args, unsigned int));
        break;

    case 'x':
        count += print_hex(va_arg(args, unsigned int), 0);
        break;

    case 'X':
        count += print_hex(va_arg(args, unsigned int), 1);
        break;

    case 'S':
        count += print_custom_string(va_arg(args, char *));
        break;

    case 'p':
        count += print_pointer(va_arg(args, void *));
        break;

    case 'r':
        count += print_reversed(va_arg(args, char *));
        break;

    case 'R':
        count += print_rot13(va_arg(args, char *));
        break;

    /* Add cases for more specifiers here as needed */

    default:
        /* Handle unknown specifier here */
        count += _putchar('%');
        count += _putchar(specifier);
        break;
    }

    return count;
}

/* Helper functions for additional conversion specifiers */

/**
 * print_int - prints int
 * @n: parameter
 * Return: count
 */

int print_int(int n)
{
    int count = 0;
    if (n < 0)
    {
        count += _putchar('-');
        n = -n;
    }
    count += print_unsigned(n);
    return count;
}

/**
 * print_binary - prints binary
 * @n: unsigned int parameter
 * Return: count
 */

int print_binary(unsigned int n)
{
    int count = 0;
    if (n == 0)
    {
        count += _putchar('0');
        return count;
    }
    count += print_binary(n / 2);
    count += _putchar('0' + n % 2);
    return count;
}

/**
 * print_unsigned - prints unsigned int
 * @n: apppropriate parameter
 * Return: count
 */

int print_unsigned(unsigned int n)
{
    int count = 0;
    if (n == 0)
    {
        count += _putchar('0');
        return count;
    }
    count += print_unsigned(n / 10);
    count += _putchar('0' + n % 10);
    return count;
}

/**
 * print_octal - prints octal
 * @n: appropriate parameter
 * Return: count
 */

int print_octal(unsigned int n)
{
    int count = 0;
    if (n == 0)
    {
        count += _putchar('0');
        return count;
    }
    count += print_octal(n / 8);
    count += _putchar('0' + n % 8);
    return count;
}

/**
 * print_hex - prints hex
 * @n: appropriate parameter
 * @uppercase: parameter for uppercase input
 * Return: count
 */

int print_hex(unsigned int n, int uppercase)
{
    int count = 0;
    if (n == 0)
    {
        count += _putchar('0');
        return count;
    }
    count += print_hex(n / 16, uppercase);
    if (n % 16 < 10)
    {
        count += _putchar('0' + n % 16);
    }
    else
    {
        count += _putchar(uppercase ? 'A' + n % 16 - 10 : 'a' + n % 16 - 10);
    }
    return count;
}

/**
 * print_custom_string - prints custom string
 * @str: c str param
 * Return: count
 */

int print_custom_string(char *str)
{
    int count = 0;
    while (*str != '\0')
    {
        if (*str >= 32 && *str < 127)
        {
            count += _putchar(*str);
        }
        else
        {
            count += _putchar('\\');
            count += _putchar('x');
            count += print_hex(*str, 1);
        }
        str++;
    }
    return count;
}

/**
 * print_pointer - prints pointer
 * @ptr: void pointer parameter
 * Return: count
 */

int print_pointer(void *ptr)
{
    int count = 0;
    count += _putchar('0');
    count += _putchar('x');
    count += print_hex((unsigned long)ptr, 1);
    return count;
}

/**
 * print_reversed - prints reversed c string
 * @str: c string parameter
 * Return: count
 */

int print_reversed(char *str)
{
    int count = 0;
    char *end = str;
    while (*end != '\0')
    {
        end++;
    }
    end--;

    while (end >= str)
    {
        count += _putchar(*end);
        end--;
    }
    return count;
}

/**
 * print_rot13 - prints rot13
 * @str: c string
 * Return: count
 */

int print_rot13(char *str)
{
    int count = 0;
    while (*str != '\0')
    {
        if ((*str >= 'A' && *str <= 'Z') || (*str >= 'a' && *str <= 'z'))
        {
            char base = (*str >= 'A' && *str <= 'Z') ? 'A' : 'a';
            count += _putchar((((*str - base) + 13) % 26) + base);
        }
        else
        {
            count += _putchar(*str);
        }
        str++;
    }
    return count;
}

/* Additional helper funcs _putchar and _puts */

/**
 * _putchar - puts char
 * @c: parameter (character)
 * Return: character
 */

int _putchar(char c)
{
    return write(1, &c, 1);
}

/**
 * _puts - puts c string
 * @str: c string parameter
 * Return: count
 */

int _puts(char *str)
{
    int count = 0;
    while (*str != '\0')
    {
        _putchar(*str);
        str++;
        count++;
    }
    return count;
}

/* usage example:
int main(void)
{
    int len;

    len = _printf("Let's try some format: %d, %s, %x\n", 42, "Hello", 255);
    _printf("Total characters printed: %d\n", len);

    return 0;
}
*/


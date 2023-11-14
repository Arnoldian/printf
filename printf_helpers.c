#include <unistd.h>

/**
 * write_str - Write a string to stdout
 * @str: String to write
 * Return: Number of chars written
 */

int write_str(char *str)
{
    int count = 0;
    char null_str[] = "(null)";

    if (str == NULL)
        return write(1, null_str, 6);

    while (*str != '\0')
    {
        count += write(1, str, 1);
        str++;
    }

    return count;
}

/**
 * write_int - Write an integer to stdout
 * @n: Integer to write
 * Return: Number of chars written
 */

int write_int(int n)
{
    int count = 0;
    char buffer[12]; /* Maximum digits for an int is 11 + sign */

    if (n < 0)
    {
        n = -n;
        count += write(1, "-", 1);
    }

    count += write(1, itoa(n, buffer), _strlen(buffer));

    return count;
}

/**
 * _strlen - Get the length of a str
 * @s: Str
 * Return: Length of the str
 */

int _strlen(char *s)
{
    int count = 0;

    while (*s != '\0')
    {
        count++;
        s++;
    }

    return count;
}

/**
 * itoa - Convert an integer to a string
 * @n: Integer to convert
 * @buffer: Buffer to store the result
 * Return: Ptr to the result buffer
 */

char *itoa(int n, char *buffer)
{
    int i = 0;

    if (n == 0)
    {
        buffer[i++] = '0';
    }
    else
    {
        while (n != 0)
        {
            int rem = n % 10;
            buffer[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
            n = n / 10;
        }
    }

    buffer[i] = '\0';

    return reverse_str(buffer);
}

/**
 * reverse_str - Reverse a string
 * @str: String to reverse
 * Return: Ptr to the reversed string
 */

char *reverse_str(char *str)
{
    int i = 0;
    int j = _strlen(str) - 1;
    char temp;

    while (i < j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }

    return str;
}

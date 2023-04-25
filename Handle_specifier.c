#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - Prints a char
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: the Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars to be printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - Prints a string
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get the width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars to be printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int lens = 0, e;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[lens] != '\0')
		++lens;

	if (precision >= 0 && precision < lens)
		lens = precision;

	if (width > lens)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], lens);
			for (e = width - lens; e > 0; --e)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (e = width - lens; e > 0; --e)
				write(1, " ", 1);
			write(1, &str[0], lens);
			return (width);
		}
	}

	return (write(1, str, lens));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent sign
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get the width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars to be printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - Print int
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get the width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars to be printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int e = BUFF_SIZE - 2;
	int is_negative = 0;
	long int x = va_arg(types, long int);
	unsigned long int nums;

	x = convert_size_number(x, size);

	if (x == 0)
		buffer[--e] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	nums = (unsigned long int)x;

	if (x < 0)
	{
		nums = (unsigned long int)((-1) * x);
		is_negative = 1;
	}

	while (nums > 0)
	{
		buffer[--e] = (nums % 10) + '0';
		nums /= 10;
	}

	++e;

	return (write_number(is_negative, e, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get the width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char to be printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int x, y, e, sums;
	unsigned int n[32];
	int lens;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	x = va_arg(types, unsigned int);
	y = 2147483648; /* (2 ^ 31) */
	n[0] = x / y;
	for (e = 1; e < 32; ++e)
	{
		y /= 2;
		n[e] = (x / y) % 2;
	}
	for (e = 0, sums = 0, lens = 0; e < 32; ++e)
	{
		sums += n[e];
		if (sums || e == 31)
		{
			char z = '0' + n[e];

			write(1, &z, 1);
			++lens;
		}
	}
	return (lens);
}

#include "main.h"

/****************** PRINT POINTER ******************/

/**
 * print_pointer - Prints the value of a pointer variable
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get the width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars to be printed.
 */

int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char treat_c = 0, pax = ' ';
	int index = BUFF_SIZE - 2, lens = 2, pax_star = 1; /* lens=2, for '0x' */
	unsigned long num_address;
	char map[] = "0123456789abcdef";
	void *address = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (address == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_address = (unsigned long)address;

	while (num_address > 0)
	{
		buffer[--index] = map[num_address % 16];
		num_address /= 16;
		++lens;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pax = '0';
	if (flags & F_PLUS)
		treat_c = '+', ++lens;
	else if (flags & F_SPACE)
		treat_c = ' ', ++lens;

	++index;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, index, lens,
		width, flags, pax, treat_c, pax_star));
}

/************************* PRINT NON PRINTABLE *************************/

/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get the width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars to be printed
 */

int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int e = 0, set = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[e] != '\0')
	{
		if (is_printable(str[e]))
			buffer[e + set] = str[e];
		else
			set += append_hexa_code(str[e], buffer, e + set);

		++e;
	}

	buffer[e + set] = '\0';

	return (write(1, buffer, e + set));
}

/************************* PRINT REVERSE *************************/

/**
 * print_reverse - Prints reverse string.
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get the width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars to be printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int e, lens = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (e = 0; str[e]; ++e)
		;

	for (e = e - 1; e >= 0; --e)
	{
		char z = str[e];

		write(1, &z, 1);
		++lens;
	}
	return (lens);
}

/************************* PRINT A STRING IN ROT13 *************************/

/**
 * print_rot13string - Print a string in rot13.
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get the width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars to be printed
 */

int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char n;
	char *str;
	unsigned int e, g;
	int lens = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (e = 0; str[e]; ++e)
	{
		for (g = 0; in[g]; ++g)
		{
			if (in[g] == str[e])
			{
				n = out[g];
				write(1, &n, 1);
				++lens;
				break;
			}
		}
		if (!in[g])
		{
			n = str[e];
			write(1, &n, 1);
			++lens;
		}
	}
	return (lens);
}

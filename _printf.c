#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - function that prints the output according to the format
 * @format: the character string
 * Return: the number of characters printed.
 */
int _printf(const char *format, ...)
{
	int e, printc = 0, args = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list ars;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(ars, format);

	for (e = 0; format && format[e] != '\0'; ++e)
	{
		if (format[e] != '%')
		{
			buffer[++buff_ind] = format[e];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[e], 1);*/
			++args;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &e);
			width = get_width(format, &e, ars);
			precision = get_precision(format, &e, ars);
			size = get_size(format, &e);
			e++;
			printc = handle_print(format, &e, ars, buffer,
				flags, width, precision, size);
			if (printc == -1)
				return (-1);
			args += printc;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(ars);

	return (args);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}

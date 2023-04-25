#include "main.h"

/**
 * get_flags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @i: take a parameter.
 * Return: Flags:
 */
int get_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int g, curry_e;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curry_e = *i + 1; format[curry_e] != '\0'; ++curry_e)
	{
		for (g = 0; FLAGS_CH[g] != '\0'; ++g)
			if (format[curry_e] == FLAGS_CH[g])
			{
				flags |= FLAGS_ARR[g];
				break;
			}

		if (FLAGS_CH[g] == 0)
			break;
	}

	*i = curry_e - 1;

	return (flags);
}

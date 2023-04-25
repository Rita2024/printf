{

	/* The number is stored at the bufer's right and starts at position i */

	int length = BUFF_SIZE - ind - 1, i = 0;

	char padd = ' ';


	UNUSED(is_negative);

	UNUSED(size);


	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')

		return (0); /* printf(".0d", 0)  no char is printed */


	if (precision > 0 && precision < length)

		padd = ' ';


	while (precision > length)

	{

		buffer[--ind] = '0';

		length++;

	}


	if ((flags & F_ZERO) && !(flags & F_MINUS))

		padd = '0';


	if (width > length)

	{

		for (i = 0; i < width - length; i++)

			buffer[i] = padd;


		buffer[i] = '\0';


		if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/

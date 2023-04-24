/**
 * print_char - Print char
 * @types: List's arguments
 * @buffer: Buffer array to handle print
 * @flags: Evaluates effective flags
 * @width: Width
 * @precision: Precision guidelines
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int print_char(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/**
 * print_string – Print string
 * @types: List's arguments
 * @buffer: Buffer array to handle print
 * @flags: Evaluates effective flags
 * @width: Get width
 * @precision: Precision guidelines
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}
	while (str[length] != '\0')
		length++;
	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}

/**
 * print_percent - Print percent sign
 * @types: List's arguments
 * @buffer: Buffer array to handle print
 * @flags: Evaluates effective flags
 * @width: Get width
 * @precision: Precision guidelines
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(precision);
	UNUSED(size);

	if (width > 1)
	{
		if (flags & F_MINUS)
		{
			write(1, "%", 1);
			for (; width > 1; width--)
				write(1, " ", 1);
		}
		else
		{
			for (; width > 1; width--)
				write(1, " ", 1);
			write(1, "%", 1);
		}
		return (width);
	}
	return (write(1, "%", 1));
}

/**
 * print_int - Print integer
 * @types: List's arguments
 * @buffer: Buffer array to handle print
 * @flags: Evaluates effective flags
 * @width: Get width
 * @precision: Precision guidelines
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--

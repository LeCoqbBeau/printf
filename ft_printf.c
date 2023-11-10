#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>	

int	ft_putchr(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	if (!str)
	{
		write(1, "(null)", 7);
		return (6);
	}
	write(1, str, strlen(str));
	return ((int)strlen(str));
}

int	ft_putnbr(long long nb)
{
	int len;

	len = (nb < 0);
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb > 9)
	{
		len += ft_putnbr(nb / 10);
		len += ft_putnbr(nb % 10);
	}
	else
		len += ft_putchr(nb + '0');
	return (len);
}

int	ft_putnbr_hexa(unsigned long nb, char *base)
{
	int	len;

	len = 0;
	if (nb > strlen(base) - 1)
	{
		len += ft_putnbr_hexa(nb / strlen(base), base);
		len += ft_putnbr_hexa(nb % strlen(base), base);
	}
	else
		len += ft_putchr(base[nb]);
	return (len);
}

int	ft_callfunc(char format, long long data, int len)
{
	if (format == '%')
		len += ft_putchr('%');
	if (format == 'c')
		len += ft_putchr((int)data);
	if (format == 'i' || format == 'd')
		len += ft_putnbr((int)data);
	if (format == 'u')
		len += ft_putnbr((unsigned int)data);
	if (format == 'x')
		len += ft_putnbr_hexa((unsigned long)data, "0123456789abcdef");
	if (format == 'X')
		len += ft_putnbr_hexa((unsigned long)data, "0123456789ABCDEF");
	if (format == 'p')
		len += ft_putnbr_hexa((unsigned long)data, "0123456789ABCDEF");
	return (len);
}

#include <stdio.h>
int	ft_printf(const char *format, ...)
{
	int		i;
	int		len;
	va_list	ap;

	va_start(ap, format);
	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] != '%')
			len += ft_putchr(format[i]);
		else
		{
			i++;
			if (format[i] == 's')
				len += ft_putstr(va_arg(ap, char *));
			else
				len = ft_callfunc(format[i],  va_arg(ap, long long), len);
		}
		i++;
	}
	va_end(ap);
	return (len);
}

#include <stdlib.h>
int main()
{
	int size1 = 0;
	int size2 = 0;
	char *ptr = "Je suis un pointeur";
	char *ptr2 = strdup(ptr);

	// ft_printf("%s\n", &ptr);
	size1 = ft_printf("Adresse de ptr puis ptr2: %p, %p\n", ptr, ptr2);
	size2 = printf("Adresse de ptr puis ptr2: %p, %p\n", ptr, ptr2);
	printf("%d vs %d\n", size1, size2);
	free(ptr2);
	return 0;
}
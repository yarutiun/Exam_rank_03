#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

int putstr(char *s)
{
    if(!s)
    {
        write(1, "(null)", 6);
        return(6);
    }
    int i = 0;
    while(s[i])
    {
        write(1, &s[i], 1);
        i++;
    }
    return(i);
}

int ft_putchar(char c)
{
    write(1, &c, 1);
    return(1);
}

int putnbr(long int nbr)
{
    int len = 0;
    if(nbr < 0)
    {
        nbr *= -1;
        len++;
        write(1, "-", 1);
    }
    if(nbr > 9)
    {
        len += putnbr(nbr / 10);
        len += putnbr(nbr % 10);
    }
    else
        len += ft_putchar('0' + nbr);
    return(len);
}

int puthex(unsigned long int hex)
{
    int len  = 0;
    char *s = "0123456789abcdef";
    if(hex > 15)
    {
        len += puthex(hex / 16);
        len += puthex(hex % 16);
    }
    else
        len += ft_putchar(s[hex]);
    return(len);
}

int ft_printf(char *format, ... )
{
    int len = 0;
    int i = 0;
    va_list ap;
    va_start(ap, format);
    while(format[i])
    {
        if(format[i] != '%')
            len += ft_putchar(format[i]);
        else if(format[i] == '%' && format[i + 1]) //always check for the format[i + 1]
        {
            i++;
            if(format[i] == 's')
                len += putstr(va_arg(ap, char *));
            if(format[i] == 'd')
                len += putnbr(va_arg(ap, int));
            if(format[i] == 'x')
                len += puthex(va_arg(ap, unsigned int));
        }
        i++;
    }
    va_end(ap); //not very importnat, I'd even say useless)
    return(len);
}

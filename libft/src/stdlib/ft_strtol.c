/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalysann <urbilya@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 13:53:36 by nalysann          #+#    #+#             */
/*   Updated: 2021/08/25 13:53:36 by nalysann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <limits.h>

#include "ft_ctype.h"
#include "in_strtol.h"

static void	skip(t_strtol *s)
{
	while (ft_isspace(s->c))
		s->c = *(s->str)++;
	if (s->c == '-')
		s->sign = -1;
	else
		s->sign = 1;
	if (s->c == '+' || s->c == '-')
		s->c = *(s->str)++;
	if ((s->base == 0 || s->base == 16) && s->c == '0'
		&& (*(s->str) == 'x' || *(s->str) == 'X'))
	{
		s->c = s->str[1];
		s->str += 2;
		s->base = 16;
	}
	if (s->base == 0)
	{
		if (s->c == '0')
			s->base = 8;
		else
			s->base = 10;
	}
}

static void	convert_main(t_strtol *s, unsigned long cutoff, int cutlim)
{
	while (1)
	{
		if (ft_isdigit(s->c))
			s->c -= '0';
		else if (ft_isalpha(s->c))
		{
			if (ft_isupper(s->c))
				s->c -= 'A' - 10;
			else
				s->c -= 'a' - 10;
		}
		else
			break ;
		if (s->c >= s->base)
			break ;
		if (s->any < 0 || s->res > cutoff
			|| (s->res == cutoff && s->c > cutlim))
			s->any = -1;
		else
		{
			s->any = 1;
			s->res = s->res * s->base + s->c;
		}
		s->c = *(s->str)++;
	}
}

static void	convert(t_strtol *s)
{
	unsigned long	cutoff;
	int				cutlim;

	if (s->sign < 0)
	{
		cutoff = -(LONG_MIN / s->base);
		cutlim = -(LONG_MIN % s->base);
	}
	else
	{
		cutoff = LONG_MAX / s->base;
		cutlim = LONG_MAX % s->base;
	}
	convert_main(s, cutoff, cutlim);
}

static long	get_return_value(t_strtol *s, const char *str, char **endptr)
{
	if (endptr)
	{
		if (s->any)
			*endptr = (char *)(s->str - 1);
		else
			*endptr = (char *)str;
	}
	if (s->any < 0)
	{
		errno = ERANGE;
		if (s->sign < 0)
			return (LONG_MIN);
		else
			return (LONG_MAX);
	}
	if (s->sign < 0)
		return ((long)(-s->res));
	else
		return ((long)(s->res));
}

long	ft_strtol(const char *str, char **endptr, int base)
{
	t_strtol	s;

	s.str = str;
	s.base = base;
	s.c = ' ';
	s.any = 0;
	s.res = 0;
	if (!(base == 0 || (2 <= base && base <= 36)))
	{
		errno = EINVAL;
		return ((long)s.res);
	}
	skip(&s);
	convert(&s);
	return (get_return_value(&s, str, endptr));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: janeway <janeway@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 16:22:49 by janeway       #+#    #+#                 */
/*   Updated: 2022/07/01 17:23:16 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	calculate(int a)
{
	int			i;
	long long	n;

	n = (long long)a;
	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*string;
	int			i;
	long long	a;

	a = (long long)n;
	i = calculate(a);
	string = (char *)malloc(sizeof(char) * (i + 1));
	if (!(string))
		return (NULL);
	string[i] = '\0';
	if (a == 0)
		string[0] = 48;
	if (a < 0)
	{
		string[0] = '-';
		a = a * -1;
	}
	while (a > 0)
	{
		string[i - 1] = a % 10 + 48;
		a = a / 10;
		i--;
	}
	return (string);
}

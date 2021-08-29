/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalysann <urbilya@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 13:51:25 by nalysann          #+#    #+#             */
/*   Updated: 2021/08/25 13:51:25 by nalysann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ft_stdio.h"

void	ft_putnbr(int n)
{
	ft_putnbr_fd(n, STDOUT_FILENO);
}

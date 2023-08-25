/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:24:07 by syluiset          #+#    #+#             */
/*   Updated: 2023/08/25 19:07:29 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int					neg;
	int					i;
	long long int		ret;
	char				*nptr0;

	nptr0 = (char *)nptr;
	ret = 0;
	i = 0;
	neg = 1;
	while ((nptr0[i] >= 9 && nptr0[i] <= 13) || nptr0[i] == 32)
		i++;
	if (nptr0[i] == '+' || nptr0[i] == '-')
	{
		if (nptr0[i] == '-')
			neg = -1;
		i++;
	}
	while (nptr0[i] >= '0' && nptr0[i] <= '9')
	{
		if (ret != ((ret * 10 + (neg * (nptr0[i] - 48))) / 10))
			return ((neg + 1) / 2 / -1);
		ret = ret * 10 + ((nptr0[i] - 48) * neg);
		i++;
	}
	return ((int)ret);
}

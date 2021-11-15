#include "libft.h"

int	ft_puissance(int nb, int puissance)
{
	int	res;

	res = nb;
	if (puissance == 0)
		return (1);
	while (puissance > 1)
	{
		res *= nb;
		puissance--;
	}
	return (res);
}
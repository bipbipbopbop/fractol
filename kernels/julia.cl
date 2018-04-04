#include "kernels.h"

t_real			power(__private t_real nb, __private int power)
{
	if (power == 0)
		return (1);
	while (power > 1)
	{
		nb *= nb;
		--power;
	}
	return (nb);
}

__kernel void	julia(__global int *image, __global t_real *inter,
							__private int max_iter)
{
	private t_real	tmp;
	private int		iter;
	private int		ind;
	private t_real	z[2];
	private t_real	c[2];

	ind = get_global_id(0);
	z[0] = (ind % (int)inter[2]) / inter[3] + inter[5];
	z[1] = (ind / (int)inter[2]) / inter[4] + inter[6];
	c[0] = inter[0];
	c[1] = inter[1];
	iter = 0;
	while (iter < max_iter && power(z[0], 2) + power(z[1], 2) < 4)
	{
		tmp = z[0];
		z[0] = (power(z[0], 2) - power(z[1], 2) + c[0]);
		z[1] = 2 * z[1] * tmp + c[1];
		++iter;
	}
	image[ind] = iter;
}
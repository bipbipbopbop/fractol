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

__kernel void	multibrot(__global int *image, __global t_real *inter,
							__private int max_iter, __private float exp)
{
	private t_real	tmp;
	private int		iter;
	private int		ind;
	private t_real	z[2];
	private t_real	c[2];

	ind = get_global_id(0);
	z[0] = 0.0;
	z[1] = 0.0;
	c[0] = (ind % (int)inter[0]) / inter[1] + inter[3];
	c[1] = (ind / (int)inter[0]) / inter[2] + inter[4];
	iter = 0;
	while (iter < max_iter && power(z[0], 2) + power(z[1], 2) < 4)
	{
		tmp = pow((z[0] * z[0] + z[1] * z[1]), (exp / 2))
			* cos(exp * atan2(z[1], z[0]))
			+ c[0];
		z[1] = pow((z[0] * z[0] + z[1] * z[1]), (exp / 2))
			* sin(exp * atan2(z[1], z[0]))
			+ c[1];
		z[0] = tmp;
		++iter;
	}
	image[ind] = iter;
}
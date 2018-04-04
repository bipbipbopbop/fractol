#include "kernels.h"

float			power(__private float nb, __private int power)
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

__kernel void	burning_ship(__global int *image, __global float *inter,
							__private int max_iter)
{
	private float	tmp;
	private int		iter;
	private int		ind;
	private float	z[2];
	private float	c[2];

	ind = get_global_id(0);
	z[0] = 0;
	z[1] = 0;
	c[0] = (ind % (int)inter[0]) / inter[1] + inter[3];
	c[1] = (ind / (int)inter[0]) / inter[2] + inter[4];
	iter = 0;
	while (iter < max_iter && power(z[0], 2) + power(z[1], 2) < 4)
	{
		tmp = z[0];
		z[0] = ABS(power(z[0], 2) - power(z[1], 2) + c[0]);
		z[1] = ABS(2 * z[1] * tmp + c[1]);
		++iter;
	}
	image[ind] = iter;
}

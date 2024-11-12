#include "philo.h"

/* tv.tv_sec Represents the number of seconds since the Unix epoch (00:00:00 on January 1, 1970) */
/* tv.tv_usec Represents the additional number of microseconds within the current second, ranging from 0 to 999,999 */
unsigned long get_time(_Atomic unsigned long *nb)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	*nb = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (*nb);
}
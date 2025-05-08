#include "INCLUDES/philo.h"


typedef struct s_mute
{
	pthread_mutex_t	*mutex;
}	t_mute;
int main(void)
{
	t_mute mute;

	mute.mutex = malloc(sizeof(pthread_mutex_t));
	if (mute.mutex[0] != NULL)
		printf("%d\n", mute.mutex);
}
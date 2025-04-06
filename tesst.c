#include "INCLUDES/philo.h"

int main(void)
{
	printf("t_vals : %ld | sum of its components sizes : %ld, int %ld, int * %ld\n", sizeof(t_vals), 4 * sizeof(int) + sizeof(int *) + sizeof(t_time) + sizeof(t_philo *), sizeof(int), sizeof(int *));
	printf("t_philo %ld, t_philo * %ld\n", sizeof(t_philo), sizeof(t_philo *));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:51:42 by mmarcele          #+#    #+#             */
/*   Updated: 2022/05/27 15:31:18 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h> // del later
# include <stdlib.h>
# include <time.h>
# include <pthread.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

typedef struct s_philo
{
	int		number_of_philosophers;
    time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	int		number_of_times_each_philosopher_must_eat;
}			t_philo;

#endif

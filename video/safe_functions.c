/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 22:38:27 by dvavryn           #+#    #+#             */
/*   Updated: 2025/07/05 22:56:24 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t	bytes)
{
	void	*out;

	out = malloc(bytes);
	if (!out)
		error_exit("Malloc error");
	return (out);
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		error_exit("The value specified by mutex is invalid");
	else if (status == EINVAL && opcode == INIT)
		error_exit("The value specified by attr is invalid");
	else if (status == EDEADLK)
		error_exit("A deadlock would occur if the thread blocked waiting for mutex");
	else if (status == EPERM)
		error_exit("The current thread does not hole a lock on mutex");
	else if (status == ENOMEM)
		error_exit("The process connot allocate enough memory to creat another mutex");
	else if (status == EBUSY)
		error_exit("Mutex is locked");
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_thread_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_thread_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_thread_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_thread_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Wrong OPCODE for mutex_handle");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode for thread_handle:"
			"use <CREATE> <JOIN> <DETACH>");
}

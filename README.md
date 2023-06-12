<p align="center">
  <img src="https://github.com/jotavare/jotavare/blob/main/42/banner/new/42_philosophers_banner_new.png">
</p>

<p align="center">
	<img src="https://img.shields.io/badge/status-finished-success?color=%2312bab9&style=flat-square"/>
	<img src="https://img.shields.io/badge/evaluated-18%20%2F%2012%20%2F%202022-success?color=%2312bab9&style=flat-square"/>
	<img src="https://img.shields.io/badge/score-100%20%2F%20100-success?color=%2312bab9&style=flat-square"/>
	<img src="https://img.shields.io/github/languages/top/jotavare/philosophers?color=%2312bab9&style=flat-square"/>
	<img src="https://img.shields.io/github/last-commit/jotavare/philosophers?color=%2312bab9&style=flat-square"/>
	<a href='https://www.linkedin.com/in/joaoptoliveira' target="_blank"><img alt='Linkedin' src='https://img.shields.io/badge/LinkedIn-100000?style=flat-square&logo=Linkedin&logoColor=white&labelColor=0A66C2&color=0A66C2'/></a>
	<a href='https://profile.intra.42.fr/users/jotavare' target="_blank"><img alt='42' src='https://img.shields.io/badge/Porto-100000?style=flat-square&logo=42&logoColor=white&labelColor=000000&color=000000'/></a>
</p>

<p align="center">
	<a href="#about">About</a> •
	<a href="#how-to-use">How to use</a> •
	<a href="#mandatory">Mandatory</a> •
	<a href="#bonus">Bonus</a> •
	<a href="#norminette">Norminette</a> •
	<a href="#license">License</a>
</p>

## ABOUT
In a house, five philosophers reside and gather around a shared dining table. Each philosopher has a designated place at the table where they dine. Their primary concern, apart from their philosophical pursuits, revolves around a particular dish of spaghetti that requires the use of two forks. There is a fork placed between each plate on the table.

The philosophers follow a rhythm of alternating between deep contemplation and enjoying their meal. However, they face a condition before they can commence eating: they must have both a left and right fork at their disposal. The availability of two forks is contingent upon their adjacent neighbors being engaged in contemplation rather than dining. Once a philosopher finishes their meal, they will set down both forks.

The challenge lies in designing a behavioral framework, or a concurrent algorithm, that ensures no philosopher will go hungry. This means establishing a system where they can perpetually alternate between eating and thinking, all while acknowledging the unpredictable nature of when their fellow philosophers will desire to eat or engage in contemplation.

For further exploration of this problem, you can consult the <a href="https://github.com/jotavare/libft/blob/master/subject/en_subject_libft.pdf">Wikipedia</a> article.

<a href="https://github.com/jotavare/philosophers/blob/master/subject/en_subject_philosophers.pdf">Click here</a> for the subject of this project.

## HOW TO USE
#### COMPILATION
#### 1º - Clone the repository
```bash
git clone git@github.com:jotavare/philosophers.git
```

#### 2º - Enter the project folder and run `make`
```bash
cd philosophers/philosophers
make
```

#### 3º - Launch the program
> The last argument is optional for the execution of the program.
```bash
./philo [n of philos] [time to die] [time to eat] [time to sleep] [n times each philo must eat]
```

#### MAKEFILE RULES

`make` or `make all` - Compile philosophers **mandatory** files.

`make clean` - Delete all .o (object files) files.

`make fclean` - Delete all .o (object file) and .a (executable) files.

`make re` - Use rules `fclean` + `all`.

#  Step 1: Understand the subject well
Objective: not to kill philosophers
 
- each philosopher is a **thread** , and each fork is a **mutex**
- they do in order: eat - sleep - think (they don't really think, they wait to have their forks to eat)
- to eat they must have two forks, knowing that there is only one fork per philosopher
- if one of them dies, the simulation stops and death must be displayed in a maximum of 10 milliseconds
- write each change of philosopher status
 
./philo arg1 arg2 arg3 arg4 arg5
 
- arg1 = number_of_philosophers (number of philosophers and number of forks)
- arg2 = time_to_die (if he hasn't eaten for time_to_die milliseconds he dies)
- arg3 = time_to_eat (time to eat with two forks in milliseconds)
- arg4 = time_to_sleep (time to sleep in milliseconds)
- arg5 = number_of_times_each_philosopher_must_eat (number of times each philosopher must eat, arg optional)
 
 
Philo (=philo_one) : threads et mutexs.
 
Philo_bonus (=philo_three) : processes and semaphores.
 
 
#  Step 2: Getting familiar with threads and mutexes
 
Thread: There is always at least one thread per process. But we can create more, and each thread includes these unique elements and its elements shared with all the other threads of the same process (code section, data section, operating-system resources like open files and signals)...
 
The libraries that allow to manage threads: pthread and openmp
 
```
pthread_create(&p->ph[i].thread_id, NULL, thread, &p->ph[i]); //pour creer un thread avec pthread
```
 
But if two threads of the same process want to access the same shared memory variable at the same time, it creates undefined behaviors (see data races below). Hence the use of mutexes. Mutexes block a piece of code, and other threads have to wait to execute that piece of code. Like a toilet key, each in turn.
 
Example here if we remove the mutexes str printed by thread 1 is overlapped by str printed by thread 2 and it will be "treatdr e1a d: 1c o:u ccoouu ccoau cvaa v?a":
 
```
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
typedef struct s_p
{
 pthread_mutex_t mutex;
 int i;
} t_p;
int ft_strlen(char *str)
{
 int i = 0;
 while (str[i])
 i++;
 return (i);
}
void *go1(void *pp)
{
 char *str;
int i = 0;
 t_p *ppp;
 ppp = (t_p *)pp;
 str = "tread 1 : coucou ca va ? \n";
 pthread_mutex_lock(&ppp->mutex); // si on enleve ici
while (str[i])
{
 write(1, &str[i], 1);
i++;
}
 pthread_mutex_unlock(&ppp->mutex); // si on enleve ici
 return (NULL);
}
int main()
{
 pthread_t thread_id1;
 pthread_t thread_id2;
 t_p p;
t_p *pp;
 pp = (malloc(sizeof(t_p) * 1));
pp = &p;
 p.i = 3;
 pthread_mutex_init(&p.mutex, NULL); // obligatoire de init le mutex
 pthread_create(&thread_id1, NULL, go1, (void *)pp);
 pthread_create(&thread_id2, NULL, go1, (void *)pp);
 sleep(1);
}
```
 
SO :
- Each fork has its own mutex which allows it to be locked when a philosopher takes it.
- We also use a mutex shared by all the philosophers which allows to print text without mixing as in the example above.
 
 
[ Tuto video que j'ai utilise pour commencer ](https://www.youtube.com/watch?v=o_GbRujGCnM&t=377s)
 
 
#  Step 3: Strategy
 
- Make even or odd philosophies leave with a delay. Because if all the philosophers start at the same time and take their right fork, no one will be able to eat.
```
 if (ph->id % 2 == 0)
 ft_usleep(ph->pa->eat / 10);
```
 
- Each philosopher has his own fork on the left (l_f) and borrows that of his neighbor on the right thanks to the pointer ( \* r_f) which points to the l_f of the neighbor on the right:
 
```
while (i < p->a.total)
{
 p->ph[i].id = i + 1;
pthread_mutex_init(&p->ph[i].l_f, NULL); // each philosopher holds his own fork on the left
 if (i == p->a.total - 1)
p->ph[i].r_f = &p->ph[0].l_f; // and borrows that of its right neighbor
 else
p->ph[i].r_f = &p->ph[i + 1].l_f; // and borrows that of its right neighbor
 i++;
}
```
 
- Obliged to check the death in a side thread otherwise do not realize in time if there is one who dies. But on the other hand if the thread check continues if the philosophy is dead it lowers the performance too much. So each time a philo goes to do his activities, a thread that checks for death is launched. And this thread will usleep(time_to_die) and then check if the philosophy is dead.
 
```
pthread_create(&ph->thread_death_id, NULL, is_dead, data);
void *is_dead(void *data)
{
 ft_usleep(ph->pa->die + 1);
 if (!check_death(ph, 0) && !ph->finish && ((actual_time() - ph->ms_eat) \
 >= (long)(ph->pa->die)))
the philosophy is dead
```
 
 
#  Step 4: Time management
 
| second | millisecond | microsecond |
|---------|-------|-------|
| 1 | 1000 | 1e+6 |
| 0.001 | 1 | 1000 |
 
- How gettimeofday works:
```
 struct timeval current_time;
 gettimeofday(&current_time, NULL);
 printf("seconds : %ld\nmicro seconds : %d", current_time.tv_sec, current_time.tv_usec);
```
 
- To know the current time in milliseconds with gettimeofday:
```
long int actual_time(void)
{
 long int time;
struct timeval current_time;
 time = 0;
 if (gettimeofday(&current_time, NULL) == -1)
 ft_exit("Gettimeofday returned -1\n");
 time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000); //temps en millisecondes
 return (time);
}
```
 
- create your own function ft_usleep because the real function waits at least the time indicated to it, so not precise
```
void ft_usleep(long int time_in_ms)
{
 long int start_time;
 start_time = 0;
 start_time = actual_time();
 while ((actual_time() - start_time) < time_in_ms)
 usleep(time_in_ms / 10);
}
````
 
# Etape 5: Leaks, segfaults et data races
 
**Data race** :
two or more threads in a single process access the same memory location concurrently, and at least one of the accesses is for writing, and the threads are not using any exclusive locks to control their accesses to that memory.
When these three conditions hold, the order of accesses is non-deterministic, and the computation may give different results from run to run depending on that order. Some data-races may be benign (for example, when the memory access is used for a busy-wait), but many data-races are bugs in the program.
 
To fix data races: **-g fsanitize=thread**
 
**valgrind --tool=helgrind** or **valgrind --tool=drd** : if these return warnings or errors, it means that a mutex is missing, or that it is misused. You have to check manually, but often it is a sign that the project is not good, even if it seems to work."
 
- detached: as soon as the thread ends its memory is clean. Be careful that the main does not end before we are finished the thread
- reachable: does not destroy his memory when he has finished. pthread_join blocks until the thread is finished
 
 
 
## TESTS
 
With fsanitize or valgrind there are less good performance of course
 
| Example | Expected Result |
| :--: | :--: |
| ./philo 1 200 200 200           | philo 1 only takes a fork and dies after 200 ms                  |
| ./philo 2 800 200 200           | nobody dies                                                      |
| ./philo 5 800 200 200           | nobody dies                                                      |
| ./philo 5 800 200 200 7         | the simulation stops when each philo has eaten 7 times           |
| ./philo 4 410 200 200           | nobody dies                                                      |
| ./philo 4 310 200 200           | a philosophy dies                                                |
| ./philo 4 500 200 1.2           | invalid argument                                                 |
| ./philo 4 0 200 200             | invalid argument                                                 |
| ./philo 4 -500 200 200          | invalid argument                                                 |
| ./philo 4 500 200 2147483647    | a philo dies after 500 ms                                        |
| ./philo 4 2147483647 200 200    | nobody dies                                                      |
| ./philo 4 214748364732 200 200  | invalid argument                                                 |
| ./philo 4 200 210 200           | a philo dies, it is necessary to display the death before 210 ms |
| ./philo 5 800 200 150           | nobody dies                                                      |
| ./philo 3 610 200 80            | nobody dies                                                      |
 

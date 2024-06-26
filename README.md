<p align="center">
  <img src="https://github.com/jotavare/jotavare/blob/main/42/banners/piscine_and_common_core/github_piscine_and_common_core_banner_philosophers.png">
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
	<a href="#philosophers">Philosophers</a> •
	<a href="#examples">Examples</a> •
	<a href="#norminette">Norminette</a> •
	<a href="#contributing">Contributing</a> •
	<a href="#license">License</a>
</p>

## ABOUT
Five philosophers reside in a house, sharing a dining table with a special spaghetti dish requiring two forks, one between each plate. To eat, a philosopher needs both left and right forks, which depend on neighbours' activities. They alternate between contemplating and dining, setting down both forks after a meal.

The challenge I had, was to figure out how to make sure no philosopher goes hungry while dealing with the unpredictability of when others want to eat or think. It's like trying to create a system that keeps everyone fed without knowing when they'll be hungry or lost in thought.

For further exploration of this problem, you can consult the <a href="https://en.wikipedia.org/wiki/Dining_philosophers_problem">Wikipedia</a> article.

- [Subject](https://github.com/jotavare/philosophers/blob/master/subject/en_subject_philosophers.pdf) `PDF`
- [References](https://github.com/jotavare/42-resources#03-philosophers) `GitHub`

## HOW TO USE
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

## MANDATORY
> Objective: can't kill the philosophers.
- [x] Each philosopher is a **thread** and each fork is a **mutex**.
- [x] They do it in order: `eat` -> `sleep` -> `think` (they don't think, they wait to have their forks to eat).
- [x] To eat they must have two forks, knowing that there is only one fork per philosopher.
- [x] If one of them dies, the simulation stops and death must be displayed in a maximum of 10 milliseconds.
- [x] Write each change of the philosopher's status.
 
## BONUS
> The bonus program takes the same arguments and it as to comply with the mandatory rules.
- [ ] All the forks are put in the middle of the table.
- [ ] They have no states in memory, but the number of available forks is represented by a semaphore.
- [ ] Each philosopher should be a process, but the main process should not be a philosopher.

## PHILOSOPHERS

```bash
./philo [arg1] [arg2] [arg3] [arg4] [arg5]
``` 

| Arg | Function | Description |
| :- | :- | :- |
| [arg1] | `number_of_philosophers`                    | Number of philosophers and number of forks.              |
| [arg2] | `time_to_die`                               | If he hasn't eaten for time_to_die milliseconds he dies. |
| [arg3] | `time_to_eat`                               | Time to eat with two forks in milliseconds.              |
| [arg4] | `time_to_sleep`                             | Time to sleep in milliseconds.                           |
| [arg5] | `number_of_times_each_philosopher_must_eat` | Number of times each philosopher must eat. (Optional)    |

#### THREADS AND MUTEXES
A **thread** is a unit of execution within a process. Each **process** has at least one **thread**, but additional **threads** can be created. A **thread** consists of unique elements and shared elements with other **threads** of the same process, such as the code section, data section, and operating system resources like open files and signals.

However, if two **threads** of the same process try to access the same shared memory variable simultaneously, it can lead to undefined behaviours, known as **data races**. To prevent this, **mutexes** are used. **Mutexes** block a piece of code, allowing only one **thread** at a time to execute that piece of code, similar to how a toilet key is used.

In the context of the given example:
* Each fork has its own **mutex**, which can be locked when a philosopher takes it.
* There is also a **mutex** shared by all the philosophers, ensuring that text is printed without mixing.

#### STRATEGY
>To prevent conflicts and ensure proper execution, the following strategies are employed:

Make even or odd philosophers start with a delay.** If all philosophers start at the same time and take their right fork, none of them will be able to eat.

```c
if (ph->id % 2 == 0)
  ft_usleep(ph->pa->eat / 10);
```
 
Each philosopher has their fork on the left (`left_fork`) and borrows the fork from their right neighbour using a pointer (`*right_fork`) that points to the left fork of the neighbour on the right.
 
```c
while (i < p->a.total)
{
  p->ph[i].id = i + 1;
  // Each philosopher has their fork on the left
  pthread_mutex_init(&p->ph[i].left_fork, NULL);
  if (i == p->a.total - 1)
    // Borrow the fork from the right neighbour if the philosopher is the last one
    p->ph[i].right_fork = &p->ph[0].left_fork;
  else
    // Borrow the fork from the right neighbor
    p->ph[i].right_fork = &p->ph[i + 1].left_fork;
  i++;
}
```
 
Death checking is performed in a separate **thread** to ensure timely detection. If the main **thread** continuously checks for death, it can significantly impact performance. So, when a philosopher performs their activities, a separate **thread** is launched to check if any philosopher has died. This **thread** sleeps for the duration specified by `time_to_die` and then checks if the philosopher is still alive.
 
```c
pthread_create(&ph->thread_death_id, NULL, is_dead, data);
void *is_dead(void *data)
{
  ft_usleep(ph->pa->die + 1);
  if (!check_death(ph, 0) && !ph->finish && ((actual_time() - ph->ms_eat) >= (long)(ph->pa->die)))
{
// The philosopher is dead
```
 
#### TIME MANAGEMENT
> Time can be managed using the following conversions:

| Second | Millisecond | Microsecond |
| :-- | :-- | :-- |
| 1     | 1000 | 1e+6 |
| 0.001 | 1    | 1000 |
 
The `gettimeofday` function is used to get the current time, which is stored in a timeval structure. The following example demonstrates how `gettimeofday` works:
```c
struct timeval current_time;
gettimeofday(&current_time, NULL);
printf("seconds : %ld\nmicro seconds : %d", current_time.tv_sec, current_time.tv_usec);
```
 
To get the current time in milliseconds using `gettimeofday`, the following function can be used:
```c
long int actual_time(void)
{
  long int time;
  struct timeval current_time;
  time = 0;
  if (gettimeofday(&current_time, NULL) == -1)
    ft_exit("Gettimeofday returned -1\n");
  //time in milliseconds
  time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
  return (time);
}
```
 
A custom `ft_usleep` function is created to provide more precise control over the sleep time compared to the actual `usleep` function, which waits at least the specified time. The custom function repeatedly checks the time difference until the desired time has passed.
```c
void ft_usleep(long int time_in_ms)
{
  long int start_time;
  start_time = 0;
  start_time = actual_time();
  while ((actual_time() - start_time) < time_in_ms)
    usleep(time_in_ms / 10);
}
````
 
#### DATA RACES
A **data race** occurs when two or more **threads** within a single process concurrently access the same memory location, with at least one of the accesses being a write operation, and no exclusive locks are used to control the accesses. **Data races** can lead to a non-deterministic order of accesses and produce different results from run to run. While some **data races** may be harmless, many are bugs in the program.

To fix **data races**, the option `-g fsanitize=thread` can be used.

The tools `valgrind --tool=helgrind` or `valgrind --tool=drd` can be utilized to detect any missing or misused **mutexes**. Warnings or errors from these tools indicate potential issues that should be manually checked. Such issues are often signs of a problematic project, even if it appears to be working.

- `detached` refers to a **thread** that cleans its memory as soon as it finishes. It is essential to ensure that the main **thread** does not terminate before the detached **thread** completes its execution.
- `reachable` refers to a **thread** that does not destroy its memory when it finishes. The `pthread_join` function can be used to block the execution until the **thread** finishes.
 
## EXAMPLES
> The performance will change if you use `-fsanitize` and `valgrind` or both together.
 
| Example | Expected Result |
| :-- | :-- |
| `./philo 1 200 200 200`           | Philosopher 1 takes a fork and dies after 200 ms.              |
| `./philo 2 800 200 200`           | No philosopher dies.                                           |
| `./philo 5 800 200 200`           | No philosopher dies.                                           |
| `./philo 5 800 200 200 7`         | The program stops when each philosopher has eaten 7 times.     |
| `./philo 4 410 200 200`           | No philosopher dies.                                           |
| `./philo 4 310 200 200`           | A philosopher dies.                                            |
| `./philo 4 500 200 1.2`           | Invalid argument.                                              |
| `./philo 4 0 200 200`             | Invalid argument.                                              |
| `./philo 4 -500 200 200`          | Invalid argument.                                              |
| `./philo 4 500 200 2147483647`    | A philosopher dies after 500 ms                                |
| `./philo 4 2147483647 200 200`    | No philosopher dies.                                           |
| `./philo 4 214748364732 200 200`  | Invalid argument.                                              |
| `./philo 4 200 210 200`           | A philosopher dies, it should display the death before 210 ms. |
| `./philo 5 800 200 150`           | No philosopher dies.                                           |
| `./philo 3 610 200 80`            | No philosopher dies.                                           |
 
## NORMINETTE
> At 42 School, it is expected that almost every project is written following the Norm, which is the coding standard of the school.

```
- No for, do...while, switch, case, goto, ternary operators, or variable-length arrays allowed;
- Each function must be a maximum of 25 lines, not counting the function's curly brackets;
- Each line must be at most 80 columns wide, with comments included;
- A function can take 4 named parameters maximum;
- No assigns and declarations in the same line (unless static);
- You can't declare more than 5 variables per function;
- ...
```

* [42 Norms](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf) - Information about 42 code norms. `PDF`
* [Norminette](https://github.com/42School/norminette) - Tool to respect the code norm, made by 42. `GitHub`
* [42 Header](https://github.com/42Paris/42header) - 42 header for Vim. `GitHub`

## CONTRIBUTING

If you find any issues or have suggestions for improvements, feel free to fork the repository and open an issue or submit a pull request.

## LICENSE

This project is available under the MIT License. For further details, please refer to the [LICENSE](https://github.com/jotavare/philosophers/blob/master/LICENSE) file.

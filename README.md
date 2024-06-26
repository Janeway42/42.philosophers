# **42.Philosophers**


Run:
------
- **make**
- ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep (optional: number_of_times_each_philosopher_must_eat)

-------------------------------------------------------------------

[42 The Network](https://www.42network.org/) Assignment:
-----------

Dining philosophers [problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)  

Input: 
-------
- number_of_philosophers: The number of philosophers and also the number of forks.
- time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
- time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
- number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.

- Each philosopher has a number ranging from 1 to number_of_philosophers.
- Philosopher number 1 sits next to philosopher number number_of_philosophers. Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1

Specific rules: 
---------------
- **philo**
  - Each philosopher is a **thread**.
  - There is **one fork** between each pair of philosophers. Therefore, if there are several philosophers, each philosopher has a fork on their left side and a fork on their right side. If there is only one philosopher, there should be only one fork on the table.
  - To prevent philosophers from duplicating forks, a mutex is used to protect the forks state for each one of them.
- **philo_bonus**
  - The forks are placed in the middle of the table and thus represented with the use of a **semaphore**
  - Each philosopher is a **process**. However, the main process cannot be a philosopher process.
--- 
- Allowed external functions: memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

-------------------------------------------------------------------

Code format: 
------------
The code must be written in accordance to the 42 set of norms.  
These include for example a maximum of 25 lines per function, at most 80 columns per line, comments included and a maximum of five functions per file. 

-------------------------------------------------------------------

Useful info:
---
- [Philosophers visualizer](https://nafuka11.github.io/philosophers-visualizer/)    *(input = output of philo)*

-------------------------------------------------------------------

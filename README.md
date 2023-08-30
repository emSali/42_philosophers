# Philosophers
### A project about creating threads and mutexes in C

## Executing the program
1. cd into the project folder
2. 'make'
3. './philosopers number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]'

◦ **number_of_philosophers**: The number of philosophers and also the number of forks.

◦ **time_to_die (in milliseconds)**: If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.

◦ **time_to_eat (in milliseconds)**: The time it takes for a philosopher to eat. During that time, they will need to hold two forks.

◦ **time_to_sleep (in milliseconds)**: The time a philosopher will spend sleeping.

◦ **number_of_times_each_philosopher_must_eat (optional argument)**: If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a   philosopher dies.

## Concepts

**THREADS**: simultanous execution of code. Difference to processes is, that memory is shared

**MUTEX**: Lock around a section of code to counter race conditions. Protects code lines against other threads trying to execute simultanously.

**Race condition**:

## Functions

**memset**:

**usleep**:

**gettimeofday**:

**pthread_create**:

**pthread_detach**:

**pthread_join**: takes two paramenters. 1. the value of 'pthread_t' variable and void **ret. ret is a variable in which the return value of the called function from p_thread_create can be saved in.

**pthread_mutex_init**: initializes a mutex. First parameter is the adress to a 'pthread_mutex_t' type variable. Second one is attributes, when passing NULL, they are set to default

**pthread_mutex_destroy**: destroys the created mutex. Takes adress to the 'pthread_mutex_t' type variable as only argument

**pthread_mutex_lock**: locks the following code lines. Takes address to variable as only argument

**pthread_mutex_unlock**: unlocks the previous locked thread. Takes adress to variable as only argument

# philosophers

A 42 school project simulating the Dining Philosophers Problem to explore concurrent programming with threads and mutexes.

## Problem

A number of philosophers sit around a table. Each philosopher alternates between thinking, eating, and sleeping. To eat, a philosopher needs both forks adjacent to them. The goal is to prevent deadlock and starvation.

## Usage

```bash
make
./philo <nb_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [nb_times_each_philosopher_must_eat]
```

Example:
```bash
./philo 5 800 200 200
```

## Arguments

| Argument | Description |
|----------|-------------|
| `nb_philosophers` | Number of philosophers (and forks) |
| `time_to_die` | ms before a philosopher dies without eating |
| `time_to_eat` | ms it takes to eat |
| `time_to_sleep` | ms spent sleeping |
| `nb_times_each_philosopher_must_eat` | (optional) Stop when all philosophers ate this many times |

## Implementation

- One thread per philosopher
- One mutex per fork
- A monitor thread checks for deaths

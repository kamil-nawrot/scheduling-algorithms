# Task scheduling
This repository includes programs made for **Control of Discrete Procceses** academic course. All implementations was made from scratch in pure C++, without using any non-standard libraries. They are not well-optimized in most cases, but the main goal was to understand how specific algorithm works, not to code the fastest version possible.


## Programs
The list below briefly describes every program in this repository. Names of subheaders correspond to filenames.

### RPQ
First attempt to solve **single machine scheduling problem** (also known as RPQ), without any prior knowledge about that topic. A goal was to minimize total makespan by organizing tasks in specific order. Each task had release time (R), proccessing time (P) and delivery time (Q). My custom-made algorithm dealt with the problem quite well, but it had many imperfections. It resembles Schrage algorithm (will be described later).

### WiTi
Again **single machine scheduling** but now instead of minimizing makespan, algorithm should find order with the smallest total tardiness. In this problem, each task was described by proccessing time (P), weight (W) and desired ending time (D). Delay for each task was computed as a product of weight and difference between real and desired ending time (delay cannot be greater than zero). Dynammic programming approach was used in this algorithm.

### NEH
It's heuristic algorithm for solving **permutation flowhop scheduling problem**, where the goal is to find optimal order of *n* jobs to be proccessed on *m* machines. Single machine can only proccess one job at the time. NEH find correct sequence (not the best one), by adding one job in every step and compute best place for it between other tasks added in previous steps. 

### Schrage
Better implementation of algorithm described in first paragraph of this section. Now it's proper, correctly working Schrage algorithm in two versions: normal and relaxed, where dividing tasks into smaller parts is allowed. 

> **Note:** Schrage algorithm is an essential part of Carlier algorithm (below), so it's included in `carlier/` directory. 

### Carlier
Final algorithm: the most complex one, but it always gives optimal results for **single machine scheduling problem**. It is based on B&B strategy and it uses Schrage to estimate upper- and lower-band for every sequence. Next, it finds critical paths and run recurrently with changed parameters. Finally, algorithm returns optimal order and final makespan.

## References
Main source of knowledge was **Mariusz Makuchowski, Ph.D.Eng.** lectures, available [here](http://mariusz.makuchowski.staff.iiar.pwr.wroc.pl/download/courses/sterowanie.procesami.dyskretnymi/wyk.slajdy/).
Datasets were taken from [here](http://mariusz.makuchowski.staff.iiar.pwr.wroc.pl/download/courses/sterowanie.procesami.dyskretnymi/lab.instrukcje/).

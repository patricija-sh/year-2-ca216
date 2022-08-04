# Author: Patricija Shalkauskaite, Student ID: 20467952
# I have read and understood the DCU Academic Integrity and Plagiarism Policy (available at http://www.dcu.ie/registry/examinations/index.shtml)
# Shortest Job First algorithm.
from utility import *

def sjf_sort(list):
    return list[2]  # If the process has the same amount of time as the next one, fcfs is implemented.

def main():
    turnaround = 0           # The amount of waiting and execution time.
    turnaround_sum = 0       # The sum of each process' turnaround time.
    processes = make_list()  # A list of lists to house processes and their information.
    wait_time_sum = 0        # The sum of each process' waiting time.

    sorted_procs = sorted(processes, key=sjf_sort)

    for proc in sorted_procs:
        turnaround += proc[2]  # Adding each process' CPU burst time.
        turnaround_sum += turnaround
        wait_time_sum += turnaround - proc[2]  # waiting time is turnaround time - burst time
        print(f"Process ({proc[0]}) arrived at time (0) and ran for ({proc[2]}) MS. It had a turn-around time of ({turnaround}).")

    avg_turnaround(turnaround_sum, len(sorted_procs))  # Getting the average turn-around time.
    avg_wait_time(wait_time_sum, len(sorted_procs))

if __name__ == "__main__":
    main()
# Author: Patricija Shalkauskaite, Student ID: 20467952
# I have read and understood the DCU Academic Integrity and Plagiarism Policy (available at http://www.dcu.ie/registry/examinations/index.shtml)
# Priority scheduling algorithm.

from utility import *

def priority_sort(list):
    return list[1]  # if the process has the same amount of time as the next one, fcfs is implemented.

def main():
    processes = make_list()  # A list of lists to house processes and their information.
    turnaround = 0           # The amount of waiting and execution time.
    turnaround_sum = 0       # The sum of each process' turnaround time.
    wait_time_sum = 0        # The sum of each process' waiting time.
    sorted_procs = sorted(processes, key=priority_sort, reverse=True)  # Sort the processes list based on their priority.

    for proc in sorted_procs:
        turnaround += proc[2]  # Getting each tasks's CPU burst time.
        turnaround_sum += turnaround
        wait_time_sum += turnaround - proc[2]  # waiting time is turnaround time - burst time
        print(f"Process ({proc[0]}) arrived at time (0) and ran for ({proc[2]}) MS. It had a turn-around time of ({turnaround}).")
    
    avg_turnaround(turnaround_sum, len(processes))  # Getting the average turn-around time.
    avg_wait_time(wait_time_sum, len(processes))    # Getting the average waiting time.

if __name__ == "__main__":
    main()
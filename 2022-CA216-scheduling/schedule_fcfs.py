# Author: Patricija Shalkauskaite, Student ID: 20467952
# I have read and understood the DCU Academic Integrity and Plagiarism Policy (available at http://www.dcu.ie/registry/examinations/index.shtml)
# First Come First Served algorithm.

from utility import *

def main():
    turnaround = 0           # The amount of waiting + execution time.
    turnaround_sum = 0       # The sum of each process' turnaround time.
    processes = make_list()  # A list of lists to house processes and their information.
    wait_time_sum = 0        # The sum of each process' waiting time.

    # name, priority, burst_time = process[0], process[1], process[2]
    for process in processes:
        turnaround += process[2]
        turnaround_sum += turnaround
        wait_time_sum += turnaround - process[2]  # waiting time is turnaround time - burst time
        print(f"Process ({process[0]}) arrived at time (0) and ran for ({process[2]}) MS. It had a turn-around time of ({turnaround}).")

    avg_turnaround(turnaround_sum, len(processes))  # Getting the average turn-around time.
    avg_wait_time(wait_time_sum, len(processes))    # Getting the average turn-around time.

if __name__ == "__main__":
    main()
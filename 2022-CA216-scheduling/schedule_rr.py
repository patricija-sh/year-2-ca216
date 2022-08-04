# Author: Patricija Shalkauskaite, Student ID: 20467952
# I have read and understood the DCU Academic Integrity and Plagiarism Policy (available at http://www.dcu.ie/registry/examinations/index.shtml)
#  Round-Robin algorithm. 
from utility import *

def main():
    processes = make_list()           # A list of lists to house processes and their information.
    proc_dict = make_dict(processes)  # A dictionary to house the task names and their associated burst times.
    turnaround = 0                    # The amount of waiting and execution time.
    turnaround_sum = 0                # The sum of each process' turnaround time.
    time_quantum = 30                 # The tasks are allowed a max of 10 miliseconds of cpu run time.
    wait_time_sum = 0                 # The sum of each process' waiting time.
    proc_count = len(processes)

    while(len(processes) != 0):
        if(processes[0][2] > time_quantum):      # If burst time is greater than 10,
            processes[0][2] -= time_quantum      # subtract 10 away from burst time,
            turnaround += time_quantum           # add it to the turnaround time,
            processes.append(processes.pop(0))   # and move task to the end of the list.
        else:
            turnaround += processes[0][2]  # Add the remaining burst time to turnaround.
            turnaround_sum += turnaround
            wait_time_sum += turnaround - proc_dict[processes[0][0]]  # waiting time is turnaround time - burst time
            print(f"Process ({processes[0][0]}) arrived at time (0) and ran for ({proc_dict[processes[0][0]]}) MS. It had a turn-around time of ({turnaround}).")
            processes.pop(0)  # We're done with the process, so get rid of it.

    avg_turnaround(turnaround_sum, proc_count)  # Getting the average turn-around time.
    avg_wait_time(wait_time_sum, proc_count)    # Getting the average waiting time.

if __name__ == "__main__":
    main()
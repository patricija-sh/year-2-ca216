# Author: Patricija Shalkauskaite, Student ID: 20467952
# I have read and understood the DCU Academic Integrity and Plagiarism Policy (available at http://www.dcu.ie/registry/examinations/index.shtml)

import sys

def make_list():
    if(len(sys.argv) == 2):  # check if a file has been provided with process and their info.
        file = sys.argv[1]
    else:
        print("No file with processes' contents given!")
        sys.exit()
    
    processes = []

    with open(file) as f:
        for line in f:
            try:
                process, priority, burst_time = line.split()
            except ValueError:  # E.g. if input is T1, 4 and no burst time is given.
                print("Not enough information about process given.\nThe format is <name> <priority> <burst time>")
                sys.exit()
            
            try:
                processes.append([process.strip(","), int(priority.strip(",")), int(burst_time.strip(","))])
            except ValueError:  # Incorrect data type is given for priority and/or burst time.
                print(f"{process}'s priority and/or burst time must be an integer value!")
                sys.exit()
                
    return processes

def make_dict(process_list):
    dict = {}
    for process in process_list:
        dict[process[0]] = int(process[2])  # associate the process' name with their burst time.
    return dict

def avg_turnaround(sum, proc_count):
    print(f"The average turn-around time is {sum / proc_count}.")

def avg_wait_time(sum, proc_count):
    print(f"The average waiting time is {sum / proc_count}.")

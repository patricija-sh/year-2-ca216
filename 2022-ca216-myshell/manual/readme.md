# **General Commands Manual**


## **Name**
`myshell`

### **Description**
`myshell` executes commands provided through standard input or a file.
   
### **Syntax**
`[]` denotes optional fields.

`./myshell [batchfile]`

---

## **ENVIRONMENT CONCEPT**
This basic shell is built by entering `make`. The shell is started by entering `./myshell` in the command line, and it is exited by typing the `quit` command or doing Ctrl + C. When interacting with the shell, a prompt is shown with the current working directory displayed beside it. The shell contains nine internal commands, the last of which sends any external (unknown) commands to a function that interprets it. See the **COMMANDS** section for more information on the internal commands. Depending on the command, the program may be executed by the parent process or a child process. Where redirection is involved, files descriptors that reference `STDIN` and `STDOUT` are made to point to files instead so the appropriate commands can be inputted/outputted to files. See [1] and [2] for information about I/O redirection.

---

## **PROCESS CONCEPT**
When a batchfile isn't provided (see **Batchfile** in the **REDIRECTION** section), the shell will take in the input given into the prompt and proceed to check commands the parent process may execute. If the command entered isn't exectuable by the parent, the program is forked and a child process is born which then checks if the input given matches the commands it is allowed to execute. The child's commands utilise the `exec` function, which overwrites the main program and branches off into another program relevant to the command. See [3] for information about forking.

---

## **COMMANDS**

1. **Name**
    `cd`

    **Description**
    - Changes the current default directory if an argument is provided. 
    - If an argument is not present, the current directory is reported.
    - Supports shortcut `..` to go back one directory.

    **Syntax** 

    `cd [DIRECTORY]`


2. **Name**
    `clr`

    **Description**
    - Clears the screen.
    - Takes no arguments.

    **Syntax**
    `clr`


3. **Name**
    `dir`

    **Description**
    - Lists the contents of a directory in the same way `ls -al` does.
    - `l` = long style, `a` = show hidden files.
    - If no argument is provided after `dir` is entered, the current directory's content is listed.


    **Syntax**
    `[]` denotes optional fields.

    `dir [DIRECTORY]`


4. **Name**
    `environ`

    **Description**
    - List all the environment strings.
    - Takes no arguments.

    **Syntax**
    `environ`


5. **Name**
    `echo`

    **Description**
    - Echo on the display followed by a new line.

    **Syntax**
    `[` denotes optional fields.

    `echo arg_1, arg_2 ... arg_n [< input.txt] [> output.txt]`


6. **Name**
    `help`

    **Description**
    - Display the user manual using the `more` filter. 

    **Syntax**
    `help`


7. **Name**
    `pause`

    **Description**
    - Pause operation of the shell until 'Enter' key is pressed.

    **Syntax**
    `pause`


8. **Name**
    `quit`

    **Description**
    - Quit the shell.

    **Syntax**
    `quit`


9. **Name**
    `external_cmd`
    
    **Description**
    - Executes any external command UNIX supports.

    **Syntax**
    `command args_1 ... args_n [< input.txt] [> output.txt]`

    E.g.
    `python3 file.py`


---

## **BACKGROUND AND FOREGROUND EXECUTION**
### **Differences in Background and Foreground Execution**
Background execution enables multiple commands to be handled at once. Foreground execution can only run one process at a time so once a command is entered, the user must wait for the command to finish, unlike background processes that can multitask [4].


### **Shell's Process of Background Execution**
Whilst parsing the command the parent will check whether a command should run in the background.
In order to run a command in the background, the & operator must be given at the end of a command.
    E.g. `command &`

The process is as follows:
- A background flag is triggered should the command carry the `&` operator.
- The process is forked and the child process carries out the command.
- Meanwhile, the flag has alerted the parent process to not wait for the child process to finish and to move onto the next command.


---

## **REDIRECTION**
Input and/or output may be redirected to files depending on the operator given. See [1] and [2] for information about I/O redirection.
These operators are `<`, `>` and `>>` and they allow commands to read input from a file and/or output to a file.

The `<` redirection operator associates the file provided with the STDIN stream, and closes the old stream.
The `>` redirection operator associates the file provided with the STDOUT stream, and closes the old stream.

Input and output redirection may be performed simultaneously:
    `command ... < input.txt > output.txt`

### **Redirecting Input**
The general format for redirecting input is:
    `command ... < input_file`

If the file does not exists, a warning will appear.

### **Redirecting Output**
The general format for redirecting input is:
    `command ... > output_file`

If the file does not exist, it will be created.
If the file does exist, the current contents will be destroyed and overwritten.

### **Appending Redirected Output**
The general format for appending redirected output is:
    `command ... >> output_file`

If the file does not exist, it will be created.
If the file exists, the contents will be appended to the end of the file.
    
### **Batchfiles**
If a batchfile is provided, the commands are read and executed line by line, whose process is the same as described in **PROCESS CONCEPT** section, until the end-of-file has been reached and the shell exists.


## **CITATIONS**

[1] Liu Y., Yue Y., Guo L., "UNIX I/O System, I/O Redirection and Piping", in ***UNIX Operating System***, Springer, Berlin, Heidelberg, ch. 7, https://doi.org/10.1007/978-3-642-20432-6_7

[2] M. J. Rochkind, "Basic File I/O" in ***Advanced UNIX programming***, 2nd ed. Boston, Mass: Addison-Wesley, 2004, ch. 2, (https://learning-oreilly-com.dcu.idm.oclc.org/library/view/advanced-unix-programming/9780132466004/ch02.html).

[3] Abraham Silberschatz, Peter Baer Galvin & Greg Gagne: "3.3 Operations on Processes" in ***Operating systems Concepts***, 10th ed., John Wiley & Sons, ch. 3.3, pp. 116-119, 978-1-118-063.
  
[4]S. M. Palakollu, “Introduction to the Linux Environment,” in ***Practical System Programming with C***, Berkeley, CA: Apress, 2020, ch. 1, sec. 'Process Utilities', (https://learning-oreilly-com.dcu.idm.oclc.org/library/view/practical-system-programming/9781484263211/html/497677_1_En_1_Chapter.xhtml).

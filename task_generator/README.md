# test generator

## generated task explanation

this script generates file `task.c`.

The generated file asks for password, checks hash of it and prints if it is valid.

The task is to write script that modifies binary file to accept any password or to reverse it behavior.

Tasks are solvable because, for example, output string constants have equal length and can be swapped.

## per file explanation

### file `task_gen.sh`

* creates `\_\_task\_\_` dir in the same dir as the file, not in the current working dir
* executes task_gen.py and places generated files into file `task.c` in `\_\_task\_\_` dir

### file `task_gen.py`

* all temporary files are created in the same dir as the file, not in the current working dir.
* generates random function for the task.
* checks injectivity by creating temporary file, compiling and running it.
* prints to stdout generated source code of the task.




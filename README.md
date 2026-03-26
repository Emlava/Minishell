_This project has been created as part of the 42 curriculum by hudescam and elara-va._

# Minishell

### Description
This project consists of a simple shell replicating _some_ behaviors of Bash, based _only_ on the contents of both the École 42 minishell subject and the Bash Reference Manual.  
Although some features that are not requested nor mentioned in these two documents are implemented (e. g., tilde [~] and hyphen [-] management in paths given to the cd builtin), 42's subject is very clear when stating that "Anything that
is not asked is not required.", so such types of features _should not_ be expected.

### Instructions
#### Installation
Run  
```git clone https://github.com/Emlava/Minishell.git Minishell```
#### Compilation
Go into the Minishell repository by running ```cd Minishell``` and run the ```make``` command.  
The ```make``` command can take the following arguments:  
1. ```all```: compiles everything, creating all the object files, archives and the minishell executable; just like running ```make``` without arguments.
2. ```clean```: deletes all the object files and archives.
3. ```fclean```: deletes all the object files and archives, as well as the executable.
4. ```re```: deletes all the object files and archives, as well as the executable, and compiles everything again.
5. ```leak_check```: runs the shell with Valgrind, including suppressions so that the leaks comming from readline() are not shown (cf. École 42's subject).  
To check this use of Valgrind, check the very last line of the Makefile inside the root of this repository.

#### Execution
Once the compilation is done and the executable is created, start the minishell by running ```./minishell```.

### Resources
* École 42 Minishell subject
* Bash Reference Manual: https://www.gnu.org/software/bash/manual/bash.html

  #### AI Usage
  AI use was limited during the development of this project, involving explanations for general C or data structure concepts, but never to directly implement features of the shell, and much less to generate code.

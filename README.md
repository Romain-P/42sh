# 42sh
Clone this project with `git clone https://github.com/romain-p/shell
##### What is it
A simple shell in which you can write commands looking at unix binaries and builtins.
This shell manages multipipes, redirections and separators. A bashrc reader is started and read, at this moment, aliases and exported variables from the 42shrc (file name can be changed in the header i.e macro SHRC).
##### How to use
* First build the project executing `make`
* Launch on a command file with `./42sh file`
* Launch with piped commands with  `echo "command" | ./42sh`
* Launch as normal mode with `./42sh`
* Exit shell `pressing ^D`

**The code** respects *Epitech-Norm* and contains no memory leak and no error.  
**Notice :** contains the following built-ins `echo` `cd` `env` `setenv` `unsetenv` *(look @src/built-in)*
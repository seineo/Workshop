# Topic 1: The Shell

## What is the shell?

Their core they are all roughly the same: they allow you to run programs, give them input, and inspect their output in a semi-structured way.

We will focus on the Bourne Again Shell("bash" for short).

## Using the shell

When you launch your terminal, you will see a *prompt*:

```sh
seineo@dell:~$
```

At this prompt you can type a *command*, which will then be interpreted by the shell. The most basic command is to execute a program:

```sh
seineo@dell:~$ echo hello
hello
```

**But how does the shell know how to find the programs like `echo`?**

Well, the shell is a programming environment, just like Python, and so it has variables, conditionals, loops, and functions. When you run commands in your shell, you are really writing code that shell interprets. If the shell is asked to execute a command that doesn't match one of its programming keywords, it consults an *environment variable* called `$PATH` that lists which directories the shell should search for programs when it is given a command.

```sh
seineo@dell:~$ echo $PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin

#for example, execute the program `typora`
seineo@dell:~$ which typora    #find which file is executed for the given program name
/usr/bin/typora
seineo@dell:~$ cd ../../usr/bin   #change directory
seineo@dell:/usr/bin$ pwd       #print working directory 
/usr/bin
seineo@dell:/usr/bin$ ./typora    #execute it
```

In a path, `.` refers to the current directory, and `..` to its parent directory.  

## Navigating in the shell

```sh
seineo@dell:~$              # ~ refers to current user directory
seineo@dell:~$ pwd    # print out working directory
/home/seineo
seineo@dell:~$ cd /   
seineo@dell:/$              # / refers to root directory
seineo@dell:/$ cd -    
/home/seineo
seineo@dell:~$ cd -     # cd - can change directory back and forth
/
```

## Connecting programs

The `|` operator lets you “chain” programs such that the output of one is the input of another:

```sh
seineo@dell:~$ ls -l | tail -n1
-rw-------  1 root   root           1 Jan 27 19:50 grub.save
```

## A versatile and powerful tool

`sysfs` exposes a number of kernel parameters as files, so that you can easily reconfigure the kernel on the fly without specialized tools. For example, the brightness of your laptop’s screen is exposed through a file called `brightness` under

```sh
/sys/class/backlight
```

We may do this :

```sh
seineo@dell:/sys/class/backlight/intel_backlight$ sudo echo 100000 > brightness
bash: brightness: Permission denied
```

Actually, operations like `|`, `>`, and `<` are done *by the shell*, not by the individual program. `echo` and friends do not “know” about `|`. They just read from their input and write to their output, whatever it may be. In the case above, it is prevented from doing so since the shell does not run as root. So we can do like this: 

```sh
seineo@dell:/sys/class/backlight/intel_backlight$ echo 82000 | sudo tee brightness 
82000
```


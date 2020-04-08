# Shell Tools and Scripting

## Shell Scripting

To assign variables in bash use the syntax `foo=bar` and access the value of the variable with `$foo`.

Strings in bash can be defined with `'` and `"` delimiters but they are not equivalent. Strings delimited with `'` are literal strings and will not substitute variable values whereas `"` delimited strings will.

```sh
seineo@dell:~/Desktop/CS$ foo=bar
seineo@dell:~/Desktop/CS$ echo "$foo"
bar
seineo@dell:~/Desktop/CS$ echo '$foo'
$foo
```

As with most languages, shell has functions.

```sh
vi mcd.sh
#in mcd.sh
mcd() {
	mkdir -p "$1"
	cd "$1"
} 
#back to terminal
source mcd
#now the mcd function has been defined in shell, we can execute it
mcd hello/world
```



**Special variables**

- `$0` - Name of the script
- `$1` to `$9` - Arguments to the script. `$1` is the first argument and so on.
- `$@` - All the arguments
- `$#` - Number of arguments
- `$?` - Return code of the previous command
- `$$` - Process Identification number for the current script
- `!!` -  Entire last command, including arguments. A common pattern is to execute a command only for it to fail due to missing permissions, then you can  quickly execute it with `sudo` by doing `sudo !!`
- `$_` - Last argument from the last command. If you are in an interactive shell

Commands will often return output using `STDOUT`, errors through `STDERR` and a **Return Code** to report errors in a more script friendly manner. 

```sh
seineo@dell:~/Desktop$ echo "hello"
hello
seineo@dell:~/Desktop$ echo $?
0
```

Another common pattern is wanting to get the output of a command as a variable. This can be done with *command substitution*. Whenever you place `$( CMD )` it will execute `CMD`, get the output of the command and substitute it in place.

These techniques are often referred to as shell *globbing* :

- Wildcards - Whenever you want to perform some sort of wildcard matching you can use `?` and `*` to match one or any amount of characters respectively. For instance, given files `foo`, `foo1`, `foo2`, `foo10` and `bar`, the command `rm foo?` will delete `foo1` and `foo2` whereas `rm foo*` will delete all but `bar`.
- Curly braces `{}` - Whenever you have a common substring in a series of commands you can  use curly braces for bash to expand this automatically. This comes in  very handy when moving or converting files.

```sh
convert image.{png,jpg}
# Will expand to
convert image.png image.jpg

cp /path/to/project/{foo,bar,baz}.sh /newpath
# Will expand to
cp /path/to/project/foo.sh /path/to/project/bar.sh /path/to/project/baz.sh /newpath

mkdir foo bar
# This creates files foo/a, foo/b, ... foo/h, bar/a, bar/b, ... bar/h
touch {foo,bar}/{a..j}
touch foo/x bar/y
# Show differences between files in foo and bar
diff <(ls foo) <(ls bar)
# Outputs
# < x
# ---
# > y
```

**shellcheck** can help us find out errors in bash scripts :

```sh
seineo@dell:~/Desktop/test$ shellcheck mcd.sh 

In mcd.sh line 1:
mcd() {
^-- SC2148: Tips depend on target shell and yours is unknown. Add a shebang.
```

## Shell Tools

### Finding how to use commands

1. man page (detailed but hard to decipher)

   ```sh
   man convert
   ```

2. tldr (nifty and with examples)

   ```sh
   tdlr convert
   ```

### Finding files
j
Use `find`

```sh
# Find all directories named src
find . -name src -type d
# Find all python files that have a folder named test in their path
find . -path '**/test/**/*.py' -type f
# Delete all files with .tmp extension
find . -name '*.tmp' -exec rm {} \;
```

### Finding code

Use `grep`

```sh
#Search specific string in specific file
grep "echo" mcd.sh
#Search recursively in current directory 
grep -R "#include <stdio.h>" .
```




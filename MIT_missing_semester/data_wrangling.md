## Data Wrangling

Take data in one format and turn it into a different format.

we use `|` operator in past lectures like:

```sh
cat hello.txt | grep 'hello'      #find and print sentences which contains 'hello' in hello.txt
```

Also, there is one of the most powerful tools in your toolkit: `sed`.

`sed` is a "stream editor". In it, you basically give short commands for how to modify the file, and one of the most common commands is `s`: substitution. For example:

```sh
cat hello.txt | grep 'hello' | sed 's/.*oh//'     #replace the characters until "oh" with null, which is equivalent to delete them
```
What we just wrote was a simple regular expression; a powerful construct that lets you match text against patterns. The s command is written on the form: s/REGEX/SUBSTITUTION/, where REGEX is the regular expression you want to search for, and SUBSTITUTION is the text you want to substitute matching text with.

## Regular expressions

Regular expressions are usually (though not always) surrounded by /. Very common patterns are:
- `.` means "any single character" except newline 
- `*` zero or more of the preceding match
- `+` one or more of the preceding match
- `[abc]` any one character of `a`, `b`, and `c`
- `(RX1 | RX2)` either something that matchs string `RX1` or `RX2`
- `^` the start of the line 
- `$` the end of the line 

`sed`'s regular expressions are somewhat weird, and will require you to put a \ before most of these to give them their special meaning. Or you can pass` -E`. For example : 

```sh
echo 'abcaba' | sed -E 's/(ab)*//g' 
echo 'abcaba' | sed 's/\(ab\)*//g'             #Because the parenthesis has special meaning. Without `\`, it will be interpreted literally.
```

Take this [short interative regex tutorial](https://regexone.com/) to learn more about regex.

## Back to data wrangling

```sh
#an example from the lecture 
ssh myserver journalctl
 | grep sshd
 | grep "Disconnected from"
 | sed -E 's/.*Disconnected from (invalid |authenticating )?user (.*) [^ ]+ port [0-9]+( \[preauth\])?$/\2/'
 | sort | uniq -c
 | sort -nk1,1 | tail -n10  
```
`sort` will sort its input. `uniq -c`will collapse consecutive lines that are the same into a single line, prefixed with a count of the number of occurrences. `sort -n` will sort in numeric (instead of lexicographic) order. `-k1,1` means “sort by only the first whitespace-separated column”. The `,n` part says “sort until the `n`th field.

### awk -another editor

`awk` is a programming language that just happens to be really good at processing text streams. Here, we’ll just go through the basics.

```sh
#still the example from the lecture
ssh myserver journalctl
 | grep sshd
 | grep "Disconnected from"
 | sed -E 's/.*Disconnected from (invalid |authenticating )?user (.*) [^ ]+ port [0-9]+( \[preauth\])?$/\2/'
 | sort | uniq -c
 | sort -nk1,1 | tail -n10
 | awk '{print $2}' | paste -sd,

```
First, what does `{print $2}` do? Inside the block, `$0` is set to the entire line’s contents, and `$1` through `$n` are set to the `n`th field of that line, when separated by the `awk` field separator (whitespace by default, change with `-F`). In this case, we’re saying that, for every line, print the contents of the second field, which happens to be the username!

```sh
#another example for `awk`
 | awk '$1 == 10 &&  $2 ~ /^hello.*world$/ {print $2}'
```

We now have a pattern (the stuff that goes before {...}). The pattern says that the first field of the line should be equal to 10(as with number, we need use `==`), and that the second field should match the given regular expression(which means a string that starts with `hello` and ends with `world`). And the block just says to print the string.

### Analyzing data
You can do math! For example, add the numbers on each line together:

```sh
 | paste -sd+ | bc -l  #bc is basic calculator and -l is to include the math library
```


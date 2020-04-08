# Command-line environment

## Terminal Multiplexers

Terminal multiplexers allow to multiplex terminal windows using panes and tabs
so you can interact with multiple shell sessions

The most popular terminal multiplexer these days is `tmux`. `tmux` is highly configurable
and using the associated keybindings you can create multiple tabs and panes
and quickly navigate through them.

`tmux` expects you to know its keybindings, and they all have the form `<C-b> x` where that means 
press `Ctrl+b` release, and the press `x`. 
**I've changed it to the form `<C-a> x`, and it's much more convenient! Recommand!**  
For convenience, I'll use the form `<C-a> x` to talk about keybindings of `tmux`.

`tmux` has the following hierarchy of objects:

- **Sessions** -  a session is an independent workspace with one or more windows 
    - `tmux` starts a new session.
    - `tmux new -s NAME` starts it with that name.
    - `tmux ls` lists the current sessions.
    - Within `tmux` typing `<C-a> d` detaches the current session
    - `tmux` a attaches the last session. You can use `-t` flag to specify which
- **Windows** - Equivalent to tabs in editors or browsers, they are visually 
separate parts of the same session 
    - `<C-a> c` Creates a new window. To close it you can just terminate the shells doing `<C-d>`
    - `<C-a> N` Go to the N th window. Note they are numbered
    - `<C-a> p` Goes to the previous window
    - `<C-a> n` Goes to the next window
    - `<C-a> ,` Rename the current window
    - `<C-a> w` List current windows
- **Panes** - Like vim splits, pane lets you have multiple shells in the same visual display.  
**(The following keybindings are not default but custom)**
    - `<C-a> -` Split the current pane horizontally
    - `<C-a> |` Split the current pane vertically
    - `<C-a> h/j/k/l` Move to the pane in the specified direction. 

## Aliases

A shell alias is a short form for another command that your shell will replace automatically for you. 
An alias in bash has the following structure:

```sh
alias alias_name="command_to_alias arg1 arg2"
```
Note that there is no space around the equal sign `=`, because alias is a shell command that takes a single argument.

To make an alias persistent you need to include it in shell startup files, like `.bashrc` or `.zshrc`

## Dotfiles

Many programs are configured using plain-text files known as *dotfiles* 
(because the file names begin with a `.`, e.g. `~/.vimrc`). Shells are one example of programs
configured with such files. On startup, your shell will read many files to load its configuration.

**How should you organize your dotfiles?**  
They should be in their own folder, under version control, and `symlinked` into place using a script. 

**What should you put in your dotfiles?**  
Look through other people’s dotfiles on [github](://github.com/search?o=desc&q=dotfiles&s=stars&type=Repositories), 
and [here](https://dotfiles.github.io/) is another good resource on the topic.

Actually, I haven't spent so much time to study *dotfiles* with those mentioned resources...
As a newbie, I've just create simple *dotfiles* by learning [this](https://leohxj.gitbooks.io/a-programmer-prepares/software/mac/dotfiles.html) so far.
(**BUT IT'S NECESSARY TO STUDY IT LATER!**)

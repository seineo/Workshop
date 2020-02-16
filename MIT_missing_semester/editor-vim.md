# Editor-Vim
## Modal editing

Vim has multiple operating modes:
- Normal: for moving around a file and making edits
- Insert: for inserting text
- Replace: for replacing text
- Visual(plain, line, or block): for selecting blocks of text
- Command-line: for running a command 

## Basics
### Buffers, tabs, and windows

Vim maintains a set of open files, called “buffers”. A Vim session has a number of tabs, each of which has a number of windows (split panes). Each window shows a single buffer. 

By default, Vim opens with a single tab, which contains a single window.

```shell
:sp     #split window in to
:vsp    #like :sp, but split vertically
Ctrl + w + h/j/k/l   #Move the current window to be at the left/bottom/top/right  
gt      #Go to the next tab page
```
### Command-line
```shell
:e {name of file}  #open file for editing 
:help {topic}      #open help
:help :w    #opens help for the `:w` command
:help w     #opens help for the `w` movement
```

## Vim's interface is a programming language

**Movement**

- Words: w (next word), b (beginning of word), e (end of word)
- Lines: 0 (beginning of line), ^ (first non-blank character), $ (end of line)
- Screen: H (top of screen), M (middle of screen), L (bottom of screen)
- Scroll: Ctrl-u (up), Ctrl-d (down)
- File: gg (beginning of file), G (end of file)
- Find: f{character}, t{character}, F{character}, T{character}
     find/to forward/backward {character} on the current line
- Search: /{regex}, n / N for navigating matches

### Edits
- `o`/`O`    insert line below/above
- d{motion}  delete {motion}
     eg: `dw` is delete word, `d$` is delete to end of line
- c{motion}  change {motion}
     eg: `cw` is change word 
- `~` flips the case of a character

### Modifiers

You can use modifiers to change the meaning of a noun. Some modifiers are i, which means “inner” or “inside”, and a, which means “around”.

- ci( change the contents inside the current pair of parentheses
- ci[ change the contents inside the current pair of square brackets
- da' delete a single-quoted string, including the surrounding single quotes


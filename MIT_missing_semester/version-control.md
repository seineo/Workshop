# Version Control(Git)

While Git admittedly has an ugly interface, its underlying design and ideas are beautiful.
While an ugly interface has to be memorized, a beautiful design can be understood. 
For this reason, we give a bottom-up explanation of Git, starting with its data model 
and later covering the command-line interface. 


## Git's data model

### Snapshots

Git models the history of a collection of files and folders within some top-level
directory as a series of snapshots. In Git terminology, a file is called a “blob”,
and it’s just a bunch of bytes. A directory is called a “tree”, and it maps names 
to blobs or trees (so directories can contain other directories). A snapshot is the top-level tree 
that is being tracked. For example, we might have a tree as follows:

```
<root> (tree)
|
+- foo (tree)
|  |
|  + bar.txt (blob, contents = "hello world")
|
+- baz.txt (blob, contents = "git is wonderful")
```

### Modeling history: relating snapshots

In Git, a history is a directed acyclic graph (DAG) of snapshots.All this means is that 
each snapshot in Git refers to a set of “parents”, the snapshots that preceded it. It’s 
a set of parents rather than a single parent (as would be the case in a linear history) 
because a snapshot might descend from multiple parents, for example due to combining (merging) 
two parallel branches of development.

Git calls these snapshots `commit`s. Visualizing a commit history might look something like this:

```
o <-- o <-- o <-- o
            ^
             \
              --- o <-- o
```
In the ASCII art above, the `o`s correspond to individual commits (snapshots). The arrows point to 
the parent of each commit (it’s a “comes before” relation, not “comes after”). After the third commit, 
the history branches into two separate branches. This might correspond to, for example, two separate 
features being developed in parallel, independently from each other. In the future, these branches may 
be merged to create a new snapshot that incorporates both of the features, producing a new history that looks 
like this, with the newly created merge commit:

```
o <-- o <-- o <-- o <---- o
            ^            /
             \          v
              --- o <-- o
```

### Data model, as pseudocode

A clean, simple model of history.

```cpp
// a file is a bunch of bytes
type blob = array<byte>

// a directory contains named files and directories
type tree = map<string, tree | file>

// a commit has parents, metadata, and the top-level tree
type commit = struct {
    parent: array<commit>
    author: string
    message: string
    snapshot: tree
}
```
### Objects and content-addressing

An “object” is a blob, tree, or commit:

```cpp
type object = blob | tree | commit
```

In Git data store, all objects are content-addressed by their [SHA-1 hash](https://en.wikipedia.org/wiki/SHA-1),
which is strings of 40 hexadecimal characters.

```cpp
objects = map<string, object>

def store(object):
    id = sha1(object)
    objects[id] = object

def load(id):
    return objects[id]
```

Blobs, trees, and commits are unified in this way: they are all objects. 
When they reference other objects, they don’t actually contain them in their on-disk 
representation, but have a `reference` to them by their hash. 

### References

Now, all snapshots can be identified by their SHA-1 hash. Git has human-readable names for SHA-1 hashes,
called “references”. References are pointers to commits. Unlike objects, which are immutable, 
references are mutable (can be updated to point to a new commit). For example, the `master` reference 
usually points to the latest commit in the main branch of development.

One detail is that we often want a notion of “where we currently are” in the history. In Git, 
that “where we currently are” is a special reference called `HEAD`.

### Repositories

Finally, we can define what (roughly) is a Git repository: it is the data `objects` and `references`.

On disk, all Git stores are objects and references: that’s all there is to Git’s data model. 
All git commands map to some manipulation of the commit DAG by adding objects and adding/updating references.

## Git command-line interface 

Actually, a lot of commands can be tested `on our own laptops`. Just set one dir for local machine and another for remote machine. (That's what the lecturer did, I think it's incredibly useful to intuitively know how those commands
work.)

List some commonly used commands:

### Basic

- `git help <command>`: get help for a git command
- `git init`: creates a new git repo, with data stored in the .git directory
- `git status`: tells you what’s going on
- git add <filename>: adds files to staging area
- `git commit`: creates a new commit
- `git log`: shows a flattened log of history
- `git log --all --graph --decorate`: visualizes history as a DAG
- `git diff <filename>`: show differences since the last commit
- `git diff <revision> <filename>`: shows differences in a file between snapshots
- `git checkout <revision>`: updates HEAD and current branch
- `git show`: show various types of objects, for example, for commits it shows
            textual diff.

### Branching and merging

- `git branch`: shows branches
- `git branch <name>`: creates a branch
- `git checkout -b <name>`: creates a branch and switches to it
         same as git branch <name>; git checkout <name>
- `git merge <revision>`: merges into current branch

If meet merge conflicts, we can use the tool(command) `vimdiff` or `mergetool`.

### Remotes

- `git remote`: list remotes
- `git remote add <name> <url>`: add a remote
- `git push <remote> <local branch>:<remote branch>`: send objects to remote, and update remote reference
- `git branch --set-upstream-to=<remote>/<remote branch>`: set up correspondence between local and remote branch
- `git fetch`: retrieve objects/references from a remote
- `git pull`: same as git fetch; git merge
- `git clone`: download repository from remote

### Undo 

- `git commit --amend`: edit a commit’s contents/message
- `git reset HEAD <file>`: unstage a file
- `git checkout -- <file>`: discard changes

## Resources

1. [Pro Git](https://git-scm.com/book/en/v2)
2. [Lean Git Branching](https://learngitbranching.js.org/)

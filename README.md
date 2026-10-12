# Command Line Interpreter

A simplified command line interpreter (shell) written in C++, with a set of Bash-like commands, input/output redirection and pipes. Built in Visual Studio as a project for the **Object-Oriented Programming 1** course at the School of Electrical Engineering, University of Belgrade (academic year 2025/2026).

## Features

- Interactive prompt (default `$`, changeable at runtime)
- Commands that read from the console, from a quoted string, or from a file
- Input (`<`) and output (`>`, `>>`) redirection
- Pipes (`|`) connecting any number of commands
- Batch execution of command files, including nested `batch` calls
- Lexical, syntax and runtime error reporting with the position of the offending characters

## Supported commands

| Command | Description |
|---|---|
| `echo [argument]` | Passes its input to its output unchanged |
| `prompt "text"` | Changes the command prompt |
| `time` | Prints the current system time |
| `date` | Prints the current system date |
| `touch filename` | Creates an empty file (error if it already exists) |
| `truncate filename` | Deletes the contents of a file |
| `rm filename` | Deletes a file |
| `wc -w [argument]` | Counts words in the input |
| `wc -c [argument]` | Counts characters in the input |
| `tr [argument] -"what" ["with"]` | Replaces every occurrence of `what` with `with`; removes it if `with` is omitted |
| `head -nCOUNT [argument]` | Passes only the first `COUNT` lines (up to 5 digits) |
| `batch filename` | Executes the command lines stored in a file |

### Input of a command

An `argument` can be given in one of two ways:

- **Quoted text:** `wc -w "Lorem ipsum dolor sit amet"` uses the text between the quotes as input.
- **File name:** `wc -w input.txt` uses the contents of the file as input.

If a command has no argument, it reads from the console until EOF (`Ctrl+Z` on Windows, `Ctrl+D` on Unix-like systems), or from a redirected file or a pipe.

## Usage examples

```
$ wc -w "Lorem ipsum dolor sit amet"
5

$ wc -w < input.txt
5

$ wc -w "Lorem ipsum dolor sit amet" > output.txt

$ wc -c "Hello" >> output.txt

$ time | tr -":" "." | wc -c > time.txt

$ prompt ">> "
>> echo "Hello, world!"
Hello, world!

>> head -n3 notes.txt

>> batch commands.txt
```

## Syntax rules

- A command line is at most 512 characters; anything beyond that is ignored.
- Commands are case-sensitive.
- The command name, option and argument are separated by spaces or tabs.
- Text in double quotes is passed as a single unit; `|`, `<` and `>` inside quotes have no special meaning.
- Redirections may appear only at the end of a command. A command that already has an argument cannot also have input redirection, and a command connected to a pipe cannot define the same stream in another way.
- In a pipe, commands without an input stream (`time`, `date`) can only be first, and commands without an output stream can only be last.

## Error handling

A command line with an error is not executed, and an error message is printed instead. Handled errors include:

- **Lexical errors:** invalid characters. The message shows the command line and marks the offending characters:
```
  $ wc& -w *"Lorem ipsum dolor sit amet" +?
  Error - unexpected characters:
  wc& -w *"Lorem ipsum dolor sit amet" +?
   ^ ^ ^^
```
- **Unknown command:** `Unknown command: <name>`
- **Syntax errors** in the command or the whole command line
- **Semantic errors** in stream definitions (for example, an argument together with input redirection)
- **Execution errors** (for example, `touch` on an existing file)
- **Operating system errors** (for example, a missing file or no access permission)

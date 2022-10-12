# todo-app

A simple TUI todo app, by Chris Keith and Matthew Read.

Please read on before using this program, thank you!

To compile, run: `make todo`
To run, type ./todo filename.txt

You may load your own todo list, or use the following lists provided:

sample.txt     <= this starts as an unsorted sample list of tasks
				(note that once you open it, it will sort and save
				as such)
empty.txt      <= this is an empty file we used for testing
badformat.txt  <= this is a file that isn't formatted correctly and
					should generate our error message


**IMPORTANT**
If you want to pre-load your own list, it must follow some rules:
It must be blank, or...
Each line must begin with either 1 or 0, followed by |, then
the text body of the task, all on one line.  Starting the line with 
a 0 indicates that the task is not complete, while a 1 indicates
the task is complete.

Enjoy!

Cheers,
Chris and Matthew
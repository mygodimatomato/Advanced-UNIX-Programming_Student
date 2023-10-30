# Group_7
## question1
1. Parse the argument, do checking and mode decision. 
2. Read and count how many lines are there in the file.
3. reset file position indicator
4. Allocate desired char string array
5. use `qsort` and `strcmp` to sort the strings.
	- `strcmp` is wrapped in `mycmp` in order to prevent compiliation warnings abount function pointer.
6. iterate all string arrays and check if it differs from the previous one.
	- do the format checking while printing
	- ignore case is implemented in `mystrcmp`

for running the program, run `make`
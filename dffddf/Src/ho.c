
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

static void print_line(char *line)
{

	char *saved_line = NULL;
	int saved_point = 0;

	/* This is readline stuff.
	   - save the cursor position
	   - save the current line contents
	   - set the line to blank
	   - tell readline we're done mucking
	   - print the message
	   - restore the standard prompt
	   - restore the line contents
	   - restore the cursor position
	   - tell readline we're done mucking (again)
	*/
	saved_point = rl_point;
	saved_line = rl_copy_text(0, rl_end);
	rl_set_prompt("");
	rl_replace_line("",0);
	rl_redisplay();
	fprintf(stdout, "%s", line);
	rl_set_prompt(PROMPT);
	rl_replace_line(saved_line, 0);
	rl_point = saved_point;
	rl_redisplay();
	free(saved_line);
}

int main(){
    print_line("hello");
}
/* readline함수를 사용하기위한 헤더 */
# include <readline/readline.h>
/* add_history함수를 사용하기위한 헤더 */
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>

int main(void)
{
	char *str;
	while(1)
	{
		/* readline함수가 호출되면 인자(prompt : )를 터미널에 출력하고 저장할 라인을 입력받는다 */
		str = readline("prompt : ");
		if (str)
			printf("%s\n", str);
		else		/* str = NULL 이라면 (EOF, cntl + D)*/
			break ;
		/* add_history에 저장된 문자열은 up & down 방향키를 이용해 확인할수있다 */
		add_history(str);
		free(str);
	}
	return(0);
}


// typedef struct _hist_entry
// {
//   char *line;
//   char *data;
// }		HIST_ENTRY;

// HIST_ENTRY **the_history_list;

// typedef struct _hist_state {
// 	HIST_ENTRY  **entries;         // Pointer to the entries themselves.
// 	int	offset;            // The location pointer within this array.
// 	int	length;            // Number of elements within this array.
// 	int	size;              // Number of slots allocated to this array.
// 	int	flags;
// }	HISTORY_STATE;

// https://junselee.tistory.com/3
/*
stdin 에 \n 이 들어오면 그 때 까지 입력된 문자열을 char * 로 리턴해준다.


The history list is an array of history entries. A history entry is declared as follows:



The history list itself might therefore be declared as




*/
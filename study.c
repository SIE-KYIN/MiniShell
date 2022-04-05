#include <dirent.h >

struct dirent{
	long d_ino; //inode 번호
	off_t d_off; // offset
	unsigned short d_reclen; //d_name 길이
	char d_name[NAME_MAX+1]; //파일 이름
};
// 1000, 100 1000~<1100

 void sig_handler(int sig_num)
    {
        g_vars.read_heredocs = false;
    }

    signal(SIGINT, sig_handler);
    while (g_vars.read_heredocs == true)
    {
        herdoc_line = readline(">> ");
        if (herdoc_line == NULL || strcmp(herdoc_line, unquoted_delimiter) == 0)
            break ;
        free(herdoc_line);
    }
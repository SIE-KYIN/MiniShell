readline
rl_on_new_line
rl_replace_line
rl_redisplay
add_history
printf, malloc, free, write, open, read, close

fork
wait, waitpid, wait3, wait4
signal, kill, exit

# 디렉토리 관련 함수
getcwd, chdir, opendir, readdir, closedir

# 파일 정보 읽기 함수
stat, lstat, fstat
```C
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
struct stat {
	dev_t	st_dev;        /*ID of device containing file */
	ino_t	st_ino;          /*inode number*/
	mode_t	st_mode;     /*protection*/
	nlink_t	st_nlink;       /*number of hard links*/
	uid_t	st_uid;          /*user ID of owner*/
	gid_t	st_gid;          /*group ID of owner*/
	dev_t	st_rdev;        /*device ID (if special file)*/
	off_t	st_size;         /*total size, in byte*/
	blksize_t	st_blksize;    /*blocksize for file system I/O*/
	blkcnt_t	st_blocks;     /*number of 512B blocks allocated*/
	time_t;	st_atime;      /*time of last access*/
	time_t;	st_mtime;     /*time of last modification*/
	time_t	st_xtime;       /*time of last status change*/
};

int stat(const char *path, struct stat * buf);
int lstat(const char *path, struct stat * buf);
int fstat(int fd, struct stat * buf);
```
path는 절대경로를, buf는 stat구조체의 주소를 넘겨주어야 한다.
호출 성공시 0 반환, 읽은 정보가 stat구조체에 들어가게 된다.
실패시 -1반환, errno변수에 에러 상태가 저장된다.

* 각 함수의 차이점
lstat함수는 path가 심볼릭 링크 파일 경우, 심볼릭 링크 파일에 대한 정보를 구조제체 채운다.
(stat함수는  원본의 정보를 채운다.)

심볼릭 링크(symbolic link)
- 링크를 연결하여 원본 파일을 직접 사용하는 것과 같은 효과를 내는 링크이다.  윈도우의 바로가기와 비슷한 개념
- 특정 폴더에 링크를 걸어 NAS, library 원본 파일을 사용하기 위해 심볼릭 링크를 사용한다.

fstat함수의 첫 인자는 fd를 넣어준다.



int unlink( const char *path)
https://badayak.com/entry/C%EC%96%B8%EC%96%B4-%EB%A7%81%ED%81%AC-%EC%82%AD%EC%A0%9C-%ED%95%A8%EC%88%98-unlink

execve
int execve(const char *filename, char *const argv[], char *const envp[]);



- dup, dup2
fd값을 복제해주는 함수.
```C
<unistd.h>
int dup(int fd);			// fd가 가리키고 있는것을 가리키는 다른fd값을 반환(최솟값)
int dup(int fd, int fd2);	// fd가 가리키고 있는것을 fd2가 가리키게 한다.
```
https://reakwon.tistory.com/104


- pipe
```C
#include <unistd.h>
int pipe(int fd[2]);
```
fd : 크기가 2인 int 형 배열을 요구
-fd[0] : 함수 호출 후 fd[0]에 데이터를 입력 받을 수 있는 파일 디스크립터가 담김(파이프 출구)
-fd[1] : 함수 호출 후 데이터를 출력할 수 있는 파일 디스크립터다 담긴다(파이프 입구)


-strerror
```C
#include <string.h>  // C++ 에서는 <cstring>
char* strerror(int errnum);
#include <errno.h>
#include <stdio.h>
#include <string.h>
int main() {
  FILE* pFile;
  pFile = fopen("unexist.ent", "r");
  if (pFile == NULL)
    printf("Error opening file unexist.ent: %s\n", strerror(errno));
  return 0;
}
```

errno, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
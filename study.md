# readline 함수
- readline, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
컴파일시 -lreadline 을 붙어야 한다.

# 프로세스 관련 함수
- fork
- wait, waitpid, wait3, wait4
- execve

자식 프로세를 생성했을 때, 부모와 자식 중 먼저 실행이 끝난 프로세스는 종료되고, 이 때 상태를 회수해주지 않으면 좀비 프로세스가 된다. 이를 방지하기 위해 wait계열 함수를 통해 부모와 자식 프로세스를 동기화시켜야 한다.

pid_t wait3(int *statloc, int options, struct rusage *rusage);
int execve(const char *filename, char *const argv[], char *const envp[]);

# 시그널 관련 함수
- signal
시그널을 처리하는 함수이다.

void	(*signal(int signum, void (*handler)(int)))(int);
signum : 시그널 type
ex) SIGINT : ^C (터미널 인터럽트), SIGQUIT : ^\, SIGKILL : ^D(프로세스 종료)

handler : 특정 시그널이 발생했을 때 실행시킬 함수의 포인터를 넣어줌. 해당 함수는 int형 변수를 매개변수로 받음.

- kill
프로세스에 시그널을 전달하여 중단한다.
int kill(pid_t pid, int sig);
sig : signal 번호
양수 : 지정한 process id에만 시그널 전송
0 : 함수를 호출하는 프로세스와 같은 그룹에 있는 모든 프로세스에 시그널 전송
-1 : 함수를 호출하는 프로세스가 전송할 수 있는 권한을 가진 모든 프로세스에 시그널 전송
음수 : 첫번째 pid의 절대값 프로세스 그룹에 속하는 모든 프로세스에 시그널 전송

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


- unlink
파일을 삭제하는 함수
파일의 하드링크의 이름과 하드링크가 참조하는 count를 감소시켜
디스크 상에서 사용할 수 없는 상태로 만든다.

int unlink( const char *path)
https://badayak.com/entry/C%EC%96%B8%EC%96%B4-%EB%A7%81%ED%81%AC-%EC%82%AD%EC%A0%9C-%ED%95%A8%EC%88%98-unlink




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
<errno.h>의 errno를 매개변수로 넘겨주면 해당 errno에 해당하는 오류 내용을 반환해준다.
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

errno

- isatty, ttyname, ttyslot
```C
#include <unistd.h>
int isatty(int fd);			// fd가 터미널에 연결되어 있는 지 확인한다.
char *ttyname(int fd);		// fd가 가리키는 파일의 경로를 가져온다.
int ttyslot(void);			// 현재 실행하는 터미널의 tty 경로를 가져온다.

int fd;
fd = open("/dev/tty1", O_RDWR, 0);
if (fd == -1)
{
	printf("cannot open /dev/tty1\n");
	return ;
}
if (isatty(fd))
	printf("/devtty1 is a terminal device\n");
```


ioctl

- tcsetattr, tcgetattr
tcgetattr : 터미널 세팅값을 얻어오는 함수
tcsetattr : 세팅을 바꿔주고 tcsetattr함수를 사용해 설정값을 적용시킨다.
-> 방향키로 커서를 옮길 때 해당 함수로 설정값을 변경하는 작업이 필요하다.
터미널 관련 함수
```C
struct termios	term;

tcgetattr(STDIN_FILENO, &term); // 현재 정보 받아옴
term.c_lflag &= ~(ECHOCTL);	// 제어문자 반향 off
term.c_cc[VMIN] = 1;	// minimum number of bytes in input queue
term.c_cc[VTIME] = 0;	// how long to wait
tcsetattr(STDIN_FILENO, TCSANOW, &term); // 설정값 업뎃 🤗
```

- tgetent, tgoto, tputs

- getenv
char *getenv(const char *name);

tgetflag, tgetnum, tgetstr,

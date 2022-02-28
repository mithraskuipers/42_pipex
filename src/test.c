#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int ret = fork();
	//printf("%d\n", ret);

	if (ret > 0)
	{
		printf("parent");
	}

	if (ret == 0)
	{
		printf("child");
		close(1);
		int fd = open("testfile", O_WRONLY | O_APPEND | O_CREAT | 0644);
		dup2(fd, 1);
		printf("pingpong");
		close(fd);
	}
}
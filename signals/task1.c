#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void signal_handler(int signum)
{
 if(signum==SIGUSR1)
 {
   	printf("received SIGUSR1\n");
 }
 else
 {
  if(signum == SIGKILL)
  {
    printf("received SIGKILL\n");
  }
  else
  {
    if(signum == SIGSTOP)
    {
      printf("received SIGSTOP\n");
    }
  }
 }

}

int main()
{
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    perror("can't catch SIGUSR1");

   if (sigaction(SIGKILL, &sa, NULL) == -1)
    perror("can't catch SIGKILL");

  if (sigaction(SIGSTOP, &sa, NULL) == -1)
    perror("can't catch SIGSTOP");
    while(1)
    {
     sleep(1);
    }
}

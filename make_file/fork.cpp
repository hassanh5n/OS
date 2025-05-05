#include <unistd.h>
#include <iostream>
#include <sys/types.h>
using namespace std;

int main(){
	pid_t child1;
	child1 = fork();
	if(child1 == 0){
		cout<<"this is the child process, "<<getpid()<<endl;
	}
	else{
		cout<<"Now parent has come, "<<getpid()<<endl;
	}
}

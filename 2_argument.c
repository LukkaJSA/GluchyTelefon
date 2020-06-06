//Wejscie: argument do programu parsowany za pomoca getopt
//Modyfikacja/wyjscie x=Nastepna liczba pierwsza


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>


#define FIFO "/tmp/myfifo"

int next_prime_no(int number){

	int prime = 0;

	if (number<3){
		return number+1;
	}

	number++;
	if ((number%2)==0){
		number++;
	}

	while (prime == 0){
		prime = 1;

		for (int i=3; i<number;i++){
			if ((number % i) == 0){
				prime = 0;
				break;
			}	
		}
	number+=2;
	}
 return number-2;
}


int main(int argc, char* argv[]){

	uint32_t received;
	int fd;
	char* myfifo=FIFO;
	ssize_t send=0;
	pid_t proc;
	
	received = getopt(argc,argv,"0123456789")-'0';
	printf("\n\nProgram 2_argument\n");
 	printf("Drugi program otrzymal %i\n", received);

	received = next_prime_no(received);	

	mkfifo(myfifo,0666);

//	system("./3_pipe.o");

	proc=fork();

	if (proc==0){
		execl("./3_pipe.o","3_pipe.o", NULL);
	}	

	fd = open(myfifo, O_WRONLY);
	
	//TODO obsuga bledu jesli nie otrzymamy fd
	send= write(fd, &received, sizeof(uint32_t)); 
	send++;//TODO usunac
	close(fd);	
	unlink(myfifo);
return 0;
}

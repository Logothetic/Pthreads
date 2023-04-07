#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc,char **argv){

    int p0,p1,p2,p3,p4,p5,p6,x;
    printf("P0  pid:%d  ppid:%d\n",getpid(),getppid());

    //Making the first child of p0
    p1=fork();
    if(p1==0){
        //The code that p1 will run
        printf("P1  pid:%d  ppid:%d\n",getpid(),getppid());
        //Making the child of p1
        p3=fork();
        if(p3==0){
            //The code that p3 will run
            printf("P3  pid:%d  ppid:%d\n",getpid(),getppid());
            printf("P3  Hello from your child\n");
        }else
            wait(&p3);
    }else{
        //second child of p0
        p2=fork();
        if(p2==0){
            //The code that p2 will run
            printf("P2  pid:%d  ppid:%d\n",getpid(),getppid());
            //making the first child of p2
            p4=fork();
            if(p4==0){
                printf("P4  pid:%d  ppid:%d\n",getpid(),getppid());
            }else{
                //making the second child of p2
                p5=fork();
                if(p5==0){
                    printf("P5  pid:%d   ppid:%d\n",getpid(),getppid());
                }else{
                    //making the third child of p2
                    p6=fork();
                    if(p6==0){
                        printf("P6  pid:%d  ppid:%d\n",getpid(), getppid());
                    }else{
                        //waiting for all the childs to terminate
                        while(wait(NULL)>0);
//                       if( ( wait(&p4) && wait(&p5) ) || ( wait(&p4) && wait(&p6) ) || ( wait(&p5) && wait(&p6) ) );
                    }

                }
            }
        }else{
            //the code that p0 will run
            x=wait(&p1);
            printf("Exit value of P1 %d\n",x);
            while(wait(NULL)>0);
            execlp("cat","cat","e1a1.c",NULL);
        }
    }

    //executed by everyone
    printf("pid %d  TERMINATES.\n", getpid());
    return 0;
}

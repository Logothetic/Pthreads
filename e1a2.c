#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc,char **argv){

    int p0,p1,p2,p3,p4,p5,p6,x,n;
    printf("How many child processes of P2 do you want : ");
    scanf("%d",&n);
    printf("P0  pid:%d  ppid:%d\n",getpid(),getppid());

    //making the first child of p0
    p1=fork();
    if(p1==0){
        //the code that p1 will run
        printf("P1  pid:%d  ppid:%d\n",getpid(),getppid());
        //making the child of p1
        p3=fork();
        if(p3==0){
            printf("P3  pid:%d  ppid:%d\n",getpid(),getppid());
            printf("P3  Hello from your child\n");
        }else
            wait(&p3);
    }else{
        //second child of p0
        p2=fork();
        if(p2==0){
            //the code that p2 will run
            printf("P2  pid:%d  ppid:%d\n",getpid(),getppid());
            //loop to make n child processes for p2
            for(int i=0;i<n;i++){
                if(fork()==0){
                    printf("P%d pid:%d  ppid:%d\n",i+4,getpid(),getppid());
                    exit(0);
                }
            }
        }else{
            //the code that p0 will run
            x=wait(&p1);
            printf("Exit value of P1 %d\n",x);
            execlp("cat","cat","e1a1.c",NULL);
        }
    }


    printf("pid %d  TERMINATES.\n", getpid());
    return 0;
}

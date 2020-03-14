#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct Counter_t
{
    int value;
    FILE* fp;
    pthread_mutex_t lock;
}Counter_t;
Counter_t gloCoun,*p;

void init(Counter_t *c,char* filename)
{
    c->value=0;
    c->fp = fopen(filename, "r");
    pthread_mutex_init(&c->lock,NULL);
}

bool readPuzzle(Counter_t *c,char *puzzle,int size)
{
    bool retBool;
    pthread_mutex_lock(&c->lock);
    if(fgets(puzzle,size,c->fp)!=NULL)
    {
	c->value++;
	retBool=true;
    }
    else
    {
	retBool=false;
    }
    pthread_mutex_unlock(&c->lock);
    return retBool;
}

void* Deal()
{
    int i=0;
    char puzzle[128];
    while(readPuzzle(p,puzzle,sizeof puzzle))
    {
	printf("%s\n",puzzle);
    }
  
    usleep(rand()%100);
    return (void*)(long)i;
}

int main()
{
    printf("input thread num: \n");
    int n;
    scanf("%d",&n);
    pthread_t thread[n];
    int retval[n],beginTime,endTime;
    
    char filename[30];
    printf("input test file:");
    scanf("%s",&filename);

    beginTime=clock();
    p=&gloCoun;
    init(p,filename);


    for(int i=0;i<n;i++)
    {
	if(pthread_create(&thread[i], NULL, Deal, NULL)!=0)
	{
	    printf("线程%d创建失败\n",i);
	}
    }

    for(int i=0;i<n;i++)
    {
	if(pthread_join(thread[i], (void**)&retval[i])!=0)
	{
	    printf("cannot join with thread%d\n",i);
	}
    }
    endTime=clock();
    
    printf("count is %d\n",p->value);
    for(int i=0;i<n;i++)
    {
	printf("Thread%d return : %d\n",i,retval[i]);
    }
    printf("Process time:%d\n",endTime-beginTime);
    return 0;
}

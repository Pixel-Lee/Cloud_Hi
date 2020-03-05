//in my branch
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Counter_t
{
    int value;
    pthread_mutex_t lock;
}Counter_t;
Counter_t gloCoun,*p;

void init(Counter_t *c)
{
    c->value=0;
    pthread_mutex_init(&c->lock,NULL);
}

void increment(Counter_t *c)
{
    pthread_mutex_lock(&c->lock);
    c->value++;
    pthread_mutex_unlock(&c->lock);
}

void* Deal()
{
    int i=0;
    for(i;i<20000;i++)
    {
	increment(p);
    }
    return (void*)(long)i;
}

int main()
{
    pthread_t thread1, thread2;
    int ret_thrd1, ret_thrd2;//pthread_create's value
    int pJoin_thrd1,pJoin_thrd2;//pthread_join's value
    int retval1,retval2;
    
    p=&gloCoun;
    init(p);
    ret_thrd1 = pthread_create(&thread1, NULL, Deal, NULL);
    ret_thrd2 = pthread_create(&thread2, NULL, Deal, NULL);

    //judge if thread is successfully created
    if(ret_thrd1!=0){
	   printf("线程1创建失败\n");
    }
    else{
	   printf("线程1创建成功\n");
    }
    
    if(ret_thrd2!=0){
	   printf("线程2创建失败\n");
    }
    else{
	   printf("线程2创建成功\n");
    }

    pJoin_thrd1=pthread_join(thread1, (void**)&retval1);
    if (pJoin_thrd1 != 0) {
        printf("cannot join with thread1\n");
    }
    pJoin_thrd2=pthread_join(thread2, (void**)&retval2);
    if (pJoin_thrd2 != 0) {
        printf("cannot join with thread2\n");
    }
    

    printf("count is %d,2.Thrd1 %d,3.Thrd2 %d\n",p->value,retval1,retval2);

    return 0;
}

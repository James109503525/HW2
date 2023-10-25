#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <stdbool.h>
#include <stdio.h>  
#include<time.h>
#include "data.h"
#include <hiredis/hiredis.h>
#define REDIS_REPLY_STRING 1
#define REDIS_REPLY_ARRAY 2
#define REDIS_REPLY_INTEGER 3
#define REDIS_REPLY_NIL 4
#define REDIS_REPLY_STATUS 5
#define REDIS_REPLY_ERROR 6
int main()
{
	srand( time(NULL) );
	clock_t start, end;
	double diff = 0;
	node dummynode = { {},0,NULL };
	database d;
	d.head = &dummynode;
	d.tail = &dummynode;
	char* keyptr;
	start = 0;
	end = 0;
	for(int i=0;i<100000;i++)
	{
		int value=rand()%10+1;
		keyptr = getKey(i);
		start = clock();
		CREATE(&d, keyptr, value);
		end = clock();
		diff = diff + ((double) end - (double)start);
	}
	printf("my average create time: %f  ms\n", diff/100000);
	start = 0;
	end = 0;
	for (int i = 0; i < 100000; i++)
	{
		keyptr = getKey(i);
		start = clock();
		READ(&d, keyptr);
		end = clock();
		diff = diff + ((double)end - (double)start);
	}
	printf("my average read time: %f  ms\n", diff/100000);
	start = 0;
	end = 0;
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == NULL || context->err) {
        if (context) {
            printf("%s\n", context->errstr);
        } else {
            printf("redisConnect error\n");
        }
        exit(EXIT_FAILURE);
    }
	printf("-----------------connect success--------------------\n");
    for(int i=0;i<100000;i++)
    {
        char *key;
        int value;
        key=getKey(i);
		value=rand()%10+1;
        start = clock();
        redisReply *reply = redisCommand(context, "SET %s %c", key,'0'+value);
        end=clock();
        diff = diff + ((double) end - (double)start);
        freeReplyObject(reply);
    }
    printf("hiredis average create time: %f  ms\n", diff/100000);
    diff=0;
    start=0;
    end=0;
    for(int i=0;i<100000;i++)
    {
        char *key;
        key=getKey(i);
        start = clock();
        redisReply *  reply = redisCommand(context, "GET %s", key);
        end=clock();
        diff = diff + ((double) end - (double)start);
        freeReplyObject(reply);
    }
    printf("hiredis average read time: %f  ms\n", diff/100000);
    redisFree(context);
}

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h> 

#define BUFFER_SIZE 10

typedef struct
{
	char type; // 0=fried chicken, 1=French fries
	int amount; // pieces or weight
	char unit; // 0=piece, 1=gram
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

void produce(item *i) 
{
	while
	((first + 1) % BUFFER_SIZE == last) {
	// do nothing -- no free buffer item
	}
	memcpy(&buffer[first], i, sizeof(item));
	first = (first + 1) % BUFFER_SIZE;
}

item *consume() 
{
	item *i = malloc(sizeof(item));
	while
	(first == last) {
	// do nothing -- nothing to consume
	}
	memcpy(i, &buffer[last], sizeof(item));
	last = (last + 1) % BUFFER_SIZE;
	return i;
}

void *threadProduceFunction(void *param)
{
	item i1, i2, i3;
	i1.type='0';
	i1.amount=4;
	i1.unit='0';
	
	i2.type='0';
	i2.amount=12;
	i2.unit='0';

	i3.type='1';
	i3.amount=500;
	i3.unit='1';

	produce(&i1);
	printf("Type: %c\nAmount: %d\nUnit: %c\n", i1.type, i1.amount, i1.unit);
	produce(&i2);
	printf("Type: %c\nAmount: %d\nUnit: %c\n", i2.type, i2.amount, i2.unit);	
	produce(&i3);
	printf("Type: %c\nAmount: %d\nUnit: %c\n", i3.type, i3.amount, i3.unit);
	printf("After produce: First: %d, Last: %d\n", first, last);	
}

void *threadConsumeFunction(void *param)
{
	consume(); printf("After consume: First: %d, Last: %d\n", first, last);
	consume(); printf("After consume: First: %d, Last: %d\n", first, last);
}

int main()
{
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, threadProduceFunction, NULL);
	pthread_join(tid1, NULL);
	
	pthread_create(&tid2, NULL, threadConsumeFunction, NULL);
	pthread_join(tid2, NULL);
	
	return 0;
}

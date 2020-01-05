#include<iostream>
#include<pthread.h>
#include<vector>

std::vector<int> box;


pthread_mutex_t lock; 


void *producer(void* threadid)
{
	long tid;
	tid = (long)threadid;
	int i = 0;
	while(i < 40 )
	{	
		pthread_mutex_lock(&lock);

		if(box.size() < 6)
		{
			std::cout << "producer " << tid << " produce " << i << std::endl;
			box.push_back(i);
			++i;
		}	
		
		pthread_mutex_unlock(&lock);
	}

	std::cout << "producer done " << tid << std::endl;
	pthread_exit(NULL);
}

void *consumer(void* threadid)
{
	long tid;
	tid = (long)threadid;
	int i = 0;
	while(i < 30 )
	{
		pthread_mutex_lock(&lock);		
		

		if(box.size() > 0)
		{
			std::cout << "consumer " << tid << " consume " << i << std::endl;
			box.pop_back();
			++i;
		}
		pthread_mutex_unlock(&lock);
	}	
	
	std::cout << "consumer  done " << tid << std::endl;
	pthread_exit(NULL);
}


int main()
{

	
	pthread_t producers[3];
	pthread_t consumers[4];
	
	size_t i;
	for( i=0; i < 3; ++i)
	{
		pthread_create(&producers[i], NULL, producer, (void *)i);
	}
	
	for( i=0; i < 4; ++i)
	{
		pthread_create(&consumers[i], NULL, consumer, (void *)i);
	}
	
	for(i = 0; i < 3; ++i)
		pthread_join(producers[i], NULL);
		
	for(i = 0; i < 4; ++i)
		pthread_join(consumers[i], NULL);
    


	pthread_exit(NULL);
	
	
	return 0;
}

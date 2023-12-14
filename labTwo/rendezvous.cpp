/**
  \file main.cpp
  \brief Program that creates a rendezvous with the usage of mutexes and semaphores
  \author Denis Perepelyuk
 */

#include "Semaphore.h"
#include <thread>
#include <vector>
#include <iostream>

/*! 
  \brief Displays the first function in the barrier being executed 
  \param mutexSem Shared semaphore used to create mutex lock
  \param barrierSem Shared semaphore that allows threads to continue
  \param threadCount Stores total number of threads
  \param count Integer to store number of threads waiting at mutex
*/
void task(std::shared_ptr<Semaphore> mutexSem,std::shared_ptr<Semaphore> barrierSem, int threadCount, std::shared_ptr<int> counter){
  std::cout << "first " << std::endl;
  
  // Acquire lock to update counter
  mutexSem->Wait(); 
  
  // Increment counter for when thread arrives
  *counter = *counter + 1;    

  // Release barrier for when all threads arrive
  if (*counter == threadCount) {
    barrierSem->Signal();   
  }
  // Release mutex lock
  mutexSem->Signal();   
  // Wait at barrier until all threads arrive
  barrierSem->Wait();   
  // Release barrier
  barrierSem->Signal();
  std::cout << "second" << std::endl;
}

/**
 * \brief Program main function
 */
int main(void){
  std::shared_ptr<int> counter;
  std::shared_ptr<Semaphore> mutexSem;
  std::shared_ptr<Semaphore> barrierSem;
  int threadCount = 5;

  // Initialise counter and semaphores
  counter=std::make_shared<int>(0);
  mutexSem=std::make_shared<Semaphore>(1);
  barrierSem=std::make_shared<Semaphore>(0);
  std::vector<std::thread> threadArray(threadCount);

  for(int i=0; i < threadArray.size(); i++){
    threadArray[i]=std::thread(task,mutexSem,barrierSem,threadCount, counter);
  }
  for(int i = 0; i < threadArray.size(); i++){
    threadArray[i].join();
  }
  return 0;
}

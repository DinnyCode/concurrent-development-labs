/*! \file helloThreads.cpp
    \brief A documented file.


*/

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

/*! displays a message first*/
void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay){
  sleep(delay);
  cout <<"I ";
  cout << "must ";
  cout << "print ";
  cout << "first"<<std::endl;
  //tell taskTwo to start now
  theSemaphore->Signal();
}

/*! displays a message second*/
void taskTwo(std::shared_ptr<Semaphore> theSemaphore){
  //wait here until taskOne finishes...
  theSemaphore->Wait();
  cout <<"This ";
  cout << "will ";
  sleep(5);
  cout << "appear ";
  cout << "second"<<std::endl;
}

int main(void){
  // Declare two threads
  thread threadOne, threadTwo;
  // Create shared semaphore object
  shared_ptr<Semaphore> sem( new Semaphore);

  sem->Signal();
  sem->Wait();//these serve no purpose

  /**< Launch the threads  */
  int taskOneDelay=5;
  threadOne=thread(taskTwo,sem);
  threadTwo=thread(taskOne,sem,taskOneDelay);
  cout << "Launched from the main\n";

  /**< Wait for the threads to finish */
  threadOne.join();
  threadTwo.join();
  return 0;
}

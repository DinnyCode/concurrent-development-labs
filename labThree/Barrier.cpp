#include "Barrier.h"

/*! 
  \class Barrier
  \brief An Implementation of a barrier Using Semaphores 
  \author Denis Perepelyuk
*/

/*! 
  \brief Barrier with no parameters constructor
*/
Barrier::Barrier(){
  this->count = 0;
  threadNum = 0;
  condition = false;
  // Initialise semaphores
  mutexSem=std::make_shared<Semaphore>(1);
  barrierSem=std::make_shared<Semaphore>(0);
}

/*! 
  \brief Barrier with parameter constructor
  \param count Number of threads to wait for at barrier
*/
Barrier::Barrier(int count){
  this->count = count;
  threadNum = 0;
  condition = false;
  std::shared_ptr<Semaphore> mutexSem(new Semaphore(1));
  std::shared_ptr<Semaphore> barrierSem(new Semaphore(0));
}

/*! 
  \brief Barrier deconstructor
*/
Barrier::~Barrier(){}

/*! 
  \brief Set the current count value
  \param  c New count value
*/
void Barrier::setCount(int c){
    this->count = c;
}

/*!
  \brief Get the current count value
  \return Current count value
*/
int Barrier::getCount(){
  return this->count;
}

/*! 
  \brief Waits for all the threads before starting second half of code
*/ 
void Barrier::waitForAll(){
  mutexSem->Wait();
  threadNum++;

  if(threadNum == count){
      barrierSem->Signal();
      threadNum = 0;
  }
  mutexSem->Signal();
  barrierSem->Wait();
  barrierSem->Signal();
}

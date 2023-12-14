#include "Barrier.h"
#include <thread>
#include <vector>

/*! 
  \brief Displays the first function in the barrier being executed 
  \param barrierObj Shared pointer to barrier object
*/
void task(std::shared_ptr<Barrier> barrierObj){
  std::cout << "first \n";
  barrierObj->waitForAll();
  std::cout << "second \n";
}

/*!
  \brief Program main function
*/
int main(void){
  /*!< An array of threads*/
  std::vector<std::thread> threadArray(5);
  /*!< Pointer to barrier object*/
  std::shared_ptr<Barrier> barrierObj( new Barrier);

  barrierObj->setCount(5);

  for(int i=0; i < threadArray.size(); i++){
    threadArray[i]=std::thread(task,barrierObj);
  }

  for(int i = 0; i < threadArray.size(); i++){
    threadArray[i].join();
  }
  
  return 0;
}

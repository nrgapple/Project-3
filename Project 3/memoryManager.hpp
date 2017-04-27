

#include <stdio.h>
#include "virtualMemoryManagerInterface.hpp"

using namespace std;


class memoryManager: protected virtualMemoryManagerInterface
{
  
  // use list of memory frames.
  
public:
  
  
  
  
  unsigned long long memoryAccess(unsigned long long address)
  {
    switch (policy) {
      case FIFO:
        break;
        
      case LRU:
        break;
        
      default:
        cout << "error: incorrect Replacement Method" << endl;
    }
    
    return 0;
  }
  
private:
  
  
  
};


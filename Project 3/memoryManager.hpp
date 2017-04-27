

#include <stdio.h>
#include "virtualMemoryManagerInterface.hpp"
#include <list>

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
  
  void swap(unsigned int frameNumber, unsigned int pageNumber)
  {
    
  }
  
  
  void FIFO()
  {
    
  }
  
  void LRU()
  {
    
  }
  
private:
  
  struct block {
    int address;
    int lru;
  };
  
  list<block> memoryTable;
  
};


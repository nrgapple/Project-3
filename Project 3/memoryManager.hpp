

#include <stdio.h>
#include "virtualMemoryManagerInterface.hpp"
#include <list>

using namespace std;


class memoryManager: public virtualMemoryManagerInterface
{
  
  // use list of memory frames.
  
  
  
public:
  
  
  memoryManager(ReplacementPolicy p,
                unsigned int pS,
                unsigned int nF,
                unsigned int vA) :
                virtualMemoryManagerInterface(p,pS,nF,vA){
    
  }
  
  
  unsigned long long FIFO(int currentPage)
  {
    list<block*>::iterator iter;
    iter = memoryTable.begin();
    
    if (memoryTable.empty())
    {
      block *newBlock = new block;
      newBlock->pageNum = currentPage;
      newBlock->frameNum = 0;
      newBlock->p_address = pow(2, N);
      
      memoryTable.push_back(newBlock);
      
      return newBlock->p_address;
    }
    else{
      
      while( (*iter) != memoryTable.back() && (*iter)->pageNum != currentPage)
      {
        iter++;
      }
      // address is in table.
      cout << "iter->pageNum: " << (*iter)->pageNum << endl;
      if ((*iter)->pageNum == currentPage)
      {
        return (*iter)->p_address;
      }
      // Table not filled.
      else if (memoryTable.size() < numFrames)
      {
        block *newBlock = new block;
        newBlock->pageNum = currentPage;
        newBlock->frameNum = (int)memoryTable.size();
        newBlock->p_address = newBlock->frameNum * pow(2, N);
        memoryTable.push_back(newBlock);
        return newBlock->p_address;
      }
      else
      {
        block *newBlock = new block;
        newBlock->pageNum = currentPage;
        newBlock->frameNum = memoryTable.front()->frameNum;
        newBlock->p_address = memoryTable.front()->p_address;
        
        memoryTable.pop_front();
        memoryTable.push_back(newBlock);
        return newBlock->p_address;
      }
    }
    return 11;
  }
  
  unsigned long long LRU(int currentPage)
  {
    list<block*>::iterator iter;
    iter = memoryTable.begin();
    
    if (memoryTable.empty())
    {
      block *newBlock = new block;
      newBlock->pageNum = currentPage;
      newBlock->frameNum = 0;
      newBlock->p_address = pow(2, N);
      
      memoryTable.push_back(newBlock);
      
      return newBlock->p_address;
    }
    else{
      while( iter != memoryTable.end() && (*iter)->pageNum != currentPage)
      {
        iter++;
      }
      // address is in table.
      if ((*iter)->pageNum == currentPage)
      {
        block *newBlock = new block;
        newBlock->pageNum = (*iter)->pageNum;
        newBlock->frameNum = (*iter)->frameNum;
        newBlock->p_address = (*iter)->p_address;
        memoryTable.erase(iter);
        memoryTable.push_back(newBlock);
        return newBlock->p_address;
      }
      // Table not filled.
      else if (memoryTable.size() < numFrames)
      {
        block *newBlock = new block;
        newBlock->pageNum = currentPage;
        newBlock->frameNum = (int)memoryTable.size();
        newBlock->p_address = newBlock->frameNum * pow(2, N);
        memoryTable.push_back(newBlock);
        return newBlock->p_address;
      }
      else
      {
        block *newBlock = new block;
        newBlock->pageNum = currentPage;
        newBlock->frameNum = memoryTable.front()->frameNum;
        newBlock->p_address = memoryTable.front()->p_address;
        
        memoryTable.pop_front();
        memoryTable.push_back(newBlock);
        return newBlock->p_address;
      }
    }
    //error?
    return 11;
  }
  
  unsigned long long memoryAccess(unsigned long long address)
  {
    cout << address << endl;
    int c_pageNum = address / pow(2, N);
    
    unsigned long long physicalAddr = 0;
    switch (policy) {
      case ReplacementPolicy::FIFO:
        physicalAddr = FIFO(c_pageNum);
        break;
        
      case ReplacementPolicy::LRU:
        physicalAddr = LRU(c_pageNum);
        break;
        
      default:
        cout << "error: incorrect Replacement Method" << endl;
    }
    
    return physicalAddr;
  }
  
private:
  
  struct block {
    int frameNum;
    int pageNum;
    unsigned long long p_address;
  };
  
  list<block*> memoryTable;
  
  
  
};


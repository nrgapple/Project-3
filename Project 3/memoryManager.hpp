/*
 * Collin DeMatt
 * Adam Geiger
 * Mike Rabbitz
 */

#include <stdio.h>
#include "virtualMemoryManagerInterface.hpp"
#include <list>

using namespace std;

class memoryManager: public virtualMemoryManagerInterface
{
public:
  memoryManager(
    ReplacementPolicy p, 
    unsigned int pS, 
    unsigned int nF, 
    unsigned int vA) : virtualMemoryManagerInterface(p, pS, nF, vA) {}

  unsigned long long FIFO(int currentPage)
  {
    // initialize a VM table iterator
    list<block*>::iterator iter;
    iter = memoryTable.begin();

    // if the VM table is currently empty
    if (memoryTable.empty())
    {
      // create a new block
      block *newBlock = new block;
      newBlock->pageNum = currentPage;
      newBlock->frameNum = 0;
      newBlock->p_address = pow(2, N);

      // push the block to the back of the list
      memoryTable.push_back(newBlock);

      return newBlock->p_address;
    }

    // if the VM table is not currently empty
    else 
    {
      // make iterator point to the last block or a matching block
      while ((*iter) != memoryTable.back() && (*iter)->pageNum != currentPage)
        iter++;

      cout << "Address in VM table on page: " << (*iter)->pageNum << endl;

      // if the block is already in the VM table
      if ((*iter)->pageNum == currentPage)
        return (*iter)->p_address;

      // if the VM table is not full
      else if (memoryTable.size() < numFrames)
      {
        // create a new block
        block *newBlock = new block;
        newBlock->pageNum = currentPage;
        newBlock->frameNum = (int)memoryTable.size();
        newBlock->p_address = newBlock->frameNum * pow(2, N);

        // push the new block to the back of the list
        memoryTable.push_back(newBlock);
        
        return newBlock->p_address;
      }

      // if the VM table is full
      else
      {
        // create a new block
        block *newBlock = new block;
        newBlock->pageNum = currentPage;
        newBlock->frameNum = memoryTable.front()->frameNum;
        newBlock->p_address = memoryTable.front()->p_address;
        
        // pop the front block
        // push the new block to the back of the list
        memoryTable.pop_front();
        memoryTable.push_back(newBlock);

        return newBlock->p_address;
      }
    }

    // return 11 in case of error
    return 11;
  }

  unsigned long long LRU(int currentPage)
  {
    // initialize a VM table iterator
    list<block*>::iterator iter;
    iter = memoryTable.begin();

    // if the VM table is currently empty
    if (memoryTable.empty())
    {
      // create a new block
      block *newBlock = new block;
      newBlock->pageNum = currentPage;
      newBlock->frameNum = 0;
      newBlock->p_address = pow(2, N);

      // push the new block to the back of the list
      memoryTable.push_back(newBlock);

      return newBlock->p_address;
    }

    // if the VM table is current not empty
    else {
      // make iterator point to the last block or a matching block
      while ( iter != memoryTable.end() && (*iter)->pageNum != currentPage)
        iter++;
      
      cout << "Address in VM table on page: " << (*iter)->pageNum << endl;

      // if the block is already in the VM table
      if ((*iter)->pageNum == currentPage)
      {
        // create a duplicate block
        block *newBlock = new block;
        newBlock->pageNum = (*iter)->pageNum;
        newBlock->frameNum = (*iter)->frameNum;
        newBlock->p_address = (*iter)->p_address;
        
        // remove the matching block from the list
        // add the duplicate block to the back of the list
        memoryTable.erase(iter);
        memoryTable.push_back(newBlock);

        return newBlock->p_address;
      }

      // if the VM table is not full
      else if (memoryTable.size() < numFrames)
      {
        // create a new block
        block *newBlock = new block;
        newBlock->pageNum = currentPage;
        newBlock->frameNum = (int)memoryTable.size();
        newBlock->p_address = newBlock->frameNum * pow(2, N);

        // push the new block to the back of the list
        memoryTable.push_back(newBlock);

        return newBlock->p_address;
      }

      // if the VM table is full
      else
      {
        // create a new block
        block *newBlock = new block;
        newBlock->pageNum = currentPage;
        newBlock->frameNum = memoryTable.front()->frameNum;
        newBlock->p_address = memoryTable.front()->p_address;

        // pop the front block
        // push the new block to the back of the list
        memoryTable.pop_front();
        memoryTable.push_back(newBlock);
        return newBlock->p_address;
      }
    }
    
    // return 11 in case of error
    return 11;
  }

  unsigned long long memoryAccess(unsigned long long address)
  {
    cout << address << endl;
    int c_pageNum = address / pow(2, N);
    unsigned long long physicalAddr = 0;
    
    switch (policy) 
    {
      case ReplacementPolicy::FIFO:
        physicalAddr = FIFO(c_pageNum); break;

      case ReplacementPolicy::LRU:
        physicalAddr = LRU(c_pageNum);  break;

      default:
        cout << "error: incorrect Replacement Method" << endl;
    }

    return physicalAddr;
  }

private:
  struct block 
  {
    int frameNum;                   // number of physical frame
    int pageNum;                    // number of virtual page
    unsigned long long p_address;   // physical address
  };

  list<block*> memoryTable;         // list of type 'block'
};

/* Collin DeMatt
 * Adam Geiger
 * Mike Rabbitz */

#pragma once
#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

enum ReplacementPolicy
{
    FIFO,
    LRU
};

class virtualMemoryManagerInterface
{
public:
    virtualMemoryManagerInterface(
        ReplacementPolicy p,
        unsigned int pS,
        unsigned int nF,
        unsigned int vA) : policy(p),
        N(pS),
        numFrames(nF),
        virtualAddressSpaceSize(vA) 
        {
            assert(virtualAddressSpaceSize > N);
            assert(pow(2, virtualAddressSpaceSize) > numFrames * pow(2, N));
        }

    /***************************************************************************
    * This is the method the test bench will drive in emulating memory         *
    * management. Your memory manager should return the physical address       *
    * corresponding to the given virtual address. This function must NOT       *
    * return until any necessary page swapping is completed. This function is  *
    * to effect page swaps by calling the other key function (defined below).  *
    ***************************************************************************/
    virtual unsigned long long memoryAccess(unsigned long long address) = 0;

    /***************************************************************************
    * This is the method your memory manager should call to swap pages. This   *
    * function has been instrumented by the TAs to report memory system        *
    * performance.                                                             *
    *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*
    * @param    frameNumber physical frame that will emulate write to the swap *
    *                       file                                               *
    * @param    pageNumber  virtual page number, read from swap file into the  *
    *                       given frame                                        *
    ***************************************************************************/
    void swap(unsigned int frameNumber, unsigned int pageNumber)
    {
        /***********************************************************************
        * @todo     TA INSTRUMENTATION TO GO HERE                              *
        *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*
        * Students should instrument memorymanager performance in their own    *
        * class for their internal verification or may modify this code for    *
        * their testing purpose; however the TAs instrumentation will be       *
        * used for determining grade basis.                                    *
        ***********************************************************************/
        numSwaps++;
    }

    /***************************************************************************
    * This is the method for reporting the to-date number of page swaps, used  *
    * by the test benches to quantify performance.                             *
    *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*
    * @returns  the number of page swaps                                       *
    ***************************************************************************/
    unsigned long long& numberPageSwaps() { return numSwaps; }

protected:
    // enumerated value inidcating VM policy to be used {FIFO or LRU}
    ReplacementPolicy policy;

    // N = page address bit size
    // 2^N = physical frame/virtual page size to manage (in bytes)
    unsigned int N;

    // numFrames = total number of physical frames
    // physical memory size = numFrames * 2^N
    unsigned int numFrames;

    // 2^virtualAddressSpaceSize = total virtual address space (in bytes)
    unsigned int virtualAddressSpaceSize;

    // numSwaps = total number of page swaps performed
    unsigned long long numSwaps = 0;
};

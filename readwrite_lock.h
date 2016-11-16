/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */

#ifndef READWRITE_LOCK_H
#define READWRITE_LOCK_H

#include <iostream>
#include <mutex>
#include <thread>
#include <atomic>

class ReadWriteLock {
    
private:
    mutable std::mutex mutex;
    std::atomic<int> readers;
    
public:
    
    void readLock() {
        mutex.lock();
        ++readers;
        mutex.unlock();
    }
    
    void readUnlock() {
        --readers;
    }
    
    void writeLock() {
        mutex.lock();
        while(readers > 0);
    }
    
    void writeUnlock() {
        mutex.unlock();
    }
    
};

#endif /* READWRITE_LOCK_H */


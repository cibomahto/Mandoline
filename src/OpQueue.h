#ifndef OPQUEUE_H
#define OPQUEUE_H

#include <list>
#include <pthread.h>
#include <stdint.h>

class OpThread;
class Operation;

class OpQueue {
private:
    std::list<OpThread*> threadpool;
    pthread_mutex_t theMutex;
    pthread_cond_t theCond;

    std::list<Operation*> running;
    std::list<Operation*> pending;
    uint32_t max_threads;

public:
    OpQueue();
    ~OpQueue();

    void addOperation(Operation *op);
    void waitUntilAllOperationsAreFinished();
    void setMaxConcurrentOperationCount(int maxcnt);

    Operation* waitForOperation(OpThread* th);
    void operationFinished(Operation* op);

private:
    void growOrPrunePool();
};

#endif

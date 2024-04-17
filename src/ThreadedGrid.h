#ifndef THREADED_GRID_H
#define THREADED_GRID_H

#include "NumberGrid.h"
#include <mutex>

class Task {
    public:
        Task( const int& row, const int& column );
        int getRow();
        int getColumn();
    
    private:
        int mRow;
        int mColumn;
};

class ThreadedGrid: public NumberGrid {
    public:
        ThreadedGrid();
        ThreadedGrid(const int& height, const int& width);
        virtual ~ThreadedGrid();
        virtual void calculateAllNumbers();
        virtual void worker();

    private:
        std::vector<Task> mTasks;
        std::mutex mMutex;
};
#endif
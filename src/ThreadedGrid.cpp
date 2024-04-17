#include "ThreadedGrid.h"
#include <thread>

Task::Task( const int& row, const int& column )
    : mRow( row ), mColumn( column )
{}

int Task::getRow() {
    return mRow;
}

int Task::getColumn() {
    return mColumn;
}

ThreadedGrid::ThreadedGrid()
    : NumberGrid(), mTasks() 
{}

ThreadedGrid::ThreadedGrid( const int& height, const int& width )
    : NumberGrid( height, width ), mTasks()
{}

ThreadedGrid::~ThreadedGrid() {}

void ThreadedGrid::worker() {

    while (1) {
        mMutex.lock();
        int task_count = mTasks.size();

        if ( task_count == 0 ) {
            mMutex.unlock();
            return;
        }

        // Grab a task and delete it from task list
        Task task = mTasks.back();
        mTasks.pop_back();
        mMutex.unlock();

        // Complete the task
        int row = task.getRow();
        int column = task.getColumn();

        int number = calculateNumber( row, column );
        setNumber( row, column, number );
    }
}

void ThreadedGrid::calculateAllNumbers() {
    int thread_count = std::thread::hardware_concurrency();

    for ( int r=0; r < this->getHeight(); r++ ) {
        for ( int c=0; c < this->getWidth(); c++ ) {
            Task task( r, c );
            mTasks.push_back( task );
        }
    }

    std::vector<std::thread> threads;
    int i;
    try {
        for(i = 0; i < thread_count; i++) {
            threads.push_back( std::thread( &ThreadedGrid::worker, this ) );
        }

        // Clean up threads
        for(i = 0; i < thread_count; i++) {
            threads[i].join();
        }
    } catch ( ... ) {
        std::cout << "Error occured while threading." << std::endl;
    }
}
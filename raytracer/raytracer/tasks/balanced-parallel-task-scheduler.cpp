#include "tasks/balanced-parallel-task-scheduler.h"
#include "easylogging++.h"
#include <thread>
#include <mutex>

using namespace tasks;


namespace
{
    /// <summary>
    /// Performs tasks parallel.
    /// </summary>
    class BalancedParallelTaskScheduler : public tasks::schedulers::_private_::TaskSchedulerImplementation
    {
    private:
        unsigned thread_count;
    public:
    	BalancedParallelTaskScheduler(unsigned thread_count) : thread_count(thread_count) {}
        void perform(std::vector<std::shared_ptr<Task>> tasks) const
        {
            static std::mutex mutex;
            std::vector<std::thread> threads;

    		for (unsigned i = 0; i < thread_count; i++)
    		{
                threads.push_back(std::thread(&BalancedParallelTaskScheduler::function, &tasks, &mutex));
    		}

            for (auto& thread : threads)
            {
                thread.join();
            }
        }
        static void* function(std::vector<std::shared_ptr<Task>>* tasks, std::mutex* mutex)
        {
            if (!tasks->empty())
            {
                mutex->lock();
                auto task = tasks->back();
                tasks->pop_back();
                mutex->unlock();
                task->perform();
            	
                function(tasks, mutex);
            }
            return 0;
        }
    };
}

TaskScheduler tasks::schedulers::balanced_parallel(unsigned thread_count)
{
    LOG(INFO) << "Creating balanced parallel scheduler with " << thread_count << " threads";

    return TaskScheduler(std::make_shared<BalancedParallelTaskScheduler>(thread_count));
}

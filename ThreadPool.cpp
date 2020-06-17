#include"ThreadPool.h"
ThreadPool ::ThreadPool():terminate(false),isEmpty(true),isFull(false){
}

//设置池中初始线程数
void ThreadPool::setSize(int num){
        (*this).init_num = num ;
}

//添加任务
void ThreadPool::addTask(const Task &f){
   
    if(!terminate){
        //保护共享资源    
        unique_lock<mutex>lk(mtx);
        
        //要是任务数量到了最大,就等待处理完再添加
        while(isFull){
            cond.wait(lk);
        }

        //给队列中添加任务
        task.push(f);
        
        if(task.size() == init_num)
            isFull = true;
        
        cout<<"Add a task"<<endl;
        isEmpty = false ;
        cond.notify_one();
    }
}

void ThreadPool::finish(){
    
        //线程池结束工作
        for(size_t i =0 ;i<threads.size();i++){
               threads[i].join() ;
        }
}

void ThreadPool::runTask(){
    
    //不断遍历队列,判断要是有任务的话,就执行
    while(!terminate){

        unique_lock<mutex>lk(mtx);
        
        //队列为空的话,就等待任务
        while(isEmpty){
            cond.wait(lk);
        }
        
        Task ta;
        //转移控制快,将左值引用转换为右值引用
        ta = move(task.front());  
        task.pop();
        
        if(task.empty()){
            isEmpty = true ;    
        }    
        
        isFull =false ;
        ta();
        cond.notify_one();
    }
}

void ThreadPool::start(int num){
    
    setSize(num);
    
    for(int i=0;i<num;i++){        
        threads.push_back(thread(&ThreadPool::runTask,this));
    }
}
ThreadPool::~ThreadPool(){   
}

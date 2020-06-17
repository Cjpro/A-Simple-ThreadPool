#pragma once

#include <iostream>
#include <stdlib.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <functional>
#include <queue>
#define N 8
using namespace std;
class ThreadPool{

public:
    //自定义void()的函数类型
    typedef function<void()>Task;

    ThreadPool();
    ~ThreadPool();
    
public:
    size_t init_num;
    //线程数组
    vector<thread> threads ;
    
    //任务队列
    queue<Task> task ;
    
    //互斥锁条件变量
    mutex mtx ;
    condition_variable cond ;
    
    //线程池工作结束时为真
    bool terminate ;
    
    //队列是否为空
    bool isEmpty;
    //队列是否为满
    bool isFull;

public:
    void addTask(const Task&f);
    void start(int num);
    void setSize(int num);
    void runTask();
    void finish();
};

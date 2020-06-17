#include <iostream>
#include"ThreadPool.h"
void func(int i){
    cout<<"task finish"<<"------>"<<i<<endl;
}
int main()
{

    ThreadPool p ;
    p.start(N);
    int i=0;

    while(1){
        i++;
        //调整线程之间cpu调度,可以去掉
       this_thread::sleep_for(chrono::seconds(1));
        auto task = bind(func,i);
        p.addTask(task);
    }

    p.finish();
    return 0;
}

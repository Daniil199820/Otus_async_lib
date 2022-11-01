#pragma once 

#include "Observer.h"
#include "Storage.h"
#include "Logger.h"
#include <atomic>
#include <thread>
#include <iostream>
#include <condition_variable>
#include <queue>
class CommandView:public Observer{
public: 
    CommandView(std::shared_ptr<Storage> store):store(store),m_bDone(false),
    thread_executer(&CommandView::execute,this){
        store.get()->addObserver(this);
    }
    
    ~CommandView(){
        m_bDone =true;
        commands_wait.notify_all();
        if(thread_executer.joinable()){
            thread_executer.join();
        }
        std::cout<<counter_1<<"\n";
        std::cout<<counter_2<<"\n";
    }

    void update(std::deque<Element>& cont) override{

        {std::unique_lock<std::mutex> lock(lock_viewer);
            container.push(cont);
        }
       // if(counter_1<container.size())counter_1=container.size();
        counter_1 = counter_1 + cont.size();
       // std::cout<<"update in command view\n";
        commands_wait.notify_all();
        
    }

    void execute(){
        
        while(!m_bDone){
            std::unique_lock<std::mutex>locker(lock_viewer);
            commands_wait.wait(locker,[&](){return !container.empty() || m_bDone;});
            std::deque<Element> temp_c = container.front();
            counter_2 = counter_2 + temp_c.size();
            container.pop();
            if(!temp_c.empty()){
                std::cout<<"bulk: "<<temp_c[0]._cmd;
            for(size_t i=1;i<temp_c.size();++i){
                std::cout<<", "<<temp_c[1]._cmd;
            }
                std::cout<< '\n';
                temp_c.clear();
            }
        }
    }
private:
    std::shared_ptr<Storage> store;
    std::mutex lock_viewer;
    std::atomic<bool>m_bDone = false;
    std::condition_variable commands_wait;
    std::atomic<bool> commands_is_ready = false;
    std::queue<decltype(store->container_commands)> container;
    std::thread thread_executer;
    int counter_1 = 0;
    int counter_2 = 0;
    std::mutex print_lock;
};
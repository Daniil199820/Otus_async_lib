#pragma once 

#include "Observer.h"
#include "Storage.h"
#include "Logger.h"
#include <atomic>
#include <thread>
#include <iostream>
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
            container = cont;
        }
        counter_1 = container.size() + counter_1;
       // std::cout<<"update in command view\n";
        commands_wait.notify_one();
    }

    void execute(){
        while(!m_bDone){
            std::unique_lock<std::mutex>locker(lock_viewer);
            commands_wait.wait(locker,[&](){return !container.empty() || m_bDone;});
            counter_2 = container.size() + counter_2;
            if(!container.empty()){
                std::cout<<"bulk: "<<container[0]._cmd;
            for(size_t i=1;i<container.size();++i){
                std::cout<<", "<<container[i]._cmd;
            }
                std::cout<< '\n';
                container.clear();
            }
        }
    }
private:
    std::shared_ptr<Storage> store;
    decltype(store->container_commands) container;
    std::mutex lock_viewer;
    std::atomic<bool>m_bDone = false;
    std::condition_variable commands_wait;
    std::atomic<bool> commands_is_ready = false;
    std::thread thread_executer;
    int counter_1 = 0;
    int counter_2 = 0;
};
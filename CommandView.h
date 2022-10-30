#pragma once 

#include "Observer.h"
#include "Storage.h"
#include "Logger.h"
#include <iostream>
class CommandView:public Observer{
public: 
    CommandView(std::shared_ptr<Storage> store):store(store),m_bDone{false},
    thread_executer(&CommandView::execute,this){
        store.get()->addObserver(this);
    }
    
    ~CommandView(){
        m_bDone =true;
        commands_wait.notify_all();
        if(thread_executer.joinable()){
            thread_executer.join();
        }
    }

    void update() override{

       // {std::unique_lock<std::mutex> lock(lock_viewer);
        container = store->container_commands;
        //}
        std::cout<<"update in command view\n";
        commands_is_ready = true;
        commands_wait.notify_one();
    }

    void execute(){
        while(!m_bDone){
            std::unique_lock<std::mutex>locker(lock_viewer);
            commands_wait.wait(locker,[&](){return container.size() || m_bDone;});
            //std::cout<<"we are in com_viewer-"<<container.size()<<"\n";
            if(container.size()){
                std::cout<<"bulk: ";
                std::cout<<container[0]._cmd;
            for(size_t i=1;i<container.size();++i){
                std::cout<<", ";
                std::cout<<container[i]._cmd;
            }
                std::cout<< '\n';
            }
            commands_is_ready = false;
            container.clear();
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
};
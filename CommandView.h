#pragma once 

#include "Observer.h"
#include "Storage.h"
#include "Logger.h"
#include <iostream>
class CommandView:public Observer{
public: 
    CommandView(std::unique_ptr<Storage> store):store(std::move(store)){
        store.get()->addObserver(this);
    }

    void update() override{

        decltype(store->container_commands) cotr = std::move(store->container_commands);

        if(cotr.size()>0){
            std::cout<<"bulk: ";
            std::cout<<cotr[0]._cmd;
        for(size_t i=1;i<cotr.size();++i){
            std::cout<<", ";
            std::cout<<cotr[i]._cmd;
        }
            std::cout<< '\n';
        }
    }
private:
    std::unique_ptr<Storage> store;
};
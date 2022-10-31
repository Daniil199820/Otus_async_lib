#pragma once

#include<iostream>
#include <string>
#include <deque>
#include "Observer.h"
#include "Logger.h"
#include <chrono>



class Storage:public Observable{
public:

    void add_command(const std::string& _command){
        const auto now = std::chrono::system_clock::now();
        const auto now_ns = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        container_commands.push_back({_command,now_ns.count()});
    }   

    void pull_commands(){
        std::unique_lock<std::mutex> lock (lock_actions_command);
        notifyUpdate(container_commands);
        container_commands.clear();   
    }
    
    std::deque<Element> container_commands;

private:
    std::mutex lock_actions_command;
};
#pragma once

#include <iostream>
#include <sstream>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Model.h"
#include "CommandView.h"
#include "Logger.h"
#include <memory>
#include <functional>
class Context
{
public:
  Context(std::size_t BlockSize):m_bDone{false},m_thread(&Context::ParceBuffer,this){
        //std::cout<<"m_thred in constructor\n";
        auto store = std::make_shared<Storage>();
        Command_prcer = std::make_unique<CommandModel>(BlockSize,store); 
       // Logger_viewer = std::make_unique<Logger>(store);
        Console_viewer = std::make_unique<CommandView>(store);  
    }
    

  void SetBuffer(const char* _Buffer, std::size_t _szSize){
    {std::unique_lock<std::mutex> lock(m_streamLock);
        std::cout<<"Set_buffer_1_Contex\n";
      _ssInputStream.write(_Buffer, _szSize);
    }
    std::cout<<"Set_buffer_2_Contex\n";
    m_bNotified = true;
    m_streamCheck.notify_one();
    
  }

  void ParceBuffer(){

    std::cout << "we are in ParceBuffer\n";
    while(!m_bDone){
      std::unique_lock<std::mutex> locker(m_streamLock);
      m_streamCheck.wait(locker,[&](){return m_bNotified || m_bDone;});
      std::cout<< "we are after cond_var\n";
      std::string tempLine;
      while( std::getline(_ssInputStream,tempLine)){
        Command_prcer->setCommand(std::move(tempLine));
      }
      Command_prcer->end_of_f();
      _ssInputStream.clear();
      m_bNotified = false;
    }
  }

  ~Context(){
    // std::cout<<"destructor";
      m_bDone = true;
      m_streamCheck.notify_all();
      if (m_thread.joinable()){
        std::cout<<"destructor";
        m_thread.join();
      }
  }

private:
  std::unique_ptr<CommandModel> Command_prcer;
  std::unique_ptr<CommandView> Console_viewer;
  //std::unique_ptr<Logger> Logger_viewer;

  std::stringstream _ssInputStream;

  std::atomic<bool> m_bDone = false;
  std::atomic<bool> m_bNotified = false;
  std::atomic<bool> thread_is_created = false;
  std::thread m_thread;
  std::mutex m_streamLock;
  std::condition_variable m_streamCheck;
};
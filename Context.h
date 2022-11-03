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
  Context(std::size_t BlockSize):m_bDone{false}{
        auto store = std::make_shared<Storage>();
        Command_prcer = std::make_shared<CommandModel>(BlockSize,store); 
       // Logger_viewer = std::make_unique<Logger>(store);
        Console_viewer = std::make_shared<CommandView>(store);  
    }
    

  void SetBuffer(const char* _Buffer, std::size_t _szSize){
   // std::unique_lock<std::mutex> lock(m_streamLock);
    _ssInputStream.write(_Buffer, _szSize);
    ParceBuffer();
  }

  void ParceBuffer(){
      std::string tempLine;
      while( std::getline(_ssInputStream,tempLine)){
        Command_prcer->setCommand(std::move(tempLine));
      }
      _ssInputStream.clear();
    }

  ~Context(){
    Command_prcer->end_of_f();
  }

private:
  std::shared_ptr<CommandModel> Command_prcer;
  std::shared_ptr<CommandView> Console_viewer;
  //std::unique_ptr<Logger> Logger_viewer;

  std::stringstream _ssInputStream;

  std::atomic<bool> m_bDone = false;
  std::atomic<bool> m_bNotified = false;
  std::atomic<bool> thread_is_created = false;
  std::thread m_thread;
  std::mutex m_streamLock;
  std::condition_variable m_streamCheck;
};
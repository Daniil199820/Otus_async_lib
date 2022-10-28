#include <iostream>
#include <sstream>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Model.h"
#include "CommandView.h"
#include "Logger.h"

class Context
{
public:
  Context(std::size_t BlockSize)
    :m_bDone{false},m_thread{&Context::ParceBuffer,this}{
        auto store = std::make_unique<Storage>();
        Logger_viewer = std::make_unique<Logger>(store);
        Console_viewer = std::make_unique<CommandView>(store);
        Command_prcer = std::make_unique<CommandModel>(BlockSize,store);   
    }
    

  ~Context(){
      m_bDone = true;
      m_streamCheck.notify_all();
      if (m_thread.joinable()){
        m_thread.join();
      }
  }

  void SetBuffer(const char* _Buffer, std::size_t _szSize){
    {std::unique_lock<std::mutex> lock(m_streamLock);
      _ssInputStream.write(_Buffer, _szSize);
    }

    m_bNotified = true;
    m_streamCheck.notify_one();
    
  }

  void ParceBuffer(){
    while(!m_bDone){
      std::unique_lock<std::mutex> locker(m_streamLock);
      m_streamCheck.wait(locker,[&](){return m_bNotified || m_bDone;});
      std::string tempLine;
      while( std::getline(_ssInputStream,tempLine)){
        Command_prcer->setCommand(std::move(tempLine));
      }
      Command_prcer->end_of_f();
      _ssInputStream.clear();
      m_bNotified = false;
    }
  }

private:
  std::unique_ptr<CommandModel> Command_prcer;
  std::unique_ptr<CommandView> Console_viewer;
  std::unique_ptr<Logger> Logger_viewer;

  std::stringstream _ssInputStream;

  std::atomic<bool> m_bDone;
  std::atomic<bool> m_bNotified;
  std::thread m_thread;
  std::mutex m_streamLock;
  std::condition_variable m_streamCheck;
};
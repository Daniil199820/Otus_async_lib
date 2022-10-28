#include "async.h"
#include<map>
#include<vector>
namespace async {

std::map<handle_t, std::shared_ptr<Context>> map_contexts;
std::mutex contex_lock;

handle_t connect(std::size_t bulk) {
    auto cur_context = std::make_shared<Context>(bulk);
    std::lock_guard<std::mutex> lock(contex_lock);
    map_contexts.emplace(std::make_pair(cur_context.get(),cur_context));
    return cur_context.get();
}

void receive(handle_t handle, const char *data, std::size_t size) {
    std::shared_ptr<Context> temp_Context;
  
  {
    std::lock_guard<std::mutex> lock(contex_lock);
    auto iter = map_contexts.find(handle);
    if (iter != map_contexts.end()) {
      temp_Context = iter->second;
    }
  }

  if (temp_Context) {
    temp_Context->SetBuffer(data,size);
  }

}

void disconnect(handle_t handle) {
    std::lock_guard<std::mutex> lock(contex_lock);
    auto iter = map_contexts.find(handle);
    if(iter!=map_contexts.end()){
        map_contexts.erase(iter);
    }
}

}
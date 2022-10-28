#pragma once  

#include <fstream>
#include <string>

class Logger: public Observer{
public:
    Logger(std::unique_ptr<Storage> store):store(std::move(store)){
        store.get()->addObserver(this);
    }

    void open_log(const std::string& filename){
        close_log();
        file.open(filename);
        flag_opened_file = true;
    }

    void write(const std::string& message){
        if(flag_opened_file){
            file << message << "\n";
        }
    }

    void close_log(){
        if(flag_opened_file){
            file.close();
            flag_opened_file = false;
        }
    }

    void update() override{
         decltype(store->container_commands) cotr = std::move(store->container_commands);

        if(cotr.size()>0){
            open_log(cotr[0]._cmd + std::to_string(cotr[0]._time));
            write(cotr[0]._cmd); 
        
        for(size_t i=1;i<cotr.size();++i){
            write(cotr[i]._cmd);
        }
            close_log();
        } 
    }

private:
    std::ofstream file;
    bool flag_opened_file = false;
    std::unique_ptr<Storage> store;
};
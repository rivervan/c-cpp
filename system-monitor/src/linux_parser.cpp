#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <string>
#include <vector>

#include <experimental/filesystem>
#include <cmath>



namespace fs = std::experimental::filesystem;

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
/*
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

*/

vector<int> LinuxParser::Pids() {
  std::vector<int> pids;   
    for (const auto &dfs : fs::directory_iterator(kProcDirectory)){
        if (is_directory(dfs)){                        
           string nombre(dfs.path().stem());
           if(std::all_of(nombre.begin(), nombre.end(), isdigit))
           {
              int pid = std::stoi(dfs.path().stem());
              pids.push_back(pid);

           }

         }
    }
     return pids;


}



//DONE: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  
    string line; 
    string key;
    string value;  
    int memTotal      = 0;
    int memAvailable  = 0;    
    short int i = 0;    
    std::ifstream is(kProcDirectory + kMeminfoFilename);
    if(is.is_open()){
       while(std::getline(is,line) && i <= 2){          
          std::replace(line.begin(), line.end(), ':',' '); 
          std::istringstream linestream(line);         
          linestream >> key >> value;          
          if(key=="MemTotal"){
              memTotal = std::stoi(value);
              i++;
          }            
          else if(key=="MemAvailable"){
              memAvailable = std::stoi(value);
              i++;
          }
       }
        return (float) (memTotal - memAvailable)/memTotal;  
  }else  
    return 0.0;
  
  

}


//DONE: Read and return the system uptime
long LinuxParser::UpTime() { 
  
   string line; 
   string tiempo; 
   

   std::ifstream is (kProcDirectory + kUptimeFilename);
   if(is.is_open()){
      std::getline(is, line);
      std::istringstream linestream(line);
      linestream >> tiempo;
      is.close();
      return std::stol(tiempo);       
   }else
      return 0; 
}









// DONE: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
   string line; 
   string lbAux;
   vector<string> tiempos={"0","0","0","0","0","0","0","0","0","0"};

    std::ifstream is(kProcDirectory + kStatFilename);
    if(is.is_open()){
        std::getline(is, line);
        std::istringstream linestream(line);


        linestream >>lbAux;
        linestream >> tiempos[LinuxParser::CPUStates::kUser_]
                   >> tiempos[LinuxParser::CPUStates::kNice_]
                   >> tiempos[LinuxParser::CPUStates::kSystem_]
                   >> tiempos[LinuxParser::CPUStates::kIdle_]
                   >> tiempos[LinuxParser::CPUStates::kIOwait_]
                   >> tiempos[LinuxParser::CPUStates::kIRQ_]
                   >> tiempos[LinuxParser::CPUStates::kSoftIRQ_]
                   >> tiempos[LinuxParser::CPUStates::kSteal_]
                   >> tiempos[LinuxParser::CPUStates::kGuest_]
                   >> tiempos[LinuxParser::CPUStates::kGuestNice_];
                   
         
      is.close();
      return tiempos;
    }else
        return {};   
    

}




//DONE: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
      return ActiveJiffies() + IdleJiffies();
}


//DONE: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
    
      long jiffies = 0;
      vector<string> jifCpu = CpuUtilization();    

      if(jifCpu.size()>0){

          jiffies += std::stol(jifCpu[LinuxParser::CPUStates::kUser_]);
          jiffies += std::stol(jifCpu[LinuxParser::CPUStates::kNice_]);
          jiffies += std::stol(jifCpu[LinuxParser::CPUStates::kSystem_]);
          jiffies += std::stol(jifCpu[LinuxParser::CPUStates::kIRQ_]);
          jiffies += std::stol(jifCpu[LinuxParser::CPUStates::kSoftIRQ_]);
          jiffies += std::stol(jifCpu[LinuxParser::CPUStates::kSteal_]);

          return jiffies;

      }else
        return 0;          
   
     
}

//DONE: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  
       long jiffiesIdle = 0;
      vector<string> jifCpu = CpuUtilization();    

      if(jifCpu.size()>0){

          jiffiesIdle += std::stol(jifCpu[LinuxParser::CPUStates::kIdle_]);
          jiffiesIdle += std::stol(jifCpu[LinuxParser::CPUStates::kIOwait_]);
         
          return jiffiesIdle;

      }else
        return 0; 
    
  return 0; 
  
  }



// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
    string line; 
    string sNumProc;

    std::ifstream is(kProcDirectory + kStatFilename);
    if(is.is_open()){
        while(std::getline(is, line)){
            std::istringstream iss(line);
            string label;
            if( (iss >> label) && label =="processes"){
                 iss >> sNumProc;
                 return std::stoi(sNumProc);
            }
               
        }
    }

    
  return 0;   
  
  }

//DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line; 
    string sNumProc;

    std::ifstream is(kProcDirectory + kStatFilename);
    if(is.is_open()){
        while(std::getline(is, line)){
            std::istringstream iss(line);
            string label;
            if( (iss >> label) && label =="procs_running"){
                 iss >> sNumProc;
                 return std::stoi(sNumProc);
            }
               
        }
    } 

      return 0; 
}


// DONE: Read and return the command associated with a process
string LinuxParser::Command(int pid) { 
  
    string line; 
    string sNumProc;

    std::ifstream is(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
    if(is.is_open() && std::getline(is, line)){
       is.close();       

        if (line.size() <= 40)    
          return line;                     
        else
        {
           return line.substr(0,40);
        }
        
    }else
      return string("-------"); 
    
    
  
  
}

// DONE: Read and return the memory used by a process
string LinuxParser::Ram(int pid ) { 
  
  string line; 
  string ram;

    std::ifstream is(kProcDirectory + std::to_string(pid) + kStatusFilename );
    if(is.is_open()){
        while(std::getline(is, line)){
            std::istringstream iss(line);
            string label;
            if( (iss >> label) && label == "VmSize:"){
                 iss >> ram;
                 auto ramInMb = std::to_string(  std::stoi(ram) / 10000 );
                 is.close();
                 return ramInMb;
            }     
        }
        is.close();
    }
    
    return string("----"); 

}



// DONE: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) { 
     
  string line; 
  string uid;

    std::ifstream is(kProcDirectory + std::to_string(pid) + kStatusFilename );
    if(is.is_open()){
        while(std::getline(is, line)){
            std::istringstream iss(line);
            string label;
            if( (iss >> label) && label == "Uid:"){
                 iss >> uid;                
                 is.close();
                 return uid;
            }     
        }
        is.close();
    }
    
    
    return string(); 


}


// DONE: Read and return the user associated with a process
string LinuxParser::User(int pid) { 

    string line;   
    string uid;
    uid = LinuxParser::Uid(pid);

    std::ifstream is(kPasswordPath);
    if(is.is_open()){
        while(std::getline(is, line)){            
            std::replace(line.begin(), line.end(), ':',' ');            
            std::istringstream iss(line);
            string nameUser, aux, etcUid;
            iss >> nameUser >> aux >> etcUid;
            if( uid == etcUid){
                 iss >> uid;                
                 is.close();
                 return nameUser;
            }     
        }
        is.close();
    }
    
    return string(); 
}



// DONE: Read and return the uptime of a process
long LinuxParser::UpTime(int pid ) { 
  
  string line; 
  string seconds;

    std::ifstream is(kProcDirectory + std::to_string(pid) + kStatFilename );
    if(is.is_open() && std::getline(is,line)){        
            std::istringstream iss(line);

            for(auto i = 1; i<=_UPTIME_UID_; i++){
                iss>>seconds;
            }                        
            is.close();
            return  std::stol(seconds) / sysconf(_SC_CLK_TCK);                              
        }
        
    
    
    return 0; 

  
}



// DONE: Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid) { 
       

  string line; 
  string data;
  long jeffis = 0;

    std::ifstream is(kProcDirectory + std::to_string(pid) + kStatFilename );
    if(is.is_open() && std::getline(is,line)){        
            std::istringstream iss(line);

            for(auto i = 1; i<=_CSTIME_; i++){
                iss>>data;

                switch (i)
                {
                  case _UTIME_: 
                  case _STIME_: 
                  case _CUTIME_: 
                  case _CSTIME_:
                    jeffis += std::stol(data);                    
                    break;                                    
                  default:
                    break;
                }

            }                        
            is.close();
            return  jeffis;                              
        }
        
    
    
    return 0; 

}
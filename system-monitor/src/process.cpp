#include "linux_parser.h"

#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include<iostream>


using std::string;
using std::to_string;
using std::vector;


Process::Process(int pid): pid(pid){ CpuUtilization();};


// DONE: Return this process's ID
int Process::Pid() { return pid; }

// DONE: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid); 
}

// DONE: Return this process's memory utilization
string Process::Ram() {    
  return LinuxParser::Ram(pid);
  }

// DONE: Return the user (name) that generated this process
string Process::User() { return  LinuxParser::User(pid);
}

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid); 
}


// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 

     long startimeSecons = LinuxParser::UpTime(pid);
     long uptime         = LinuxParser::UpTime();
     long jeffis         = LinuxParser::ActiveJiffies(pid);
      
     cpuU = (float)(jeffis / sysconf(_SC_CLK_TCK)) /  (float) ( uptime - startimeSecons);
    
     return  cpuU;

}


// DONE: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {    
          /*  
         if( std::stol( LinuxParser::Ram(pid)) < std::stol( LinuxParser::Ram(a.pid))  )
            return true;
          else
            return false;
        */

         


        if(   cpuU < a.cpuU )
            return true;
          else
            return false;

     

}
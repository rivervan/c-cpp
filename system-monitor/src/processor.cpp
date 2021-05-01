#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    
     long total = LinuxParser::Jiffies();
     long idle  = LinuxParser::IdleJiffies();

     long diffTotal = total - prevTotal;
     long diffIdle  = idle  - prevIdle;

      prevTotal = total;
      prevIdle  = idle;

      return (float)(diffTotal - diffIdle)/(float)diffTotal;


    }
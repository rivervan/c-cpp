#include "format.h"

#include <string>
#include <ctime>

using std::string;

// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    
    
     time_t ts = seconds;
     char buffer[9];
     struct tm *timeinfo;
     timeinfo = localtime (&ts);
     strftime (buffer,80,"%T",timeinfo);
     string miTiempoF(buffer);
     return miTiempoF;


}
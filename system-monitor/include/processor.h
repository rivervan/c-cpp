#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  //DONE: See src/processor.cpp

  // DONE: Declare any necessary private members
 private:
      long prevTotal{0};
      long prevIdle{0};



};

#endif
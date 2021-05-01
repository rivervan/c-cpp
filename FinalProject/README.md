# Capstone: ATC(Air Traffic Control) Computer Game

This implementation is a demo of a minimalist computer game, through which explains several concepts related with POO, management memory and concurrency in C++.

The goal of game is simulate one Air Traffic Controller (ATC), that avoid crashes and to achieve successful landings of planes.


# Context of Scene & Play instructions: ATC Computer Game

The context of game is the airspace around an airport, which is represented by two trajectories compoused how explains follow:

* Direct to one of three tracks in airport (Left , Center and Right). The selection of which track is random, made by game.

* Wait. Sometimes the tracks are bussy, in consecuence, is necesary to fly in circles, the game makes decision if keep one plane in wait or if plane is redirected to a specific track. This desicion can affected the air landings, generating possibles crashes.

The trajectories are represented by six paths:  horizontal line (sense right to left for the arrives of airplanes), one semi-elipitic for veer toward airport tracks, one elipse for wait (to fly in circles) , two sigmoides curves and one horizontal line for arrive to tracks.  The paths are drawn on cartesian axis which convergin on origin. 


Interaction

1. User control: 
   * Arrow left key. Generate a new airplane posicioned on path of arrived.
   * Arrow right key.  End the game, after 3 seconds the window is closed.
   
2. How to game: 
   * Each game last 60 seconds.
   
   *  One crash happen when two airplane aproximing between them, according an specific default distance, which is defined based on size of airplanes.
   
   * When exist a crash, both airplane are switched red, a few seconds later, the airplanes are switched gray. When this happen the airplanes  are as ghost, only are visualiced but no produce damage to others ones.

   * Those airplanes that arrive to final, in yellow, are considered as successful landings.

   * The score is placed on the title of window.


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

* SDL 2.0 
  * [click here for installation instructions](https://wiki.libsdl.org/Installation)
  
  The above instructions were tested on linux Ubuntu 18.04, Cmake 3.17.2, g++ 7.5.0. and SDL Library 2.0.
  

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory (FinalProject): `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./MyGame`.



## RUBRIC

The project is composed by following structure of directories and files: 

 FinalProject (Project directory)    
 
      |---> CMakeLists.txt (Cmake file to build project)
      
      |---> README.md (Documentation file)
      
      |---> src (source files directory)
                                   __
              |---> airpath.cpp      |            
              |---> airpath.h        |
              |---> airplane.cpp     |
              |---> airplane.h       |  .CPP's class implementation files (definitios) & entry point to program (main)
              |---> atc.cpp          >  .h files declare classes, structures and enum
              |---> atc.h            |
              |---> sut.cpp          |
              |---> sut.h            |              
              |---> main.cpp       __|
                                   
                                   
# Object Oriented Programming                                   
   
   > The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.
     
   > All class data members are explicitly specified as public, protected, or private.
     
   > Appropriate data and functions are grouped into classes. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions.
     
     
     - The project has the following classes: 

        * AirPath.  Declared in airpath.h and defined in airpath.cpp        (meaning: explicit in the name)
        * Position. Declared in airplane.h and defined in airplane.cpp      (meaning: position of the airplane on the airspace <<paths>>)
        * AirPlane. Declared in airplane.h and defined in airplane.cpp      (meaning: explicit in the name)
        * Atc.      Declared in atc.h and defined in atc.cpp                (meaning: Air Traffic Controller)
        * Sut.      Declared in atc.h and defined in atc.cpp                (meaning: Specific utilities)
    
      - Each class is defined based on following template: 
        
          public: 
                Constructors
                Accessor Functions
                Mutator Functions
                Member functions (do specific actions related with behavioral of object)
           
                *Posible friend members ( )
           
          private:                
                Member variable
                Helper functions
           
                          
      - The project has the following structures:
    
          * PointCartesian. Declared in the file sut.h
          * score.          Declared in the class Atc
    
    
      - The project has the following enum types:
    
          * TypeDecision.   Declared in the class Sut
          * TypePath.       Declared in the file airpath.h
          * Sense.          Declared in the file airpath.h
    

   > All class members that are set to argument values are initialized through member initialization lists.
   
    - See hashtag: #initializerlist in class AirPath in airpath.cpp. In this case only was possible to use a reduced initializer list for two constructor.
   
   > All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways.
   
    - See hashtag: #DocumentthroughNameFunction in  airpath.h,  airpath.cpp, airplane.h, atc.cpp, etc.
     
   > Inheritance hierarchies are logical. Composition is used instead of inheritance when appropriate. Abstract classes are composed of pure virtual functions. Override functions are specified.
   
    - See hashtag: //#Composition in airplane.h 
   
   > One function is overloaded with different signatures for the same function name.
   
    - See hashtag: #OverloadFunction in airpath.h
    
    
# Loops, Functions, I/O 

   > A variety of control structures are used in the project. The project code is clearly organized into functions.
   
    - See hashtag: #datastructures in main.cpp
                   #controlstructures in airpath.cpp, airplane.cpp, main.cpp
                     
   > The project accepts input from a user as part of the necessary operation of the program.
   
    -  See hashtag: #inputfromauser in main.cpp
   
   
# Memory Management

  >  At least two variables are defined as references, or two functions use pass-by-reference in the project code.
  
    -  See hashtag: #passbyreference in airplane.h, airpath.cpp
    
  > The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction.
  
  > For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined.
  
  > For classes with move constructors, the project returns objects of that class by value, and relies on the move constructor, instead of copying the object.
  
  > The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. The project does not use raw pointers.
  
    - See hashtag: #RAIIsemanticmovesmartpointers
            
                          Move constructor:      in airpath.h / airpath.cpp
                          RAII & smartpointer :  in airpath.cpp
                          Move operator:         in airplane.cpp
                          Move semantic:         in main.cpp / atc.cpp
  
  
 # Concurrency
 
  > The project uses multiple threads in the execution.
  
  > A promise and future is used to pass data from a worker thread to a parent thread in the project code.
  
  > A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code.
  
    - See hashtag: #Concurrency
             
                          mutex                       : in atc.cpp
                          std::lock_guard<std::mutex> : in atc.cpp
                          Task & futures              : in main.cpp
                          
                          
                          
                          
# Does not apply

  * Object Oriented Programming
  
    > ~~One member function in an inherited class overrides a virtual base class member function.~~
  
    > ~~One function is declared with a template that allows it to accept a generic parameter.~~
  
  * Loops, Functions, I/O
  
    > ~~The project reads data from an external file or writes data to a file as part of the necessary operation of the program.~~
    
  * Memory Management
  
    > ~~At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor.~~
    
  * Concurrency    
    
    > ~~A std::condition_variable is used in the project code to synchronize thread execution.~~
    
    
  
    
    
    
    
    
    
 
 
 

                          
                          
                        
  
  
  
   
   
   
   
   
   
   
   
   
                                   
                                   





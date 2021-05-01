
#include <vector>
#include <memory>
#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <algorithm>

#include "SDL.h"
#include "airplane.h"

 
class Atc
{

   

    
    public:

        struct score
        {
            int crashes{0};
            int effectiveLanding{0};
        };
        

        Atc()=default;

        void recivePlaneAirSpaceIN(Position &&position);
        void fly(SDL_Renderer *sdl_renderer);        
        void  takeoffPlaneOUT();
        int  getNumPlanes()const{return _planes.size();};                
        void workerDetectedCrash(int idx);
        void doUnEnablePlains();

        score getScore(){return _score;};

    private:
        std::mutex _mutex;
        std::condition_variable _condition;
        std::vector<AirPlane> _planes;

        score _score;

             

};




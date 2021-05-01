

#include <vector>
#include <memory>
#include <map>

#include "airpath.h"
#include "SDL.h"







class Position
{

 

    public:        
        
         Position()=default;
         Position(std::map<TypePath, std::shared_ptr<AirPath>> &paths, TypePath typePath, AirPath::_IndexPointOnPath indexPointOnPath); //#passbyreference
         Position(Position &&src);
         Position &operator=( Position &&src);         
                 
         friend class AirPlane;

                  
     private: 
                 
        std::map<TypePath, std::shared_ptr<AirPath>>  _paths; 
        std::shared_ptr<AirPath>                      _currentPath;   //#Composition: one current position has one path                     
        AirPath::_IndexPointOnPath                    _currentIndexPoint{0};
         
         
                    
};
 




class AirPlane{



  public:
        typedef int _SizeAirPlane;

        AirPlane()=default;
        AirPlane(Position &&position ,_SizeAirPlane sizeAirPlane = 24, int speedFactor=1);
               
        //#DocumentthroughNameFunction
        bool getIsPathFinish()const{return _isPathFinish;};
        bool getIsEndTrip()const{return _isEndTrip;};
        SDL_Point& getCurrentPointS()const {return _position._currentPath->getPoints().get()[_position._currentIndexPoint];   };

        int getSizePlane();      
        void RenderAirplane(SDL_Renderer *sdl_renderer);
        void simulate();

        void setCrashed(){_Crashed = true;};
        bool getIsCrashed()const{return _Crashed ;};
                        
        void setIsEnable(bool enable){_isEnable = enable;};
        bool getIsEnable()const{return _isEnable ;};

  
   private:
  
     
      //#Composition: one airplane has a Position
      Position _position;
    
      //Shape of plane
      SDL_Rect  _cabCtr;
      SDL_Point _wingBottom[3];
      SDL_Point _wingTop[3];


      //Members of control
      bool  _isPathFinish{false};
      int   _speedFactor;
      bool  _isEndTrip;
      bool  _Crashed{false};
      bool  _isEnable{true};



      //Help functions
      void drawAirPlane(const SDL_Point &currentPoint); //#passbyreference



};






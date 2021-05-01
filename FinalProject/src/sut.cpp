#include <random>

#include "SDL.h"
#include "sut.h"








 SDL_Point Sut::getTraslatePointScreen(int x, int y, int xso, int yso){
     SDL_Point screenXY;     
     screenXY.x = xso + x;
     screenXY.y = yso + y*(-1);     
     return screenXY;
}


Sut::TypeDecision Sut::getFollowWay(){   
      std::random_device rd;
      std::mt19937 eng(rd());
      std::uniform_int_distribution<> distr(1, 4);
      int wayDecision = distr(eng);
      TypeDecision value;

      switch (wayDecision)
      {
        case 1:
            value = TypeDecision::Rail1;             
            break;
      
        case 2:
            value = TypeDecision::Rail2;
            break;

        case 3:
            value = TypeDecision::Rail3;
            break;

        case 4:
            value = TypeDecision::Wait;
            break;      
      }

                           
      return value;

}
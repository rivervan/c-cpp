#include<iostream>
#include<memory>

#include "SDL.h"
#include "airpath.h"
#include "sut.h"



//#initializerlist
AirPath::AirPath(int lenPath, int b, int x0, Sense sense): _lenPath(lenPath), _startPoint(0)  {

      if(sense == Sense::Right)
        _typePath = TypePath::OnTrackCenter;
      else
        _typePath = TypePath::LineArriving;
        
      _points   = getPointsLineArrivePath(_lenPath,b,x0,sense);           
     _endPoint   = _lenPath * Sut::sScale - 1;





}


//#RAIIsemanticmovesmartpointers
AirPath::AirPath(AirPath &&src){
      _typePath = src._typePath;
      _lenPath  = src._lenPath;
      _points   = src._points;


      
     _startPoint = src._startPoint; //Ready to  paths with variable direction
     _endPoint   = src._endPoint;


     src._points = nullptr;
     src._lenPath = 0;
     src._startPoint = 0;
     src._endPoint = 0;




}



//#passbyreference
AirPath::AirPath(const PointCartesian& center, int Ax, int By, int x0, bool isWhole ){
    
    if (isWhole == false){
        _typePath = TypePath::CycleVeer;
        _lenPath  = 2*Ax;
        _points   = getPointsCycleVeerPath(_lenPath, center, Ax, By, x0);  
    }else
    {
        _typePath = TypePath::CycleWait;
        _lenPath  = 4*Ax;
        _points   = getPointsCycleWaitPath(_lenPath, center, Ax, By, x0);  

    }
   
    _startPoint = 0; //Ready to  paths with variable direction
     _endPoint   = _lenPath  * Sut::sScale - 1;
    

}

//#initializerlist
AirPath::AirPath(const PointCartesian& center,  int P, int length): _lenPath(length), _startPoint(0) {
    
    if ( P < 0)
        _typePath = TypePath::OnTrackRight;           
    else
        _typePath = TypePath::OnTrackLeft;

     _points   = getPointsLateralTrack(_lenPath, center, P);
  
    
    _endPoint   = _lenPath  * Sut::sScale - 1;

   
}







//#DocumentthroughNameFunction:  Functions that get points on screen for generate paths

std::shared_ptr<SDL_Point> AirPath::getPointsLineArrivePath(int lenPath, int b, int x0, Sense sense){   
   std::shared_ptr<SDL_Point> points (new SDL_Point[lenPath * Sut::sScale]);   //#RAIIsemanticmovesmartpointers: RAII & smartpointer
   int xScreen =  x0 * Sut::sScale;   
   int yScreen =  b  * Sut::sScale;     
   int xScreenMax = lenPath * Sut::sScale;

   
      
   for(auto i = 0; i < xScreenMax; i++){                               
     points.get()[i] = Sut::getTraslatePointScreen(xScreen,yScreen,Sut::OriginAxisX,Sut::OriginAxisY);      
     
       switch (sense)
       {
            case Sense::Right:
                xScreen++;
                 break;
            case Sense::Left:
                xScreen--;
                break;       
            default:
                break;
       }
     
        
   }    

    
    return points;    
  }


std::shared_ptr<SDL_Point> AirPath::getPointsCycleVeerPath(int lenPath, PointCartesian center, int Ax, int By, int x0){
      int pointsOnX = lenPath * Sut::sScale;
      std::shared_ptr<SDL_Point> points (new SDL_Point[lenPath * Sut::sScale]); //#RAIIsemanticmovesmartpointers: RAII & smartpointer
     
   float x = 0; 
   float y = 0;


   int xScreen =  x * Sut::sScale;
   int yScreen =  y * Sut::sScale;

   float  yPartial = 0;
   
    for(auto i = 0; i < (pointsOnX/2)  ; i++){
       
              yPartial = sqrt((By*By) - ( (By*By) * pow((x - center.x),2)/(Ax*Ax)) );        
              yScreen  = (-1)*yPartial * Sut::sScale + center.y * Sut::sScale;
              xScreen =  x * Sut::sScale;

       points.get()[i] = Sut::getTraslatePointScreen(xScreen,yScreen,Sut::OriginAxisX,Sut::OriginAxisY);      
        x -= 1.0/Sut::sScale;
    }


    for(auto i = 0; i < (pointsOnX/2)  ; i++){
       
              yPartial = sqrt((By*By) - ( (By*By) * pow((x - center.x),2)/(Ax*Ax)) );        
              yScreen  = yPartial * Sut::sScale + center.y * Sut::sScale;
              xScreen  = x * Sut::sScale;

       points.get()[(pointsOnX/2) +i] = Sut::getTraslatePointScreen(xScreen,yScreen,Sut::OriginAxisX,Sut::OriginAxisY);      
        x += 1.0/Sut::sScale;
    }




      return std::move(points);

    
  }

          
std::shared_ptr<SDL_Point> AirPath::getPointsCycleWaitPath(int lenPath, PointCartesian center, int Ax, int By, int x0){

      int pointsOnX = lenPath * Sut::sScale;
      std::shared_ptr<SDL_Point> points (new SDL_Point[lenPath * Sut::sScale]); //#RAIIsemanticmovesmartpointers: RAII & smartpointer
     
      float x = 0; 
      float y = 0;


      int xScreen =  x * Sut::sScale;
      int yScreen =  y * Sut::sScale;

      float  yPartial = 0;
   
    //#controlstructures
    for(auto i = 0; i < (pointsOnX/4)  ; i++){
       
        yPartial = sqrt((By*By) - ( (By*By) * pow((x - center.x),2)/(Ax*Ax)) );        
        yScreen  = (-1)*yPartial * Sut::sScale + center.y * Sut::sScale;
        xScreen  =  x * Sut::sScale;

       points.get()[i] = Sut::getTraslatePointScreen(xScreen,yScreen,Sut::OriginAxisX,Sut::OriginAxisY);      
       x += 1.0/Sut::sScale;
    }


    for(auto i = 0; i < (pointsOnX/4)  ; i++){
       
              yPartial = sqrt((By*By) - ( (By*By) * pow((x - center.x),2)/(Ax*Ax)) );        
              yScreen  = yPartial * Sut::sScale + center.y * Sut::sScale;
              xScreen  = x * Sut::sScale;

       points.get()[(pointsOnX/4) +i] = Sut::getTraslatePointScreen(xScreen,yScreen,Sut::OriginAxisX,Sut::OriginAxisY);      
        x -= 1.0/Sut::sScale;
    }



     for(auto i = 0; i < (pointsOnX/4)  ; i++){
       
              yPartial = sqrt((By*By) - ( (By*By) * pow((x - center.x),2)/(Ax*Ax)) );        
              yScreen  = yPartial * Sut::sScale + center.y * Sut::sScale;
              xScreen  = x * Sut::sScale;

       points.get()[(2*pointsOnX/4) +i] = Sut::getTraslatePointScreen(xScreen,yScreen,Sut::OriginAxisX,Sut::OriginAxisY);      
        x -= 1.0/Sut::sScale;
    }



    for(auto i = 0; i < (pointsOnX/4)  ; i++){
       
              yPartial = sqrt((By*By) - ( (By*By) * pow((x - center.x),2)/(Ax*Ax)) );        
              yScreen  = (-1)*yPartial * Sut::sScale + center.y * Sut::sScale;
              xScreen =  x * Sut::sScale;

       points.get()[(3*pointsOnX/4) + i] = Sut::getTraslatePointScreen(xScreen,yScreen,Sut::OriginAxisX,Sut::OriginAxisY);      
        x += 1.0/Sut::sScale;
    }


      return std::move(points);





   }


std::shared_ptr<SDL_Point> AirPath::getPointsLateralTrack(int lenPath, PointCartesian center, int P){
      
      std::shared_ptr<SDL_Point> points (new SDL_Point[lenPath * Sut::sScale]); //#RAIIsemanticmovesmartpointers: RAII & smartpointer
      

      float x =  (float) center.x;
      float y =  (float) center.y; 

      for(auto i = 0; i < (lenPath*Sut::sScale); i++){

         float y = ( -P / (1 + exp(x-2*Sut::PI)))  + P ;
         int yScreen = (int) (y * Sut::sScale);
         int xScreen = (int) (x * Sut::sScale);

         points.get()[i] = Sut::getTraslatePointScreen(xScreen,yScreen,Sut::OriginAxisX,Sut::OriginAxisY);

         x += (1.0/Sut::sScale) ;
      }


      return std::move(points);

}



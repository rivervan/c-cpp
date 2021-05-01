
#include <iostream>
#include <cmath>
#include <memory>
#include <map>
#include <vector>
#include <string>

#include "SDL.h"
#include "sut.h"
#include "atc.h"





int main() {

 

  SDL_Renderer *sdl_renderer;
  SDL_Window   *sdl_window;


  
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Mi Game", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, Sut::kScreenWidth, Sut::kScreenHeight, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }




  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  


  //Data structures for planes and paths  #datastructures
  std::map<TypePath, std::shared_ptr<AirPath>> pathsAirs;   
  std::vector<std::shared_ptr<AirPlane>> planes;

  //Create PATHS
               
  //Create Path arrive
  pathsAirs[TypePath::LineArriving]  = std::make_shared<AirPath>(12,-4,12,Sense::Left);
                   
  //Create Path veer
  PointCartesian centerSemi(0,-2);
  pathsAirs[TypePath::CycleVeer]     = std::make_shared<AirPath>(centerSemi, 4,2,0);
          
  //Create Path Wait
  PointCartesian centerWhole(0,4);
  pathsAirs[TypePath::CycleWait]     = std::make_shared<AirPath>(centerWhole, 6,4,0, true);
     
  //Create Path Track Rigth
  PointCartesian centerTR(0,0);
  pathsAirs[TypePath::OnTrackRight]  = std::make_shared<AirPath>(centerTR,-2, 12);
          
  //Create Path Track Left
  PointCartesian centerTL(0,0);
  pathsAirs[TypePath::OnTrackLeft]   = std::make_shared<AirPath>(centerTL, 2, 12);
     
  //Create Path Track Center          
  pathsAirs[TypePath::OnTrackCenter] =  std::make_shared<AirPath>(12,0,0, Sense::Right);
     
     
     


// Controller smart pointe r
std::shared_ptr<Atc> atc(new Atc);


// Variables of control for game
SDL_Event e;
bool running = true;
int countEnable = 0;
Atc::score _score; 
std::chrono::time_point<std::chrono::system_clock> lastUpdate;
lastUpdate = std::chrono::system_clock::now();


//Main loop where to renderer scene 
//#controlstructures
while (running) {

     
    
    frame_start = SDL_GetTicks();


     // #inputfromauser
    while (SDL_PollEvent(&e)) 
    {
      if (e.type == SDL_KEYDOWN && e.key.keysym.sym== SDLK_RIGHT) {
        running = false;

      } 
      else {
         if (e.type == SDL_KEYDOWN && e.key.keysym.sym== SDLK_LEFT) {            
              std::future<void> future;
              Position position (pathsAirs, TypePath::LineArriving, 0);                                              
              atc->recivePlaneAirSpaceIN(std::move(position)); //#RAIIsemanticmovesmartpointers: Move semantic
        }
      }
    }
    
     
    
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E,0xFF);
    SDL_RenderClear(sdl_renderer);


    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xe6, 0xe6, SDL_ALPHA_OPAQUE); 
    SDL_RenderDrawLine(sdl_renderer,Sut::OriginAxisX,0, Sut::OriginAxisX, Sut::kScreenHeight);
    SDL_RenderDrawLine(sdl_renderer, 0,Sut::OriginAxisY,Sut::kScreenWidth,Sut::OriginAxisY);

      
    

    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xcc, 0xcc, SDL_ALPHA_OPAQUE);   


                                       
                                           
    SDL_RenderDrawPoints(sdl_renderer, pathsAirs[TypePath::LineArriving]->getPoints().get(),       pathsAirs[TypePath::LineArriving]->getLenPath()*Sut::sScale );
    SDL_RenderDrawPoints(sdl_renderer, pathsAirs[TypePath::CycleVeer]->getPoints().get(),          pathsAirs[TypePath::CycleVeer]->getLenPath()*Sut::sScale );
    SDL_RenderDrawPoints(sdl_renderer, pathsAirs[TypePath::CycleWait]->getPoints().get(),          pathsAirs[TypePath::CycleWait]->getLenPath()*Sut::sScale );
    SDL_RenderDrawPoints(sdl_renderer, pathsAirs[TypePath::OnTrackRight]->getPoints().get(),       pathsAirs[TypePath::OnTrackRight]->getLenPath()*Sut::sScale );
    SDL_RenderDrawPoints(sdl_renderer, pathsAirs[TypePath::OnTrackLeft]->getPoints().get(),        pathsAirs[TypePath::OnTrackLeft]->getLenPath()*Sut::sScale );        
    SDL_RenderDrawPoints(sdl_renderer, pathsAirs[TypePath::OnTrackCenter]->getPoints().get(),      pathsAirs[TypePath::OnTrackCenter]->getLenPath()*Sut::sScale);
    
    

    SDL_SetRenderDrawColor(sdl_renderer, 0xff, 0xff, 0x00, SDL_ALPHA_OPAQUE);

    countEnable++;
                  
    atc->fly(sdl_renderer);    //Move objects (airplanes)     
                  


     //#Concurrency: Task & futures <<for detect crashes: compare from much to much >>
    std::vector<std::future<void>> futures;       
     for(auto idx = 0; idx < (atc->getNumPlanes()-1) ; idx++){           
         futures.emplace_back(std::async(std::launch::deferred, &Atc::workerDetectedCrash, atc, idx));
     } 
                 
    std::for_each(futures.begin(), futures.end(), [](std::future<void> &f){f.wait();});
    
     if (atc->getNumPlanes() > 0 && countEnable%111==0){
         countEnable = 1; 
         atc->doUnEnablePlains();
     }


    //Delete airplane when trip is ended
    atc->takeoffPlaneOUT();
    _score = atc->getScore();
       
     long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
     std::string title;
     
     if(running == false)     
        title = "Air Traffic Controller    ABORTED...         Time: "  + std::to_string( 60 - timeSinceLastUpdate/1000)  ;
     else

        if ((60 - timeSinceLastUpdate/1000) == 0){
          title = "Air Traffic Controller    END GAME...   Effective Landing: " + std::to_string( _score.effectiveLanding) + ", Crashes: " + std::to_string(_score.crashes)  + "              Time: "  + std::to_string( 60 - timeSinceLastUpdate/1000)  ;
          running = false;
        }else
        {
          title = "Air Traffic Controller     Effective Landing: " + std::to_string( _score.effectiveLanding) + ", Crashes: " + std::to_string(_score.crashes)  + "              Time: "  + std::to_string( 60 - timeSinceLastUpdate/1000)  ;
        }
        
            





    SDL_RenderPresent(sdl_renderer);
    SDL_SetWindowTitle(sdl_window,  title.c_str() ); 
    frame_end = SDL_GetTicks();
  
  
     
    frame_count++;
    frame_duration = frame_end - frame_start;
      
     
    if (frame_duration < Sut::kMsPerFrame) {
        SDL_Delay(Sut::kMsPerFrame - frame_duration);
    }
    
    

 }


    
    SDL_Delay(3000);  

    // Close and destroy the window
    SDL_DestroyWindow(sdl_window);

    // Clean up
    SDL_Quit();

    std::cout<<"FIN DEL PROGRAMA" << std::endl;
     
    return 0;


  
 



}
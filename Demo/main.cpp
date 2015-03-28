#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <time.h>

//Função para desenhar retangulos
void FillRect(int x, int y, int w, int h, int color, SDL_Surface *screen) {
    SDL_Rect rect = {x,y,w,h};
    SDL_FillRect(screen, &rect, color);
}

int main ( int argc, char** argv )
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    // load an image
    SDL_Surface* bmp = SDL_LoadBMP("cb.bmp");
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    // centre the bitmap on screen
    SDL_Rect dstrect;
    dstrect.x = (screen->w - bmp->w) / 2;
    dstrect.y = (screen->h - bmp->h) / 2;

    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // draw bitmap
        //SDL_BlitSurface(bmp, 0, screen, &dstrect);


        // draw rectangle
        //FillRect(x+direction,y,50,50,0xFFFFFF,screen);
        //FillRect(x+direction+1,y+1,48,48,0x0,screen);

        int random;
        int direction = 50;
        int x = 50, y = 150;

        /* initialize random seed: */
        srand (time(NULL));

        for(int num_salas = 15; num_salas != 0; num_salas--){
           random = rand() % 3;
           direction = rand() % 2;
           if (direction == 0)
               direction = 50;
           else
               direction = -50;

           if (random == 0){
                //FillRect(x,y,50,50,0xFFFFFF,screen);
                FillRect(x+direction,y,50,50,0xFFFFFF,screen);
                FillRect(x+direction+1,y+1,48,48,0x0,screen);
                x = x+direction;
           }
           else if (random == 1){

                FillRect(x,y+direction,50,50,0xFFFFFF,screen);
                FillRect(x+1,y+direction+1,48,48,0x0,screen);
                y = y+direction;
           }
           else if (random == 2){
                FillRect(x,y-direction,50,50,0xFFFFFF,screen);
                FillRect(x+1,y-direction+1,48,48,0x0,screen);
                y = y-direction;
           }
           else if (random == 3){
                FillRect(x-direction,y,50,50,0xFFFFFF,screen);
                FillRect(x-direction+1,y+1,48,48,0x0,screen);
                x = x-direction;
           }
        }

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop

    // free loaded bitmap
    SDL_FreeSurface(bmp);

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}

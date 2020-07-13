#include <iostream>
#include <sstream>

#include <stdio.h>
#include <string>

#include "SDL.h"
#include "SDL_thread.h"
#include "deck.h"
#include "table.h"

using namespace std;

typedef struct{

    uint64_t loops;
    uint64_t *passes;

}thread_s;

int loop_thread(void* parameters){

    uint64_t loops, *passes;
    uint8_t fail;

    Card card;
    Deck deck;
    Table table;

    thread_s *thread_params = (thread_s*)parameters;

    loops = thread_params->loops;
    passes = thread_params->passes;

    while(loops--){

        fail = 0;

        deck.Shuffle();
        table.Clear();

        while(1){

            card = *deck.CurrentCard();

            if(!deck.CardsLeft()){
                (*passes)++;
                break;
            }

            if(!table.Push(&card)){

                deck.PushBack();

                if(fail++ > deck.CardsLeft() + 1){
                    break;
                }

            }else{

                deck.NextCard();
                fail = 0;
            }
        }
    }

    return 1;
}

int main(int argc, char* args[]){

    uint32_t start_time;
    uint64_t *pass;
    uint64_t i, loops, total_pass = 0;
    uint8_t threads;
    std::stringstream time;
    SDL_Thread **thread;

//    FILE *ctt = fopen("CON", "w" );
//    freopen( "CON", "w", stdout );
//    freopen( "CON", "w", stderr );

    if ( argc != 3 )
    {
        printf("Bad arguments, terminating ->\r\n");
        printf("First parameter is number of threads and second loop count\r\n");

        return false;
    }

    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ){
        return false;
    }

    start_time = SDL_GetTicks();

    threads = atoi(args[1]);
    loops = atoi(args[2]);

    printf("Starting %d threads and doing %d loops of PPasiannsi\r\n", (int)threads, (int)loops);

    pass = new uint64_t[threads];
    thread =  new SDL_Thread*[threads];

    for(i=0; i<threads; i++){

        thread_s thread_init;
        thread_init.loops = loops / threads;
        thread_init.passes = &pass[i];

        if(i==0){
            thread_init.loops += loops % threads;
        }

        pass[i] = 0;

        thread[i] = SDL_CreateThread( loop_thread, NULL, (void*)&thread_init );
    }

    //Wait for the threads to finish
    for(i=0; i<threads; i++){
        SDL_WaitThread( thread[i], NULL );
        total_pass += pass[i];
    }

    //Convert the timer's time to a string
    time << "Finished in " << SDL_GetTicks() - start_time << " ms";

    printf("%s\r\n", time.str().c_str());
    printf("%d/%d passed (%.1f%%)", (int)total_pass, (int)loops, (double)total_pass/(double)loops * 100);

    SDL_Quit();

    delete [] pass;
    delete [] thread;

    return 0;
}

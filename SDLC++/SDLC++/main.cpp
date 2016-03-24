#include <SDL.h>
#include <SDL_thread.h>
#include <SDL_timer.h>
#include <stdio.h>

// Very simple thread - counts 0 to 9 delaying 50ms between increments
FILE* archivo;
SDL_mutex* mutex;
static int TestThread(void *ptr)
{
	SDL_mutexP(mutex);
    int cnt;

    for (cnt = 0; cnt < 10; ++cnt) {
        printf("\nThread counter: %d", cnt);
		fprintf(archivo,"\nThread counter: %d", cnt);
        SDL_Delay(10);
    }
	SDL_mutexV(mutex);
    return cnt;
}

int main(int argc, char* argv[]) {
    /* Desmarca esto si quieres una ventanita con SDL, y agrega a vinculador->sistema-> subsistema -> windows
	// Start SDL2
    SDL_Init(SDL_INIT_EVERYTHING);

    // Create a Window in the middle of the screen
    SDL_Window *window = 0;

    window = SDL_CreateWindow("Hello World!",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              640, 480,
                              SDL_WINDOW_SHOWN);

    // Delay so that we can see the window appear
    SDL_Delay(2000);

    // Cleanup and Quit
    SDL_DestroyWindow(window);
    SDL_Quit();
	*/

	archivo=fopen("prueba.txt","w");
	SDL_Thread *thread;
	SDL_Thread *thread2;
	SDL_Thread* vthread[10];
    int         threadReturnValue;
	int         threadReturnValue2;
	mutex=SDL_CreateMutex();
    printf("\nSimple SDL_CreateThread test:");

    // Simply create a thread
    thread = SDL_CreateThread(TestThread, "TestThread", (void *)NULL);
	thread2 = SDL_CreateThread(TestThread, "TestThread", (void *)NULL);
    if (NULL == thread) {
        printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
    } else {
        SDL_WaitThread(thread, &threadReturnValue);
       // esto se puede pisar igual porque no protejo el output
		printf("\nThread returned value: %d", threadReturnValue);
    }
		
	    SDL_WaitThread(thread2, &threadReturnValue2);
		printf("\nThread2 returned value: %d", threadReturnValue2);
		SDL_DestroyMutex(mutex);
	fclose(archivo);
	// demorar 5 seg
	SDL_Delay(5000);
	
    return 0;
}
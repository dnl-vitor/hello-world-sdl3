#include <iostream>
#include <SDL3/SDL.h>
#include <cstdlib>

int main(int args, char *argv[]){

    //inicialização do subsistema de vídeo
    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("erro na inicializacao: %s", SDL_GetError());
        return 1;
    }

    //cria a janela
    SDL_Window *pwindow = SDL_CreateWindow("window", 900, 600, 0);
    if(!pwindow){
        SDL_Log("nao foi possivel criar a tela: %s", SDL_GetError());
        SDL_APP_FAILURE;
    }

    //cria o Renderer
    SDL_Renderer *prenderer = SDL_CreateRenderer(pwindow, NULL);
    if (!prenderer) return 1;
    
    bool running = true;
    SDL_Event event;

    //loop principal da janela
    while(running){
        //gerenciamento de inputs/eventos
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT){
                running = false;
            }
        }

        //trocando a cor da tela e renderizando a mudança
        //azul escuro formato RGBA
        SDL_SetRenderDrawColor(prenderer, 20, 50, 100, 255);

        //limpa o frame anterior com a nova cor escolhida
        SDL_RenderClear(prenderer);
    
        //desenhando texto na tela
        SDL_SetRenderDrawColor(prenderer, 255, 255, 255, 255);
        SDL_RenderDebugText(prenderer, 400, 20, "hello world!");

        //atualiza a janela com o novo frame
        SDL_RenderPresent(prenderer);

    }

    
    //limpeza e encerramento
    SDL_DestroyRenderer(prenderer);
    SDL_DestroyWindow(pwindow);
    SDL_Quit();

    return 0;
}

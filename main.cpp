#include <iostream>
#include <SDL3/SDL.h>
#include <cstdlib>
#include <cstring>

int main(int args, char *argv[]){
    
    //inicialização do subsistema de vídeo
    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("erro na inicializacao: %s", SDL_GetError());
        return 1;
    }

    int windowWidth = 800;
    int windowHeight = 400;

    //cria a janela
    SDL_Window *pwindow = SDL_CreateWindow("window", windowWidth, windowHeight, 0);
    if(!pwindow){
        SDL_Log("nao foi possivel criar a tela: %s", SDL_GetError());
        SDL_APP_FAILURE;
    }

    //cria o Renderer
    SDL_Renderer *prenderer = SDL_CreateRenderer(pwindow, NULL);
    if (!prenderer) return 1;
    
    bool running = true;
    SDL_Event event;
    const char* url = "https://www.youtube.com/watch?v=OaQhEcea10k&list=RDOaQhEcea10k&start_radio=1";

    //centralizando texto na tela
    int totalChars = strlen(url);
    float textWidth = totalChars * 8.0f;
    float textHeight = 8.0f;

    float xCentered = (windowWidth - textWidth)/ 2.0f;
    float yCentered = (windowHeight - textHeight) / 2.0f;

    SDL_FRect textArea;
    textArea.x = xCentered;
    textArea.y = yCentered - 4.0f;
    textArea.w = textWidth;
    textArea.h = 16.0f;


    //loop principal da janela
    while(running){
        //gerenciamento de inputs/eventos
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT){
                running = false;
            }
            //capturando eventos do teclado
            else if(event.type == SDL_EVENT_KEY_DOWN){
                if(event.key.key == SDLK_C && (event.key.mod & SDL_KMOD_CTRL)){
                    SDL_SetClipboardText(url);
                    SDL_Log("texto copiado");
                }
            }

            //capturando eventos do mouse
            else if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
                //verifica se foi o botão esquerdo do mouse
                if(event.button.button == SDL_BUTTON_LEFT){
                    float mouseX = event.button.x;
                    float mouseY = event.button.y;

                    //verifica se a coordenada do clique está dentro da área do texto
                    if(mouseX >= textArea.x && mouseX <= (textArea.x + textArea.w) &&
                       mouseY >= textArea.y && mouseY <= (textArea.y + textArea.h)){
                        SDL_SetClipboardText(url);
                        SDL_Log("texto copiado");
                    }
                }
            }
        }

        //trocando a cor da tela e renderizando a mudança
        //azul escuro formato RGBA
        SDL_SetRenderDrawColor(prenderer, 20, 50, 100, 255);

        //limpa o frame anterior com a nova cor escolhida
        SDL_RenderClear(prenderer);
    
        //desenhando texto na tela
        SDL_SetRenderDrawColor(prenderer, 255, 255, 255, 255);
        SDL_RenderDebugText(prenderer, xCentered, yCentered - 15.0f, "hello world!");
        SDL_RenderDebugText(prenderer, xCentered, yCentered, url);

        //atualiza a janela com o novo frame
        SDL_RenderPresent(prenderer);

    }

    
    //limpeza e encerramento
    SDL_DestroyRenderer(prenderer);
    SDL_DestroyWindow(pwindow);
    SDL_Quit();

    return 0;
}

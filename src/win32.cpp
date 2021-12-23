/*
* TapiocaBuilder 1.0
* Sistema de Compilação Via Scripts
*
* Para Usar o Programa
* Crie um Arquivo Chamado "Buildscript.cmd"
* e Para Usar Funcões de Limpeza Crie Outro Chamado "Cleanscript.cmd"
* o TapiocaBuilder Executa esses Scripts na Hora de Compilar ou Limpar o Projeto
*
* Dentro dos Scripts Você Coloca oque quiser exemplo
*
* para compliar C++ "clang++ arquivo.cpp"
* executar arquivo python "python arquivo.py"
*/


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <time.h>


using namespace std;
// Configuração de Cores ANSI
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define USE_ANSI false //Mude isto para false caso quiser usar em Windows 8.1/8/7/XP
//Outras Cores ANSI
//#define ANSI_COLOR_YELLOW  "\x1b[33m"
//#define ANSI_COLOR_BLUE    "\x1b[34m"
//#define ANSI_COLOR_MAGENTA "\x1b[35m"
//#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
//Funções de cor para Prompt do Windows para Windows 8.1/8/7/XP
void resetcolors();
void setcolor(WORD color);

//Outras Configurações
#define CLEAN_ENALED true //Habilitar a Função de Limpeza

int main(int argc, char** argv) {
    if (argc < 2) { //Verifica se a Quantidade de Argumentos e Menor que 2
        printf("%s: Invalid Command. Try '%s help'", argv[0], argv[0]);
        return 0;
    }
    else { //Verificação dos Argumentos
        if (strcmp(argv[1], "help") == 0) { // Função de Ajuda
            printf("TapiocaBuilder 1.0\n\n");
            printf("Build - Build Project \n");
            printf("Clean - Clean Project\n");
            printf("\n");
        }
        else if (strcmp(argv[1], "build") == 0) { //Função de Build
            clock_t start = clock();//Inicio da Contagem do Tempo
            int exitcode = system("call BuildScript.cmd"); //Verifica o Codigo de Saida do Script de Compilação
            if (exitcode == 0) {
                clock_t stop = clock();//Final da Contagem do Tempo
                double elapsed = (double)(stop - start) * 1000.0;//Calculando o Tempo de Execução
                if(USE_ANSI == true){
                    printf(ANSI_COLOR_GREEN "Build Complete ! in %f Miliseconds " ANSI_COLOR_RESET, elapsed);//Mostra o Tempo de Execução em Milisegundos
                } else {
                    setcolor(2);
                    printf("Build Complete ! in %f Miliseconds ", elapsed);
                    resetcolors();
                }
                    
            }
            else {//Uma Outra Função Caso o Script de Compilação Falhar
                clock_t stop = clock();
                double elapsed = (double)(stop - start) * 1000.0;
                if (USE_ANSI == true){
                    printf(ANSI_COLOR_RED "Build Failed ! in %f Miliseconds" ANSI_COLOR_RESET, elapsed);
                } else {
                    setcolor(4);
                    printf("Build Failed ! in %f Miliseconds", elapsed);
                    resetcolors();
                }
                

            }
        }
        else if (strcmp(argv[1], "clean") == 0) {//Função de Limpar
            if (CLEAN_ENALED == false){
                if (USE_ANSI == true){
                    printf(ANSI_COLOR_RED "Clean Function Disabled !" ANSI_COLOR_RESET);    
                    return 0;
                } else {
                    setcolor(4);
                    printf("Clean Function Disabled !");
                    resetcolors();
                    return 0;
                }
                
                
            }
            else {
                clock_t start = clock();
                int exitcode = system("call CleanScript.cmd"); //Verifica o Codigo de Saida do Script de Limpeza
                if (exitcode == 0) {//Obs: O Codigo da Função de Limpar e bem parecido com o de Compilar
                    clock_t stop = clock();
                    double elapsed = (double)(stop - start) * 1000.0;
                    if (USE_ANSI == true){
                        printf(ANSI_COLOR_GREEN "Clean Complete ! in %f Miliseconds " ANSI_COLOR_RESET, elapsed);
                    } else {
                        setcolor(2);
                        printf("Clean Complete ! in %f Miliseconds ", elapsed);
                        resetcolors();
                    }
                }
                else {
                    clock_t stop = clock();
                    double elapsed = (double)(stop - start) * 1000.0;
                    if (USE_ANSI == true){
                        printf(ANSI_COLOR_RED "Clean Failed ! in %f Miliseconds" ANSI_COLOR_RESET, elapsed);
                    } else {
                        setcolor(4);
                        printf("Clean Failed ! in %f Miliseconds",elapsed);
                        resetcolors();
                    }
                    

                }
            }
        }
        else {//Caso o Argumento for invalido
            printf("%s: Invalid Command. Try '%s help'", argv[0], argv[0]);
            return 0;
        }
    }
    return 0;
}

void setcolor(WORD color){//Codigo para mudar cor do terminal sem ANSI
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}

void resetcolors(){//Codigo para resetar cor do terminal sem ANSI
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
}



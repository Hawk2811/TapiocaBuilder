/*
* TapiocaBuilder
* Sistema de Compila��o Via Scripts
*
* Para Usar o Programa
* Crie um Arquivo Chamado "Buildscript.cmd"
* e Para Usar Func�es de Limpeza Crie Outro Chamado "Cleanscript.cmd"
* o TapiocaBuilder Executa esses Scripts na Hora de Compilar ou Limpar o Projeto
*
* Dentro dos Scripts Voc� Coloca oque quiser exemplo
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
// Configura��o de Cores ANSI
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define USE_ANSI false //Mude isto para false caso quiser usar em Windows 8.1/8/7/XP
//Outras Cores ANSI
#define ANSI_COLOR_YELLOW  "\x1b[33m"
//#define ANSI_COLOR_BLUE    "\x1b[34m"
//#define ANSI_COLOR_MAGENTA "\x1b[35m"
//#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
//Fun��es de cor para Prompt do Windows para Windows 8.1/8/7/XP
void resetcolors();
void setcolor(WORD color);
string PROG_VERSION = "2.0";
//Outras Configura��es
#define CLEAN_ENALED true //Habilitar a Fun��o de Limpeza

int main(int argc, char** argv) {
    if (argc < 2) { //Verifica se a Quantidade de Argumentos e Menor que 2
        printf("%s: Invalid Command. Try '%s help'", argv[0], argv[0]);
        return 0;
    }
    else { //Verifica��o dos Argumentos
        if (strcmp(argv[1], "help") == 0) { // Fun��o de Ajuda
            printf("TapiocaBuilder %s\n\n",PROG_VERSION.c_str());
            printf("build - Build Project \n");
            printf("clean - Clean Project\n");
            printf("test - Execute Project Tests\n");
            printf("task taskName - perform selected task\n");
            printf("\n");
        }
        else if (strcmp(argv[1], "build") == 0) { //Fun��o de Build
            clock_t start = clock();//Inicio da Contagem do Tempo
            int exitcode = system("call BuildScript.cmd"); //Verifica o Codigo de Saida do Script de Compila��o
            if (exitcode == 0) {
                clock_t stop = clock();//Final da Contagem do Tempo
                double elapsed = (double)(stop - start) * 1000.0;//Calculando o Tempo de Execu��o
                if(USE_ANSI == true){
                    printf(ANSI_COLOR_GREEN "Build Complete ! in %f Miliseconds " ANSI_COLOR_RESET, elapsed);//Mostra o Tempo de Execu��o em Milisegundos
                } else {
                    setcolor(2);
                    printf("Build Complete ! in %f Miliseconds ", elapsed);
                    resetcolors();
                }
                    
            }
            else {//Uma Outra Fun��o Caso o Script de Compila��o Falhar
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
        else if (strcmp(argv[1], "clean") == 0) {//Fun��o de Limpar
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
                if (exitcode == 0) {//Obs: O Codigo da Fun��o de Limpar e bem parecido com o de Compilar
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
        } else if(strcmp(argv[1],"test") == 0){//Codigo do sistema de testes
            if (USE_ANSI == true){
                printf(ANSI_COLOR_YELLOW "Started Tests" ANSI_COLOR_RESET "\n");
            } else {
                setcolor(14);
                printf("Started Tests\n");
                resetcolors();
            }
            clock_t start = clock();
            int exitcode = system("call TestScript.cmd");
            if (exitcode == 0){
                clock_t stop = clock();
                double elapsed = (double)(stop - start) * 1000.0;
                if (USE_ANSI == true) {
                    printf(ANSI_COLOR_GREEN "Test Pass! in %f Miliseconds\n" ANSI_COLOR_RESET, elapsed);
                } else {
                    setcolor(2);
                    printf("Test Pass! in %f Miliseconds\n", elapsed);
                    resetcolors();
                }
                
            } else {
                clock_t stop = clock();
                double elapsed = (double)(stop - start) * 1000.0;
                if (USE_ANSI == true) {
                    printf(ANSI_COLOR_RED "Test Failed ! in %f Miliseconds\n" ANSI_COLOR_RESET, elapsed);
                } else {
                    setcolor(4);
                    printf("Test Failed ! in %f Miliseconds\n", elapsed);
                    resetcolors();
                }
            }
            /*
            Codigo da função de tasks
            */
        } else if (strcmp(argv[1],"task") == 0){
            clock_t start = clock();
            char taskrunner[13] = "call tasks\\";//chama o script que estiver dentro da pasta tasks no seu projeto
            string taskname = argv[2]; //guarda oque o usuario digitou em uma variavel para ser usado como nome da task
            string taskfile = strcat(argv[2],".cmd");//concatena oque o usuario digitou com a extenção ".cmd"
            string code = strcat(taskrunner,taskfile.c_str()); //junta tudo isso em uma unica variavel
            int exitcode = system(code.c_str());//Executa e pega o codigo de saida igual as funções de build, clean e test
            if(exitcode == 0){
                clock_t stop = clock();
                double elapsed = (double)(stop - start) * 1000.0;
                if (USE_ANSI == true){
                    printf(ANSI_COLOR_GREEN "Task '%s' Complete ! in %f Miliseconds\n" ANSI_COLOR_RESET,taskname.c_str(), elapsed);
                } else {
                    setcolor(2);
                    printf("Task '%s' Complete ! in %f Miliseconds\n",taskname.c_str(), elapsed);
                    resetcolors();
                }
            } else {
                clock_t stop = clock();
                double elapsed = (double)(stop - start) * 1000.0;                
                if (USE_ANSI == true){
                    printf(ANSI_COLOR_RED "Task '%s' Failed ! in %f Miliseconds\n" ANSI_COLOR_RESET,taskname.c_str(), elapsed);
                } else {
                    setcolor(4);
                    printf("Task '%s' Failed ! in %f Miliseconds\n",taskname.c_str(),elapsed);
                    resetcolors();
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



/*
* TapiocaBuilder for Unix
*/

//Inclusão das Biblotecas
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <time.h>
#include <cstring>

using namespace std;
//Configuração de Cores ANSI
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
//Outras Cores ANSI
#define ANSI_COLOR_YELLOW  "\x1b[33m"
//#define ANSI_COLOR_BLUE    "\x1b[34m"
//#define ANSI_COLOR_MAGENTA "\x1b[35m"
//#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//Outras Configurações
#define CLEAN_ENALED true //Habilitar Funcão de Limpeza

int main(int argc, char const *argv[]) {
    if (argc < 2) { //Verifica se a quantidade de argumentos e menor que 2
        printf("%s: Invalid Command. Try '%s help'\n", argv[0], argv[0]);
        return 0;
    } else { //Verificação dos Argumentos
        if (strcmp(argv[1], "help") == 0){
            printf("TapiocaBuilder 1.5\n\n");
            printf("build - Build Project \n");
            printf("clean - Clean Project\n");
            printf("test - Execute Tests of Project\n");
            printf("\n");
        } else if(strcmp(argv[1],"build") == 0){
            clock_t start = clock();//Inicio da Contagem do Tempo
            int exitcode = system("./BuildScript.sh"); //Executa o script de compilação e guarda o codigo de saida em uma variavel
            if (exitcode == 0){
                clock_t stop = clock();//Final da Contagem do Tempo
                double elapsed = (double)(stop - start) * 1000.0;//Calcula o Tempo de Execução
                printf(ANSI_COLOR_GREEN "Build Complete ! in %f Miliseconds\n" ANSI_COLOR_RESET, elapsed);//Mostra o Tempo de Execução em Milisegundos
            } else { //Função de failback caso o script falhar
                clock_t stop = clock();
                double elapsed = (double)(stop - start) * 1000.0;
                printf(ANSI_COLOR_RED "Build Failed ! in %f Miliseconds\n" ANSI_COLOR_RESET, elapsed);
            }
        } else if (strcmp(argv[1],"clean") == 0){
            if (CLEAN_ENALED == false){
                    printf(ANSI_COLOR_RED "Clean Function Disabled !\n" ANSI_COLOR_RESET);    
                    return 0;
            } else {
                clock_t start = clock();
                int exitcode = system("./CleanScript.sh");
                if (exitcode == 0){
                    clock_t stop = clock();
                    double elapsed = (double)(stop - start) * 1000.0;
                    printf(ANSI_COLOR_GREEN "Clean Complete ! in %f Miliseconds\n" ANSI_COLOR_RESET, elapsed);
                } else {
                    clock_t stop = clock();
                    double elapsed = (double)(stop - start) * 1000.0;
                    printf(ANSI_COLOR_RED "Clean Failed ! in %f Miliseconds\n" ANSI_COLOR_RESET, elapsed);
                    
                }
            }
        } else if(strcmp(argv[1],"test")== 0){//Codigo do sistema de testes
            printf(ANSI_COLOR_YELLOW "Started Tests" ANSI_COLOR_RESET "\n");
            clock_t start = clock();
            int exitcode = system("./TestScript.sh");
            if (exitcode == 0){
                clock_t stop = clock();
                double elapsed = (double)(stop - start) * 1000.0;
                printf(ANSI_COLOR_GREEN "Test Pass! in %f Miliseconds\n" ANSI_COLOR_RESET, elapsed);
            } else {
                clock_t stop = clock();
                double elapsed = (double)(stop - start) * 1000.0;
                printf(ANSI_COLOR_RED "Test Failed ! in %f Miliseconds\n" ANSI_COLOR_RESET, elapsed);
            }
            /*
            Codigo da função de tasks
            */
        } else if (strcmp(argv[1],"task") == 0){
            clock_t start = clock();
            char taskrunner[13] = "./tasks/";//chama o script que estiver dentro da pasta tasks no seu projeto
            string taskname = argv[2]; //guarda oque o usuario digitou em uma variavel para ser usado como nome da task
            //concatena oque o usuario digitou com a extenção ".sh"
            string taskfile;     
            string buf(argv[2]); 
            taskfile = buf.append(".sh");
            //e coloca na variavel taskfile
            string code = strcat(taskrunner,taskfile.c_str()); //junta tudo isso em uma unica variavel
            int exitcode = system(code.c_str());//Executa e pega o codigo de saida igual as funções de build, clean e test
            if(exitcode == 0){
                clock_t stop = clock();
                double elapsed = (double)(stop - start) * 1000.0;
                printf(ANSI_COLOR_GREEN "Task '%s' Complete ! in %f Miliseconds\n" ANSI_COLOR_RESET,taskname.c_str(), elapsed);
            } else {
                clock_t stop = clock();
                double elapsed = (double)(stop - start) * 1000.0;                
                printf(ANSI_COLOR_RED "Task '%s' Failed ! in %f Miliseconds\n" ANSI_COLOR_RESET,taskname.c_str(), elapsed);
            }
            
        } else {// Em caso de argumento invalido
            printf("%s: Invalid Command. Try '%s help'\n", argv[0], argv[0]);
            return 0;
        } 
    }
}


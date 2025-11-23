#include <stdio.h> // Biblioteca padrão para entrada e saída
#include <stdlib.h> // Biblioteca padrão para entrada e saída
#include <stdbool.h> // Biblioteca para tipo booleano
#include <time.h> // Biblioteca para geração de números aleatórios

//  ============================================================ 
//  Desafio Tetris Stack - Nível Mestre Completo
//  Tema 3 - Integração de Fila e Pilha
//  Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
//  Use as instruções de cada nível para desenvolver o desafio.
//  ============================================================

// Struct Peca:
// Representa uma peça do Tetris com tipo (letra) e id sequencial
typedef struct {
    char tipo; // Tipo da peça (ex: 'I', 'O', 'T', 'L', 'S', 'Z', 'J')
    int id; // Identificador único da peça
} Peca;

// Fila circular de peças futuras
#define TAM_FILA 5
Peca fila[TAM_FILA]; // Vetor que armazena as peças da fila
int iniFila = 0; // Índice do início da fila
int fimFila = 0; // Índice do final da fila
int qtdFila = 0; // Quantidade de peças na fila

// Pilha linear de reserva
#define TAM_PILHA 3
Peca pilha[TAM_PILHA]; // Vetor que armazena as peças da pilha
int topoPilha = -1; // Índice do topo da pilha

// Controle de geração de peças
int proximoId = 1; // Id sequencial para cada nova peça

// Protótipos das funções
// Funções para operar a fila
void inicializarFila();
bool filaCheia();
bool filaVazia();
void enqueue(Peca p); // Insere peça no final da fila
Peca dequeue(); // Remove peça da frente da fila
void mostrarFila();
Peca gerarPeca();

// Funções para operar a pilha
void inicializarPilha();
bool pilhaCheia();
bool pilhaVazia();
void push(Peca p);
Peca pop();
void mostrarPilha();

// Funções do menu e operações
void menu();
void jogarPeca();
void enviarParaReserva();
void usarReserva();
void trocarFrenteComTopo();
void trocarTresFilaTresPilha();

// Função principal
int main() {
    srand(time(NULL)); // Semeia o gerador de aleatórios
    inicializarFila();
    inicializarPilha();
    menu();
    return 0;
}

// Inicializa a fila circular com 5 peças geradas automaticamente
void inicializarFila() {
    iniFila = fimFila = qtdFila = 0; // Inicializa índices e quantidade
    for(int i=0; i<TAM_FILA; i++) { // Preenche a fila com peças iniciais
        enqueue(gerarPeca()); // Gera e insere uma peça na fila
    }
}

// Verifica se a fila está cheia
bool filaCheia() {
    return qtdFila == TAM_FILA; // A fila está cheia se a quantidade atingir o tamanho máximo
}

// Verifica se a fila está vazia
bool filaVazia() {
    return qtdFila == 0; // A fila está vazia se a quantidade for zero
}

// Insere uma peça no final da fila
void enqueue(Peca p) {
    if(filaCheia()) return; // Não insere se a fila estiver cheia
    fila[fimFila] = p; // Insere a peça no final da fila
    fimFila = (fimFila + 1) % TAM_FILA; // Atualiza o índice do final da fila circularmente
    qtdFila++;  // Incrementa a quantidade de peças na fila
}

// Remove e retorna a peça da frente da fila
Peca dequeue() {
    Peca removida = {'-', -1}; // Peça inválida padrão
    if(filaVazia()) return removida; // Retorna peça inválida se a fila estiver vazia
    removida = fila[iniFila]; // Remove a peça da frente da fila
    iniFila = (iniFila + 1) % TAM_FILA; // Atualiza o índice do início da fila circularmente
    qtdFila--;  // Decrementa a quantidade de peças na fila
    return removida;
}

// Exibe o conteúdo da fila
void mostrarFila() {
    printf("\nFila de Peças Futuras: ");
    if(filaVazia()) { printf("[vazia]\n"); return; } // Exibe mensagem se a fila estiver vazia
    for(int i=0, idx=iniFila; i<qtdFila; i++, idx=(idx+1)%TAM_FILA) { // Percorre a fila circularmente
        printf("[%c#%d] ", fila[idx].tipo, fila[idx].id); // Exibe cada peça da fila
    }
    printf("\n");
}

// Gera uma peça aleatória com tipo e id sequencial
Peca gerarPeca() {
    char tipos[] = {'I','O','T','L','S','Z','J'}; // Tipos possíveis de peças
    int n = sizeof(tipos)/sizeof(tipos[0]); // Número de tipos
    Peca p; // Peça a ser gerada
    p.tipo = tipos[rand()%n]; // Seleciona um tipo aleatório
    p.id = proximoId++; // Atribui o próximo id sequencial
    return p; 
}

// Inicializa a pilha de reserva
void inicializarPilha() {
    topoPilha = -1; // Inicializa o topo da pilha como vazio
}

// Verifica se a pilha está cheia
bool pilhaCheia() {
    return topoPilha == TAM_PILHA-1; // A pilha está cheia se o topo atingir o tamanho máximo -1 
}

// Verifica se a pilha está vazia
bool pilhaVazia() {
    return topoPilha == -1; // A pilha está vazia se o topo for -1
}

// Empilha uma peça no topo da pilha
void push(Peca p) {
    if(pilhaCheia()) return;
    pilha[++topoPilha] = p; // Adiciona a peça no topo da pilha
}

// Desempilha e retorna a peça do topo
Peca pop() {
    Peca removida = {'-', -1}; // Peça inválida padrão
    if(pilhaVazia()) return removida; // Retorna peça inválida se a pilha estiver vazia
    removida = pilha[topoPilha--]; // Remove a peça do topo da pilha
    return removida; 
}

// Exibe o conteúdo da pilha
void mostrarPilha() {
    printf("Reserva (Pilha): ");
    if(pilhaVazia()) { printf("[vazia]\n"); return; } // Exibe mensagem se a pilha estiver vazia
    for(int i=0; i<=topoPilha; i++) { // Percorre a pilha do fundo ao topo
        printf("[%c#%d] ", pilha[i].tipo, pilha[i].id); // Exibe cada peça da pilha
    }
    printf("\n");
}

// Menu principal do programa
void menu() {
    int op;
    do {
        printf("\n==============================\n");
        printf("   TETRIS STACK - MENU\n");
        printf("==============================\n");
        mostrarFila();
        mostrarPilha();
        printf("------------------------------\n");
        printf("1 - Jogar peça (remover da frente da fila)\n");
        printf("2 - Enviar peça da fila para a reserva (pilha)\n");
        printf("3 - Usar peça da reserva (remover do topo da pilha)\n");
        printf("4 - Trocar peça da frente com topo da pilha\n");
        printf("5 - Trocar 3 primeiros da fila com os 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op); getchar(); // Limpa o buffer do teclado
        switch(op) {
            case 1: 
                jogarPeca(); // Executa a ação de jogar peça
                break; 
            case 2: 
                enviarParaReserva(); // Executa a ação de enviar peça para a reserva
                break;
            case 3: 
                usarReserva(); // Executa a ação de usar peça da reserva
                break;
            case 4: 
                trocarFrenteComTopo(); // Executa a ação de trocar peça da frente com topo da pilha
                break;
            case 5: 
                trocarTresFilaTresPilha(); // Executa a ação de trocar os 3 primeiros da fila com os 3 da pilha
                break;
            case 0: 
                printf("Saindo...\n"); 
                break;
            default: printf("Opção inválida!\n");
        }
        if(op != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar(); // Aguarda o usuário pressionar ENTER
        }
    } while(op != 0); // Repete até o usuário escolher sair
}

// Opção 1: Jogar peça (remove da frente da fila e repõe)
void jogarPeca() {
    if(filaVazia()) { // Verifica se a fila está vazia
        printf("Fila vazia!\n");
        return;
    }
    Peca jogada = dequeue(); // Remove a peça da frente da fila
    printf("Peça jogada: [%c#%d]\n", jogada.tipo, jogada.id); // Exibe a peça jogada
    enqueue(gerarPeca()); // Repõe uma nova peça
}

// Opção 2: Enviar peça da fila para a pilha de reserva
void enviarParaReserva() {
    if(filaVazia()) { // Verifica se a fila está vazia
        printf("Fila vazia!\n");
        return;
    }
    if(pilhaCheia()) { // Verifica se a pilha está cheia
        printf("Reserva cheia!\n");
        return;
    }
    Peca p = dequeue(); // Remove a peça da frente da fila
    push(p); // Empilha a peça na pilha de reserva
    printf("Peça [%c#%d] enviada para a reserva.\n", p.tipo, p.id); // Exibe a peça enviada para a reserva
    enqueue(gerarPeca()); // Repõe uma nova peça
}

// Opção 3: Usar peça da reserva (remover do topo da pilha)
void usarReserva() {
    if(pilhaVazia()) { // Verifica se a pilha está vazia
        printf("Reserva vazia!\n");
        return;
    }
    Peca p = pop(); // Remove a peça do topo da pilha de reserva
    printf("Peça da reserva usada: [%c#%d]\n", p.tipo, p.id); // Exibe a peça usada da reserva
}

// Opção 4: Trocar peça da frente da fila com topo da pilha
void trocarFrenteComTopo() {
    if(filaVazia()) { // Verifica se a fila está vazia
        printf("Fila vazia!\n");
        return;
    }
    if(pilhaVazia()) {
        printf("Reserva vazia!\n");
        return;
    }
    int idxFila = iniFila; // Índice da frente da fila
    int idxPilha = topoPilha; // Índice do topo da pilha
    Peca temp = fila[idxFila]; // Armazena temporariamente a peça da frente da fila
    fila[idxFila] = pilha[idxPilha]; // Troca a peça da frente da fila com a do topo da pilha
    pilha[idxPilha] = temp; // Coloca a peça temporária no topo da pilha
    printf("Troca realizada entre frente da fila e topo da pilha.\n");
}

// Opção 5: Trocar os 3 primeiros da fila com os 3 da pilha
void trocarTresFilaTresPilha() {
    if(qtdFila < 3) { // Verifica se a fila tem pelo menos 3 peças
        printf("A fila deve ter pelo menos 3 peças!\n");
        return;
    }
    if(topoPilha != 2) { // Verifica se a pilha tem exatamente 3 peças
        printf("A pilha deve ter exatamente 3 peças!\n");
        return;
    }
    for(int i=0; i<3; i++) { // Itera sobre os 3 primeiros elementos
        int idxFila = (iniFila + i) % TAM_FILA; // Calcula o índice circular na fila
        Peca temp = fila[idxFila]; // Armazena temporariamente a peça da fila
        fila[idxFila] = pilha[i]; // Troca a peça da fila com a da pilha
        pilha[i] = temp; // Coloca a peça temporária na pilha
    }
    printf("Troca realizada entre os 3 primeiros da fila e os 3 da pilha.\n");
}
/*
    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.



    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha
*/

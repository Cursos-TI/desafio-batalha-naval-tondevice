#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM 10     // Tamanho do tabuleiro
#define NAVIO 3    // Valor que representa navio
#define AGUA 0     // Valor que representa água
#define HABIL 1    // Valor que representa área afetada por habilidade

// Função para inicializar o tabuleiro com 0 (água)
void inicializarMatriz(int matriz[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            matriz[i][j] = AGUA;
        }
    }
}

// Função para imprimir uma matriz
void imprimirMatriz(int matriz[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Verifica se pode posicionar o navio
int podePosicionar(int matriz[TAM][TAM], int linha, int coluna, char orientacao) {
    for (int i = 0; i < NAVIO; i++) {
        int l = linha + ((orientacao == 'V') ? i : (orientacao == 'D') ? i : (orientacao == 'E') ? i : 0);
        int c = coluna + ((orientacao == 'H') ? i : (orientacao == 'D') ? i : (orientacao == 'E') ? -i : 0);
        if (l < 0 || l >= TAM || c < 0 || c >= TAM || matriz[l][c] != AGUA) {
            return 0;
        }
    }
    return 1;
}

// Posiciona o navio no tabuleiro
void posicionarNavio(int matriz[TAM][TAM], int linha, int coluna, char orientacao) {
    for (int i = 0; i < NAVIO; i++) {
        int l = linha + ((orientacao == 'V') ? i : (orientacao == 'D') ? i : (orientacao == 'E') ? i : 0);
        int c = coluna + ((orientacao == 'H') ? i : (orientacao == 'D') ? i : (orientacao == 'E') ? -i : 0);
        matriz[l][c] = NAVIO;
        printf("Navio %c - Parte %d em: (%d, %d)\n", orientacao, i + 1, l, c);
    }
    printf("\n");
}

// Aplica padrão de habilidade "cone"
void aplicarCone(int matriz[TAM][TAM], int centroX, int centroY) {
    for (int i = 0; i < 3; i++) {
        for (int j = -i; j <= i; j++) {
            int x = centroX + i;
            int y = centroY + j;
            if (x >= 0 && x < TAM && y >= 0 && y < TAM)
                matriz[x][y] = HABIL;
        }
    }
}

// Aplica padrão de habilidade "cruz"
void aplicarCruz(int matriz[TAM][TAM], int centroX, int centroY) {
    for (int i = -2; i <= 2; i++) {
        if (centroX + i >= 0 && centroX + i < TAM)
            matriz[centroX + i][centroY] = HABIL;
        if (centroY + i >= 0 && centroY + i < TAM)
            matriz[centroX][centroY + i] = HABIL;
    }
}

// Aplica padrão de habilidade "octaedro"
void aplicarOctaedro(int matriz[TAM][TAM], int centroX, int centroY) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (abs(i) + abs(j) <= 1) {
                int x = centroX + i;
                int y = centroY + j;
                if (x >= 0 && x < TAM && y >= 0 && y < TAM)
                    matriz[x][y] = HABIL;
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarMatriz(tabuleiro);

    // Posicionamento dos navios
    printf("Posicionamento dos navios:\n");

    if (podePosicionar(tabuleiro, 2, 2, 'H')) posicionarNavio(tabuleiro, 2, 2, 'H');
    if (podePosicionar(tabuleiro, 5, 5, 'V')) posicionarNavio(tabuleiro, 5, 5, 'V');
    if (podePosicionar(tabuleiro, 0, 0, 'D')) posicionarNavio(tabuleiro, 0, 0, 'D');
    if (podePosicionar(tabuleiro, 0, 9, 'E')) posicionarNavio(tabuleiro, 0, 9, 'E');

    printf("Tabuleiro com navios (0 = água, 3 = navio):\n");
    imprimirMatriz(tabuleiro);

    // Matrizes para habilidades
    int cone[TAM][TAM], cruz[TAM][TAM], octaedro[TAM][TAM];
    inicializarMatriz(cone);
    inicializarMatriz(cruz);
    inicializarMatriz(octaedro);

    // Aplicação das habilidades
    aplicarCone(cone, 1, 2);        // Cone a partir da linha 1, coluna 2
    aplicarCruz(cruz, 5, 5);        // Cruz centrada na linha 5, coluna 5
    aplicarOctaedro(octaedro, 7, 7); // Octaedro centrado em 7,7

    printf("Habilidade: Cone\n");
    imprimirMatriz(cone);

    printf("Habilidade: Cruz\n");
    imprimirMatriz(cruz);

    printf("Habilidade: Octaedro\n");
    imprimirMatriz(octaedro);

    return 0;
}

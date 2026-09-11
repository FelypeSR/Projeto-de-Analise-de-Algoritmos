#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Como words.h é um arquivo criado por você e está na pasta
 * do projeto, usamos aspas em vez de < >.
 */
#include "words.h"

/*
 * Esta função compara duas strings e encontra o maior
 * prefixo que elas possuem em comum.
 *
 * Exemplo:
 * str1 = "programador"
 * str2 = "programacao"
 *
 * Resultado: "programa"
 */
char *pre_longo_comum(const char *str1, const char *str2) {

    /*
     * Aqui recebemos as duas strings e calculamos
     * o tamanho de cada uma.
     *
     * strlen() retorna size_t, um tipo próprio para
     * representar tamanhos e quantidades de memória.
     */
    size_t tamanho1 = strlen(str1);
    size_t tamanho2 = strlen(str2);

    /*
     * Precisamos comparar somente até o tamanho da menor string.
     *
     * Por exemplo:
     * "casa" possui 4 caracteres
     * "casamento" possui 9 caracteres
     *
     * A comparação deve ir somente até 4, pois não podemos
     * acessar posições que não existem na menor palavra.
     */
    size_t tamanho_minimo =
        (tamanho1 < tamanho2) ? tamanho1 : tamanho2;

    /*
     * Esta variável armazena quantos caracteres iguais
     * foram encontrados no início das duas strings.
     */
    size_t tamanho_prefixo = 0;

    /*
     * Alocamos memória para armazenar o prefixo longo comum.
     *
     * O "+ 1" reserva espaço para o caractere '\0',
     * que indica o final de uma string em C.
     */
    char *prefixo =
        malloc((tamanho_minimo + 1) * sizeof(char));

    /*
     * Verificamos se a alocação de memória foi bem-sucedida.
     *
     * malloc() retorna NULL quando não consegue
     * reservar a memória solicitada.
     */
    if (prefixo == NULL) {
        printf("Erro ao alocar memória para o prefixo.\n");
        exit(EXIT_FAILURE);
    }

    /*
     * Comparamos os caracteres das duas strings
     * começando pela primeira posição.
     */
    for (size_t i = 0; i < tamanho_minimo; i++) {

        /*
         * Se os caracteres forem iguais, copiamos
         * o caractere para a string prefixo.
         */
        if (str1[i] == str2[i]) {
            prefixo[tamanho_prefixo] = str1[i];
            tamanho_prefixo++;
        } else {
            /*
             * Quando encontramos o primeiro caractere diferente,
             * encerramos a comparação.
             *
             * Isso acontece porque procuramos um PREFIXO.
             * Portanto, os caracteres precisam ser iguais
             * desde o começo da palavra.
             */
            break;
        }
    }

    /*
     * Toda string em C precisa terminar com '\0'.
     *
     * Sem isso, printf() e outras funções poderiam continuar
     * lendo posições de memória indevidamente.
     */
    prefixo[tamanho_prefixo] = '\0';

    /*
     * Retornamos o endereço da memória que contém o prefixo.
     *
     * Como essa memória foi criada com malloc(), quem chamar
     * esta função deverá liberá-la posteriormente com free().
     */
    return prefixo;
}

/*
 * Esta função utiliza divisão e conquista para encontrar
 * o prefixo comum de várias palavras.
 *
 * Ela divide o vetor de palavras em duas partes:
 *
 * 1. Parte esquerda;
 * 2. Parte direita.
 *
 * Depois encontra o prefixo de cada parte e compara
 * os dois resultados.
 */
char *divisao_conquista(
    const char *strings[],
    int inicio,
    int fim
) {

    /*
     * Caso-base da recursão:
     *
     * Quando inicio e fim são iguais, significa que existe
     * somente uma palavra nessa parte do vetor.
     */
    if (inicio == fim) {

        /*
         * Criamos uma cópia da palavra.
         *
         * Não devemos retornar diretamente strings[inicio],
         * pois posteriormente o programa utilizará free()
         * para liberar os resultados das chamadas recursivas.
         *
         * Só podemos usar free() em memória criada com
         * malloc(), calloc() ou realloc().
         */
        char *prefixo =
            malloc((strlen(strings[inicio]) + 1) * sizeof(char));

        /*
         * Verificamos se malloc() conseguiu alocar a memória.
         */
        if (prefixo == NULL) {
            printf("Erro ao alocar memória para a palavra.\n");
            exit(EXIT_FAILURE);
        }

        /*
         * Copiamos a palavra para a memória recém-alocada.
         *
         * strcpy() também copia o caractere final '\0'.
         */
        strcpy(prefixo, strings[inicio]);

        return prefixo;
    }

    /*
     * Calculamos o ponto central do intervalo.
     *
     * Esta forma evita alguns problemas que poderiam acontecer
     * com a expressão:
     *
     *     (inicio + fim) / 2
     */
    int meio = inicio + (fim - inicio) / 2;

    /*
     * Chamamos novamente a função para encontrar
     * o prefixo comum da metade esquerda.
     */
    char *prefixo_esquerda =
        divisao_conquista(strings, inicio, meio);

    /*
     * Agora encontramos o prefixo comum
     * da metade direita.
     */
    char *prefixo_direita =
        divisao_conquista(strings, meio + 1, fim);

    /*
     * Comparamos o resultado da esquerda com o resultado
     * da direita para encontrar o prefixo comum entre eles.
     */
    char *resultado =
        pre_longo_comum(prefixo_esquerda, prefixo_direita);

    /*
     * Os dois prefixos foram criados com malloc().
     *
     * Como eles já foram usados para gerar o resultado final,
     * não precisamos mais deles e devemos liberar a memória.
     */
    free(prefixo_esquerda);
    free(prefixo_direita);

    /*
     * Retornamos o prefixo encontrado nessa etapa.
     */
    return resultado;
}

/*
 * Esta é a função principal do algoritmo.
 *
 * Ela recebe:
 *
 * strings -> vetor contendo as palavras;
 * tamanho -> quantidade de palavras no vetor.
 */
char *prefixo_longo_comum(
    const char *strings[],
    int tamanho
) {

    /*
     * Se o vetor não possuir palavras, retornamos
     * uma string vazia.
     */
    if (tamanho <= 0) {

        /*
         * Uma string vazia ainda precisa de uma posição
         * para armazenar o caractere final '\0'.
         */
        char *vazio = malloc(sizeof(char));

        /*
         * Verificamos se a memória foi alocada.
         */
        if (vazio == NULL) {
            printf("Erro ao alocar memória para a string vazia.\n");
            exit(EXIT_FAILURE);
        }

        /*
         * Colocamos o terminador de string na primeira posição.
         */
        vazio[0] = '\0';

        return vazio;
    }

    /*
     * Iniciamos o algoritmo de divisão e conquista.
     *
     * O primeiro índice é 0.
     * O último índice é tamanho - 1.
     */
    return divisao_conquista(strings, 0, tamanho - 1);
}

int main(void) {

    /*
     * Calculamos a quantidade de palavras existentes
     * no vetor declarado em words.h.
     *
     * sizeof(palavras) retorna o tamanho total do vetor.
     * sizeof(palavras[0]) retorna o tamanho de uma posição.
     */
    int quantidade =
        sizeof(palavras) / sizeof(palavras[0]);

    /*
     * Chamamos a função que encontra o prefixo longo comum.
     *
     * O resultado aponta para uma região criada com malloc().
     */
    char *resultado =
        prefixo_longo_comum(palavras, quantidade);

    /*
     * Mostramos as palavras utilizadas no teste.
     */
    printf("Palavras analisadas:\n");

    for (int i = 0; i < quantidade; i++) {
        printf("- %s\n", palavras[i]);
    }

    /*
     * Mostramos o prefixo longo comum encontrado.
     *
     * As aspas ajudam a visualizar quando o resultado
     * é uma string vazia.
     */
    printf("\nPrefixo longo comum: \"%s\"\n", resultado);

    /*
     * Como o resultado foi criado com malloc(),
     * precisamos liberar essa memória antes de encerrar.
     */
    free(resultado);

    return 0;
}
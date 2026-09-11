# Projeto-de-Analise-de-Algoritmos
Grupo destinado aos trabalhos
 aqui está o pseudo-código
 ALGORITMO "Prefixo Longo Comum"

/*
    Encontra o maior prefixo comum entre duas palavras.

    Exemplo:
    palavra1 = "programador"
    palavra2 = "programacao"

    Resultado = "programa"
*/
FUNÇÃO PRE_LONGO_COMUM(palavra1, palavra2)

    // Descobre o tamanho de cada palavra.
    tamanho1 ← COMPRIMENTO(palavra1)
    tamanho2 ← COMPRIMENTO(palavra2)

    // A comparação deve acontecer somente até o fim
    // da menor palavra.
    SE tamanho1 < tamanho2 ENTÃO
        tamanhoMinimo ← tamanho1
    SENÃO
        tamanhoMinimo ← tamanho2
    FIM_SE

    // Inicialmente, o prefixo é uma string vazia.
    prefixo ← ""

    // Percorre as duas palavras desde a primeira posição.
    PARA i ← 0 ATÉ tamanhoMinimo - 1 FAÇA

        // Se os caracteres forem iguais, adicionamos
        // o caractere ao prefixo.
        SE palavra1[i] = palavra2[i] ENTÃO
            prefixo ← prefixo + palavra1[i]
        SENÃO

            // Quando encontramos caracteres diferentes,
            // encerramos a comparação, pois o prefixo precisa
            // começar na primeira posição da palavra.
            INTERROMPER
        FIM_SE

    FIM_PARA

    RETORNAR prefixo

FIM_FUNÇÃO


/*
    Aplica a estratégia de divisão e conquista.

    O vetor de palavras é dividido em duas partes.
    Depois, o prefixo da parte esquerda é comparado
    com o prefixo da parte direita.
*/
FUNÇÃO DIVISAO_CONQUISTA(palavras, inicio, fim)

    /*
        Caso-base da recursão:

        Quando início e fim são iguais, existe somente
        uma palavra nessa parte do vetor.
    */
    SE inicio = fim ENTÃO
        RETORNAR CÓPIA(palavras[inicio])
    FIM_SE

    // Calcula a posição central do intervalo.
    meio ← inicio + ((fim - inicio) DIV 2)

    // Encontra o prefixo comum da metade esquerda.
    prefixoEsquerda ← DIVISAO_CONQUISTA(
        palavras,
        inicio,
        meio
    )

    // Encontra o prefixo comum da metade direita.
    prefixoDireita ← DIVISAO_CONQUISTA(
        palavras,
        meio + 1,
        fim
    )

    // Compara os resultados das duas metades.
    resultado ← PRE_LONGO_COMUM(
        prefixoEsquerda,
        prefixoDireita
    )

    // Retorna o prefixo encontrado nesta etapa.
    RETORNAR resultado

FIM_FUNÇÃO


/*
    Função responsável por iniciar o algoritmo.

    palavras: vetor contendo todas as palavras;
    quantidade: número de palavras existentes no vetor.
*/
FUNÇÃO PREFIXO_LONGO_COMUM(palavras, quantidade)

    // Se não existirem palavras, retorna uma string vazia.
    SE quantidade <= 0 ENTÃO
        RETORNAR ""
    FIM_SE

    /*
        Inicia a divisão e conquista.

        O primeiro índice do vetor é 0.
        O último índice é quantidade - 1.
    */
    RETORNAR DIVISAO_CONQUISTA(
        palavras,
        0,
        quantidade - 1
    )

FIM_FUNÇÃO


INÍCIO

    // Palavras que serão analisadas.
    palavras ← [
        "programacao",
        "programador",
        "programar",
        "programa"
    ]

    // Descobre quantas palavras existem no vetor.
    quantidade ← TAMANHO(palavras)

    // Executa o algoritmo de prefixo longo comum.
    resultado ← PREFIXO_LONGO_COMUM(
        palavras,
        quantidade
    )

    // Mostra as palavras analisadas.
    ESCREVA("Palavras analisadas:")

    PARA i ← 0 ATÉ quantidade - 1 FAÇA
        ESCREVA(palavras[i])
    FIM_PARA

    // Mostra o prefixo encontrado.
    ESCREVA("Prefixo longo comum: ", resultado)

FIM

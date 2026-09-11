#ifndef WORDS_H
#define WORDS_H

/*
 * Este arquivo contém as palavras que serão analisadas.
 *
 * O uso de const indica que o programa não deve modificar
 * o conteúdo dessas palavras.
 *
 * O uso de static faz com que este vetor pertença somente
 * ao arquivo que incluiu este cabeçalho, evitando conflitos
 * durante a compilação de projetos pequenos.
 */
static const char *palavras[] = {
    "programacao",
    "programador",
    "programar",
    "programa"
};

#endif
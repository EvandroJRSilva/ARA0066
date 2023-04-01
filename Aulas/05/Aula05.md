# Aula 05

Sumário

- [Aula 05](#aula-05)
  - [Ponteiros](#ponteiros)
    - [Alocação dinâmica de memória](#alocação-dinâmica-de-memória)
  - [Listas encadeadas](#listas-encadeadas)

---

## Ponteiros

Um `ponteiro` guarda um endereço de memória de uma variável.

```c
int a, *p;

p = &a;
```

No exemplo acima temos um trecho de programa em `C` com duas variáveis declaradas. A variável `a` é do tipo inteiro, e a variável `*p` é um `ponteiro` que *aponta* para uma variável do tipo inteiro. Literalmente, `*p` armazena o endereço da variável `a` ([exemplo 01](exemplo01.c)). A partir de um ponteiro é possível também manipular os valores de alguma variável ([exemplo 02](exemplo2.c)).

<br>

### Alocação dinâmica de memória

Vimos nas aulas anteriores que quando declaramos uma variável, o compilador reserva um espaço de memória (e seu endereço) de tamanho apropriado para o tipo de dado.

Em programas pequenos, onde sabemos de antemão e de forma estática quantas variáveis utilizaremos, é trivial declaramos e utilizarmos todas as variáveis necessárias, inclusive quando se trata de algum tipo *composto*:

```c
typedef struct{
    char nome[50];
    int idade;
    float peso;
} Pessoa;
```

No exemplo acima foi criado um tipo de dados chamado **Pessoa**, o qual é composto por três tipos de dados: *String*, *int* e *float*. Uma variável do tipo **Pessoa**, assim que declarada, terá reservada para si um espaço de memória suficiente para armazenar os três tipos de dados.

Voltando ao assunto anterior, em um programa simples, sabemos quantas variáveis diferentes de cada tipo (mesmo sendo do tipo **Pessoa**) utilizaremos. Porém, existe a situação, em programas mais complexos, que não sabemos quantas variáveis de cada tipo iremos manipular. A partir disso temos duas soluções possíveis: (1) criar uma lista estática com um tamanho predefinido contendo uma quantidade razoável de variáveis de cada tipo; (2) declarar dinamicamente cada nova variável que precisarmos.

A primeira solução tem o problema de não se ter como saber qual o tamanho razoável de variáveis para cada tipo precisamos declarar: 10? 100? 1000? 10000? Imagine mil variáveis de cada tipo: **int**, **float**, **char**, etc. Não é viável, pois muita memória possivelmente será reservada a toa. Ou ainda, não será reservado espaço suficiente para o que realmente será utilizado. 

Por exemplo, suponha que você crie um programa que reserva mil variáveis dos três tipos citados, porém acaba utilizando de fato 900 variáveis inteiras e apenas 50 do tipo `float`, e 200 do tipo `char`. Considerando 1 byte por `char`, 4 bytes por número inteiro, e 8 bytes por `float`, ao fim do programa teríamos (1 * 800 + 4 * 100 + 8 * 950 =) 8800 bytes (~ 8kB) de memória desperdiçada. Hoje em dia 8kB são irrisórios, mas eram significativos há pouco mais de 20 anos atrás.

Agora, imagine que, na realidade, você tenha precisado de 2500 variáveis do tipo `char`, 7 mil do tipo `int` e 25 mil do tipo `float`. Ter reservado apenas mil para cada não terá sido suficiente.

A melhor solução então é a segunda apresentada, ou seja, uma alocação dinâmica de memória para cada variável que necessitarmos.

Em `C` podemos manipular a memória de forma dinâmica com 04 funções principais:

- `malloc`: *memory allocation*;
- `calloc`: *contiguous allocation*;
- `realloc`: *reallocation*;
- `free`.

A sintaxe de cada função é da seguinte forma:

```c
endereco = tipo *malloc(int tamanho);

endereco = tipo *calloc(int numElementos, int tamanhoElemento);

endereco = tipo *realloc(tipo *ptr, int novoTamanho);

free(*ptr);
```

A variável `endereco` vai receber o endereço da memória dinamicamente alocada. No lugar de `tipo` pode-se declarar qualquer tipo de variável, inclusive uma criada pelo programador. Por exemplo:

```c
endereco = Pessoa *malloc(sizeof(Pessoa));
// ou
endereco = (Pessoa *)malloc(sizeof(Pessoa));
```

A função `sizeof` retorna o tamanho de algum objeto. No caso do exemplo, retorna o tamanho de um tipo de dado **Pessoa**. O `*ptr` é o ponteiro que está sendo utilizado, `numElementos` é a quantidade de elementos, `tamanhoElemento` é o tamanho do elemento (o qual pode ser descoberto com a função `sizeof`), e, por fim, `novoTamanho` é a nova quantidade de espaço necessária para alocação (a qual pode ser menor ou maior que a anterior).

A diferença fundamental de `calloc` para `malloc`, é que a primeira função garante que o espaço alocado é inicializado com zeros, enquanto a segunda não, ou seja, a memória alocada pode conter *lixo*. Outra diferença é que o `calloc` aloca *numElementos* blocos, enquanto o `malloc` aloca apenas 01 bloco (de tamanho variável).

Na função `realloc`, e `novoTamanho` for maior e não houver espaço para que a alocação *cresça*, o conteúdo será mudado para outro endereço.

<br>

## Listas encadeadas

Quando espaços de memória são alocados dinamicamente, às vezes é interessante a utilização de uma `estrutura de dados` chamada `lista encadeada`.

Em uma `lista encadeada` cada elemento possui um `ponteiro` para o elemento seguinte, ou vazio (`NULL`). Existe a possibilidade de uma `lista encadeada` ser um `ciclo`, ou seja, o último elemento aponta para o primeiro, ou ser `duplamente encadeada`, onde cada elemento aponta para o próximo elemento e o elemento anterior.

Exemplo:

```c
typedef struct{
    int a;
    float b;
    struct Pessoa *anterior, *proximo; // duplamente encadeado
} Pessoa;
```

Com as listas é possível criar um conjunto de dados acessíveis guardando-se apenas o endereço para o primeiro elemento. Porém, existe a desvantagem de se fazer uma busca pelo n-ésimo elemento caso a lista seja enorme.

Outras estruturas de dados que podem ser implementadas de forma similar às listas são `pilhas` e `árvores`.
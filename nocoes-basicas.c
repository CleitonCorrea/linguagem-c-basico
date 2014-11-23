#include <stdio.h>
#include <stdlib.h>


Alocação dinâmica de memória
As declarações abaixo alocam memória para diversas variáveis. A alocação é estática, pois acontece antes que o programa comece a ser executado:

char c; int i; int v[10];
Às vezes, a quantidade de memória a alocar só se torna conhecida durante a execução do programa. Para lidar com essa situação é preciso recorrer à alocação dinâmica de memória. A alocação dinâmica é gerenciada pelas funções malloc e free, que estão na biblioteca stdlib.  Para usar esta biblioteca, é preciso dizer

#include <stdlib.h>
no início do programa.

Função malloc

A função  malloc  (abreviatura de memory allocation) aloca um bloco de bytes consecutivos na memória do computador e devolve o endereço desse bloco.  O número de bytes é especificado no argumento da função. No seguinte fragmento de código, malloc aloca 1 byte:

   char *ptr;
   ptr = malloc( 1);
   scanf( "%c", ptr);
O endereço devolvido por malloc é do tipo "genérico"  void *.   O programador armazena esse endereço num ponteiro de tipo apropriado. No exemplo acima, o endereço é armazenado num ponteiro-para-char.

Para alocar um tipo-de-dado que ocupa vários bytes, é preciso recorrer ao operador sizeof, que diz quantos bytes o tipo especificado tem:

   typedef struct {
      int dia, mes, ano;
   } data;
   data *d;
   d = malloc( sizeof (data));
   d->dia = 31; d->mes = 12; d->ano = 2008;
[As aparências enganam: sizeof não é uma função.]

Overhead. Cada invocação de malloc aloca um bloco de bytes consecutivos maior que o solicitado: os bytes adicionais são usados para guardar informações administrativas sobre o bloco de bytes (essas informações permitem que o bloco seja corretamente desalocado, mais tarde, pela função free).  O número de bytes adicionais pode ser grande, mas não depende do número de bytes solicitado no argumento de malloc.  Não é recomendável, portanto, invocar malloc repetidas vezes com argumento muito pequeno.  É preferível alocar um grande bloco de bytes e retirar pequenas porções desse bloco na medida do necessário.

Exercícios

Verificação do tamanho.  Compile e execute o seguinte programa:
   typedef struct {
      int dia, mes, ano;
   } data;
   int main( void) {
      printf( "sizeof (data) = %d\n", sizeof (data));
      printf( "sizeof (data *) = %d\n", sizeof (data *));
      return 0;
   }
A memória é finita

Se a memória do computador já estiver toda ocupada, malloc não consegue alocar mais espaço e devolve NULL. Convém verificar essa possibilidade antes de prosseguir:

   ptr = malloc( sizeof (data));
   if (ptr == NULL) {
      printf( "Socorro! malloc devolveu NULL!\n");
      exit( EXIT_FAILURE);
   }
A codificação frequente e repetida desse teste é cansativa para o programador e desvia a atenção do leitor. Por isso, vamos usar a seguinte versão alternativa de malloc:

void *mallocc( size_t nbytes)
{
   void *ptr;
   ptr = malloc( nbytes);
   if (ptr == NULL) {
      printf( "Socorro! malloc devolveu NULL!\n");
      exit( EXIT_FAILURE);
   }
   return ptr;
}
O parâmetro de mallocc é do tipo size_t.  Em muitos computadores, size_t é equivalente a unsigned int.   A função mallocc não está em nenhuma biblioteca e é desconhecida fora destas notas de aula. Ela é apenas uma abreviatura conveniente.

Função free

As variáveis alocadas estaticamente dentro de uma função desaparecem quando a execução da função termina. Já as variáveis alocadas dinâmicamente continuam a existir mesmo depois que a execução da função termina. Se for necessário liberar a memória ocupada por essas variáveis, é preciso recorrer à função free.

A função free libera a porção de memória alocada por malloc. O comando free( ptr) avisa o sistema de que o bloco de bytes apontado por ptr está livre. A próxima chamada de malloc poderá tomar posse desses bytes.

A função free não deve ser aplicada a uma parte de um bloco de bytes alocado por malloc; aplique free apenas ao bloco todo.

Convém não deixar ponteiros "soltos" (= dangling pointers) no seu programa, pois isso pode ser explorado por hackers para atacar o seu computador. Portanto, depois de cada free( ptr), atribua NULL a ptr:

   free( ptr);
   ptr = NULL;
Atribuir um valor a um ponteiro que se tornou inútil é decididamente deselegante, mas não há como lidar com hackers de maneira elegante…

Para não cansar o leitor com detalhes repetitivos, estas notas não seguem a recomendação de segurança acima.

Vetores e matrizes

Eis como um vetor (= array) com n elementos inteiros pode ser alocado (e depois desalocado) durante a execução de um programa:

   int *v;
   int n, i;
   scanf( "%d", &n);
   v = mallocc( n * sizeof (int));
   for (i = 0; i < n; ++i)
      scanf( "%d", &v[i]);
   for (i = n; i > 0; --i)
      printf( "%d ", v[i-1]);
   free( v);
(A propósito, veja observação sobre vetores e endereços em outra página.)  Do ponto de vista conceitual (mas apenas desse ponto de vista) o comando

   v = mallocc( 100 * sizeof (int));
tem o mesmo efeito que a alocação estática

   int v[100];
A propósito, convém lembrar que não permite escrever "int v[n]", a menos que n seja uma constante, definida por um #define.

Matrizes bidimensionais são implementadas como vetores de vetores. Uma matriz com m linhas e n colunas é um vetor cada um de cujos m elementos é um vetor de n elementos. O seguinte fragmento de código faz a alocação dinâmica de uma tal matriz:

   int **A;
   int i;
   A = mallocc( m * sizeof (int *));
   for (i = 0; i < m; ++i)
      A[i] = mallocc( n * sizeof (int));
O elemento de A que está no cruzamento da linha i com a coluna j é denotado por A[i][j].

Exercícios

Escreva uma função que receba um caractere c e transforme c em uma cadeia de caracteres, ou seja, devolva uma cadeia de caracteres de comprimento 1 tendo c como único elemento.
Escreva um programa que leia um número inteiro positivo n seguido de n números inteiros e imprima esses n números em ordem invertida. Por exemplo, ao receber
    5  222 333 444 555 666
o seu programa deve imprimir

    666 555 444 333 222
O seu programa não deve impor limitações sobre o valor de n.




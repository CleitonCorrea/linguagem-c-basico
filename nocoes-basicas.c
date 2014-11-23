#include <stdio.h>
#include <stdlib.h>


Aloca��o din�mica de mem�ria
As declara��es abaixo alocam mem�ria para diversas vari�veis. A aloca��o � est�tica, pois acontece antes que o programa comece a ser executado:

char c; int i; int v[10];
�s vezes, a quantidade de mem�ria a alocar s� se torna conhecida durante a execu��o do programa. Para lidar com essa situa��o � preciso recorrer � aloca��o din�mica de mem�ria. A aloca��o din�mica � gerenciada pelas fun��es malloc e free, que est�o na biblioteca stdlib.  Para usar esta biblioteca, � preciso dizer

#include <stdlib.h>
no in�cio do programa.

Fun��o malloc

A fun��o  malloc  (abreviatura de memory allocation) aloca um bloco de bytes consecutivos na mem�ria do computador e devolve o endere�o desse bloco.  O n�mero de bytes � especificado no argumento da fun��o. No seguinte fragmento de c�digo, malloc aloca 1 byte:

   char *ptr;
   ptr = malloc( 1);
   scanf( "%c", ptr);
O endere�o devolvido por malloc � do tipo "gen�rico"  void *.   O programador armazena esse endere�o num ponteiro de tipo apropriado. No exemplo acima, o endere�o � armazenado num ponteiro-para-char.

Para alocar um tipo-de-dado que ocupa v�rios bytes, � preciso recorrer ao operador sizeof, que diz quantos bytes o tipo especificado tem:

   typedef struct {
      int dia, mes, ano;
   } data;
   data *d;
   d = malloc( sizeof (data));
   d->dia = 31; d->mes = 12; d->ano = 2008;
[As apar�ncias enganam: sizeof n�o � uma fun��o.]

Overhead. Cada invoca��o de malloc aloca um bloco de bytes consecutivos maior que o solicitado: os bytes adicionais s�o usados para guardar informa��es administrativas sobre o bloco de bytes (essas informa��es permitem que o bloco seja corretamente desalocado, mais tarde, pela fun��o free).  O n�mero de bytes adicionais pode ser grande, mas n�o depende do n�mero de bytes solicitado no argumento de malloc.  N�o � recomend�vel, portanto, invocar malloc repetidas vezes com argumento muito pequeno.  � prefer�vel alocar um grande bloco de bytes e retirar pequenas por��es desse bloco na medida do necess�rio.

Exerc�cios

Verifica��o do tamanho.  Compile e execute o seguinte programa:
   typedef struct {
      int dia, mes, ano;
   } data;
   int main( void) {
      printf( "sizeof (data) = %d\n", sizeof (data));
      printf( "sizeof (data *) = %d\n", sizeof (data *));
      return 0;
   }
A mem�ria � finita

Se a mem�ria do computador j� estiver toda ocupada, malloc n�o consegue alocar mais espa�o e devolve NULL. Conv�m verificar essa possibilidade antes de prosseguir:

   ptr = malloc( sizeof (data));
   if (ptr == NULL) {
      printf( "Socorro! malloc devolveu NULL!\n");
      exit( EXIT_FAILURE);
   }
A codifica��o frequente e repetida desse teste � cansativa para o programador e desvia a aten��o do leitor. Por isso, vamos usar a seguinte vers�o alternativa de malloc:

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
O par�metro de mallocc � do tipo size_t.  Em muitos computadores, size_t � equivalente a unsigned int.   A fun��o mallocc n�o est� em nenhuma biblioteca e � desconhecida fora destas notas de aula. Ela � apenas uma abreviatura conveniente.

Fun��o free

As vari�veis alocadas estaticamente dentro de uma fun��o desaparecem quando a execu��o da fun��o termina. J� as vari�veis alocadas din�micamente continuam a existir mesmo depois que a execu��o da fun��o termina. Se for necess�rio liberar a mem�ria ocupada por essas vari�veis, � preciso recorrer � fun��o free.

A fun��o free libera a por��o de mem�ria alocada por malloc. O comando free( ptr) avisa o sistema de que o bloco de bytes apontado por ptr est� livre. A pr�xima chamada de malloc poder� tomar posse desses bytes.

A fun��o free n�o deve ser aplicada a uma parte de um bloco de bytes alocado por malloc; aplique free apenas ao bloco todo.

Conv�m n�o deixar ponteiros "soltos" (= dangling pointers) no seu programa, pois isso pode ser explorado por hackers para atacar o seu computador. Portanto, depois de cada free( ptr), atribua NULL a ptr:

   free( ptr);
   ptr = NULL;
Atribuir um valor a um ponteiro que se tornou in�til � decididamente deselegante, mas n�o h� como lidar com hackers de maneira elegante�

Para n�o cansar o leitor com detalhes repetitivos, estas notas n�o seguem a recomenda��o de seguran�a acima.

Vetores e matrizes

Eis como um vetor (= array) com n elementos inteiros pode ser alocado (e depois desalocado) durante a execu��o de um programa:

   int *v;
   int n, i;
   scanf( "%d", &n);
   v = mallocc( n * sizeof (int));
   for (i = 0; i < n; ++i)
      scanf( "%d", &v[i]);
   for (i = n; i > 0; --i)
      printf( "%d ", v[i-1]);
   free( v);
(A prop�sito, veja observa��o sobre vetores e endere�os em outra p�gina.)  Do ponto de vista conceitual (mas apenas desse ponto de vista) o comando

   v = mallocc( 100 * sizeof (int));
tem o mesmo efeito que a aloca��o est�tica

   int v[100];
A prop�sito, conv�m lembrar que n�o permite escrever "int v[n]", a menos que n seja uma constante, definida por um #define.

Matrizes bidimensionais s�o implementadas como vetores de vetores. Uma matriz com m linhas e n colunas � um vetor cada um de cujos m elementos � um vetor de n elementos. O seguinte fragmento de c�digo faz a aloca��o din�mica de uma tal matriz:

   int **A;
   int i;
   A = mallocc( m * sizeof (int *));
   for (i = 0; i < m; ++i)
      A[i] = mallocc( n * sizeof (int));
O elemento de A que est� no cruzamento da linha i com a coluna j � denotado por A[i][j].

Exerc�cios

Escreva uma fun��o que receba um caractere c e transforme c em uma cadeia de caracteres, ou seja, devolva uma cadeia de caracteres de comprimento 1 tendo c como �nico elemento.
Escreva um programa que leia um n�mero inteiro positivo n seguido de n n�meros inteiros e imprima esses n n�meros em ordem invertida. Por exemplo, ao receber
    5  222 333 444 555 666
o seu programa deve imprimir

    666 555 444 333 222
O seu programa n�o deve impor limita��es sobre o valor de n.




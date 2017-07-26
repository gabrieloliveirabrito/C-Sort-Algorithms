#include "includes.h"

FILE *saida;
int nS[6] = { 1000, 5000, 10000, 50000, 100000, 200000 }; //Tamanho das entradas
struct sList listas[6]; //Listas para armazenar os itens das entradas acima
const char words[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; //Caractéres para gerar as strings aleatórias

#ifdef DOUBLE_CHECK
//Percorre a lista pelo total de itens adicionados, procurando pela chave
int contemChave(struct sList *lista, Chave chave) 
{
	Chave i;
	for(i = 0; i < lista->total; i++)
	{
		if(lista->items[i].chave == chave)
			return 1;
	}
	return 0;
}
#endif

//Percorre a lista, gerando um índice aleatório para alteração do item na iteração
void mistura(struct sList *lista)
{
	int i;
	for(i = 0; i < lista->total; i++)
	{
		printf("Embaralhando items (%d%%)...\r", percentage(i, lista->total - 1));
		Chave j = random(0, RAND_MAX / (lista->total - 1) + 1);
		
		struct sItem a = lista->items[i];
		lista->items[i] = lista->items[j];
		lista->items[j] = a;
	}
	printf("\n");
}

//Método responvável por criar o item, suas strings e reais
//Após a criação, mistura os itens e escreve eles no arquivo de saída
void geraItems(struct sList *lista, FILE *f, int n)
{
	int i, j, k;
		
	for(i = 0 ; i < n; i++)
	{
		struct sItem novo;
		novo.chave = i + 1;
		
		printf("Gerando items (%d%%)...\r", percentage(i, n - 1));
		for(j = 0; j < 5; j++)
			novo.reais[j] = random(-50, 50);
		
		for(j = 0; j < 10; j++)
		{
			for(k = 0; k < 100; k++)
			{
				novo.strings[j][k] = words[random(0, 26 * 2)];
			}
			novo.strings[j][k] = '\0';
		}
		adicionar(lista, novo);
	}
	printf("\n");
	mistura(lista);
	
	for(i = 0 ; i < n; i++)
	{
		struct sItem item = lista->items[i];

		printf("Escrevendo items (%d%%)...\r", percentage(i, n - 1));				
		fprintf(f, "%d ", item.chave);
		for(j = 0; j < 5; j++)
		{
			fprintf(f, "%lf ", item.reais[j]);
		}
		
		for(j = 0; j < 10; j++)
		{
			fprintf(f, "%s", item.strings[j]);
			if(j != 9)
				fprintf(f, " ");
		}
		fprintf(f, "\r\n");
	}
	printf("\n");
}

void leItems(struct sList *lista, FILE *f, int n)
{	
	//Chave c;
	//fscanf(f, "%ld", &c);
	
	int i, j;
	for(i = 0; i < n; i++)
	{			
		printf("Lendo entrada %d de %d... (%d%%)\r", i + 1, n, percentage(i, n - 1));
		struct sItem item;
		fscanf(f, "%ld", &item.chave);
		
		for(j = 0; j < 5; j++)			
			fscanf(f, "%lf", &item.reais[j]);
		
		for(j = 0; j < 10; j++)			
			fscanf(f, "%s", &item.strings[j]);	
		
		#ifdef DOUBLE_CHECK
		if(contemChave(lista, item.chave))
		{
			printf("Chave %ld existente! Pulando....\n", item.chave);
			system("pause");
		}		
		else
		#endif
			adicionar(lista, item);
	}
	printf("\n");
}

//Após a lista ser iniciada, este método irá adicionar as informações da lista.
//Caso o arquivo exista, irá adicionar os dados dele, caso não, gera e salva o arquivo.
void carregaItems(struct sList *lista, int n)
{		
	criaLista(lista, n);
	
	char caminho[50] = { 0 };
	sprintf(caminho, "dados_%d.txt", n);
	
	FILE *f = fopen(caminho, "rb");
	if(!f)
	{
		printf("Arquivo nao encontrado, gerando...\n");
		f = fopen(caminho, "wb");
		
		printf("Gerando %d chaves....\r\n", n);		
		geraItems(lista, f, n);
	}
	else
	{
		printf("Lendo dados do arquivo...\n");		
		leItems(lista, f, n);
	}
	
	fclose(f);
	printf("FIM!\n");
}

int contem(int n, Chave chaves[n], Chave c)
{
	int i;
	for(i = 0; i < n; i++)
		if(chaves[i] == c)
			return 1;
	return 0;
}

//Após obter a lista, tendo um delegate como ponteiro de método, executa esse e a pesquisa
//Armazenando o tempo de execução de cada, além de suas trocas em uma struct
//Com um valor constante de incremento, cria um vetor de chaves de acordo com tal incremento, e testa os algorítmos de pesquisa e ordenação
Results testaSort(FILE* arq, struct sList *lista, unsigned int (*sortPointer)(struct sList*))
{
	#ifdef DEBUG
	printf("Ordenando lista....\n");
	#endif
	Results results;
	
	
	int i, t = SORT_INCREMENT, f = 0;
	double bTime;
	
	do
	{	
		struct sList toSort;
		copiaN(lista, &toSort, t);
		Chave chaves[t];
		
		for(i = 0; i < t; i++)
			chaves[i] = i + 1;
		
		for(i = 0; i < t; i++)
		{
			int j = random(0, t - 1);
		
			Chave aux = chaves[i];
			chaves[i] = chaves[j];
			chaves[j] = aux;
		}
		
		
		iniciaTimer();
		for(i = 0; i < t; i++)
		{
			Chave c = chaves[i];
			sequentialSearch(toSort, c, &results.sComp);
		}
		results.seqTime = paraTimer();
		
		iniciaTimer();
		results.trocas = (*sortPointer)(&toSort);
		results.sortTime = paraTimer();	
	
		iniciaTimer();
		#ifdef DEBUG
		printf("Procurando por uma chave aleatoria com binary search ordenado....\n");
		#endif
		for(i = 0; i < t; i++)
		{
			Chave c = chaves[i];
			binarySearch(toSort, c, &results.bComp);
		}
		results.searchTime = results.sortTime + paraTimer();
		
		#ifdef DEBUG
		if(bPos)
			printf("Chave %d encontrada (pos = %ld)!\n\r", c, bPos);
		else
			printf("Chave %d nao encontrada!\n\r", c);*/
		#endif	
		
		f = results.searchTime < results.seqTime;
		
		if(!f)
			t += SORT_INCREMENT;
	} while(t <= lista->total && !f);
	
	results.t = f ? t : 0;
	return results;
}

//Imprime os resultados gerados pelos algorítmos
//Caso o valor t da estrutura seja 0, a busca binária não conseguiu ser melhor que a sequencial nos testes
Results imprimeResultados(FILE *arq,Results results, char* name)
{	
	fprintf(arq, "Resultados com o algoritmo -%s-\r\n", name);
	fprintf(arq, "Tempo da busca sequencial: %lf\r\n", results.seqTime);
	fprintf(arq, "Comparacoes do sequential feitas: %d\r\n", results.sComp);
	fprintf(arq, "Tempo do algoritmo de ordenacao: %lf\r\n", results.sortTime);
	fprintf(arq, "Trocas feitas: %d\r\n", results.trocas);
	fprintf(arq, "Tempo de pesquisa com o binary search: %lf\r\n", results.searchTime);
	fprintf(arq, "Comparacoes do binary feitas: %d\r\n", results.bComp);
	if(results.t == 0)
		fprintf(arq, "Para esse caso, a busca sequencial se saiu melhor para todos os testes (incremento de %d chaves por teste)!\r\n", SORT_INCREMENT);
	else
		fprintf(arq, "Apos %d chaves, a busca binaria se saiu melhor!\r\n", results.t);
	fprintf(arq, "\r\n");
	
	return results;
}

//Utilizando a lista de itens, gera resultados, sendo esses o tempo para organizar, pesquisar e o número de trocas
//Após os resultados, define qual algorítmo se saiu melhor
void testaVetor(struct sList *lista, FILE* arq)
{	
	//Executa os testes com o algoritmo informado, e depois imprime os resultados armazenados
	imprimeResultados(arq, testaSort(arq, lista, &shellSort), "Shell Sort");
	imprimeResultados(arq, testaSort(arq, lista, &mergeSort), "Merge Sort");
	imprimeResultados(arq, testaSort(arq, lista, &heapSort), "Heap Sort");
	imprimeResultados(arq, testaSort(arq, lista, &mergeSort), "Quick Sort");
}

void verificaSaida()
{
	saida = fopen("saida.txt", "r");
	if(saida)
		unlink("saida.txt");
	saida = fopen("saida.txt", "wb");
}

int main(int argc, char *argv[])
{	
	//Caso o arquivo de saida exista, deleta ele, se não o programa irá criar
	verificaSaida();
	
	//Marca para a próxima chamada da função random(min,max) gerar uma nova seed
	randReg.n = -1;
		
	int i;
	//Percorre o vetor de entradas pelo seu tamanho
	for(i = 0; i < sizeof(nS) / sizeof(nS[0]); i++)
	{
		int n = nS[i]; //Número de entradas armazenado no vetor
		struct sList *lista = &listas[i]; //Obtem o ponteiro da lista pela mesma posição do vetor
		
		fprintf(saida, "------- %d chaves -------\r\n", n);
		carregaItems(lista, n); //Lê ou escreve a lista, retornando a chave aleatória única
		testaVetor(lista, saida); //Testa a lista e as chaves com os algoritmos de busca e ordenação
		fprintf(saida, "------- FIM %d chaves -------\r\n\r\n", n);
	}	
		
	fclose(saida);
	system("pause");
	return 0;
}

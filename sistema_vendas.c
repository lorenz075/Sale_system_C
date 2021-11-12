#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define o struct da venda e tipo de dados venda
typedef struct venda {
	char nome_comprador[100];
	long long int cpf_comprador;
	char email[50];
	float preco_ingresso;
	char evento[100];
	char formaPagamento[50];
	
}venda;

// Compra do ingresso
void comprar()
{
	venda *v;
	FILE *ponteiro_arquivo;
	int num_ingressos, i = 0;
	 
	printf("Digite quantos ingressos deseja: ");
	scanf("%d", &num_ingressos);
	
	// Aloca dinamicamente memória para quantas compras o usuario desejar fazer
	v = (venda*)calloc(num_ingressos, sizeof(venda));
	//  abre arquivo em modo append e se nao existir cria um
	ponteiro_arquivo = fopen("vendas.txt", "a");
	
	
	for(i = 0; i < num_ingressos; i++)
	{
		int escolhaPagamento = 0, escolhaEvento = 0;
		
		while (escolhaEvento==0){
			printf("Escolha o evento: \n1)Show Restart\n2)Peppa Pig live with Slipknot\n3)Matanza e Sandy Júnior\n");
			scanf("%d", &escolhaEvento);
			switch (escolhaEvento) {
				case 1:
					strcpy(v[i].evento, "Show Restart");
					v[i].preco_ingresso = 200.00;
					break;
				case 2:
					strcpy(v[i].evento, "Peppa Pig live with Slipknot");
					v[i].preco_ingresso = 40.00;
					break;
				case 3:
					strcpy(v[i].evento, "Matanza e Sandy Júnior");
					v[i].preco_ingresso = 500.00;
					break;
				default:
					escolhaEvento = 0;
					printf("Opção nao existente\n");
			}
		}
		
		fflush(stdin);
		printf("Informe o nome: \n");
		scanf("%[^\n]s", v[i].nome_comprador);
		
		printf("Informe o cpf(apenas numeros): \n");
		scanf("%lld", &v[i].cpf_comprador);
		
		fflush(stdin);
		printf("Informe o email: \n");
		scanf("%[^\n]s", v[i].email);
		
		while (escolhaPagamento == 0) {
			printf("Escolha a forma de pagamento: \n1)Credito\n2)Boleto\n");
			scanf("%d", &escolhaPagamento);
			if (escolhaPagamento == 1) {
				strcpy(v[i].formaPagamento, "Credito");
				escolhaPagamento++;
			} else if (escolhaPagamento == 2) {
				strcpy(v[i].formaPagamento, "Boleto");
				escolhaPagamento++;
			} else {
				printf("Escolha inválida, tente novamente.");
				escolhaPagamento++;
			}
		}
		
		fwrite(&v[i], sizeof(venda), 1, ponteiro_arquivo);
	}
	fclose(ponteiro_arquivo);
	printf("\n++++++++++++++ INGRESSO COMPRADO COM SUCESSO ++++++++++++++\n");
};

// Lista todos os ingressos ja comprados
void listar()
{
	venda v;
	FILE *ponteiro_arquivo;
	
	ponteiro_arquivo = fopen("vendas.txt", "r");
	printf("\n|   %s 	|	 %s	  |	  %s   |   %s	|   %s	|   %s	|\n", "NOME", "CPF", "EMAIL", "EVENTO", "PRECO", "FORMA PAGAMENTO");
	
	// Lê arquivo e printa
	while(fread(&v, sizeof(venda), 1, ponteiro_arquivo))
	{
		printf("\n|  %5s  |  %5s  |  %lld  |  %5s  | R$%.2f  |  %s  |\n",v.nome_comprador, v.email, v.cpf_comprador, v.evento, v.preco_ingresso, v.formaPagamento);
	}
	fclose(ponteiro_arquivo);
};

// Busca comprador(es) pelo código
void buscar_por_cpf()
{
	venda v;
	FILE *ponteiro_arquivo;
	int encontrado = 0;
	long long int cpf=0;
	
	ponteiro_arquivo = fopen("vendas.txt", "r");
	printf("Digite o cpf da compra que deseja buscar: ");
	scanf("%lld", &cpf);
	while(fread(&v, sizeof(venda), 1, ponteiro_arquivo))
	{	
		// Se o código da leitura bate com o input o comprador é printado
		if (v.cpf_comprador == cpf)
		{
			encontrado = 1;
			printf("\n++++++++++++++ INGRESSO ENCONTRADO COM SUCESSO ++++++++++++++\n");
			printf("\n|  %5s  |  %5s  |  %lld  |  %5s  | R$%.2f  |  %s  |\n",v.nome_comprador, v.email, v.cpf_comprador, v.evento, v.preco_ingresso, v.formaPagamento);
		}
	}
	if (encontrado != 1)
	{
		printf("\nCpf nao encontrado\n");
	}
	fclose(ponteiro_arquivo);
};

// Atualiza dados de uma compra usando um arquivo temporário
void atualizar()
{
	venda v;
	FILE *ponteiro_arquivo, *arquivo_temp;
	long long int cpf, encontrado = 0;
	
	// abre o arquivo principal para leitura e o temp para escrita
	ponteiro_arquivo = fopen("vendas.txt", "r");
	arquivo_temp = fopen("temp.txt", "w");
	
	printf("Digite o CPF da comprador que deseja atualizar: ");
	scanf("%lld", &cpf);
	while(fread(&v, sizeof(venda), 1, ponteiro_arquivo))
	{
		if (v.cpf_comprador == cpf)
		{
			encontrado = 1;
			fflush(stdin);
			printf("Digite o novo nome: ");
			scanf("%[^\n]s", v.nome_comprador);
			
			fflush(stdin);
			printf("Digite o novo email: ");
			scanf("%[^\n]s", v.email);
			
			fflush(stdin);
			printf("Digite o novo nome do evento: ");
			scanf("%[^\n]s", v.evento);
			
			printf("Digite novo o preco do ingresso: ");
			scanf("%f", &v.preco_ingresso);
			
			int escolhaPagamento = 0;
			while (escolhaPagamento == 0) {
			printf("Escolha a nova forma de pagamento: \n1)Credito\n2)Boleto\n");
			scanf("%d", &escolhaPagamento);
			if (escolhaPagamento == 1) {
				strcpy(v.formaPagamento, "Credito");
			} else if (escolhaPagamento == 2) {
				strcpy(v.formaPagamento, "Boleto");
			} else {
				printf("Escolha inválida, tente novamente.");
			}
		}
		}
		// escreve novas informações no arquivo temp
		fwrite(&v, sizeof(venda), 1, arquivo_temp);
	}
	fclose(ponteiro_arquivo);
	fclose(arquivo_temp);
	if (encontrado)
	{	
		// agora abre o temp pra leitura e o principal pra escrita, pra transferencia dos novos dados
		arquivo_temp = fopen("temp.txt", "r");
		ponteiro_arquivo = fopen("vendas.txt", "w");
		
		while(fread(&v, sizeof(venda), 1, arquivo_temp))
		{
			fwrite(&v, sizeof(venda), 1, ponteiro_arquivo);
		}
		
		fclose(ponteiro_arquivo);
		fclose(arquivo_temp);
		printf("\n++++++++++++++ INGRESSO ATUALIZADO COM SUCESSO ++++++++++++++\n");
	} else {
		printf("\nCPF nao encontrado...\n");
	}
	
}

void deletar()
{
	venda v;
	FILE *ponteiro_arquivo, *arquivo_temp;
	long long int cpf;
	int encontrado=0;
	
	// Usa a mesma lógica de criar um arquivo temporário
	ponteiro_arquivo = fopen("vendas.txt", "r");
	arquivo_temp = fopen("temp.txt", "w");
	
	printf("Digite o cpf da compra que deseja excluir: ");
	scanf("%lld", &cpf);
	
	// verifica se o código existe e atualiza var encontrado
	while(fread(&v, sizeof(venda), 1, ponteiro_arquivo))
	{
		if (v.cpf_comprador == cpf)
		{
			encontrado = 1;
		}
		else{
			fwrite(&v, sizeof(venda), 1, arquivo_temp);	
		}
		
	}
	
	fclose(ponteiro_arquivo);
	fclose(arquivo_temp);
	
	// se encontrado 
	if (encontrado)
	{
		arquivo_temp = fopen("temp.txt", "r");
		ponteiro_arquivo = fopen("vendas.txt", "w");
		
		// le do temp e escreve no principal
		while(fread(&v, sizeof(venda), 1, arquivo_temp))
		{
			fwrite(&v, sizeof(venda), 1, ponteiro_arquivo);
		}
		
		fclose(ponteiro_arquivo);
		fclose(arquivo_temp);
		printf("\n++++++++++++++ INGRESSO DELETADO COM SUCESSO ++++++++++++++\n");
	} else {
		printf("\nCpf nao encontrado...\n");
	}
	
}

int main()
{
	int opcao;
	do {
		printf("\n*-*-**-*-**-*-**-*-* SISTEMA DE VENDA DE INGRESSOS *-*-**-*-**-*-**-*-*\n");
		printf("\n1.COMPRAR INGRESSO(S)");
		printf("\n2.MOSTRAR INGRESSOS COMPRADOS");
		printf("\n3.BUSCAR POR CPF");
		printf("\n4.ATUALIZAR COMPRA");
		printf("\n5.DELETAR COMPRA");
		printf("\n0.EXIT");
		
		printf("\nEscolha sua opcao: ");
		scanf("%d", &opcao);
		
		switch(opcao){
			case 1:
				comprar();
				break;
			case 2:
				listar();
				break;
			case 3:
				buscar_por_cpf();
				break;
			case 4:
				atualizar();
				break;
			case 5:
				deletar();
				break;
		}
	}while(opcao!=0);
	
	return 0;
}

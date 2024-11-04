#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_PRODUTOS 100
#define NOME_MAX 50
#define MAX_VENDAS 100

typedef struct {
    int id;
    char nome[NOME_MAX];
    float preco;
    int quantidade; 
} Produto;

typedef struct {
    int idProduto;
    float valorPago;
    float troco;
} Venda;

Produto produtos[MAX_PRODUTOS]; 
Venda vendas[MAX_VENDAS]; 
int totalProdutos = 0; 
int totalVendas = 0; 

void limparTela() {
    system("clear || cls"); 
}

void adicionarProduto() {
    if (totalProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido!\n");
        return;
    }

    Produto novoProduto;
    novoProduto.id = totalProdutos + 1; 

    printf("Digite o nome do produto: ");
    scanf(" %[^\n]s", novoProduto.nome); 
    printf("Digite o preco do produto: ");
    scanf("%f", &novoProduto.preco);
    printf("Digite a quantidade em estoque: ");
    scanf("%d", &novoProduto.quantidade);

    produtos[totalProdutos] = novoProduto; 
    totalProdutos++;

    printf("Produto cadastrado com sucesso! ID: %d\n", novoProduto.id);
}

void listarProdutos() {
    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\nLista de Produtos:\n");
    for (int i = 0; i < totalProdutos; i++) {
        printf("ID: %d | Nome: %s | Preco: R$ %.2f | Quantidade: %d\n", 
               produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].quantidade);
    }
}

void venderProduto() {
    int idProduto, quantidade;
    float valorPago, troco;

    printf("Digite o ID do produto que deseja vender: ");
    scanf("%d", &idProduto);

    
    if (idProduto < 1 || idProduto > totalProdutos) {
        printf("Produto nao encontrado!\n");
        return;
    }

    printf("Digite a quantidade a ser vendida: ");
    scanf("%d", &quantidade);

    
    if (produtos[idProduto - 1].quantidade < quantidade) {
        printf("Quantidade em estoque insuficiente! Disponivel: %d\n", produtos[idProduto - 1].quantidade);
        return;
    }

    
    float totalCompra = produtos[idProduto - 1].preco * quantidade;
    printf("Total da compra: R$ %.2f\n", totalCompra);

    
    printf("Digite o valor pago pelo cliente: R$ ");
    scanf("%f", &valorPago);
    
    troco = valorPago - totalCompra;
    if (troco < 0) {
        printf("Valor pago é insuficiente! É necessário R$ %.2f a mais.\n", -troco);
        return;
    }

    printf("Troco a ser devolvido: R$ %.2f\n", troco);
    char confirmar;
    printf("Confirmar a venda? (s/n): ");
    scanf(" %c", &confirmar);

    if (confirmar == 's' || confirmar == 'S') {
        
        produtos[idProduto - 1].quantidade -= quantidade;

        
        Venda novaVenda;
        novaVenda.idProduto = idProduto;
        novaVenda.valorPago = valorPago;
        novaVenda.troco = troco;
        vendas[totalVendas] = novaVenda;
        totalVendas++;

        printf("Venda realizada com sucesso!\n");
    } else {
        printf("Venda cancelada.\n");
    }
}

void listarVendas() {
    if (totalVendas == 0) {
        printf("Nenhuma venda registrada.\n");
        return;
    }

    
    float totalGeral = 0.0;
    for (int i = 0; i < totalVendas; i++) {
        totalGeral += vendas[i].valorPago;
    }

    printf("\nLista de Vendas:\n");
    printf("Total de Vendas: R$ %.2f\n", totalGeral); 

    for (int i = 0; i < totalVendas; i++) {
        printf("Venda %d | ID do Produto: %d | Valor Pago: R$ %.2f | Troco: R$ %.2f\n", 
               i + 1, vendas[i].idProduto, vendas[i].valorPago, vendas[i].troco);
    }
}

int main() {
    
    setlocale(LC_ALL, "pt_BR.UTF-8");

    int opcao;

    do {
        printf("\n===============================\n");
        printf("     Gerenciamento de Estoque   \n");
        printf("===============================\n");
        printf("1. Adicionar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Vender Produto\n");
        printf("4. Listar Vendas\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarProduto();
                break;
            case 2:
                listarProdutos();
                break;
            case 3:
                venderProduto();
                break;
            case 4:
                listarVendas();
                break;
            case 5:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

        
        if (opcao != 5) {
            printf("\nPressione Enter para retornar ao menu...\n");
            getchar(); 
            getchar(); 
            limparTela(); 
        }
    } while (opcao != 5);

    return 0;
}

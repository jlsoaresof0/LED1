#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *arquivo;
    int id;
    char nome[100];
    float salario;
    char continuar;

    // Abre o arquivo em modo de escrita ("w"). 
    // Para não sobrescrever dados antigos em execuções futuras, use "a" (append).
    arquivo = fopen("funcionarios.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir ou criar o arquivo.\n");
        return 1;
    }

    do {
        printf("\n--- Cadastro de Funcionario ---\n");
        
        printf("Digite o ID: ");
        scanf("%d", &id);

        printf("Digite o nome: ");
        // O espaço antes do % lê o buffer e evita pular a leitura do nome
        scanf(" %[^\n]", nome); 

        printf("Digite o salario: ");
        scanf("%f", &salario);

        // Grava as informações formatadas no arquivo de texto
        fprintf(arquivo, "ID: %d | Nome: %s | Salario: %.2f\n", id, nome, salario);

        printf("\nDeseja cadastrar outro funcionario? (S/N): ");
        scanf(" %c", &continuar);

    } while (continuar == 'S' || continuar == 's');

    // Fecha o arquivo para salvar as alterações no disco
    fclose(arquivo);
    
    printf("\nInformacoes salvas com sucesso no arquivo 'funcionarios.txt'.\n");

    return 0;
}
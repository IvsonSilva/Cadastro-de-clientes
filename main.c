#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_USUARIOS 10
#define MAX_CLIENTES 100

typedef struct {
    char username[50];
    char password[50];
} Usuario;

typedef struct {
    char nome[100];
    char responsavel[100];
    char empresa[100];
    char cnpj[20];
    char razaoSocial[100];
    char nomeFantasia[100];
    char telefone[20];
    char endereco[200];
    char email[100];
    char dataAbertura[20];
} Cliente;

bool validarCampos(char *username, char *password) {
    if (strlen(username) == 0 || strlen(password) == 0) {
        return false;
    }

    for (int i = 0; i < strlen(username); i++) {
        if (!isalnum(username[i])) {
            return false;
        }
    }
    for (int i = 0; i < strlen(password); i++) {
        if (!isalnum(password[i])) {
            return false;
        }
    }

    return true;
}

void criptografar(char *str) {
    while (*str) {
        *str = *str + 1;
        str++;
    }
}

void salvarDadosTXT(Cliente cliente) {
    FILE *file = fopen("clientes.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar os dados.\n");
        return;
    }

    fprintf(file, "Nome: %s\n", cliente.nome);
    fprintf(file, "Responsável: %s\n", cliente.responsavel);
    fprintf(file, "Empresa: %s\n", cliente.empresa);
    fprintf(file, "CNPJ: %s\n", cliente.cnpj);
    fprintf(file, "Razão Social: %s\n", cliente.razaoSocial);
    fprintf(file, "Nome Fantasia: %s\n", cliente.nomeFantasia);
    fprintf(file, "Telefone: %s\n", cliente.telefone);
    fprintf(file, "Endereço: %s\n", cliente.endereco);
    fprintf(file, "Email: %s\n", cliente.email);
    fprintf(file, "Data de Abertura: %s\n\n", cliente.dataAbertura);

    fclose(file);
}

void salvarDadosCSV(Cliente cliente) {
    FILE *file = fopen("clientes.csv", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar os dados.\n");
        return;
    }

    fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
            cliente.nome, cliente.responsavel, cliente.empresa, cliente.cnpj, cliente.razaoSocial,
            cliente.nomeFantasia, cliente.telefone, cliente.endereco, cliente.email, cliente.dataAbertura);

    fclose(file);
}

int main() {
    Usuario usuarios[MAX_USUARIOS] = { {"admin", "admin123"} };
    Cliente clientes[MAX_CLIENTES];
    int totalClientes = 0;
    char username[50];
    char password[50];
    bool loginSucesso = false;

    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (!validarCampos(username, password)) {
        printf("Username ou password inválidos. Certifique-se de que os campos não estão vazios e contêm apenas caracteres alfanuméricos.\n");
        return 1;
    }

    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (strcmp(usuarios[i].username, username) == 0 && strcmp(usuarios[i].password, password) == 0) {
            loginSucesso = true;
            break;
        }
    }

    if (loginSucesso) {
        printf("Login bem-sucedido!\n");
        int opcao;
        do {
            printf("\nMenu Inicial\n");
            printf("1. Cadastrar Cliente\n");
            printf("2. Listar Clientes\n");
            printf("3. Salvar Relatório\n");
            printf("4. Sair\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);
            switch (opcao) {
                case 1:
                    if (totalClientes >= MAX_CLIENTES) {
                        printf("Limite de clientes atingido!\n");
                        break;
                    }
                    Cliente novoCliente;
                    printf("Nome: ");
                    scanf(" %[^\n]%*c", novoCliente.nome);
                    printf("Responsável: ");
                    scanf(" %[^\n]%*c", novoCliente.responsavel);
                    printf("Empresa: ");
                    scanf(" %[^\n]%*c", novoCliente.empresa);
                    printf("CNPJ: ");
                    scanf(" %[^\n]%*c", novoCliente.cnpj);
                    printf("Razão Social: ");
                    scanf(" %[^\n]%*c", novoCliente.razaoSocial);
                    printf("Nome Fantasia: ");
                    scanf(" %[^\n]%*c", novoCliente.nomeFantasia);
                    printf("Telefone: ");
                    scanf(" %[^\n]%*c", novoCliente.telefone);
                    printf("Endereço: ");
                    scanf(" %[^\n]%*c", novoCliente.endereco);
                    printf("Email: ");
                    scanf(" %[^\n]%*c", novoCliente.email);
                    printf("Data de Abertura: ");
                    scanf(" %[^\n]%*c", novoCliente.dataAbertura);

                    novoCliente.nome[strcspn(novoCliente.nome, "\n")] = '\0';
                    novoCliente.responsavel[strcspn(novoCliente.responsavel, "\n")] = '\0';
                    novoCliente.empresa[strcspn(novoCliente.empresa, "\n")] = '\0';
                    novoCliente.cnpj[strcspn(novoCliente.cnpj, "\n")] = '\0';
                    novoCliente.razaoSocial[strcspn(novoCliente.razaoSocial, "\n")] = '\0';
                    novoCliente.nomeFantasia[strcspn(novoCliente.nomeFantasia, "\n")] = '\0';
                    novoCliente.telefone[strcspn(novoCliente.telefone, "\n")] = '\0';
                    novoCliente.endereco[strcspn(novoCliente.endereco, "\n")] = '\0';
                    novoCliente.email[strcspn(novoCliente.email, "\n")] = '\0';
                    novoCliente.dataAbertura[strcspn(novoCliente.dataAbertura, "\n")] = '\0';

                    criptografar(novoCliente.cnpj);
                    criptografar(novoCliente.email);
                    clientes[totalClientes++] = novoCliente;

                    printf("Cliente cadastrado com sucesso!\n");
                    break;
                case 2:
                    for (int i = 0; i < totalClientes; i++) {
                        printf("\nCliente %d\n", i + 1);
                        printf("Nome: %s\n", clientes[i].nome);
                        printf("Responsável: %s\n", clientes[i].responsavel);
                        printf("Empresa: %s\n", clientes[i].empresa);
                        printf("CNPJ: %s\n", clientes[i].cnpj);
                        printf("Razão Social: %s\n", clientes[i].razaoSocial);
                        printf("Nome Fantasia: %s\n", clientes[i].nomeFantasia);
                        printf("Telefone: %s\n", clientes[i].telefone);
                        printf("Endereço: %s\n", clientes[i].endereco);
                        printf("Email: %s\n", clientes[i].email);
                        printf("Data de Abertura: %s\n", clientes[i].dataAbertura);
                    }
                    break;
                case 3:
                    printf("Escolha o formato do relatório (1 para TXT, 2 para CSV): ");
                    int formato;
                    scanf("%d", &formato);
                    if (formato == 1) {
                        for (int i = 0; i < totalClientes; i++) {
                            salvarDadosTXT(clientes[i]);
                        }
                        printf("Relatório salvo em TXT.\n");
                    } else if (formato == 2) {
                        for (int i = 0; i < totalClientes; i++) {
                            salvarDadosCSV(clientes[i]);
                        }
                        printf("Relatório salvo em CSV.\n");
                    } else {
                        printf("Formato inválido!\n");
                    }
                    break;
                case 4:
                    printf("Saindo...\n");
                    break;
                default:
                    printf("Opção inválida!\n");
            }
        } while (opcao != 4);
    } else {
        printf("Usuário ou senha incorretos.\n");
    }

    return 0;
}




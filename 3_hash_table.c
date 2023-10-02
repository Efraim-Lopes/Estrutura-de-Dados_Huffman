typedef struct element element;
typedef struct hash_table hash_table;

#define SIZE_ASCII 256

struct element{
    int frequency;
    char bits[SIZE_ASCII];
};

struct hash_table{
    element *table[SIZE_ASCII];
};

// Função para criar uma tabela de hash inicializada com frequências zeradas e bits vazios.
hash_table *create_hash_table(){
    hash_table *new_hash_table = (hash_table*) malloc(sizeof(hash_table));
    int i;
    for(i = 0; i < SIZE_ASCII; i++){
        new_hash_table->table[i] = (element*) malloc(sizeof(element));
        new_hash_table->table[i]->frequency = 0;
    }
    return new_hash_table;
}

// Função para percorrer as arestas da árvore de Huffman e adicionar os caracteres correspondentes na tabela de hash.
void pass_through_edges_and_add_characters(hash_table *ht, node *huffman_tree, unsigned char *bit_string, int index, unsigned char bit) {
    // Atualiza o "bit_string" com o bit atual e adiciona o caractere à tabela de hash quando um nó folha é alcançado.
    int i;
    if(index > -1){
        bit_string[index] = bit;
        if(is_leaf(huffman_tree)){
            bit_string[index + 1] = '\0'; // Termina a string com nulo para indicar o final.
            // Copia o bit_string para o elemento correspondente na tabela de hash.
            strcpy(ht->table[(int)(*(unsigned char*) huffman_tree->item)]->bits, bit_string);
        }
    }

    // Recursivamente percorre as arestas da esquerda para a direita na árvore de Huffman.
    if(huffman_tree->left != NULL){
        pass_through_edges_and_add_characters(ht, huffman_tree->left, bit_string, index + 1, '0');
    }

    if(huffman_tree->right != NULL){
        pass_through_edges_and_add_characters(ht, huffman_tree->right, bit_string, index + 1, '1');
    }
}

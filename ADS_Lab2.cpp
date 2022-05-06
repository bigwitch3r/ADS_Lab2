#include <iostream>

// Структура дерева
typedef struct tree
{
    int key;
    struct tree* left;
    struct tree* right;
    struct tree* parent;
} node;

// Функция инициализации дерева корневым ключом
node* create(node* root, int key)
{
    // Выделение памяти под корень дерева
    node* tmp = (node*)malloc(sizeof(node));

    // Присваивание значения ключу
    tmp->key = key;

    // Присваивание указателю на родителя значения NULL
    tmp->parent = NULL;

    // Присваивание указателю на левое и правое поддерево значения NULL
    tmp->left = tmp->right = NULL;
    root = tmp;

    return root;
}

// Функция добавления узла
node* add(node* root, int key)
{
    node* root2 = root, * root3 = NULL;

    // Выделение памяти под узел дерева
    node* tmp = (node*)malloc(sizeof(node));

    // Присваивание значения ключу
    tmp->key = key;

    // Поиск нужной позиции для вставки
    while (root2 != NULL)
    {
        root3 = root2;
        if (key < root2->key)
            root2 = root2->left;
        else
            root2 = root2->right;
    }

    /* Присваивание указателю на родителя значения указателя root3
    (указатель root3 был найден выше) */
    tmp->parent = root3;

    // Присваивание указателю на левое и правое поддерево значения NULL
    tmp->left = NULL;
    tmp->right = NULL;

    // Вставляем узел в дерево
    if (key < root3->key) root3->left = tmp;
    else root3->right = tmp;
    return root;
}

node* search(node* root, int key)
{
    // Если дерево пусто или ключ корня равен искомому ключу, то возвращается указатель на корень
    if ((root == NULL) || (root->key == key))
        return root;

    // Поиск нужного узла
    if (key < root->key)
        return search(root->left, key);
    else return search(root->right, key);
}

// Минимальный элемент дерева
node* min(node* root)
{
    node* l = root;
    while (l->left != NULL)
        l = l->left;
    return l;
}

// Максимальный элемент дерева
node* max(node* root)
{
    node* r = root;
    while (r->right != NULL)
        r = r->right;
    return r;
}

// Функция поиска элемента, который следует за удаляемым
node* succ(node* root)
{
    node* p = root, * l = NULL;
    // Если есть правое поддерево, то ищем минимальный элемент в этом поддереве
    if (p->right != NULL)
        return min(p->right);

    /* Правое дерево пусто, идем по родителям до тех пор,
    пока не найдем родителя, для которого наше поддерево левое */
    l = p->parent;
    while ((l != NULL) && (p == l->right))
    {
        p = l;
        l = l->parent;
    }
    return l;
}

// Функция удаления узла
node* del(node* root, int key)
{
    // Поиск удаляемого узла по ключу
    node* p = root, * l = NULL, * m = NULL;
    l = search(root, key);
    // 1 случай
    if ((l->left == NULL) && (l->right == NULL))
    {
        m = l->parent;
        if (l == m->right) m->right = NULL;
        else m->left = NULL;
        free(l);
    }
    // 2 случай, 1 вариант - поддерево справа
    if ((l->left == NULL) && (l->right != NULL))
    {
        m = l->parent;
        if (l == m->right) m->right = l->right;
        else m->left = l->right;
        free(l);
    }
    // 2 случай, 2 вариант - поддерево слева
    if ((l->left != NULL) && (l->right == NULL))
    {
        m = l->parent;
        if (l == m->right) m->right = l->left;
        else m->left = l->left;
        free(l);
    }
    // 3 случай
    if ((l->left != NULL) && (l->right != NULL))
    {
        m = succ(l);
        l->key = m->key;
        if (m->right == NULL)
            m->parent->left = NULL;
        else m->parent->left = m->right;
        free(m);
    }
    return root;
}

// Симметричный обход дерева
void inorder(node* root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    if (root->key)
        printf("%d ", root->key);
    inorder(root->right);
}

int main()
{
    srand(time(0));

    int N = 5 + rand() % 96;

    int* key = new int[N];

    for (int i = 0; i < N; i++)
    {
        key[i] = rand() % 256;
    }

    node* root = NULL;

    for (int i = 0; i < N; i++)
    {
        if (i == 0)
        {
            root = create(root, key[i]);
        }
        else
        {
            root = add(root, key[i]);
        }
    }

    inorder(root);

}

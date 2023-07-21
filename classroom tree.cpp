// Function to create a new AVL tree node
AVLNode* newNodeCL(Classroom classroom) 
{
    AVLNode* node = (AVLNode*) malloc(sizeof(AVLNode));
    node->classroom= classroom;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}


int maxCL(int a, int b) 
{
    return (a > b) ? a : b;
}

int getHeightCL(AVLNode* node) 
{
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int getBalanceCL(AVLNode* node) 
{
    if (node == NULL) {
        return 0;
    }
    return getHeightCL(node->left) - getHeightCL(node->right);
}

AVLNode* rotateLeftCL(AVLNode* node) 
{
    AVLNode* newRoot = node->right;
    AVLNode* leftSubtree = newRoot->left;
    newRoot->left = node;
    node->right = leftSubtree;
    node->height = 1 + maxCL(getHeightCL(node->left), getHeightCL(node->right));
    newRoot->height = 1 + maxCL(getHeightCL(newRoot->left), getHeightCL(newRoot->right));
    return newRoot;
}

AVLNode* rotateRightCL(AVLNode* node) 
{
    AVLNode* newRoot = node->left;
    AVLNode* rightSubtree = newRoot->right;
    newRoot->right = node;
    node->left = rightSubtree;
    node->height = 1 + maxCL(getHeightCL(node->left), getHeightCL(node->right));
    newRoot->height = 1 + maxCL(getHeightCL(newRoot->left), getHeightCL(newRoot->right));
    return newRoot;
}

AVLNode* insertCL(AVLNode* node, Classroom classroom) 
{
    if (node == NULL) 
    {
        return newNodeCL(classroom);
    }
    if (classroom.capacity < node->classroom.capacity) 
    {
        node->left = insertCL(node->left, classroom);
    } 
    else if (classroom.capacity > node->classroom.capacity) 
    {
        node->right = insertCL(node->right, classroom);
    } 
    else 
    {
        node->classroom.capacity = classroom.capacity;
        return node;
    }
    
    node->height = 1 + maxCL(getHeightCL(node->left), getHeightCL(node->right));
    
    int balance = getBalanceCL(node);
    
    if (balance > 1 && classroom.capacity < node->left->classroom.capacity) 
    {
        return rotateRightCL(node);
    }
    if (balance < -1 && classroom.capacity > node->right->classroom.capacity) 
    {
    return rotateLeftCL(node);
    }
    if (balance > 1 && classroom.capacity > node->left->classroom.capacity) 
    {
        node->left = rotateLeftCL(node->left);
        return rotateRightCL(node);
    }
    if (balance < -1 && classroom.capacity < node->right->classroom.capacity) 
    {
        node->right = rotateRightCL(node->right);
        return rotateLeftCL(node);
    }

    return node;
}

void printInOrder(AVLNode* node) 
{
    if (node == NULL) 
    {
        return;
    }
    printInOrder(node->left);
    printf("Room %d: capacity %d\n", node->classroom.roomNumber, node->classroom.capacity);
    printInOrder(node->right);
}


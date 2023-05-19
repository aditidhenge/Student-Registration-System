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

// Function to get the height of an AVL tree node
int getHeightCL(AVLNode* node) 
{
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Function to get the balance factor of an AVL tree node
int getBalanceCL(AVLNode* node) 
{
    if (node == NULL) {
        return 0;
    }
    return getHeightCL(node->left) - getHeightCL(node->right);
}

// Function to rotate an AVL tree node to the left
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

// Function to rotate an AVL tree node to the right
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

// Function to insert a new node into an AVL tree
AVLNode* insertCL(AVLNode* node, Classroom classroom) 
{
    // Perform standard BST insertion
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
        // If the classroom already exists, update the capacity
        node->classroom.capacity = classroom.capacity;
        return node;
    }
    
    // Update the height of the current node
    node->height = 1 + maxCL(getHeightCL(node->left), getHeightCL(node->right));
    
    // Get the balance factor of the current node
    int balance = getBalanceCL(node);
    
    // If the node becomes unbalanced, there are four cases
    // Left Left Case
    if (balance > 1 && classroom.capacity < node->left->classroom.capacity) 
    {
        return rotateRightCL(node);
    }
    // Right Right Case
    if (balance < -1 && classroom.capacity > node->right->classroom.capacity) 
    {
    return rotateLeftCL(node);
    }
    // Left Right Case
    if (balance > 1 && classroom.capacity > node->left->classroom.capacity) 
    {
        node->left = rotateLeftCL(node->left);
        return rotateRightCL(node);
    }
    // Right Left Case
    if (balance < -1 && classroom.capacity < node->right->classroom.capacity) 
    {
        node->right = rotateRightCL(node->right);
        return rotateLeftCL(node);
    }

    // Return the updated node
    return node;
}

// Function to print an AVL tree in-order
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


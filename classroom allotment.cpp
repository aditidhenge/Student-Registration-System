//classroom allotment

int arr[10]={0};

void for_same_slot(int n,course* root,AVLNode* node)
{
	if(node)
	{
		for_same_slot(n,root,node->right);
		if(node->classroom.capacity >= root->count && node->classroom.roomNumber != n )
		{
			root->classroom = node->classroom.roomNumber;
            arr[root->slot] = node->classroom.roomNumber;
		}
		for_same_slot(n,root,node->left);
	}
}

AVLNode* allotclass(course* root,AVLNode* node)
{
	AVLNode* t=node;
    if(node)
    {
        allotclass(root,node->left);
        if(node->classroom.capacity >= root->count && arr[root->slot] == 0)
        {
            root->classroom = node->classroom.roomNumber;
            arr[root->slot] = root->id;
            return node;
        }
        else if(arr[root->slot]!=root->id)
        {
        	for_same_slot(arr[root->slot],root,t);
            return node;
        }
        allotclass(root,node->right);
    }
    return node;
}

void inorderc(course* root,AVLNode* node)
{
	if(root != NULL)
	{
		inorderc(root->left,node);
		node=allotclass(root,node);
        //printf("%d\n",root->id);
		inorderc(root->right,node);
	}
}

void printc(course* root)
{
	if(root != NULL)
	{
		printc(root->left);
		printf("%d-%d\n",root->id,root->classroom);
		printc(root->right);
	}
}


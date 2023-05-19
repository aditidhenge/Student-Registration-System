// Creating student tree within courses 
int Sheight(SNode* node) 
{
    if (node == NULL) 
    {
        return 0;
    } 
    else 
    {
        return node->height;
    }
}

int Smax(int a, int b) 
{
    return (a > b) ? a : b;
}

int Sget_balance(SNode* node) 
{
    if (node == NULL) 
    {
        return 0;
    } 
    else 
    {
        return Sheight(node->left) - Sheight(node->right);
    }
}

SNode* rightrotate(SNode* node) 
{
    SNode* left_child = node->left;
    SNode* right_of_left_child = left_child->right;

    left_child->right = node;
    node->left = right_of_left_child;

    node->height = Smax(Sheight(node->left), Sheight(node->right)) + 1;
    left_child->height = Smax(Sheight(left_child->left), Sheight(left_child->right)) + 1;

    return left_child;
}

SNode* leftrotate(SNode* node) 
{
    SNode* right_child = node->right;
    SNode* left_of_right_child = right_child->left;

    right_child->left = node;
    node->right = left_of_right_child;

    node->height = Smax(Sheight(node->left), Sheight(node->right)) + 1;
    right_child->height = Smax(Sheight(right_child->left), Sheight(right_child->right)) + 1;

    return right_child;
}

SNode* newnode(struct course_student student)
{
	SNode* ptr=(SNode*)malloc(sizeof(SNode));
	ptr->student.enrolment_number=student.enrolment_number;
	strcpy(ptr->student.name,student.name);
	ptr->left=NULL;
	ptr->right=NULL;
	ptr->height=1;
	return ptr;
}

SNode* insertstud(SNode* node,struct course_student student)
{
	 	if (node == NULL) 
        {
            node = newnode(student);
        } 
        else if (student.enrolment_number < node->student.enrolment_number) 
        {
            node->left = insertstud(node->left, student);
        } 
        else if (student.enrolment_number > node->student.enrolment_number) 
        {
            node->right = insertstud(node->right, student);
        } 
    
        node->height = Smax(Sheight(node->left), Sheight(node->right)) + 1;
        int balance = Sget_balance(node);
        if (balance > 1 && student.enrolment_number < node->left->student.enrolment_number) 
        {
            return rightrotate(node);
        }
        if (balance < -1 && student.enrolment_number > node->right->student.enrolment_number) 
        {
            return leftrotate(node);
        }
        if (balance > 1 && student.enrolment_number > node->left->student.enrolment_number) 
        {
            node->left = leftrotate(node->left);
            return rightrotate(node);
        }
        if (balance < -1 && student.enrolment_number < node->right->student.enrolment_number) 
        {
            node->right = leftrotate(node->right);
            return rightrotate(node);
        }
    
    return node;
}

void studinc(course* root,Student student)
{
	int i;
	course* c;
	for(i=0;i<5;i++)
	{
		c=searchcourse(student.courses[i],root);
		struct course_student s;
    	s.enrolment_number=student.enrolment_number;
		strcpy(s.name,student.name);
		c->sroot=insertstud(c->sroot,s);
		c->count++;
	}
}

SNode* deletesnode(SNode* snode, int enrolment_number)
{
    // Base case: node is NULL or the node to be deleted is found
    if (snode == NULL) 
    {
        return snode;
    } 
    else if (enrolment_number < snode->student.enrolment_number) 
    {
        // The node to be deleted is in the left subtree
        snode->left = deletesnode(snode->left, enrolment_number);
    } 
    else if (enrolment_number > snode->student.enrolment_number) 
    {
        // The node to be deleted is in the right subtree
        snode->right = deletesnode(snode->right, enrolment_number);
    } 
    else 
    {
        // Node to be deleted is found
        // If the node has only one child or no child
        if (snode->left == NULL || snode->right == NULL) 
        {
            SNode* temp = snode->left ? snode->left : snode->right;

            // If the node has no child
            if (temp == NULL) 
            {
                temp = snode;
                snode = NULL;
            } 
            else 
            { // If the node has one child
                *snode = *temp; // Copy the contents of the child to the node to be deleted
            }

            free(temp); // Free memory
        } 
        else 
        { // If the node has two children
            // Find the node with the minimum value in the right subtree
            SNode* temp = snode->right;
            while (temp->left != NULL) 
            {
                temp = temp->left;
            }

            // Replace the node to be deleted with the minimum node
            snode->student = temp->student;

            // Delete the minimum node
            snode->right = deletesnode(snode->right, temp->student.enrolment_number);
        }
    }

    // If the tree had only one node and it is deleted, return NULL
    if (snode == NULL) 
    {
        return snode;
    }
    // Update the height of the current node
    snode->height = 1 + Smax(Sheight(snode->left), Sheight(snode->right));

    int balance = Sget_balance(snode);

    if (balance > 1 && Sget_balance(snode->left) >= 0) 
    {
        return rightrotate(snode);
    } 
    else if (balance > 1 && Sget_balance(snode->left) < 0) 
    {
        snode->left = leftrotate(snode->left);
        return rightrotate(snode);
    } 
    else if (balance < -1 && Sget_balance(snode->right) <= 0) 
    {
        return leftrotate(snode);
    } 
    else if (balance < -1 && Sget_balance(snode->right) > 0) 
    {
        snode->right = rightrotate(snode->right);
        return leftrotate(snode);
    }
    return snode;
}



void delete_from_course(course* root,Student s)
{
    	course* c;
    	int i;
    	for(i=0;i<5;i++)
    	{
    		c=searchcourse(s.courses[i],root);
    		printf("%d\n",c->id);
    		c->sroot=deletesnode(c->sroot,s.enrolment_number);
		}
    	
}

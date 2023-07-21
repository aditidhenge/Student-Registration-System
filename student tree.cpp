// creating student tree for student database
int height(Node* node) 
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

int max(int a, int b) 
{
    return (a > b) ? a : b;
}

int get_balance(Node* node) 
{
    if (node == NULL) 
    {
        return 0;
    } 
    else 
    {
        return height(node->left) - height(node->right);
    }
}

Node* create_node(Student student) 
{
    Node* node = (Node*) malloc(sizeof(Node));
    node->student = student;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* right_rotate(Node* node) 
{
    Node* left_child = node->left;
    Node* right_of_left_child = left_child->right;

    left_child->right = node;
    node->left = right_of_left_child;

    node->height = max(height(node->left), height(node->right)) + 1;
    left_child->height = max(height(left_child->left), height(left_child->right)) + 1;

    return left_child;
}

Node* left_rotate(Node* node) 
{
    Node* right_child = node->right;
    Node* left_of_right_child = right_child->left;

    right_child->left = node;
    node->right = left_of_right_child;

    node->height = max(height(node->left), height(node->right)) + 1;
    right_child->height = max(height(right_child->left), height(right_child->right)) + 1;

    return right_child;
}

Node* insert(Node* node, Student student,course* root) 
{
    int flag=1,i,j;
    int ar[10]={0};
    course* c;
    // Check if the student is trying to take 2 courses in the same slot
    for (i = 0; i < 5 && flag==1; i++) 
    {
        c=searchcourse(student.courses[i],root);
        ar[c->slot]=1+ar[c->slot];
        if(ar[c->slot]>1)
        {
        	printf("%d : Cannot take two courses of same slot.\n",student.enrolment_number);
        	flag=0;
		}
        
    }
    if(flag==1)
    {
    	
        if (node == NULL) 
        {
            node = create_node(student);
            studinc(root,student);
        } 
        else if (student.enrolment_number < node->student.enrolment_number) 
        {
            node->left = insert(node->left, student,root);
        } 
        else if (student.enrolment_number > node->student.enrolment_number) 
        {
            node->right = insert(node->right, student,root);
        } 
        else 
        {
            printf("Student already prsent!");
            return node;
        }
        node->height = max(height(node->left), height(node->right)) + 1;
        int balance = get_balance(node);
        if (balance > 1 && student.enrolment_number < node->left->student.enrolment_number) 
        {
            return right_rotate(node);
        }
        if (balance < -1 && student.enrolment_number > node->right->student.enrolment_number) 
        {
            return left_rotate(node);
        }
        if (balance > 1 && student.enrolment_number > node->left->student.enrolment_number) 
        {
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }
        if (balance < -1 && student.enrolment_number < node->right->student.enrolment_number) 
        {
            node->right = left_rotate(node->right);
            return right_rotate(node);
        }
    }
    return node;
}

Student searchstudent(Node* node,int enrol)
{
	if(node!=NULL)
	{
		if(node->student.enrolment_number==enrol)
		{
			return node->student;
		}
		else if(node->student.enrolment_number < enrol)
		{
			return searchstudent(node->right,enrol);
		}
		else
		{
			return searchstudent(node->left,enrol);
		}
	}
}


Node* deletenode(Node* node, int enrolment_number,course* root)
{
     Student s=searchstudent(node,enrolment_number);
     delete_from_course(root,s);
    if (node == NULL) 
    {
        return node;
    } 
    else if (enrolment_number < node->student.enrolment_number) 
    {
        node->left = deletenode(node->left, enrolment_number,root);
    } 
    else if (enrolment_number > node->student.enrolment_number) 
    {
        node->right = deletenode(node->right, enrolment_number,root);
    } 
    else 
    {
        if (node->left == NULL || node->right == NULL) 
        {
            Node* temp = node->left ? node->left : node->right;
            // If the node has no child
            if (temp == NULL) 
            {
                temp = node;
                node = NULL;
            } 
            else 
            {
                *node = *temp; 
            }

            free(temp);
            
        } 
        else 
        { 
            Node* temp = node->right;
            while (temp->left != NULL) 
            {
                temp = temp->left;
            }

            node->student = temp->student;

            node->right = deletenode(node->right, temp->student.enrolment_number,root);
        }
    }

    if (node == NULL) 
    {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = get_balance(node);

    if (balance > 1 && get_balance(node->left) >= 0) 
    {
        return right_rotate(node);
    } 
    else if (balance > 1 && get_balance(node->left) < 0) 
    {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    } 
    else if (balance < -1 && get_balance(node->right) <= 0) 
    {
        return left_rotate(node);
    } 
    else if (balance < -1 && get_balance(node->right) > 0) 
    {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    return node;
}


void print_student(Student student) 
{
    printf("Enrolment Number: %d\n", student.enrolment_number);
    printf("Name: %s\n", student.name);
    printf("Courses:\n");
    int i;
    for (i = 0; i < 5; i++) 
    {
        printf("%d\n", student.courses[i]);
    }
}

void inorder_traversal(Node* node) 
{
    if (node != NULL) 
    {
        inorder_traversal(node->left);
        print_student(node->student);
        inorder_traversal(node->right);
    }
}

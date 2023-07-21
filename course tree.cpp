//Creating course tree for course database

int heightC(course *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int maxC(int a, int b) {
    return (a > b) ? a : b;
}

course* newNode(int id, char name[],int slot) {
    course *node = (course*) malloc(sizeof(course));
    node->id = id;
    strcpy(node->name, name);
    node->sroot=NULL;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    node->count=0;
    node->slot=slot;
    return node;
}

course* rightRotate(course *y) {
    course *x = y->left;
    course *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = maxC(heightC(y->left), heightC(y->right)) + 1;
    x->height = maxC(heightC(x->left), heightC(x->right)) + 1;

    return x;
}

course* leftRotate(course *x) {
    course *y = x->right;
    course *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = maxC(heightC(x->left), heightC(x->right)) + 1;
    y->height = maxC(heightC(y->left), heightC(y->right)) + 1;

    return y;
}

int getBalanceC(course *node) {
    if (node == NULL) {
        return 0;
    }
    return heightC(node->left) - heightC(node->right);
}

course* insertCourse(course *node, course Course) {
    if (node == NULL) 
    {
        return newNode(Course.id, Course.name,Course.slot);
    }

    if (Course.id <= node->id) 
    {
        node->left = insertCourse(node->left, Course);
    } 
    else if (Course.id > node->id) 
    {
        node->right = insertCourse(node->right, Course);
    } 
    else
    {
    	printf("Course already present\n");
    	return node;
    }
    node->height = 1 + maxC(heightC(node->left), heightC(node->right));

    int balance = getBalanceC(node);

    if (balance > 1 && Course.id < node->left->id) {
        return rightRotate(node);
    }

    if (balance < -1 && Course.id > node->right->id) {
        return leftRotate(node);
    }

    if (balance > 1 && Course.id > node->left->id) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && Course.id < node->right->id) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

course* deleteCourse(course* node, int courseid)
{
    if (node == NULL) 
    {
        return node;
    } 
    else if (courseid < node->id) 
    {
        node->left = deleteCourse(node->left, courseid);
    } 
    else if (courseid > node->id) 
    {
        node->right = deleteCourse(node->right, courseid);
    } 
    else 
    {
        if(node->count == 0)
        {
            if (node->left == NULL || node->right == NULL) 
            {
                course* temp = node->left ? node->left : node->right;

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
                course* temp = node->right;
                while (temp->left != NULL) 
                {
                    temp = temp->left;
                }

                node->id = temp->id;

                node->right = deleteCourse(node->right, temp->id);
            }
        }
        else
        {
            printf("Cannot delete\n");
        }
    }

    if (node == NULL) 
    {
        return node;
    }

    node->height = 1 + maxC(heightC(node->left), heightC(node->right));

    int balance = getBalanceC(node);

    if (balance > 1 && getBalanceC(node->left) >= 0) 
    {
        return rightRotate(node);
    } 
    else if (balance > 1 && getBalanceC(node->left) < 0) 
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    } 
    else if (balance < -1 && getBalanceC(node->right) <= 0) 
    {
        return leftRotate(node);
    } 
    else if (balance < -1 && getBalanceC(node->right) > 0) 
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

course* searchcourse(int n,course* c)
{
	if(c!=NULL)
	{
		if(c->id==n)
		{
			return c;
		}
		else if(c->id < n)
		{
			return searchcourse(n,c->right);
		}
		else
		{
			return searchcourse(n,c->left);
		}
	}
}

void printstudent(SNode* s)
{
	if(s!=NULL)
	{
		printstudent(s->left);
		printf("%s-%d\n",s->student.name,s->student.enrolment_number);
		printstudent(s->right);
	}
}
void print_courses(course* root) 
{
    if (root != NULL) 
    {
        print_courses(root->left);
        printf("\nCourse ID: %d\n", root->id);
        printf("Course Name: %s\n", root->name);
        printf("Slots %d\n",root->slot);
        printf("Students Enrolled: ");
       	printstudent(root->sroot);
        print_courses(root->right);
        
    }
}

course* insertCap(course *node, course Course) {
    if (node == NULL) 
    {
        return newNode(Course.id, Course.name,Course.slot);
    }

    if (Course.count <= node->count) 
    {
        node->left = insertCap(node->left, Course);
    } 
    else if (Course.count > node->count) 
    {
        node->right = insertCourse(node->right, Course);
    } 
    else
    {
    	printf("Course already present\n");
    	return node;
    }
    node->height = 1 + maxC(heightC(node->left), heightC(node->right));

    int balance = getBalanceC(node);

    if (balance > 1 && Course.count < node->left->count) {
        return rightRotate(node);
    }

    if (balance < -1 && Course.count > node->right->count) {
        return leftRotate(node);
    }

    if (balance > 1 && Course.count > node->left->count) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && Course.count < node->right->count) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

//range search

void RangeSearch(course* rootC,int id1,int id2)
{
    if(rootC)
    {
        RangeSearch(rootC->left,id1,id2);
        if(rootC->id > id1 && rootC->id < id2)
        {
            printf("%s %d \n",rootC->name,rootC->id);
        }
        RangeSearch(rootC->right,id1,id2);
    }
}

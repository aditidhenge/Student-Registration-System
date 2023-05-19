////seat allotment

int k=0,q=0,r=0;
int a[10]={0};
void printstudentseat(SNode* s)
{
	if(s!=NULL)
	{
		printstudentseat(s->left);
		printf("%s-%d is in classroom %d on bench %d and in row %d\n",s->student.name,s->student.enrolment_number,
		s->student.classroom,s->student.benchno,s->student.rowno);
		printstudentseat(s->right);
	}
}
void printseats(course* c)
{
	if(c!=NULL)
	{
		printseats(c->left);
		printf("For course %s-%d\n",c->name,c->id);
		printstudentseat(c->sroot);
		printseats(c->right);
	}
}



int array[5]={0};

void arrclass(AVLNode* cl)
{
	if(cl!=NULL)
	{
		arrclass(cl->left);
		array[cl->classroom.roomNumber-1]=cl->classroom.capacity/3;
		arrclass(cl->right);
	}
}


void traversestudent(SNode* s,AVLNode* cl,int slot)
{
	if(s!=NULL)
	{
		traversestudent(s->left,cl,slot);
		if(k<= array[q] && a[slot]==0)
		{
			s->student.benchno=k;
			k++;
			s->student.rowno=r;
			s->student.classroom=q+1;
		}
		else if(k > array[q] && a[slot]==0)
		{
			k=1;
			q++;
			s->student.benchno=k;
			k++;
			s->student.rowno=r;
			s->student.classroom=q+1;
		}
		else if(k<= array[q] && a[slot]!=0)
		{
			s->student.benchno=k;
			k++;
			s->student.rowno=r+1;
			s->student.classroom=q+1;
		}
		else
		{
			k=1;
			q++;
			s->student.benchno=k;
			k++;
			s->student.rowno=r+1;
			s->student.classroom=q+1;
		}
		traversestudent(s->right,cl,slot);
	}
	
}


void coursetraverse(course* root,AVLNode* cl) 
{
    if (root != NULL) 
    {
        coursetraverse(root->left,cl);
        k=1;
        r=1;
        q=0;
        traversestudent(root->sroot,cl,root->slot);
        a[root->slot]++;
        coursetraverse(root->right,cl);
    }
}


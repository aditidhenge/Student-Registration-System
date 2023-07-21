#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tree structure.cpp"
#include "course tree.cpp"
#include "student in course.cpp"
#include "student tree.cpp"
#include "classroom tree.cpp"
#include "classroom allotment.cpp"
#include "seat allotment.cpp"
int main() 
{
    int j,control_line;
    int i=0,id,slot;
    char data;
    course* rootC=NULL,*rootcap=NULL;
    char name[50];
    control_line=1;
    FILE *fptrc;
    fptrc=fopen("course.txt","r");
    if(fptrc==NULL)
        printf("Error");
    while(i<7)
    {
        fscanf(fptrc,"%d %s %d",&id,name,&slot);
        course c;
        c.id=id;
        strcpy(c.name,name);
        c.slot=slot;
        rootC=insertCourse(rootC,c);
    	rootcap=insertCap(rootcap,c);
        i++;
    }
    printf("\n=========== Courses ==============\n");
    print_courses(rootC);
    
    printf("\n==================================\n");

    Node *root=NULL;
    int enrolment;
    int courseid[5];
    int courseslot[5];
    char sname[50],cname[50];
    FILE *fptrs;
    fptrs=fopen("student_file.txt","r");
    i=0;
    while(i<5)
    {
        fscanf(fptrs,"%d %s",&enrolment,sname);
        for(int j=0 ; j<5 ; j++)
        {
            fscanf(fptrs,"%d",&courseid[j]);
        }
        Student s;
        s.enrolment_number=enrolment;
        strcpy(s.name,sname);
        for(int j=0; j<5 ; j++)
        {
            s.courses[j]=courseid[j];
        }
        root=insert(root,s,rootC);
        i++;
    }
    printf("\n=========== Students ==============\n");
    inorder_traversal(root);
    printf("\n===================================\n");
    print_courses(rootC);
	AVLNode *rootCL=NULL;
    int room_number,capacity_room;
    FILE *fptrcl;
    fptrcl=fopen("classroom_file.txt","r");
    i=0;
    while(i<5)
    {
        fscanf(fptrcl,"%d %d",&room_number,&capacity_room);
        Classroom cl;
        cl.roomNumber=room_number;
        cl.capacity=capacity_room;
      
        rootCL=insertCL(rootCL,cl);
        i++;
    }
    printf("\n=========== Classrooms ==============\n");
    printInOrder(rootCL);

    while(control_line!=0)
    {
        printf("\n____________________\n");
	printf("0 -- exit\n");
        printf("1 -- add student to student list\n");
        printf("2 -- delete a student from student list\n");
        printf("3 -- add course to course list\n");
        printf("4 -- delete a course\n");
        printf("5 -- allotment of classrooms for lectures\n");
        printf("6 -- allotment of classrooms for exams\n");
        printf("7 -- print the list fo students\n");
        printf("8 -- print the list of courses and students enrolled\n");
        printf("9 -- print list of courses which have course-ids between course-id-1 and course-id-2");

        printf("\nEnter the number beside the function you want to execute : ");
	scanf("%d",&control_line);

        switch (control_line)
	{
		case 0: //Exit
		{
			printf("User Interface exited");
			break;
		}
		case 1:
		{
	                int enrolment_num,c;
	                char name_student[50];
	                printf("Enter the enrolment number ");
	                scanf("%d",&enrolment_num);
	                printf("Enter the name of the student ");
	                scanf("%s",name_student);
	                for(int i=0 ; i<5 ; i++)
	                {
	                    printf("Enter the course ids");
	                    scanf("%d ",&c);
	                }
	                Student s1;
	                s1.enrolment_number=enrolment_num;
	                strcpy(s1.name,name_student);
	                for(int i=0 ; i<5 ; i++)
	                {
	                    s1.courses[i]=c;
	                }
	                root=insert(root,s1,rootC);
	                inorder_traversal(root);
	                break;
            	}
	        case 2:
	    	{
			int enrolment_num;
			printf("Enter the enrolment number of the student you want to delete ");
			scanf("%d",&enrolment_num);
			root = deletenode(root,enrolment_num,rootC);
			printf("Deleted successfully\n");
			break;
	    	}
            	case 3:
            	{
               		course c;
	                printf("Enter course id ");
	                scanf("%d",&c.id);
	                printf("Enter course name ");
	                scanf("%s",c.name);
	                printf("Enter slot ");
	                scanf("%d",&c.slot);
	                rootC=insertCourse(rootC,c);
	                break;
            	}
            	case 4:
	    	{
			int cID;
			printf("Enter course id to delete ");
			scanf("%d",&cID);
			rootC=deleteCourse(rootC,cID);
			break;
	    	}
            	case 5:
            	{
	                inorderc(rootC,rootCL);
	                printc(rootC);
	                break;
            	}
            	case 6:
            	{
	            	coursetraverse(rootC,rootCL);
	            	printseats(rootC);
	            	break;
		}	
            	case 7:
            	{
	                inorder_traversal(root);
	                break;
            	}
            	case 8:
            	{
	                print_courses(rootC);
	                break;
            	}
            	case 9:
            	{
	                int courseid1,courseid2;
	                printf("Enter course id's ");
	                scanf("%d %d",&courseid1,&courseid2);
	                RangeSearch(rootC,courseid1,courseid2);
            	}
            	default:
		{
			printf("Loop exited");
			control_line=0;
			break;
		}
        }
    }
    return 0;
}

// All the structures required in the project

//for course database
typedef struct course{
    int id;
    char name[50];
    int slot;
    struct stunode* sroot; //root of the bst of students enrolled in this course
    struct course *left;
    struct course *right;
    int height; //height of the AVL Tree
    int count;  //number of students enrolled in this course
    int classroom; //classroom number where the course is held
}course;


struct course_student{
	int benchno;  //bench number in the classroom
	int rowno;    //row number in the classroom
	int classroom; 
	int enrolment_number;
	char name[50];    
};

//structure to represent students in a specific course
typedef struct stunode {
    struct course_student student;
    int height;
    struct stunode* left;
    struct stunode* right;
}SNode;

//for student database
typedef struct student {
    int enrolment_number;
    char name[50];
    int courses[5];  //to store course ids of the courses the student is enrolled in
}Student;

typedef struct node {
    Student student;
    int height;
    struct node* left;
    struct node* right;
}Node;

//for classroom database
typedef struct Classroom 
{
    int roomNumber;
    int capacity; //maximum capacity of classroom
}Classroom;

typedef struct AVLNode 
{
    Classroom classroom;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
}AVLNode;

// All the structures required in the project

//for course database
typedef struct course{
    int id;
    char name[50];
    int slot;
  	struct stunode* sroot;
    struct course *left;
    struct course *right;
    int height;
    int count;
    int classroom; 
}course;

//for student in course database
struct course_student{
	int benchno;
	int rowno;
	int classroom;
	int enrolment_number;
    char name[50];    
};

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
    int courses[5];
} Student;

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
    int capacity;
} Classroom;

typedef struct AVLNode 
{
    Classroom classroom;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

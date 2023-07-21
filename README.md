# Student-Registration-System

## Problem Statement : 
You need to develop a system for registration, allotment of classrooms for lectures as well as
examination allotment for students. Maintain one database for students’ data. Every student
has registered for five courses. Maintain information such as name of student, enrolment
number, courses taken etc. Every course will also have its record of students taking that
course, slot assigned to that course, maintained separately. Multiple courses (across semesters
and also for the same semester) can be assigned to the same slot.
Maintain another database of classrooms. For every room, maintain the number of seats in
that room. Also assume that there are 4 rows in each room and each bench can provide seats
for 3 students. The number of benches per row would depend on the class capacity.

**Several structures required for the project that involves managing course, student, and classroom databases are created first.**

**1. Adding a student to the student-database. When adding a student to the student-
database, verify that a student cannot take 2 courses in the same slot.**
* Before adding student data course slots are checked using and extra hash array, if the slot frequency is greater than 1 for a particular student it means there are two courses of same slot and thus student cannot be added
* Else BST insertion is performed and at the same time the student data is also added in the course database and the tree is balanced by performing necessary rotations.

**2. Deletion of a student from the student-database. When deleting a student, ensure that
the student record is also deleted from the courses taken by that student.**
* The student record is deleted from the student database as well as the course database based on the provided enrollment number.
* Standard BST deletion is performed taking care of three cases node will no child, one child and two child.

**3. Adding a course to the course database. When deleting a course, ensure that no
student has taken that course.**
* The count variable stores the number of students enrolled in the course and if count is zero only then course deletion is performed.
* The courses in the course database are inserted according to the count i.e. the number of students enrolled in that course.

**4. Allotment of classrooms for lectures. Allot every course to a classroom such that the
capacity of the room is larger than the number of students registered for the course.
Allot the classrooms in the most optimal way such that minimum number of
classrooms are utilised. Two courses in the same slot to get different rooms. Also as
much as possible the same room is to be used for consecutive slots for students of the
same class/semester. If it is not possible, then different rooms can be utilised. Detect
the situation if a room cannot be allocated to some course in a particular slot. In such
case make sure that least number of courses are not allocated the rooms and these
courses together have as less number of students as possible.**
* Recursively traverses the BST of course using inorder traversal and firstly checks if the particular slot is allotted a classroom or not which is done using an extra array and if that slot is already allotted a class then a helper function is called which makes sure to allot another classroom for it other than the one alloted already because same slots cannot be assigned same classrooms.

**5. Allotment of classrooms for exams. Seats in the classroom can be numbered based on
row-number, bench-number etc. When assigning seats in the examination hall, ensure
that no students of the same course can be assigned adjacent seats.**
* Firstly an array is declared to store the number of benches present in every classroom.
* BST that contains students enrolled in courses is traversed recursively and students are assigned bench number and row number based on the number of benches and rows present in the classroom.

**6. Print the list of students and the exam seat allotted to each student for a given slot.**

**7. Range-search – Search and print list of courses which have course-ids between
course-id-1 and course-id-2.**
* It performs range search on the course database BST to find and print courses whose ID's lie between id1 and id2.
* It performs an inorder traversal on the BST and prints the details of the courses whose id's are in range.

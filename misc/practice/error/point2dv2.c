// question : define a struct point with two fields - x and y each integers. Then write a function make point, which returns a point after heap allocating it and sets its fields, returning the pointer. In the main, call the make_point to create two points. print both the values of it. Finally free them after the main program ends. But this one comes with experiments.
// file : point2dv2.c 
// date : 05/05/2026 
// day  : tuesday


// initialise the header files
#include <stdio.h> 
// for printf 
#include <stdlib.h> 
// for malloc and free 


//============================ define the structs and datas =============================

// Point : has x, y - the values, we shall typedef it now. 

typedef struct Point {
  int x;
  int y;
} Point;

//============================ declare function prototypes===============================

Point *make_point(int x, int y);
// this function takes two integers : x and y and returns a pointer to Point; ie returns a Point * type. this is currently the only function.

//=========================== define the main function ==================================

int main(void) {
  // create two points in two different ways. 
  // way one : just do int during initialisation of the variable.
  Point point1 = { 100, 200 };

  // way two : initialise then assign.
  Point point2;
  // here is the time window between an uninitialised struct and the assignment of values.
  // now here we go assigning the values. 
  // test case : 1 ; print now;
  printf("init x :%d; init y: %d\n", point1.x, point1.y);  
  printf("uninit x :%d; uninit y: %d\n", point2.x, point2.y);
  
  // assigned 
  point2.x = 300;
  point2.y = 400;

  // but hey, it is - on stack. The next point is on the heap?

  Point *point3;
  point3 = make_point(500, 600);
  printf("init x :%d; init y: %d\n", point2.x, point2.y);  
  printf("init x :%d; init y: %d\n", point3->x, point3->y);

  // now free it. free the pointer.
  free(point3);

  // now try to access the point 3.
  printf("init x: %d; init y: %d\n", point3->x, point3->y);

  // now try the double free.
  free(point3);
  


}

//=========================== function definitions ======================================

Point *make_point(int x, int y) {
  
  // writing the first malloc code; 
  Point *point = (Point *)malloc(sizeof(Point));
  if (point == NULL) {
    printf("Warning: the point is NULL; no space allocated.\n");
    return NULL;
  }
  // the above if block is a mandatory NULL gaurd; this prevents us from using the unassigned space, directing it to a NULL pointer. 
  
  // hey, create a type Point * - a pointer to Point datatype which exists in the heap memory. get the size of the Point datatype using the sizeof() function. Though we know that int + int in x64 is 4 + 4 = 8 bytes, we do not assign it manually because architectures can change code MAY produce unpredictable behaviour. yet- sizeof is always safe to use. Now assign the amount of bytes in heap via malloc. Each train as I said has compartments and this returns a pointer to the engine (refer the doubt section if you don't understand what I am saying). Yet it is not necessary for us to cast the void * (which is as returned by the malloc) to Point * , but it is done explicitly for clarity - c23; but in older C standards, it is mandatory for us to cast. 
  // assign the data to the pointer and return the pointer. 

  point->x = x;
  point->y = y;

  // these both are same as (*point).x = x and (*point).y = y respectively. the -> is just a good syntax notation.

  // return : the pointer to the point in the heap.
  return point;
}

//=======================================================================================

// compiler run result : 

// init x :100; init y: 200 - fine here
// uninit x :0; uninit y: 0 - Undefined Behaviour; here it is uninitialised value accessed; the kernel zeros the pages before providing them to any program, so the results are almost always zero : (in my machine) - yet it is completely predictable in by machine that it will always be zero.
// init x :300; init y: 400 - fine here
// init x :500; init y: 600 - fine here
// init x: 1477482336; init y: 5 - Undefined Behaviour; here it is accessed after freeing the point3; yet freeing does not mean zeroing the page, it just clears the exising memory with random data. So, when we call upon a freed space, it results in garbage dump, accessed via a dangling pointer.
// free(): double free detected in tcache 2 - Double Free errored; 
// fish: Job 1, './point2dv2' terminated by signal SIGABRT (Abort); the kernel sends a SIGABRT to the shell running the C program - ie the fish shell catches the SIGABRT and aborts the program from continue running. 


//======================================= Doubts remain, see them in the doubts section.


#ifndef TAD_H
#define TAD_H

typedef struct person Person;
typedef struct people People;

People *createPeople();
void freePeople(People **p);
void addPerson(People *p, int numChildren, float salary, int i);
float calculateAvgSalary(People *p);
float calculateAvgChildren(People *p);

#endif

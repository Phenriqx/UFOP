#include <stdio.h>
#include <stdlib.h>

#include "tad.h"

struct person {
    float salario;
    int filhos;
};

struct people {
    Person *people;
    int size;
    int capacity;
};

People *createPeople() {
    People *people = (People *) malloc(sizeof(People));
    if (!people)
        return NULL;

    people->capacity = 10;

    people->people = (Person *) malloc(people->capacity * sizeof(Person));
    if (!people->people) {
        free(people);
        return NULL;
    }

    people->size = 0;
    return people;
}

void freePeople(People **p) {
    free((*p)->people);
    (*p)->people = NULL;

    free((*p));
    *p = NULL;
}

void addPerson(People *p, int numChildren, float salary, int i) {
    if (p->size >= p->capacity) {
        p->capacity *= 2;
        Person *temp = (Person *) realloc(p->people, p->capacity * sizeof(Person));
        if (!temp)
            return;

        p->people = temp;
    }

    p->people[i].salario = salary;
    p->people[i].filhos = numChildren;

    p->size++;
}

float calculateAvgSalary(People *p) {
    float avgSalary = 0;
    for (int i = 0; i < p->size; i++) {
        avgSalary += p->people[i].salario;
    }        

    avgSalary /= p->size;
    
    return avgSalary;
}

float calculateAvgChildren(People *p) {
    float avgChildren = 0;
    for (int i = 0; i < p->size; i++) {
        avgChildren += p->people[i].filhos;
    }

    avgChildren /= p->size;

    return avgChildren;
}

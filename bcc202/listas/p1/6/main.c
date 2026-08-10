#include <stdio.h>

#include "tad.h"

int main() {
    int numChildren, i = 0;
    float salary;

    People *p = createPeople();
    
    do {
        
        printf("Insira seu salário: ");
        scanf("%f", &salary);

        printf("Insira a quantidade de filhos que você tem: ");
        scanf("%d", &numChildren);

        addPerson(p, numChildren, salary, i);
        i++;

    } while (salary > 0);

    float avgSalary = calculateAvgSalary(p);
    printf("Média de salário: %.2f\n", avgSalary);

    printf("Média de filhos: %.2f\n", calculateAvgChildren(p));

    freePeople(&p);
    return 0;
}

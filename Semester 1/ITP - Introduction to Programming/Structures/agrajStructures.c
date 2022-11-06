//instructions to preprocessor
#include <stdio.h>
#include <string.h>
//structure definition
struct engine
{
    char material[10];//stores material type
    int date, month, year;//store date in three integer variables
    int weight;//stores weight of component
    char serial_num[4];//stores serial number of component
};
//function declarations
int weight_count(struct engine *e);
int year_count(struct engine *e);
int details(struct engine *e);
int max_date(int m, int y);

//beginning of main method
int main(void){
    int n;
    printf("Enter number of engine parts: ");
    //asking for number of parts('n')
    scanf("%d", &n);
    //declaring array of engines of size 'n'
    struct engine en[n];
    for(int i = 0; i < n; i++){
        int check = 0;//used to check for incorrect input
        printf("Enter serial number of part %d: ", i + 1);
        scanf("%s", en[i].serial_num);//input for serial number
        printf("Enter date of manufacture(dd-mm-yy) of part %d: ", i + 1);
        scanf("%d-%d-%d", &en[i].date, &en[i].month, &en[i].year);//input for date in the form of integers separated by hyphens
        printf("Enter material of part %d: ", i + 1);
        scanf("%s", en[i].material);//input for material type
        printf("Enter weight of part %d: ", i + 1);
        scanf("%d", &en[i].weight);//input for weight of engine
        //condition to check for valid weight
        if(en[i].weight > 10 || en[i].weight < 1){
            check = 1;
        }
        //condtion for month
        else if(en[i].month < 1 || en[i].month > 12){
            check = 1;
        }
        //condition for year
        else if(en[i].year < 0){
            check = 1;
        }
        //condition for date
        else if(en[i].date < 1 || en[i].date > max_date(en[i].month, en[i].year)){
            check = 1;
        }
        //condtion for material type
        else if(!(strcmp(en[i].material, "Iron") == 0 || strcmp(en[i].material, "Steel") == 0)){
            check = 1;
        }
        if(check == 1){
            printf("Invalid input!! Please enter again: \n");
            i--;
        }
    }
    printf("\n");
    printf("Serial numbers of engine parts with weight greater than 5: ");
    struct engine *e;
    int count = 0;
    //cycling through entire array
    for(int i = 0; i < n; i++){
        e = &en[i];
        count += weight_count(e);
    }
    //case of no matches
    if(count == 0){
        printf("No entries found!");
    }
    printf("\n");
    printf("Year of manufacture of engine parts with serial number between AA2 and BB7: ");
    count = 0;
    //cycling through entire array
    for(int i = 0 ; i < n; i++){
        e = &en[i];
        count += year_count(e);
    }
    //case of no matches
    if(count == 0){
        printf("No entries found!");
    }
    printf("\n");
    count = 0;
    printf("Details of parts where date of manufacture is within 3 years of 15th november 2019: \n");
    //cycling through entire array
    for(int i = 0; i < n; i++){
        e = &en[i];
        count += details(e);
    }
    //case of no matches
    if(count == 0){
        printf("No entries found!");
    }
    printf("\n");
}
int weight_count(struct engine *enginePtr){
        //condtion to be checked
        if(enginePtr->weight > 5){
            printf("%s ", enginePtr->serial_num);//printing serial number in case of match
            return 1;
        }
        else return 0;
}
int year_count(struct engine *enginePtr){
        int check = 0;//'check' variable to see if there is a match
        if(enginePtr->serial_num[0] == 'A' && enginePtr->serial_num[2] >= '2'){
            check = 1;
        }
        else if(enginePtr->serial_num[0] == 'B' && enginePtr->serial_num[2] <= '7'){
            check = 1;
        }
        //steps in case match is made
        if(check == 1){
            printf("%d ", enginePtr->year);//printing year of matched part
            return 1;
        }
        else
        {
            return 0;
        }
        
}
int details(struct engine *enginePtr){
        int check = 0;//to keep track of whether part matches required condition
        //checking required condition
        if(enginePtr->year > 2016 &&  enginePtr->year < 2022){
            check = 1;
        }
        else if(enginePtr->year == 2016){
            if(enginePtr->month > 11){
                check = 1;
            }
            else if(enginePtr->month == 11){
                if(enginePtr->date >= 15){
                    check = 1;
                }
            }
        }
        else if(enginePtr->year == 2022){
            if(enginePtr->month < 11){
                check = 1;
            }
            else if(enginePtr->month == 11){
                if(enginePtr->date <= 15){
                    check = 1;
                }
            }
        }
        //steps in case match is made
        if(check == 1){
            //printing details
            printf("Serial number: %s\n", enginePtr->serial_num);
            printf("Date of manufacture: %d-%d-%d\n", enginePtr->date, enginePtr->month, enginePtr->year);
            printf("Material: %s\n", enginePtr->material);
            printf("Weight: %d\n", enginePtr->weight);
            return 1;
        }
        else
        {
            return 0;
        }
}
//returns total number of days in a month
int max_date(int month, int year){
    int max[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    //case of leap year
    if(year % 4 == 0){
        max[1] = 29;
    }
    return max[month - 1];
}
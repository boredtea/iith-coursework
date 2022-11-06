#include <stdio.h>
#include <string.h>

struct Date
{
    int day;
    int month;
    int year;
};

struct Engine
{
    char serialNo[4];
    struct Date date;
    int material;
    int weight;
};

//checks if the date entered by the user is a valid date
int dateValidity(struct Date *date)
{
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(date->year % 4 == 0 && date->year != 2000)
    days[1] = 29; //changing February's maximum number of days for leap years

    if(date->month < 1 || date->month > 12)
    return -1;
    else if(date->day < 1 || date->day > days[date->month - 1])
    return -1;
    else
    return 0;
}

//takes input regarding engine parts
void input(struct Engine *part, int n)
{
    int flag = 0;

    printf("\n");
    //accepting serial number
    printf("Enter serial number of part %d: ", n + 1);
    scanf(" %s", part->serialNo);

    //accepting date of manufacture
    while(1)
    {
        printf("Enter date of manufacture (dd-mm-yyyy) of part %d: ", n + 1);
        scanf("%d-%d-%d", &part->date.day, &part->date.month, &part->date.year);
        flag = dateValidity(&part->date);

        if(flag == -1)
        printf("Invalid date. Enter again.\n"); 
        else
        break;
    }

    //accepting material of engine part
    while(1)
    {
        printf("Enter material of part %d (1. Iron 2. Steel): ", n + 1);
        scanf("%d", &part->material);

        if(part->material != 1 && part->material != 2)
        printf("Invalid material. Enter again.\n");
        else
        break;   
    }

    //accepting weight of engine part
    while(1)
    {
        printf("Enter weight of part %d: ", n + 1);
        scanf("%d", &part->weight);

        if(part->weight >= 1 && part->weight <= 10)
        break;
        else
        printf("Invalid weight. Enter again.\n");
    }
}

//displays information about engine parts
void display(struct Engine *part)
{
    printf("\n");
    printf("Serial number: %s\n", part->serialNo);
    printf("Date of manufacture (dd-mm-yyyy): %d-%d-%d\n", part->date.day, part->date.month, part->date.year);
    char material[5]; 
    strcpy(material, (part->material == 1)?"Iron":"Steel");
    printf("Material: %s\n", material);
    printf("Weight: %d\n", part->weight);
    printf("\n");
}

//checks for engine parts with weight greater than 5 kg
int weightCheck(struct Engine *part)
{
    int count = 0;
    if(part->weight > 5)
    {
        printf("%s\n", part->serialNo);
        count++;
    }
    if(count != 0)
        return 1; //weight > 5 kg
    else
        return 0; //weight <= 5 kg
}

//checks for engine parts having serial numbers between AA2 and BB7(both inclusive)
int serialNo(struct Engine *part)
{
    int flag = 0;
    //looking for AA and BB
    switch(part->serialNo[0])
    {
        case 'A':
            if(part->serialNo[2] >= '2')
            flag++;
            break;
        case 'B':
            if(part->serialNo[2] <= '7')
            flag++;
            break;
    }

    if(flag == 1)
    {
        printf("%d\n", part->date.year);
        return 1; //lies between AA2 and BB7
    }
    else
        return 0; //doesn't lie between AA2 and BB7
}

//checks if date of manufacture is within three years of 15th November, 2019
int checkDate(struct Engine *part)
{
    //assuming 3 years to be 365 x 3 = 1095 days
    int flag = 0;

    //if year lies between 2017 and 2021, both inclusive
    if(part->date.year > 2016 && part->date.year < 2022)
        flag = 1;
    else if(part->date.year == 2016) //if year is 2016
    {
        switch(part->date.month)
        {
            case 12:
                flag = 1;
                break;
            case 11:
                if(part->date.day > 15) //setting 16th November, 2016 as the lower limit
                    flag = 1;
                break;
        }
    }
    else if(part->date.year == 2022)
    {
        if(part->date.month >= 1 && part->date.month <= 10)
            flag = 1;
        else if(part->date.month == 11)
        {
            if(part->date.day < 15) //setting 14th November, 2022 as the upper limit
                flag = 1;
        }
    }

    if(flag == 1)
    {
        display(part);
        return 1;
    }
    else
    {
        return 0;
    }
    
}

int main(int argc, char const *argv[])
{
    int inputs; //stores number of engine parts
    int flag; //used to check if engine parts satisfy the given condition

    //keeps taking input until valid input is entered
    while(1)
    {
        printf("Enter the number of parts: ");
        scanf("%d", &inputs);

        if(inputs <= 0 || inputs > 5)
        printf("Invalid input. Must be positive and less than 5. Enter again.\n");
        else
        break;
    }

    struct Engine engines[inputs]; //structure array
    struct Engine *parts; //structure pointer

    //taking input regarding engine part characteristics
    for(int i = 0; i < inputs; i++)
    {
        input(&engines[i], i);
    }

    //checking for engine parts with weight greater than 5 kg
    printf("\nSerial numbers where weight is more than 5kg: \n");
    flag = 0;
    for(int i = 0; i < inputs; i++)
    {
        parts = &engines[i];
        flag = flag + weightCheck(parts);
    
    }
    if(flag == 0)
    printf("\nSorry, no entries found.\n");

    //checking for engine parts having serial numbers between AA2 and BB7(both inclusive)
    printf("\nYears of manufacture of engine parts having serial number between AA2 and BB7: \n");
    flag = 0;
    for(int i = 0; i < inputs; i++)
    {
        parts = &engines[i];
        flag = flag + serialNo(parts);
        
    }
    if(flag == 0)
    printf("\nSorry, no entries found.\n");

    //checking if date of manufacture is within three years of 15th November, 2019
    printf("\nDetails of engine parts where year of manufacture is within 3 years of 15th Nov 2019: ");
    flag = 0;
    for(int i = 0; i < inputs; i++)
    {
        parts = &engines[i];
        flag = flag + checkDate(parts);
    }
    if(flag == 0)
    printf("\nSorry, no entries found.\n");

    return 0;
}
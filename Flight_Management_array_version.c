// Usefull Libraries
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 1000 //size of the records
#define NAME_LEN 100 // name length of particular flight
#define TIME_LEN 10 // Time length
#define STATUS_LEN 10 // status length of the flight
#define CLASS_LEN 100 // class length of the flight
#define LOCAL_KEY_LEN 16
#define SUCCESS 1
#define FAILURE 0

/* A brief introduction to some of the structure's elements. Here: 
"Name" of the flight is like real company names of flight like Kingfisher, Airlines, etc.
"id" can be connected to the model number of the flight with particular name or company.
"key" is the unique parameter of every flight which is made with id and arrival time, the idea behind is not the same model number flight can come two times at same time. It is possible if same id (or model) flight visit particular airport twice a day and in that case the record will be updated (while trying to insert) if you put same id and arrival time. */
typedef struct flightManagement
{
    char name[NAME_LEN];
    unsigned int id;
    unsigned int capacity;
    char arrival[TIME_LEN];
    char departure[TIME_LEN];
    char class[CLASS_LEN];
    char status[STATUS_LEN];
    char delay[TIME_LEN];
    unsigned long key;
} flight;

/* Reversing a string */
void reverse(char str[]) 
{ 
    char temp;
    int i = 0; 
    int len = strlen(str); 
    while (i < len/2) 
    { 
        temp = str[i];
        str[i]= str[len-i-1];
        str[len-i-1]=temp;
        i++;
    } 
} 

/* This function helps in converting an integer (decimal) to string, taking a string and an integer which is needs to be converted. */  
void integerToStringConverter(char str[], int num) 
{ 
    int i = 0;
    if (num == 0) 
    { 
        str[i++] = '0'; 
        str[i] = '\0'; 
    } 
    while (num != 0) 
    { 
        int c = num % 10; 
        str[i++] = c + '0'; 
        num = num/10; 
    } 
    str[i] = '\0'; 
    reverse(str); 
}

/* Initilizing every element of the record to zero or null */
void initialize_rec(flight records[])
{
    int i;
    for (i = 0; i < SIZE; i++)
    {
        records[i].name[0] = '\0';
        records[i].id = 0;
        records[i].capacity = 0;
        records[i].arrival[0] = '\0';
        records[i].departure[0] = '\0';
        records[i].class[0] = '\0';
        records[i].delay[0] = '\0';
        records[i].status[0] = '\0';
        records[i].key = 0;
    }
}

/* This function take number of hours and mins and thus convert and return proper string of the time in 24-HRS format returning value in HH:MM HRS */
void timeMaker(char time[], int hrs, int mins)
{
    char mm[2];
    char hh[1];
    if(hrs>9)
        integerToStringConverter(time, hrs);
    else
    {
        integerToStringConverter(time, 0);
        integerToStringConverter(hh,hrs);
        strcat(time,hh);
    }
    strcat(time, ":");
    if(mins<10)
        strcat(time, "0");
    integerToStringConverter(mm, mins);
    strcat(time, mm);
    strcat(time, " HRS");
}

/* Remember user does not know what is key, this function made key for the system taking id and arrival time as its input parameters.*/
long keyMaker(int id, char arrival[])
{
    int i, j;
    long key;
    char a[LOCAL_KEY_LEN];
    integerToStringConverter(a,id);
    strcat(a, arrival);
    i = 0;
    j = 5;
    while (arrival[i] != '\0')
    {
        if (arrival[i] >= '0' && arrival[i] <= '9')
            a[j++] = arrival[i];
        i++;
    }
    a[j] = '\0';
    key = atol(a); // This function converts string to an integer
    return key;
}

/* This simply check whether the record is empty or not by keeping track of the first element */
int isEmpty(flight records[])
{
    int status_code = FAILURE;
    if (records[0].key == 0)
        status_code = SUCCESS;
    return status_code;
}

/* This simply check whether the record is full or not by keeping track of the last element */
int isFull(flight records[])
{
    int status_code = SUCCESS;
    if (records[SIZE - 1].key == 0)
        status_code = FAILURE;
    return status_code;
}

/* It returns the total number of the flight(s) present in the record. */ 
int getNumFlights(flight records[])
{
    int i;
    i = 0;
    while (i < SIZE && records[i].key != 0)
    {
        i++;
    }
    return i;
}

/* This function simply displays the existing record. */
void displayRecord(flight records[])
{
    int loc;
    loc=0;
    if(loc<getNumFlights(records))
    {
        printf("\nNAME ID CAPACITY ARRIVAL DEPARTURE CLASS STATUS DELAY\n");
        while(loc<getNumFlights(records))
        {
            printf("%s %d %d %s %s %s %s",records[loc].name,records[loc].id,records[loc].capacity,records[loc].arrival,records[loc].departure,records[loc].class,records[loc].status);
            if(records[loc].delay[0]!='\0')
                printf(" %s",records[loc].delay);
            else
            printf(" --"); 
            printf("\n");
            loc++;
        }
        printf("\n");
    }
    else
        printf("\nNo records to DISPLAY\n");
}

/* This function simply displays the field of existing record. */
void displayFieldOfRecord(flight records[],int loc)
{
    printf("\nNAME ID CAPACITY ARRIVAL DEPARTURE CLASS STATUS DELAY\n");
    if(loc<getNumFlights(records))
    {
        printf("%s %d %d %s %s %s %s",records[loc].name,records[loc].id,records[loc].capacity,records[loc].arrival,records[loc].departure,records[loc].class,records[loc].status);
        if(records[loc].delay[0]!='\0')
            printf(" %s",records[loc].delay);
        else
           printf(" --"); 
        printf("\n");
        printf("\n");
    }
    else
        printf("\nNo records to DISPLAY\n");
}

/* Stay time as per the given defination in the question is the time which we get subtracting the departure time and arrival time. It takes departure and arrival as an input and returns the difference in 24-HRS format. */
void getStayTime(char stay[], char arrival[], char departure[])
{
    int i, j;
    char a[TIME_LEN];
    char d[TIME_LEN];
    i = 0, j = 0;
    while (arrival[i] != '\0')
    {
        if (arrival[i] >= '0' && arrival[i] <= '9')
            a[j++] = arrival[i];
        i++;
    }
    a[j] = '\0';
    i = 0, j = 0;
    while (departure[i] != '\0')
    {
        if (departure[i] >= '0' && departure[i] <= '9')
            d[j++] = departure[i];
        i++;
    }
    d[j] = '\0';
    int data1 = atoi(a);
    int data2 = atoi(d);
    int hr1 = data1 / 100;
    int hr2 = data2 / 100;
    int min1 = data1 % 100;
    int min2 = data2 % 100;
    int diff_hr = abs(hr2 - hr1); //if departure time is less signifying next day departure
    int diff_min = abs(min2 - min1); 
    timeMaker(stay,diff_hr,diff_min);
}

/* Give the location flight in a record which highest stay time. */
int getFlightWithtLongeststay(flight records[])
{
    int i, loc;
    char stayTime[TIME_LEN];
    char temp[TIME_LEN];
    if (isEmpty(records)==1)
        loc = -1;
    else
    {
        getStayTime(stayTime, records[0].arrival, records[0].departure);
        loc = 0;
        for (i = 1; i < getNumFlights(records); i++)
        {
            getStayTime(temp, records[i].arrival, records[i].departure);
            if (strcmp(stayTime, temp) < 0)
            {
                strcpy(stayTime, temp);
                loc = i;
            }
        }
    }
    return loc;
}

/* Used in sorting */
void merge_self(flight a[], flight c[], int l, int m, int h, int parameter)
{
    int i, j, k;
    k = l;
    i = l;
    j = m + 1;
    if (parameter == 0)
    {
        while (i <= m && j <= h)
        {
            if (a[i].key < a[j].key)
                c[k++] = a[i++];
            else
                c[k++] = a[j++];
        }
    }
    else if (parameter == 1)
    {
        while (i <= m && j <= h)
        {
            if (strcmp(a[i].arrival, a[j].arrival) < 0)
                c[k++] = a[i++];
            else
                c[k++] = a[j++];
        }
    }
    else if (parameter == 2)
    {
        while (i <= m && j <= h)
        {
            if (strcmp(a[i].departure, a[j].departure) < 0)
                c[k++] = a[i++];
            else
                c[k++] = a[j++];
        }
    }
    else if (parameter == 3)
    {
        char temp1[TIME_LEN];
        char temp2[TIME_LEN];

        while (i <= m && j <= h)
        {
            getStayTime(temp1, a[i].arrival, a[i].departure);
            getStayTime(temp2, a[j].arrival, a[j].departure);
            if (strcmp(temp1, temp2) < 0)
                c[k++] = a[i++];
            else
                c[k++] = a[j++];
        }
    }
    while (i <= m)
        c[k++] = a[i++];
    while (j <= h)
        c[k++] = a[j++];
    for (i = l; i <= h; i++)
        a[i] = c[i];
}

/* Sorting using mergesort */
void mergesort(flight a[], flight c[], int lo, int hi, int parameter)
{
    int mid;
    if (lo < hi)
    {
        mid = (lo + hi) / 2;
        mergesort(a, c, lo, mid, parameter);
        mergesort(a, c, mid + 1, hi, parameter);
        merge_self(a, c, lo, mid, hi, parameter);
    }
}

/* Function which sorts the record on the basis of the key, using mergesort. */
void getSortedOnKey(flight records[], flight helper[])
{
    mergesort(records, helper, 0, getNumFlights(records) - 1, 0);
}

/* Function which sorts the record on the basis of arrival time, using mergesort. */
void getSortedOnArrivalTime(flight records[], flight helper[])
{
    mergesort(records, helper, 0, getNumFlights(records) - 1, 1);
}

/* Function which sorts the record on the basis of departure time, using mergesort. */
void getSortedOnDepartureTime(flight records[], flight helper[])
{
    mergesort(records, helper, 0, getNumFlights(records) - 1, 2);
}

/* Function which sorts the record on the basis of departure time, using mergesort. */
void getSortedOnStayTime(flight records[], flight helper[])
{
    mergesort(records, helper, 0, getNumFlights(records) - 1, 3);
}

/* Searching a key from a record using linear search */ 
int linear_search_key(flight records[], long key)
{
    int loc = -1;
    int i = 0;
    int found = 0;
    while (!found && i < getNumFlights(records))
    {
        if (records[i].key == key)
        {
            loc = i;
            found = 1;
        }
        else
            i++;
    }
    return loc;
}

/* This function takes key of the record which has to be deleted. */
int delete (flight records[], long key)
{
    int status_code = SUCCESS;
    if (isEmpty(records)==1)
        status_code = FAILURE;
    else
    {
        int loc = 0;
        int i = 0;
        int found = 0;
        while (!found && i < getNumFlights(records))
        {
            if (records[i].key == key)
            {
                found = 1;
                loc = i;
            }
            else
                i++;
        }
        if (found == 1)
        {
            if (loc != getNumFlights(records) - 1)
            {
                while (loc < getNumFlights(records) - 1)
                {
                    records[loc] = records[loc + 1];
                    loc++;
                }
            }
            records[loc].name[0] = '\0';
            records[loc].id = 0;
            records[loc].capacity = 0;
            records[loc].arrival[0] = '\0';
            records[loc].departure[0] = '\0';
            records[loc].class[0] = '\0';
            records[loc].key = 0;
            records[loc].status[0] = '\0';
            records[loc].delay[0] = '\0';
        }
        else
            status_code = FAILURE;
    }
    return status_code;
}

/* Uniqueness should only be consider if we have two flights with same id and name which is possible when same model of particular flight is visiting airport more than once which is very much possible especially in domestic flights. In that case if any time has been delayed then it has be removed (For example a flight is coming in an at 3am and then again at 6pm on same day and lets say it is delayed for 6 hours so not able to come at 3pm. Now it is not possible for the flight to come at 6pm again and thus need to be removed. */

/* This will remove the delayed flight in the record as soon as it find any */
void listUnique(flight records[])
{
    int i, j, n, flag;
    flag = 0;
    n = getNumFlights(records);
    for (i = 0; i < n - 1 && flag == 0; i++)
    {
        for (j = i + 1; j < n && flag == 0; j++)
        {
            if (strcmp(records[i].name, records[j].name) == 0 && (records[i].id - records[j].id == 0))
            {
                if (strcmp(records[i].status, "DELAY") == 0 || strcmp(records[j].status, "DELAY") == 0)
                {
                    flag = 1;
                    if (strcmp(records[i].status, "DELAY") == 0 && strcmp(records[j].status, "DELAY") == 0)
                    {
                        if (strcmp(records[i].delay, records[j].delay) >= 0)
                            delete (records, records[i].key);
                        else
                            delete (records, records[j].key);
                    }
                    else if (strcmp(records[i].status, "DELAY") == 0)
                        delete (records, records[i].key);
                    else
                        delete (records, records[j].key);
                }
            }
        }
    }
}

/* Inserts new record in the file and update the old if re inserted */
int insert(flight records[], char name[], int id, int capacity, char arrival[], char departure[], char class[])
{
    flight helper[SIZE];
    int status_code = SUCCESS;
    int j;
    long given_key = keyMaker(id, arrival);
    if (isFull(records)==1)
        status_code = FAILURE;
    else
    {
        j = getNumFlights(records);

        if (linear_search_key(records, given_key) != -1)  // if the key is old one
            j = linear_search_key(records, given_key);

        strcpy(records[j].name, name);
        records[j].id = id;
        records[j].capacity = capacity;
        strcpy(records[j].arrival, arrival);
        strcpy(records[j].departure, departure);
        strcpy(records[j].status, "ON_TIME");
        strcpy(records[j].class, class);
        records[j].key = keyMaker(id, arrival);

        if (j != linear_search_key(records, given_key) && j != 0)
            getSortedOnKey(records, helper); 
        listUnique(records); // If record entered found with any duplicacy
    }
    return status_code;
}

/* Update the current status of the flight */
int UpdateFlightStatus(flight records[], char name[], long key, char status[], char delay[], char class[])
{
    int status_code = SUCCESS;
    if (isEmpty(records)==1)
        status_code = FAILURE;
    else
    {
        int loc = 0;
        int i = 0;
        int found = 0;
        while (!found && i < getNumFlights(records))
        {
            if (records[i].key == key && strcmp(records[i].name,name)==0)
            {
                found = 1;
                loc = i;
            }
            else
                i++;
        }
        if (found == 1)
        {
            strcpy(records[loc].status,status);
            if(strcmp(status,"DELAY")==0)
                strcpy(records[loc].delay,delay);
            else if(strcmp(status,"PROMOTED")==0)
                strcpy(records[loc].class,class);
            listUnique(records); // If record updated found with any duplicacy
        }
        else
            status_code = FAILURE;
    }
    return status_code;
}
int main()
{
    flight records[SIZE], helper[SIZE];
    flight VIP_records[SIZE], VVIP_records[SIZE], public_records[SIZE];
    initialize_rec(records);
    initialize_rec(helper);
    initialize_rec(VIP_records);
    initialize_rec(VVIP_records);
    initialize_rec(public_records);

    char name[NAME_LEN], arrival[TIME_LEN], departure[TIME_LEN], class[CLASS_LEN], status[STATUS_LEN], delay[TIME_LEN];
    int id, arrival_hr, arrival_min, departure_hr, departure_min, delay_hr, delay_min, capacity;
    long key;
    int i,input, flag, found,num,loc;
    flag = 0;
    found = FAILURE;
    printf("You can perform the following operations any number of times. Select the appropriate option for your query\n");
    do
    {
        printf("Enter the number to perform the respective operation :\n 1. To Insert a new record or update an existing record, enter 1\n 2. To Delete any record, enter 2\n 3. To get the number of flights present in the current record, enter 3\n 4. To check whether the list of record is full, enter 4\n 5. To check whether the list of record is empty, enter 5\n 6. To get the flight with longest stay present in the current record, enter 6\n 7. To see the record sorted on the basis of arrival time, enter 7\n 8. To see the record sorted on the basis of departure time, enter 8\n 9. To see the record sorted on the basis of stay time, enter 9\n 10. To update status of the flight, enter 10\n 11. To display existing record(s) of the flight, enter 11\n Any other key to EXIT\n");
        scanf("%d", &input);
        switch (input)
        {
            case 1:
                found = FAILURE;
                printf("You will enter fields of record one by one, insert the name of flight\n");
                scanf("%s",&name); 
                printf("Enter the id of the flight.");
                do
                {
                    printf("Remember that id should contain 5 digits only\n");
                    scanf("%d", &id);
                } while (id < 10000 || id > 99999);// Specific id because system handle this way only. Again a try to make this real.

                printf("Enter the arrival time of flight, which is excepted in 24-hours format only\n");
                do
                {
                    printf("Enter the HRS of the arrival which has value between 0 and 23\n");
                    scanf("%d", &arrival_hr);
                } while (arrival_hr < 0 || arrival_hr > 23); // Correct time input
                do
                {
                    printf("Enter the MINS of the arrival which has value between 0 and 59\n");
                    scanf("%d", &arrival_min);
                } while (arrival_min < 0 || arrival_min > 60);
                timeMaker(arrival, arrival_hr, arrival_min);

                key = keyMaker(id, arrival);

                printf("Enter the departure time of flight, which is excepted in 24-hours format only\n");
                do
                {
                    printf("Enter the HRS of the departure which has value between 0 and 23\n");
                    scanf("%d", &departure_hr);
                } while (departure_hr < 0 || departure_hr > 23);
                do
                {
                    printf("Enter the MINS of the departure which has value between 0 and 59\n");
                    scanf("%d", &departure_min);
                } while (departure_min < 0 || departure_min > 60);
                timeMaker(departure, departure_hr, departure_min);
                
                do
                {
                    printf("Enter the capacity of passengers in the airbus keeping in mind that it can exist only between 50 and 1000 as of now\n");
                    scanf("%d", &capacity);
                } while (capacity < 50 || capacity > 1000); // Appropriate Capacity
                
                printf("Enter the class of flight. ");
                do
                {
                    printf("This can be \"VIP\" or \"VVIP\" or \"public\"\n");
                    scanf("%s",&class);
                } while (strcmp(class, "VIP") != 0 && strcmp(class, "VVIP") != 0 && strcmp(class, "public") != 0); //Taking correct class.

                if (linear_search_key(records, key) != -1)
                {
                    delete (VIP_records, key);
                    delete (VVIP_records, key);
                    delete (public_records, key);
                }
                
                found = insert(records, name, id, capacity, arrival, departure, class);
                /* All the three sorted records are updated. */
                if(strcmp(class,"VIP") == 0) 
                    insert(VIP_records, name, id, capacity, arrival, departure, class);
                else if(strcmp(class,"VVIP") == 0)
                    insert(VVIP_records, name, id, capacity, arrival, departure, class);
                else
                    insert(public_records, name, id, capacity, arrival, departure, class);
                
                if (found)
                    printf("OPERATION SUCCESSFULL\n");
                else
                    printf("FAILED to INSERT, check the record size\n");
                break;
            case 2:
                found = FAILURE;
                printf("Enter the id of the flight record which needs to be deleted. ");
                do
                {
                    printf("Remember that id should contain 5 digits only\n");
                    scanf("%d", &id);
                } while (id < 10000 || id > 99999);

                printf("Enter the arrival time of flight, which is excepted in 24-hours format only\n");
                do
                {
                    printf("Enter the HRS of the arrival which has value between 0 and 23\n");
                    scanf("%d", &arrival_hr);
                } while (arrival_hr < 0 || arrival_hr > 23);
                do
                {
                    printf("Enter the MINS of the arrival which has value between 0 and 59\n");
                    scanf("%d", &arrival_min);
                } while (arrival_min < 0 || arrival_min > 60);
                timeMaker(arrival, arrival_hr, arrival_min);

                key = keyMaker(id, arrival);
                
                /* All the three sorted records are updated. */
                if (linear_search_key(records, key) != -1)
                {
                    delete (VIP_records, key);
                    delete (VVIP_records, key);
                    delete (public_records, key);
                }
                
                found = delete (records, key); // If found then only deleted.

                if (found)
                    printf("OPERATION SUCCESSFULL\n");
                else
                    printf("FAILED to DELETE, record does not exists\n");
                break;
            case 3:
                printf("Enter the record's specific number to get the number of flights in that record\n 1. Enter 1 to get number of flights in the record containing all flights\n 2. Enter 2 to get number of flights in the record containing VIP class flights\n 3. Enter 3 to get number of flights in the record containing VVIP class flights\n 4. Enter 4 to get number of flights in the record containing public class flights\n");
                do
                {
                    printf("Enter a valid number to get the number of flights of that particular record\n");
                    scanf("%d",&num);
                } while (num < 0 || num > 4);

                switch (num)
                {
                    case 1:
                        printf("Number of flights in the record is/are %d\n", getNumFlights(records));
                        break;
                    case 2:
                        printf("Number of flights in the record is/are %d\n", getNumFlights(VIP_records));
                        break;
                    case 3:
                        printf("Number of flights in the record is/are %d\n", getNumFlights(VVIP_records));
                        break;
                    case 4:
                        printf("Number of flights in the record is/are %d\n", getNumFlights(public_records));
                        break;
                    default:
                    printf("Wrong query");
                }
                break;
            case 4:
                if (isFull(records)==1)
                    printf("List of records is Full\n");
                else
                    printf("List of records is NOT Full\n");
                break;
            case 5:
                if (isEmpty(records)==1)
                    printf("List of records is Empty\n");
                else
                    printf("List of records is NOT Empty\n");
                break;
            case 6:
                if(getFlightWithtLongeststay(records)<0)
                    printf("Record is empty\n");
                else
                {
                    char stay[TIME_LEN];
                    printf("Enter the record's specific number to get the flight with longest stay in that record\n 1. Enter 1 to get the flight with longest stay in the record containing all flights\n 2. Enter 2 to get the flight with longest stay in the record containing VIP class flights\n 3. Enter 3 to get the flight with longest stay in the record containing VVIP class flights\n 4. Enter 4 to get the flight with longest stay in the record containing public class flights\n");
                    do
                    {
                        printf("Enter a valid number to get the number of flights of that particular record\n");
                        scanf("%d",&num);
                    } while (num < 0 || num > 4);

                    switch (num)
                    {
                        case 1:
                            loc = getFlightWithtLongeststay(records);
                            getStayTime(stay,records[loc].arrival,records[loc].departure);
                            printf("Flight with Longest stay Time in record is\n");
                            displayFieldOfRecord(records,loc);
                            printf("Stay Time of the flight is: ");
                            puts(stay);
                            break;
                        case 2:
                            loc = getFlightWithtLongeststay(VIP_records);
                            getStayTime(stay,VIP_records[loc].arrival,VIP_records[loc].departure);
                            printf("Flight with Longest stay Time in record is\n");
                            displayFieldOfRecord(VIP_records,loc);
                            printf("Stay Time of the flight is: ");
                            puts(stay);
                            break;
                        case 3:
                            loc = getFlightWithtLongeststay(VVIP_records);
                            getStayTime(stay,VVIP_records[loc].arrival,VVIP_records[loc].departure);
                            printf("Flight with Longest stay Time in record is\n");
                            displayFieldOfRecord(VVIP_records,loc);
                            printf("Stay Time of the flight is: ");
                            puts(stay);
                            break;
                        case 4:
                            loc = getFlightWithtLongeststay(public_records);
                            getStayTime(stay,public_records[loc].arrival,public_records[loc].departure);
                            printf("Flight with Longest stay Time in record is\n");
                            displayFieldOfRecord(public_records,loc);
                            printf("Stay Time of the flight is: ");
                            puts(stay);
                            break;
                        default:
                        printf("Wrong query");
                    }
                }
                break;
            case 7:
                getSortedOnArrivalTime(records,helper);
                displayRecord(records);
                break;
            case 8:
                getSortedOnDepartureTime(records,helper);
                displayRecord(records);
                break;
            case 9:
                getSortedOnStayTime(records,helper);
                displayRecord(records);            
                break;
            case 10:
                printf("Enter the name of the flight which needs to be updated.\n");
                scanf("%s",&name);
                printf("Enter the id of the flight record which needs to be updated. ");
                do
                {
                    printf("Remember that id should contain 5 digits only\n");
                    scanf("%d", &id);
                } while (id < 10000 || id > 99999);

                printf("Enter the arrival time of flight, which is excepted in 24-hours format only\n");
                do
                {
                    printf("Enter the HRS of the arrival which has value between 0 and 23\n");
                    scanf("%d", &arrival_hr);
                } while (arrival_hr < 0 || arrival_hr > 23);
                do
                {
                    printf("Enter the MINS of the arrival which has value between 0 and 59\n");
                    scanf("%d", &arrival_min);
                } while (arrival_min < 0 || arrival_min > 60);
                timeMaker(arrival, arrival_hr, arrival_min);

                key = keyMaker(id, arrival);
                
                if(linear_search_key(records,key)>=0) //checking if record exits or not
                {
                    printf("Enter the new status of the flight\n");
                    do
                    {
                        printf("This can be \"DELAY\" or \"ON_TIME\" or \"CANCELLED\" or \"PROMOTED\"\n");
                        scanf("%s", &status);
                    } while (strcmp(status, "DELAY") != 0 && strcmp(status, "ON_TIME") != 0 && strcmp(status, "CANCELLED") != 0 && strcmp(status, "PROMOTED") != 0); //status can be of these things only

                    if(strcmp(status,"DELAY")==0)
                    {
                        printf("Enter the delay time of flight, which is excepted in 24-hours format only\n");
                        do
                        {
                            printf("Enter the HRS of the delay which has value between 0 and 23\n");
                            scanf("%d", &delay_hr);
                        } while (delay_hr < 0 || delay_hr > 23);
                        do
                        {
                            printf("Enter the MINS of the delay which has value between 0 and 59\n");
                            scanf("%d", &delay_min);
                        } while (delay_min < 0 || delay_min > 60);

                        if(delay_hr==0 && delay_min==0) // Ensuring correct delay time
                        {
                            printf("Operation ended, no proper delay time given");
                        }
                        else
                        {
                            timeMaker(delay, delay_hr, delay_min);
                            /* Updating Everything */
                            if(UpdateFlightStatus(records,name,key,status,delay,"\0"))
                            {
                                UpdateFlightStatus(VVIP_records,name,key,status,delay,"\0");
                                UpdateFlightStatus(VIP_records,name,key,status,delay,"\0");
                                UpdateFlightStatus(public_records,name,key,status,delay,"\0");
                                printf("Operation Successful\n");
                            }
                            else
                                printf("Record does not exists\n");
                        }
                    }
                    else if(strcmp(status,"PROMOTED")==0)
                    {
                        loc = linear_search_key(records,key);
                        printf("Enter the new class of flight. ");
                            do
                            {
                                printf("This can be \"VIP\" or \"VVIP\"\n");
                                scanf("%s",class);
                            } while (strcmp(class, "VIP") != 0 && strcmp(class, "VVIP") != 0);
                        if(strcmp(records[loc].class,"VVIP")==0)//Making sure it cant promoted further
                            printf("Already highest class exists, operation ended\n");
                        else
                        {
                            /* Updating Everything */
                          if(UpdateFlightStatus(records,name,key,status,"\0",class))
                            {
                                delete (VIP_records, key);
                                delete (public_records, key);
                                if(strcmp(class,"VVIP")==0)
                                    insert(VVIP_records,records[loc].name,records[loc].id,records[loc].capacity,records[loc].arrival,records[loc].departure,records[loc].class);
                                else
                                    insert(VIP_records,records[loc].name,records[loc].id,records[loc].capacity,records[loc].arrival,records[loc].departure,records[loc].class);
                                printf("Operation Successful\n");
                            }
                            else
                                printf("Record does not exists\n");
                        }
                    }
                    else// Cancelled or changed to On_Time {if record has been changed from delay, delay is passed as null}
                    {
                        /* Updating Everything */
                        if(UpdateFlightStatus(records,name,key,status,"\0","\0"))
                        {
                            UpdateFlightStatus(VIP_records,name,key,status,"\0","\0");
                            UpdateFlightStatus(VVIP_records,name,key,status,"\0","\0");
                            UpdateFlightStatus(public_records,name,key,status,"\0","\0");
                            printf("OPERATION SUCCESSFULL\n");
                        }
                        else
                          printf("Record does not exists\n");  
                    }
                }
                else
                    printf("Record does not exists\n");
                break;
            case 11:
                displayRecord(records);
                break;
            default:
                printf("You have successfully exited");
                flag = 1;
        }
    } while (flag == 0);
    return 0;
}

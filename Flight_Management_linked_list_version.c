// Usefull Libraries
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 1000     //size of the records
#define NAME_LEN 100  // name length of particular flight
#define TIME_LEN 10   // Time length
#define STATUS_LEN 10 // status length of the flight
#define CLASS_LEN 100 // class length of the flight
#define LOCAL_KEY_LEN 16
typedef enum
{
    FAILURE,
    SUCCESS
} status_code;

/* A brief introduction to some of the structure's elements. Here: 
"Name" of the flight is like real company names of flight like Kingfisher, Airlines, etc.
"id" can be connected to the model number of the flight with particular name or company.
"key" is the unique parameter of every flight which is made with id and arrival time, the idea behind is not the same model number flight can come two times at same time. It is possible if same id (or model) flight visit particular airport twice a day and in that case the record will be updated (while trying to insert) if you put same id and arrival time. */
typedef struct FlightNode
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
    struct FlightNode *next;
} Node;

// DECLARATION OF THE FUNCTIONS USED IN PROJECT
/* -------------------------------------------------------------------------------------------------- */
void reverse(char str[]);
void integerToStringConverter(char str[], int num);
void timeMaker(char time[], int hrs, int mins);
long keyMaker(int id, char arrival[]);
int getNumFlights(Node *records_head);
status_code isEmpty(Node *records_heads);
status_code isFull(Node *records_heads);
void displayRecord(Node *records_head);
void displayFieldOfRecord(Node *nptr);
void getStayTime(char stay[], char arrival[], char departure[]);
Node *getFlightWithtLongeststay(Node *records_head);
Node *MakeNode(char name[], int id, int capacity, char arrival[], char departure[], char class[]);
int linear_search_key(Node *records_heads, long key);
Node *Divide(Node *lptr);
Node *Merge(Node *lptr, Node *nptr, int parameter);
Node *MergeSort(Node *lptr, int parameter);
Node *getSortedOnKey(Node *records_head);
Node *getSortedOnArrivalTime(Node *records_head);
Node *getSortedOnDepartureTime(Node *records_head);
Node *getSortedOnStayTime(Node *records_head);
status_code delete (Node **records_head_address, long key);
Node *listUnique(Node *records_head);
int insert(Node **records_head_address, char name[], int id, int capacity, char arrival[], char departure[], char class[]);
status_code UpdateFlightStatus(Node **records_head_address, char name[], long key, char status[], char delay[], char class[]);
/* -------------------------------------------------------------------------------------------------- */

int main()
{
    Node *records_head, *VIP_records_head, *VVIP_records_head, *public_records_head;
    records_head = NULL;
    VIP_records_head = NULL;
    VVIP_records_head = NULL;
    public_records_head = NULL;

    char name[NAME_LEN], arrival[TIME_LEN], departure[TIME_LEN], class[CLASS_LEN], status[STATUS_LEN], delay[TIME_LEN];
    int id, arrival_hr, arrival_min, departure_hr, departure_min, delay_hr, delay_min, capacity;
    long key;
    int i, input, flag, found, num;
    Node *temp;
    flag = 0;
    found = FAILURE;

    printf("You can perform the following operations any number of times. Select the appropriate option for your query\n");
    do
    {
        printf("\n===============================================================\n");
        printf(" 1  - To INSERT a new record or UPDATE an existing record\n");
        printf(" 2  - To DELETE any record\n");
        printf(" 3  - To get the NUMBER of FLIGHTS present in the current record\n");
        printf(" 4  - To CHECK whether the list of record is FULL\n");
        printf(" 5  - To CHECK whether the list of record is EMPTY\n");
        printf(" 6  - To get the Node with LONGEST STAY present in the current record\n");
        printf(" 7  - To see the record SORTED on the basis of ARRIVAL TIME\n");
        printf(" 8  - To see the record SORTED on the basis of DEPARTURE TIME\n");
        printf(" 9  - To see the record SORTED on the basis of STAY TIME\n");
        printf(" 10 - To UPDATE STATUS of the flight\n");
        printf(" 11 - To DISPLAY existing record(s) of the flight\n");
        printf(" .. - Any other key to EXIT\n");
        printf("===============================================================\n");
        printf("Enter the CHOICE you want to Execute\n-> ");

        scanf("%d", &input);
        switch (input)
        {
        case 1:
            found = FAILURE;
            printf("You will enter fields of record one by one, insert the name of flight: ");
            scanf("%s", &name); 
            printf("Enter the id of the flight: ");
            do
            {
                printf("(Remember that id should contain 5 digits only) ");
                scanf("%d", &id);
            } while (id < 10000 || id > 99999); // Specific id because system handle this way only. Again a try to make this real.

            printf("Enter the arrival time of flight, which is excepted in 24-hours format only\n");
            do
            {
                printf("Enter the HRS of the arrival which has value between 0 and 23: ");
                scanf("%d", &arrival_hr);
            } while (arrival_hr < 0 || arrival_hr > 23); // Correct time input
            do
            {
                printf("Enter the MINS of the arrival which has value between 0 and 59: ");
                scanf("%d", &arrival_min);
            } while (arrival_min < 0 || arrival_min > 60);
            timeMaker(arrival, arrival_hr, arrival_min);

            key = keyMaker(id, arrival);

            printf("Enter the departure time of flight, which is excepted in 24-hours format only\n");
            do
            {
                printf("Enter the HRS of the departure which has value between 0 and 23: ");
                scanf("%d", &departure_hr);
            } while (departure_hr < 0 || departure_hr > 23);
            do
            {
                printf("Enter the MINS of the departure which has value between 0 and 59: ");
                scanf("%d", &departure_min);
            } while (departure_min < 0 || departure_min > 60);
            timeMaker(departure, departure_hr, departure_min);

            do
            {
                printf("Enter the capacity of passengers in the airbus (it can exist only between 50 and 1000): ");
                scanf("%d", &capacity);
            } while (capacity < 50 || capacity > 1000); // Appropriate Capacity

            printf("Enter the class of flight: ");
            do
            {
                printf("(This can be \"VIP\" or \"VVIP\" or \"public\") ");
                scanf("%s", &class);
            } while (strcmp(class, "VIP") != 0 && strcmp(class, "VVIP") != 0 && strcmp(class, "public") != 0); //Taking correct class.

            if (linear_search_key(records_head, key))
            {
                delete (&VIP_records_head, key);
                delete (&VVIP_records_head, key);
                delete (&public_records_head, key);
            }

            found = insert(&records_head, name, id, capacity, arrival, departure, class);
            /* All the three sorted records are updated. */
            if (strcmp(class, "VIP") == 0)
                insert(&VIP_records_head, name, id, capacity, arrival, departure, class);
            else if (strcmp(class, "VVIP") == 0)
                insert(&VVIP_records_head, name, id, capacity, arrival, departure, class);
            else
                insert(&public_records_head, name, id, capacity, arrival, departure, class);

            if (found)
                printf("OPERATION SUCCESSFULL\n");
            else
                printf("FAILED to INSERT, check the record size\n");
            break;
        case 2:
            found = FAILURE;
            printf("Enter the id of the Node record which needs to be deleted. ");
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
            if (linear_search_key(records_head, key))
            {
                delete (&VIP_records_head, key);
                delete (&VVIP_records_head, key);
                delete (&public_records_head, key);
            }

            found = delete (&records_head, key); // If found then only deleted.

            if (found)
                printf("OPERATION SUCCESSFULL\n");
            else
                printf("FAILED to DELETE, record does not exists\n");
            break;
        case 3:
            printf("\n=====================================================================================\n");
            printf(" Enter the record's specific number to get the number of flights in that record\n");
            printf(" 1. To get number of flights in the record containing all flights\n");
            printf(" 2. To get number of flights in the record containing VIP class flights\n");
            printf(" 3. To get number of flights in the record containing VVIP class flights\n");
            printf(" 4. To get number of flights in the record containing public class flights\n");
            printf("\n=====================================================================================\n");
            do
            {
                printf("Enter a valid number to get the number of flights of that particular record\n");
                scanf("%d", &num);
            } while (num < 0 || num > 4);

            switch (num)
            {
            case 1:
                printf("Number of flights in the record is/are %d\n", getNumFlights(records_head));
                break;
            case 2:
                printf("Number of flights in the record is/are %d\n", getNumFlights(VIP_records_head));
                break;
            case 3:
                printf("Number of flights in the record is/are %d\n", getNumFlights(VVIP_records_head));
                break;
            case 4:
                printf("Number of flights in the record is/are %d\n", getNumFlights(public_records_head));
                break;
            default:
                printf("Wrong query");
            }
            break;
        case 4:
            if (isFull(records_head))
                printf("List of records is Full\n");
            else
                printf("List of records is NOT Full\n");
            break;
        case 5:
            if (isEmpty(records_head))
                printf("List of records is Empty\n");
            else
                printf("List of records is NOT Empty\n");
            break;
        case 6:
            if (!records_head)
                printf("Record is empty\n");
            else
            {
                char stay[TIME_LEN];
                printf("\n=====================================================================================\n");
                printf("Enter the record's specific number to get the flight with longest stay in that record\n");
                printf(" 1. To get the Flight with longest stay in the record containing all flights\n");
                printf(" 2. To get the Flight with longest stay in the record containing VIP class flights\n");
                printf(" 3. To get the Flight with longest stay in the record containing VVIP class flights\n");
                printf(" 4. To get the Flight with longest stay in the record containing public class flights\n");
                printf("\n=====================================================================================\n");
                do
                {
                    printf("Enter a valid number to get the number of flights of that particular record\n");
                    scanf("%d", &num);
                } while (num < 0 || num > 4);

                switch (num)
                {
                case 1:
                    temp = getFlightWithtLongeststay(records_head);
                    getStayTime(stay, temp->arrival, temp->departure);
                    printf("Flight with Longest stay Time in record is\n");
                    displayFieldOfRecord(temp);
                    printf("Stay Time of the flight is: ");
                    puts(stay);
                    break;
                case 2:
                    temp = getFlightWithtLongeststay(VIP_records_head);
                    getStayTime(stay, temp->arrival, temp->departure);
                    printf("Flight with Longest stay Time in record is\n");
                    displayFieldOfRecord(temp);
                    printf("Stay Time of the flight is: ");
                    puts(stay);
                    break;
                case 3:
                    temp = getFlightWithtLongeststay(VVIP_records_head);
                    getStayTime(stay, temp->arrival, temp->departure);
                    printf("Flight with Longest stay Time in record is\n");
                    displayFieldOfRecord(temp);
                    printf("Stay Time of the flight is: ");
                    puts(stay);
                    break;
                case 4:
                    temp = getFlightWithtLongeststay(public_records_head);
                    getStayTime(stay, temp->arrival, temp->departure);
                    printf("Flight with Longest stay Time in record is\n");
                    displayFieldOfRecord(temp);
                    printf("Stay Time of the flight is: ");
                    puts(stay);
                    break;
                default:
                    printf("Wrong query");
                }
            }
            break;
        case 7:
            records_head = getSortedOnArrivalTime(records_head);
            displayRecord(records_head);
            records_head = getSortedOnKey(records_head);
            break;
        case 8:
            records_head = getSortedOnDepartureTime(records_head);
            displayRecord(records_head);
            records_head = getSortedOnKey(records_head);
            break;
        case 9:
            records_head = getSortedOnStayTime(records_head);
            displayRecord(records_head);
            records_head = getSortedOnKey(records_head);
            break;
        case 10:
            printf(" Enter the name of the flight which needs to be updated: \n");
            scanf("%s", &name);
            printf(" Enter the id of the flight which needs to be updated: ");
            do
            {
                printf("(Remember that id should contain 5 digits only) ");
                scanf("%d", &id);
            } while (id < 10000 || id > 99999);

            printf("Enter the arrival time of flight, which is excepted in 24-hours format only\n");
            do
            {
                printf("Enter the HRS of the arrival which has value between 0 and 23: ");
                scanf("%d", &arrival_hr);
            } while (arrival_hr < 0 || arrival_hr > 23);
            do
            {
                printf("Enter the MINS of the arrival which has value between 0 and 59: ");
                scanf("%d", &arrival_min);
            } while (arrival_min < 0 || arrival_min > 60);
            timeMaker(arrival, arrival_hr, arrival_min);

            key = keyMaker(id, arrival);

            if (linear_search_key(records_head, key)) //checking if record exits or not
            {
                printf("Enter the new status of the flight\n");
                do
                {
                    printf("This can be \"DELAY\" or \"ON_TIME\" or \"CANCELLED\" or \"PROMOTED\"\n");
                    scanf("%s", &status);
                } while (strcmp(status, "DELAY") != 0 && strcmp(status, "ON_TIME") != 0 && strcmp(status, "CANCELLED") != 0 && strcmp(status, "PROMOTED") != 0); //status can be of these things only

                if (strcmp(status, "DELAY") == 0)
                {
                    printf("Enter the delay time of flight, which is excepted in 24-hours format only\n");
                    do
                    {
                        printf("Enter the HRS of the delay which has value between 0 and 23: ");
                        scanf("%d", &delay_hr);
                    } while (delay_hr < 0 || delay_hr > 23);
                    do
                    {
                        printf("Enter the MINS of the delay which has value between 0 and 59: ");
                        scanf("%d", &delay_min);
                    } while (delay_min < 0 || delay_min > 60);

                    if (delay_hr == 0 && delay_min == 0) // Ensuring correct delay time
                    {
                        printf("Operation ended, no proper delay time given");
                    }
                    else
                    {
                        timeMaker(delay, delay_hr, delay_min);
                        /* Updating Everything */
                        if (UpdateFlightStatus(&records_head, name, key, status, delay, "\0"))
                        {
                            UpdateFlightStatus(&VVIP_records_head, name, key, status, delay, "\0");
                            UpdateFlightStatus(&VIP_records_head, name, key, status, delay, "\0");
                            UpdateFlightStatus(&public_records_head, name, key, status, delay, "\0");
                            printf("Operation Successful\n");
                        }
                        else
                            printf("Record does not exists\n");
                    }
                }
                else if (strcmp(status, "PROMOTED") == 0)
                {
                    Node *ptr = records_head;
                    found = 0;
                    while (ptr && !found)
                    {
                        if (ptr->key == key)
                            found = 1;
                        else
                            ptr = ptr->next;
                    }
                    printf("Enter the new class of flight. ");
                    do
                    {
                        printf("This can be \"VIP\" or \"VVIP\"\n");
                        scanf("%s", class);
                    } while (strcmp(class, "VIP") != 0 && strcmp(class, "VVIP") != 0);
                    if (strcmp(ptr->class, "VVIP") == 0) //Making sure it cant promoted further
                        printf("Already highest class exists, operation ended\n");
                    else
                    {
                        /* Updating Everything */
                        if (UpdateFlightStatus(&records_head, name, key, status, "\0", class))
                        {
                            delete (&VIP_records_head, key);
                            delete (&public_records_head, key);
                            if (strcmp(class, "VVIP") == 0)
                                insert(&VVIP_records_head, ptr->name, ptr->id, ptr->capacity, ptr->arrival, ptr->departure, ptr->class);
                            else
                                insert(&VIP_records_head, ptr->name, ptr->id, ptr->capacity, ptr->arrival, ptr->departure, ptr->class);
                            printf("Operation Successful\n");
                        }
                        else
                            printf("Record does not exists\n");
                    }
                }
                else // Cancelled or changed to On_Time {if record has been changed from delay, delay is passed as null}
                {
                    /* Updating Everything */
                    if (UpdateFlightStatus(&records_head, name, key, status, "\0", "\0"))
                    {
                        UpdateFlightStatus(&VIP_records_head, name, key, status, "\0", "\0");
                        UpdateFlightStatus(&VVIP_records_head, name, key, status, "\0", "\0");
                        UpdateFlightStatus(&public_records_head, name, key, status, "\0", "\0");
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
            displayRecord(records_head);
            break;
        default:
            printf("You have successfully exited");
            flag = 1;
        }
    } while (flag == 0);
    return 0;
}

/* Reversing a string */
void reverse(char str[])
{
    char temp;
    int i = 0;
    int len = strlen(str);
    while (i < len / 2)
    {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
        i++;
    }
}

/* This function helps in converting an integer (decimal) to string, taking a string and an integer which is needs to be converted. */
void integerToStringConverter(char str[], int num)
{
    int i = 0;
    if (num == 0) // Handle 0 explicitely, otherwise empty string is printed for 0
    {
        str[i++] = '0';
        str[i] = '\0';
    }
    while (num != 0)
    {
        int c = num % 10;
        str[i++] = c + '0';
        num = num / 10;
    }
    str[i] = '\0'; // Append string terminator
    reverse(str);  // Reverse the string  to get original integer in the form of the string
}

/* This function take number of hours and mins and thus convert and return proper string of the time in 24-HRS format returning value in HH:MM HRS */
void timeMaker(char time[], int hrs, int mins)
{
    char mm[2];
    char hh[1];
    if (hrs > 9)
        integerToStringConverter(time, hrs);
    else
    {
        integerToStringConverter(time, 0);
        integerToStringConverter(hh, hrs);
        strcat(time, hh);
    }
    strcat(time, ":");
    if (mins < 10)
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
    integerToStringConverter(a, id);
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

/* It returns the total number of the flight(s) present in the record. */
int getNumFlights(Node *records_head)
{
    int num;
    num = 0;
    while (records_head)
    {
        num++;
        records_head = records_head->next;
    }
    return num;
}

/* This simply check whether the record is empty or not by keeping track of the head node of linked list */
status_code isEmpty(Node *records_heads)
{
    status_code sc;
    if (!records_heads)
        sc = SUCCESS;
    else
        sc = FAILURE;
    return sc;
}

/* This simply check whether the record is full or not by keeping track of the tail node of linked list */
status_code isFull(Node *records_heads)
{
    status_code sc;
    if (getNumFlights(records_heads) == SIZE)
        sc = SUCCESS;
    else
        sc = FAILURE;
    return sc;
}

/* This function simply displays the existing record of the flights */
void displayRecord(Node *records_head)
{
    if (records_head)
    {
        printf("\n\nNAME ID CAPACITY ARRIVAL DEPARTURE CLASS STATUS DELAY\n\n");
        while (records_head)
        {
            printf("%s %d %d %s %s %s %s", records_head->name, records_head->id, records_head->capacity, records_head->arrival, records_head->departure, records_head->class, records_head->status);
            if (records_head->delay[0] != '\0')
                printf(" %s", records_head->delay);
            else
                printf(" --");
            printf("\n");
            records_head = records_head->next;
        }
        printf("\n");
    }
    else
        printf("\nNo records to DISPLAY\n");
}

/* This function simply displays the required field of the existing record. */
void displayFieldOfRecord(Node *nptr)
{
    if (nptr)
    {
        printf("\nNAME ID CAPACITY ARRIVAL DEPARTURE CLASS STATUS DELAY\n");
        printf("%s %d %d %s %s %s %s", nptr->name, nptr->id, nptr->capacity, nptr->arrival, nptr->departure, nptr->class, nptr->status);
        if (nptr->delay[0] != '\0')
            printf(" %s", nptr->delay);
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
    int diff_hr = abs(hr2 - hr1);    //if departure time is less signifying next day departure
    int diff_min = abs(min2 - min1); 
    timeMaker(stay, diff_hr, diff_min);
}

/* Return the pointer, pointing to the Node in the record with highest stay time. */
Node *getFlightWithtLongeststay(Node *records_head)
{
    Node *ptr = records_head;
    Node *nptr = NULL;
    char stayTime[TIME_LEN];
    char temp[TIME_LEN];
    if (ptr)
    {
        getStayTime(stayTime, ptr->arrival, ptr->departure);
        nptr = ptr;
        while (ptr)
        {
            getStayTime(temp, ptr->arrival, ptr->departure);
            if (strcmp(stayTime, temp) < 0)
            {
                strcpy(stayTime, temp);
                nptr = ptr;
            }
            ptr = ptr->next;
        }
    }
    return nptr;
}

/* Making a node and initilizing every element of the node to the value given by user */
Node *MakeNode(char name[], int id, int capacity, char arrival[], char departure[], char class[])
{
    Node *nptr;
    nptr = (Node *)malloc(sizeof(Node));
    strcpy(nptr->name, name);
    nptr->id = id;
    nptr->capacity = capacity;
    strcpy(nptr->arrival, arrival);
    strcpy(nptr->departure, departure);
    strcpy(nptr->status, "ON_TIME");
    nptr->delay[0] = '\0';
    strcpy(nptr->class, class);
    nptr->key = keyMaker(id, arrival);
    nptr->next = NULL;
    return nptr;
}

/* Searching a key from a record using linear search */
int linear_search_key(Node *records_heads, long key)
{
    int node_num = 0;
    int found = 0;
    int i = 0;
    while (records_heads && !found)
    {
        i++;
        if (records_heads->key == key)
        {
            node_num = i;
            found = 1;
        }
        else
            records_heads = records_heads->next;
    }
    return node_num;
}

/* Used in sorting (Helper Function) */
Node *Divide(Node *lptr)
{
    Node *slow, *fast, *prev;
    slow = fast = lptr;
    while (fast != NULL && fast->next != NULL)
    {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    prev->next = NULL;
    return slow;
}
/* Used in sorting (Helper Function) */
Node *Merge(Node *lptr, Node *nptr, int parameter)
{
    Node *head, *ptr;
    if (parameter == 0)
    {
        if (lptr->key > nptr->key)
        {
            head = nptr;
            nptr = nptr->next;
        }
        else
        {
            head = lptr;
            lptr = lptr->next;
        }
        ptr = head;
        while (nptr != NULL && lptr != NULL)
        {
            if (lptr->key > nptr->key)
            {
                ptr->next = nptr;
                nptr = nptr->next;
            }
            else
            {
                ptr->next = lptr;
                lptr = lptr->next;
            }
            ptr = ptr->next;
        }
        if (lptr != NULL)
            ptr->next = lptr;
        else
            ptr->next = nptr;
    }
    else if (parameter == 1)
    {
        if (strcmp(lptr->arrival, nptr->arrival) > 0)
        {
            head = nptr;
            nptr = nptr->next;
        }
        else
        {
            head = lptr;
            lptr = lptr->next;
        }
        ptr = head;
        while (nptr != NULL && lptr != NULL)
        {
            if (strcmp(lptr->arrival, nptr->arrival) > 0)
            {
                ptr->next = nptr;
                nptr = nptr->next;
            }
            else
            {
                ptr->next = lptr;
                lptr = lptr->next;
            }
            ptr = ptr->next;
        }
        if (lptr != NULL)
            ptr->next = lptr;
        else
            ptr->next = nptr;
    }
    else if (parameter == 2)
    {
        if (strcmp(lptr->departure, nptr->departure) > 0)
        {
            head = nptr;
            nptr = nptr->next;
        }
        else
        {
            head = lptr;
            lptr = lptr->next;
        }
        ptr = head;
        while (nptr != NULL && lptr != NULL)
        {
            if (strcmp(lptr->departure, nptr->departure) > 0)
            {
                ptr->next = nptr;
                nptr = nptr->next;
            }
            else
            {
                ptr->next = lptr;
                lptr = lptr->next;
            }
            ptr = ptr->next;
        }
        if (lptr != NULL)
            ptr->next = lptr;
        else
            ptr->next = nptr;
    }
    else
    {
        char temp1[TIME_LEN];
        char temp2[TIME_LEN];
        getStayTime(temp1, lptr->arrival, lptr->departure);
        getStayTime(temp2, nptr->arrival, nptr->departure);

        if (strcmp(temp1, temp2) > 0)
        {
            head = nptr;
            nptr = nptr->next;
        }
        else
        {
            head = lptr;
            lptr = lptr->next;
        }
        ptr = head;
        while (nptr != NULL && lptr != NULL)
        {
            getStayTime(temp1, lptr->arrival, lptr->departure);
            getStayTime(temp2, nptr->arrival, nptr->departure);
            if (strcmp(temp1, temp2) > 0)
            {
                ptr->next = nptr;
                nptr = nptr->next;
            }
            else
            {
                ptr->next = lptr;
                lptr = lptr->next;
            }
            ptr = ptr->next;
        }
        if (lptr != NULL)
            ptr->next = lptr;
        else
            ptr->next = nptr;
    }
    return head;
}

/* Sorting using mergesort */
Node *MergeSort(Node *lptr, int parameter)
{
    Node *nptr;
    if (lptr != NULL && lptr->next != NULL)
    {
        nptr = Divide(lptr);
        lptr = MergeSort(lptr, parameter);
        nptr = MergeSort(nptr, parameter);
        lptr = Merge(lptr, nptr, parameter);
    }
    return lptr;
}

/* Function which sorts the record on the basis of the key, using MergeSort. */
Node *getSortedOnKey(Node *records_head)
{
    Node *nptr;
    nptr = MergeSort(records_head, 0);
    return nptr;
}

/* Function which sorts the record on the basis of arrival time, using MergeSort. */
Node *getSortedOnArrivalTime(Node *records_head)
{
    Node *nptr;
    nptr = MergeSort(records_head, 1);
    return nptr;
}

/* Function which sorts the record on the basis of departure time, using MergeSort. */
Node *getSortedOnDepartureTime(Node *records_head)
{
    Node *nptr;
    nptr = MergeSort(records_head, 2);
    return nptr;
}

/* Function which sorts the record on the basis of departure time, using MergeSort. */
Node *getSortedOnStayTime(Node *records_head)
{
    Node *nptr;
    nptr = MergeSort(records_head, 3);
    return nptr;
}

/* This function takes key of the record which has to be deleted. */
status_code delete (Node **records_head_address, long key)
{
    status_code sc = SUCCESS;
    if (!(*records_head_address)) // List is Empty
        sc = FAILURE;
    else
    {
        Node *prev, *ptr;
        prev = NULL;
        ptr = *records_head_address;
        int found = 0;

        while (ptr && !found)
        {
            if (ptr->key == key)
                found = 1;
            else
            {
                prev = ptr;
                ptr = ptr->next;
            }
        }
        if (found)
        {
            if (!prev) // first node to be deleted
            {
                *records_head_address = ptr->next;
                free(ptr);
            }
            else
            {
                prev->next = ptr->next;
                free(ptr);
            }
        }
        else // given record by user is incorrect and cannot be found
            sc = FAILURE;
    }
    return sc;
}

/* Uniqueness should only be consider if we have two flights with same id and name which is possible when same model of particular flight is visiting airport more than once which is very much possible especially in domestic flights. In that case if any time has been delayed then it has be removed (For example a flight is coming in an at 3am and then again at 6pm on same day and lets say it is delayed for 6 hours so not able to come at 3pm. Now it is not possible for the flight to come at 6pm again and thus need to be removed. */

/* This will remove the delayed flight in the record as soon as it find any */
Node *listUnique(Node *records_head)
{
    Node *ptr = records_head;
    Node *duplicate_ptr;
    Node *prev, *prev2;
    prev2 = NULL;
    int found = 0;
    while (ptr->next && !found)
    {
        prev = ptr;
        duplicate_ptr = ptr->next;
        while (duplicate_ptr && !found)
        {
            if (strcmp(ptr->name, duplicate_ptr->name) == 0 && (ptr->id - duplicate_ptr->id == 0) && (strcmp(ptr->status, "DELAY") == 0 || strcmp(duplicate_ptr->status, "DELAY") == 0))
                found = 1;
            else
            {
                prev = duplicate_ptr;
                duplicate_ptr = duplicate_ptr->next;
            }
        }
        if (!found)
        {
            prev2 = ptr;
            ptr = ptr->next;
        }
    }
    if (found)
    {
        if (strcmp(ptr->status, "DELAY") == 0 && strcmp(duplicate_ptr->status, "DELAY") == 0)
        {
            if (strcmp(ptr->delay, duplicate_ptr->delay) >= 0)
            {
                if (ptr == records_head) // the node to be removed is the head node
                    records_head = ptr->next;
                else
                    prev2->next = ptr->next;
                free(ptr);
            }
            else
            {
                prev->next = duplicate_ptr->next;
                free(duplicate_ptr);
            }
        }
        else if (strcmp(ptr->status, "DELAY") == 0)
        {
            if (ptr == records_head) // the node to be removed is the head node
                records_head = ptr->next;
            else
                prev2->next = ptr->next;
            free(ptr);
        }
        else
        {
            prev->next = duplicate_ptr->next;
            free(duplicate_ptr);
        }
    }
    return records_head;
}

/* Inserts new record in the file or update the old record if reinserted */
int insert(Node **records_head_address, char name[], int id, int capacity, char arrival[], char departure[], char class[])
{
    status_code sc = SUCCESS;
    Node *records_head = *records_head_address;
    long given_key = keyMaker(id, arrival);
    int node_index = linear_search_key(records_head, given_key);
    Node *ptr = records_head;
    if (node_index) // if the key is old one
    {
        int i = 1;
        while (ptr && i < node_index)
        {
            ptr = ptr->next;
            i++;
        }
        strcpy(ptr->name, name);
        ptr->capacity = capacity;
        strcpy(ptr->departure, departure);
        strcpy(ptr->status, "ON_TIME");
        strcpy(ptr->class, class);
    }
    else if (isFull(*records_head_address) == SUCCESS)
        sc = FAILURE;
    else
    {
        if (!records_head)
        {
            Node *nptr;
            nptr = MakeNode(name, id, capacity, arrival, departure, class);
            if (!nptr)
                sc = FAILURE;
            else
                *records_head_address = nptr;
        }
        else
        {
            Node *nptr;
            nptr = MakeNode(name, id, capacity, arrival, departure, class);
            if (!nptr)
                sc = FAILURE;
            else
            {
                while (ptr->next != NULL)
                    ptr = ptr->next;
                ptr->next = nptr;
            }
            *records_head_address = getSortedOnKey(records_head); // maintaing sorted order
            *records_head_address = listUnique(*records_head_address); // If record entered found with any duplicacy
        }
    }
    return sc;
}

/* Update the current status of the flight */
status_code UpdateFlightStatus(Node **records_head_address, char name[], long key, char status[], char delay[], char class[])
{
    status_code sc = SUCCESS;
    if (isEmpty(*records_head_address))
        sc = FAILURE;
    else
    {
        Node *ptr = *records_head_address;
        int found = 0;
        while (ptr && !found)
        {
            if (ptr->key == key && strcmp(ptr->name, name) == 0)
                found = 1;
            else
                ptr = ptr->next;
        }
        if (found)
        {
            strcpy(ptr->status, status);
            if (strcmp(status, "DELAY") == 0)
                strcpy(ptr->delay, delay);
            else if (strcmp(status, "PROMOTED") == 0)
                strcpy(ptr->class, class);
            *records_head_address = listUnique(*records_head_address); // If record updated found with any duplicacy
        }
        else // If the record entered by user is incorrect
            sc = FAILURE;
    }
    return sc;
}
	/*edit*/

/*custom header*/
#include <stdio.h>
#include <string.h>
#define MAX_ROOM 5
#define MAX_NAME_CHAR 20
#define strcasecmp _stricmp
	/*end_edit*/
	/*edit*/
/* Write your code here */

void listOccupiedRooms(void);
void assignRoom(void);
void removeRoom(void);
void findCustomer(void);
_Bool isRoomsOccupied(_Bool);
void getInt(int*);

typedef struct
{
 int roomID;
 _Bool status;
 char customerName[MAX_NAME_CHAR];
} Room;

Room rooms[MAX_ROOM];

int main(void) {
    Room* room;
    int notQuit = 1;
    int choose;
    int i;
    for (i = 0; i < MAX_ROOM;) {
        room = rooms + i;
        room->roomID = ++i;
        room->status = 0;
    }
    puts("NTU HOTEL ROOM RESERVATION PROGRAM:\n1: listOccupiedRooms()\n2: assignRoom()\n3: removeRoom()\n4: findCustomer()\n5: quit");
    while(notQuit) {
        fputs("Enter your choice: ", stdout);
        getInt(&choose);
        switch(choose) {
            case 1:
                listOccupiedRooms();
                break;
            case 2:
                assignRoom();
                break;
            case 3:
                removeRoom();
                break;
            case 4:
                findCustomer();
                break;
            case 5:
                notQuit = 0;
                break;
        }
    }
    return 0;
}

void listOccupiedRooms(void){
    int isNoOccupiedRooms = 1;
    int i;
    Room* room;
    puts("listOccupiedRooms():");
    for (i = 0; i < MAX_ROOM; ++i) {
        room = rooms + i;
        if (room->status) {
            isNoOccupiedRooms = 0;
            printf("roomID: %d\ncustomer name: %s\n", room->roomID, room->customerName);
        }
    }
    if (isNoOccupiedRooms) {
        puts("The hotel is empty");
    }
}

void assignRoom(void) {
    int roomID;
    Room* room;
    puts("assignRoom():");
    if (isRoomsOccupied(0)) {
        puts("The hotel is full");
        return;
    }
    while (1) {
        printf("Enter a roomID between 1 and %d: ", MAX_ROOM);
        getInt(&roomID);
        if (roomID > 0 && roomID <= MAX_ROOM) {
            room = rooms + roomID - 1;
            if (room->status) {
                puts("Occupied! Enter another roomID");
            } else {
                fputs("Enter customer name: ", stdout);
                if (scanf_s(" %[^\n]s", room->customerName, MAX_NAME_CHAR)) {
                    putchar('\n');
                    room->status = 1;
                    puts("The room has been assigned successfully");
                }
                break;
            }
        }
        
        
    }
}

void removeRoom(void) {
    puts("removeRoom():");

    if (!isRoomsOccupied(1)) {
        puts("All the rooms are empty");
        return;
    }

    while (1) {
        int roomID;
        Room* room;
        printf("Enter a roomID between 1 and %d: ", MAX_ROOM);
        getInt(&roomID);
        if (roomID > 0 && roomID <= MAX_ROOM) {
            room = rooms + roomID - 1;
            if (room->status) {
                memset(room->customerName, 0, MAX_NAME_CHAR);
                room->status = 0;
                puts("Removal is successful");
                return;
            } else {
                puts("Empty! Enter another roomID for removal");

            }
        }
        
    }
}

void findCustomer(void) {
    char customerName[MAX_NAME_CHAR];
    Room* room;
    int i;
    _Bool isNotFound = 1;
    fputs("findCustomer():\nEnter customer name:", stdout);
    if (scanf_s(" %[^\n]s", customerName, MAX_NAME_CHAR)) {
        putchar('\n');
        for (i = 0; i < MAX_ROOM; ++i) {
            room = rooms + i;
            if (!strcasecmp(room->customerName, customerName)) {
                printf("The target customer name is found\nroomID: %d\ncustomer name: %s\n", room->roomID, room->customerName);
                isNotFound = 0;
                break;
            }
        }
    }
  
    if (isNotFound) {
        puts("The target customer name is not found");
    }
}


void getInt(int* intput) {
    if (scanf_s("%d", intput)) {
        putchar('\n');
    }
    else {
        /*just in cast if the user key in anything other then number*/
        scanf_s("%*[^\n]%*c");
    };
}

_Bool isRoomsOccupied(_Bool occupied/* if true break after the occupied room else break after the first empty room*/) {
    int status;
    int i;
    for (i = 0; i < MAX_ROOM; ++i) {
        status = rooms[i].status;
        if (occupied == status) {
            return status;
        }
    }
    return status;
}
	/*end_edit*/
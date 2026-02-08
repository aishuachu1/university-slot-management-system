#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#define DAYS 5
#define SLOTS 8

int compareIgnoreCase(char a[], char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (tolower(a[i]) != tolower(b[i]))
            return 0;
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0')
        return 1;
    return 0;
}

char *dayNames[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

char *timeSlots[SLOTS] = {
    "8:50 - 9:40",
    "9:40 - 10:30",
    "10:45 - 11:30",
    "11:30 - 12:30",
    "1:15 - 2:05",
    "2:05 - 2:55",
    "2:55 - 3:45",
    "3:45 - 4:30"
};


char *timetable[DAYS][SLOTS] = {
    {"FREE", "Linear Algebra", "Python Programming", "Probability theory and Estimation",
     "Optimization Techniques", "Data Structures", "Data Structures", "CIR"},
    {"Python Programming", "FREE", "R Programming", "Probability theory and Estimation",
     "Linear Algebra", "Linear Algebra", "Optimization Techniques", "Data Structures"},
    {"Data Structures", "Linear Algebra", "R Programming", "Probability theory and Estimation",
     "Optimization Techniques", "FREE", "Python Programming", "Python Programming"},
    {"Optimization Techniques", "FREE", "R Programming", "R Programming",
     "Data Structures", "Python Programming", "FREE", "CIR"},
    {"R Programming", "Linear Algebra", "Probability theory and Estimation",
     "Probability theory and Estimation", "FREE", "FREE", "CIR", "FREE"}
};

void showTimetable(int dayIndex) {
    int i;
    printf("\nTimetable for %s:\n", dayNames[dayIndex]);
    for (i = 0; i < SLOTS; i++)
        printf("Slot %2d (%s): %s\n", i + 1, timeSlots[i], timetable[dayIndex][i]);
}


void showFreeSlots(int dayIndex) {
    int i, found = 0;
    printf("\nFree Slots on %s:\n", dayNames[dayIndex]);
    for (i = 0; i < SLOTS; i++) {
        if (compareIgnoreCase(timetable[dayIndex][i], "FREE")) {
            printf("Slot %2d (%s)\n", i + 1, timeSlots[i]);
            found = 1;
        }
    }
    if (!found)
        printf("No free slots available.\n");
}


void bookSlot(int dayIndex, int slot, char subject[], char date[]) {
    if (compareIgnoreCase(timetable[dayIndex][slot - 1], "FREE")) {
        timetable[dayIndex][slot - 1] = strdup(subject);  
        printf("\nSlot %d booked successfully for '%s' on %s!\n", slot, subject, date);
    } else {
        printf("\nSlot already occupied!\n");
    }
}

void cancelSlot(int dayIndex, int slot) {
    timetable[dayIndex][slot - 1] = "FREE";
    printf("\nSlot %d has been cancelled and marked as FREE.\n", slot);
}

void main() {
    char day[20], date[20], subject[30];
    int dayIndex = -1, choice, slot, i;

    clrscr();

    printf("Enter Day (e.g., Monday): ");
    scanf("%s", day);
    printf("Enter Date (DD/MM/YYYY): ");
    scanf("%s", date);

    // find day index
    for (i = 0; i < DAYS; i++) {
        if (compareIgnoreCase(day, dayNames[i])) {
            dayIndex = i;
            break;
        }
    }

    if (dayIndex == -1) {
        printf("Invalid day entered!\n");
        getch();
        return;
    }

    while (1) {
        clrscr();
        printf("--- Timetable Management (Batch A) ---\n");
        printf("1. Show Timetable\n");
        printf("2. Show Free Slots\n");
        printf("3. Book a Slot\n");
        printf("4. Cancel a Slot\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                clrscr();
                showTimetable(dayIndex);
                break;
            case 2:
                clrscr();
                showFreeSlots(dayIndex);
                break;
            case 3:
                clrscr();
                showFreeSlots(dayIndex);
                printf("\nEnter Slot number to book: ");
                scanf("%d", &slot);
                if (slot < 1 || slot > SLOTS) {
                    printf("Invalid slot number!\n");
                    break;
                }
                printf("Enter Subject name: ");
                scanf("%s", subject);
                bookSlot(dayIndex, slot, subject, date);
                break;
            case 4:
                clrscr();
                showTimetable(dayIndex);
                printf("\nEnter Slot number to cancel: ");
                scanf("%d", &slot);
                if (slot < 1 || slot > SLOTS) {
                    printf("Invalid slot number!\n");
                    break;
                }
                cancelSlot(dayIndex, slot);
                break;
            case 5:
                printf("Exiting program...\n");
                getch();
                return;
            default:
                printf("Invalid choice! Try again.\n");
        }
        printf("\nPress any key to continue...");
        getch();
    }
}

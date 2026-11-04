#include <stdio.h>
#define ROWS 5
#define COLS 8

void initializeSeats(int seats[ROWS][COLS]);
void displaySeats(int seats[ROWS][COLS]);
int bookSeat(int seats[ROWS][COLS], int row, int col);
int cancelSeat(int seats[ROWS][COLS], int row, int col);
int reserveGroup(int seats[ROWS][COLS], int groupSize);
void displayReport(int seats[ROWS][COLS]);

int main() {
    int seats[ROWS][COLS];
    int choice, row, col, groupSize;

    initializeSeats(seats);
    printf("=== SEATSMART - Auditorium Management ===\n");

    while (1) {
        printf("\n----- MENU -----\n");
        printf("1. Display seats\n");
        printf("2. Book one seat\n");
        printf("3. Cancel booking\n");
        printf("4. Group reservation\n");
        printf("5. Occupancy report\n");
        printf("6. Exit\n");
        printf("Enter your choice (1-6): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Enter number 1-6.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                displaySeats(seats);
                break;
            case 2:
                printf("Enter row (1-5): ");
                scanf("%d", &row);
                printf("Enter seat (1-8): ");
                scanf("%d", &col);
                if (bookSeat(seats, row, col)) {
                    displaySeats(seats);
                }
                break;
            case 3:
                printf("Enter row (1-5): ");
                scanf("%d", &row);
                printf("Enter seat (1-8): ");
                scanf("%d", &col);
                if (cancelSeat(seats, row, col)) {
                    displaySeats(seats);
                }
                break;
            case 4:
                printf("Enter group size (2-8): ");
                scanf("%d", &groupSize);
                if (reserveGroup(seats, groupSize)) {
                    displaySeats(seats);
                }
                break;
            case 5:
                displayReport(seats);
                break;
            case 6:
                printf("Thank you for using SEATSMART. Exiting...\n");
                return 0;
            default:
                printf("Invalid menu choice! Please enter 1-6.\n");
        }
    }
}

void initializeSeats(int seats[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            seats[i][j] = 0;
}

void displaySeats(int seats[ROWS][COLS]) {
    printf("\nSeating Arrangement [0=Available, 1=Booked]\n");
    printf("      1 2 3 4 5 6 7 8\n");
    for (int i = 0; i < ROWS; i++) {
        printf("Row %d: ", i + 1);
        for (int j = 0; j < COLS; j++) {
            printf("%d ", seats[i][j]);
        }
        printf("\n");
    }
    printf("Legend: 0 = Available, 1 = Booked\n");
}

int bookSeat(int seats[ROWS][COLS], int row, int col) {
    if (row < 1 || row > ROWS || col < 1 || col > COLS) {
        printf("Invalid row/seat number! Row must be 1-5, Seat 1-8.\n");
        return 0;
    }
    int r = row - 1, c = col - 1;
    if (seats[r][c] == 1) {
        printf("Seat Row %d Seat %d is already booked! Cannot book.\n", row, col);
        return 0;
    }
    seats[r][c] = 1;
    printf("Successfully booked Row %d Seat %d.\n", row, col);
    return 1;
}

int cancelSeat(int seats[ROWS][COLS], int row, int col) {
    if (row < 1 || row > ROWS || col < 1 || col > COLS) {
        printf("Invalid row/seat number! Row must be 1-5, Seat 1-8.\n");
        return 0;
    }
    int r = row - 1, c = col - 1;
    if (seats[r][c] == 0) {
        printf("Seat Row %d Seat %d is already free! Cannot cancel.\n", row, col);
        return 0;
    }
    seats[r][c] = 0;
    printf("Successfully cancelled Row %d Seat %d.\n", row, col);
    return 1;
}

int reserveGroup(int seats[ROWS][COLS], int groupSize) {
    if (groupSize < 2 || groupSize > 8) {
        printf("Invalid group size! Must be 2-8.\n");
        return 0;
    }
    for (int i = 0; i < ROWS; i++) {
        for (int start = 0; start <= COLS - groupSize; start++) {
            int available = 1;
            for (int k = 0; k < groupSize; k++) {
                if (seats[i][start + k] == 1) {
                    available = 0;
                    break;
                }
            }
            if (available) {
                for (int k = 0; k < groupSize; k++) {
                    seats[i][start + k] = 1;
                }
                printf("Group of %d seats reserved successfully at Row %d, Seats %d to %d.\n",
                       groupSize, i + 1, start + 1, start + groupSize);
                return 1;
            }
        }
    }
    printf("No consecutive block of %d seats available in any row. Reservation failed.\n", groupSize);
    return 0;
}

void displayReport(int seats[ROWS][COLS]) {
    int booked = 0;
    int rowCount[ROWS] = {0};
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (seats[i][j] == 1) {
                booked++;
                rowCount[i]++;
            }
        }
    }
    int total = ROWS * COLS;
    int free = total - booked;
    float percent = (booked * 100.0) / total;

    printf("\n--- Occupancy Report ---\n");
    printf("Booked seats: %d\n", booked);
    printf("Available seats: %d\n", free);
    printf("Occupancy: %.2f%%\n", percent);

    int max = rowCount[0];
    for (int i = 1; i < ROWS; i++) if (rowCount[i] > max) max = rowCount[i];

    printf("Busiest row(s) with %d bookings: ", max);
    for (int i = 0; i < ROWS; i++) if (rowCount[i] == max) printf("Row %d ", i + 1);
    printf("\n");
}

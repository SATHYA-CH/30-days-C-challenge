#include <stdio.h>

#define ZONES 5
#define DAYS 7

/* Mandatory Function Prototypes */
void inputWaterData(int usage[ZONES][DAYS], int dailyTarget[ZONES]);
void displayWaterData(int usage[ZONES][DAYS], int dailyTarget[ZONES]);
void calculateZoneStats(int *zoneUsage, int *total, float *average, int *peakUsage, int *peakDay);
void detectWaterAlerts(int *zoneUsage, int dailyTarget, int *overLimitDays, int *totalExcess, int *spikeDays, int *alertDays);
void generateAuditReport(int usage[ZONES][DAYS], int dailyTarget[ZONES], int excessByZone[ZONES], int overLimitByZone[ZONES], int spikeByZone[ZONES], int alertByZone[ZONES]);
void rankZones(int excessByZone[ZONES]);
void displayConservationActions(int overLimitByZone[ZONES], int spikeByZone[ZONES], int excessByZone[ZONES]);

void printZoneName(int zoneIndex) {
    if (zoneIndex == 0) {
        printf("Academic Block");
    } else if (zoneIndex == 1) {
        printf("Hostel        ");
    } else if (zoneIndex == 2) {
        printf("Library       ");
    } else if (zoneIndex == 3) {
        printf("Cafeteria     ");
    } else if (zoneIndex == 4) {
        printf("Sports Complex");
    }
}

/* Main function explicitly taking no arguments */
int main(void) {
    int usage[ZONES][DAYS];
    int dailyTarget[ZONES];
    int excessByZone[ZONES] = {0};
    int overLimitByZone[ZONES] = {0};
    int spikeByZone[ZONES] = {0};
    int alertByZone[ZONES] = {0};

    int choice;
    int auditGenerated = 0;

    printf("====================================================================\n");
    printf("               WATERWISE - CAMPUS WATER AUDIT SYSTEM                \n");
    printf("                     Track. Detect. Conserve.                       \n");
    printf("====================================================================\n");

    inputWaterData(usage, dailyTarget);

    do {
        printf("\n--------------------------------------------------------------------\n");
        printf("PROGRAM MENU:\n");
        printf("1. Display Water Data\n");
        printf("2. Generate Audit Report\n");
        printf("3. Rank Zones by Excess\n");
        printf("4. Conservation Actions\n");
        printf("5. Exit\n");
        printf("--------------------------------------------------------------------\n");
        printf("Enter your choice (1-5): ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input! Please enter a number between 1 and 5.\n");
            continue;
        }

        if (choice == 1) {
            displayWaterData(usage, dailyTarget);
        } else if (choice == 2) {
            generateAuditReport(usage, dailyTarget, excessByZone, overLimitByZone, spikeByZone, alertByZone);
            auditGenerated = 1;
        } else if (choice == 3) {
            if (auditGenerated == 0) {
                printf("\n[!] Please generate the Audit Report first (Select Option 2).\n");
            } else {
                rankZones(excessByZone);
            }
        } else if (choice == 4) {
            if (auditGenerated == 0) {
                printf("\n[!] Please generate the Audit Report first (Select Option 2).\n");
            } else {
                displayConservationActions(overLimitByZone, spikeByZone, excessByZone);
            }
        } else if (choice == 5) {
            printf("\nExiting WATERWISE. Thank you for conserving water!\n");
        } else {
            printf("\n[!] Invalid menu choice! Please enter a number from 1 to 5.\n");
        }

    } while (choice != 5);

    return 0;
}

void inputWaterData(int usage[ZONES][DAYS], int dailyTarget[ZONES]) {
    int z, d;

    printf("\n--- ENTER SIMULATED/AUTHORISED WATER CONSUMPTION DATA (IN LITRES) ---\n");
    for (z = 0; z < ZONES; z++) {
        printf("\nZone %d: ", z + 1);
        printZoneName(z);
        printf("\n");

        do {
            printf("  Enter Daily Target (100 - 50000 L): ");
            if (scanf("%d", &dailyTarget[z]) != 1) {
                while (getchar() != '\n');
                dailyTarget[z] = -1;
            }
            if (dailyTarget[z] < 100 || dailyTarget[z] > 50000) {
                printf("  [Error] Invalid target! Must be between 100 and 50,000 litres.\n");
            }
        } while (dailyTarget[z] < 100 || dailyTarget[z] > 50000);

        for (d = 0; d < DAYS; d++) {
            do {
                printf("  Day %d Consumption (0 - 50000 L): ", d + 1);
                if (scanf("%d", &usage[z][d]) != 1) {
                    while (getchar() != '\n');
                    usage[z][d] = -1;
                }
                if (usage[z][d] < 0 || usage[z][d] > 50000) {
                    printf("  [Error] Invalid reading! Must be between 0 and 50,000 litres.\n");
                }
            } while (usage[z][d] < 0 || usage[z][d] > 50000);
        }
    }
}

void displayWaterData(int usage[ZONES][DAYS], int dailyTarget[ZONES]) {
    int z, d;

    printf("\n==========================================================================================\n");
    printf("                          WEEKLY WATER CONSUMPTION MATRIX (LITRES)                        \n");
    printf("==========================================================================================\n");
    printf("Zone Name      |   Day 1   Day 2   Day 3   Day 4   Day 5   Day 6   Day 7 | Daily Target\n");
    printf("------------------------------------------------------------------------------------------\n");

    for (z = 0; z < ZONES; z++) {
        printZoneName(z);
        printf(" | ");
        for (d = 0; d < DAYS; d++) {
            printf("%7d ", usage[z][d]);
        }
        printf("| %10d L\n", dailyTarget[z]);
    }
    printf("==========================================================================================\n");
}

void calculateZoneStats(int *zoneUsage, int *total, float *average, int *peakUsage, int *peakDay) {
    int day;
    int sum = 0;
    int maxVal = *(zoneUsage + 0);
    int maxDay = 1;

    for (day = 0; day < DAYS; day++) {
        int currentVal = *(zoneUsage + day);
        sum += currentVal;

        if (currentVal > maxVal) {
            maxVal = currentVal;
            maxDay = day + 1;
        }
    }

    *total = sum;
    *average = (float)sum / DAYS;
    *peakUsage = maxVal;
    *peakDay = maxDay;
}

void detectWaterAlerts(int *zoneUsage, int dailyTarget, int *overLimitDays, int *totalExcess, int *spikeDays, int *alertDays) {
    int day;
    int overCount = 0;
    int excessSum = 0;
    int spikeCount = 0;
    int uniqueAlerts = 0;

    for (day = 0; day < DAYS; day++) {
        int current = *(zoneUsage + day);
        int isOver = 0;
        int isSpike = 0;

        if (current > dailyTarget) {
            isOver = 1;
            overCount++;
            excessSum += (current - dailyTarget);
        }

        if (day > 0) {
            int prev = *(zoneUsage + (day - 1));
            if ((long)current * 100 > (long)prev * 140) {
                isSpike = 1;
                spikeCount++;
            }
        }

        if (isOver == 1 || isSpike == 1) {
            uniqueAlerts++;
        }
    }

    *overLimitDays = overCount;
    *totalExcess = excessSum;
    *spikeDays = spikeCount;
    *alertDays = uniqueAlerts;
}

void generateAuditReport(int usage[ZONES][DAYS], int dailyTarget[ZONES], int excessByZone[ZONES], int overLimitByZone[ZONES], int spikeByZone[ZONES], int alertByZone[ZONES]) {
    int z;
    int total, peakUsage, peakDay;
    float average;
    int maxExcess = -1;

    printf("\n=========================================================================================================\n");
    printf("                                        CAMPUS WATER AUDIT REPORT                                        \n");
    printf("=========================================================================================================\n");
    printf("Zone Name      |   Total (L) |   Avg (L) | Peak (Day) | Over-Limit | Excess (L) | Spikes | Unique Alerts\n");
    printf("---------------------------------------------------------------------------------------------------------\n");

    for (z = 0; z < ZONES; z++) {
        calculateZoneStats(&usage[z][0], &total, &average, &peakUsage, &peakDay);
        detectWaterAlerts(&usage[z][0], dailyTarget[z], &overLimitByZone[z], &excessByZone[z], &spikeByZone[z], &alertByZone[z]);

        printZoneName(z);
        printf(" | %11d | %9.2f | %6d (D%d) | %10d | %10d | %6d | %13d\n",
               total, average, peakUsage, peakDay,
               overLimitByZone[z], excessByZone[z], spikeByZone[z], alertByZone[z]);

        if (excessByZone[z] > maxExcess) {
            maxExcess = excessByZone[z];
        }
    }
    printf("=========================================================================================================\n");

    printf("Highest Excess Consumption (%d L): ", maxExcess);
    int first = 1;
    for (z = 0; z < ZONES; z++) {
        if (excessByZone[z] == maxExcess) {
            if (!first) {
                printf(", ");
            }
            if (z == 0) {
                printf("Academic Block");
            } else if (z == 1) {
                printf("Hostel");
            } else if (z == 2) {
                printf("Library");
            } else if (z == 3) {
                printf("Cafeteria");
            } else if (z == 4) {
                printf("Sports Complex");
            }
            first = 0;
        }
    }
    printf("\n");
}

void rankZones(int excessByZone[ZONES]) {
    int indices[ZONES] = {0, 1, 2, 3, 4};
    int i, j, temp;

    for (i = 0; i < ZONES - 1; i++) {
        for (j = 0; j < ZONES - i - 1; j++) {
            if (excessByZone[indices[j]] < excessByZone[indices[j + 1]]) {
                temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }

    printf("\n========================================================\n");
    printf("          ZONE RANKING BY TOTAL EXCESS LITRES           \n");
    printf("========================================================\n");
    printf("Rank | Zone Name      | Total Excess (L)\n");
    printf("--------------------------------------------------------\n");

    int currentRank = 1;
    for (i = 0; i < ZONES; i++) {
        if (i > 0 && excessByZone[indices[i]] < excessByZone[indices[i - 1]]) {
            currentRank = i + 1;
        }

        printf("%4d | ", currentRank);
        printZoneName(indices[i]);
        printf(" | %14d L\n", excessByZone[indices[i]]);
    }
    printf("========================================================\n");
}

void displayConservationActions(int overLimitByZone[ZONES], int spikeByZone[ZONES], int excessByZone[ZONES]) {
    int z;

    printf("\n====================================================================\n");
    printf("                 WATER CONSERVATION RECOMMENDATIONS                 \n");
    printf("====================================================================\n");

    for (z = 0; z < ZONES; z++) {
        int over = overLimitByZone[z];
        int spike = spikeByZone[z];
        int hasAction = 0;

        printf("\nZone %d: ", z + 1);
        printZoneName(z);
        printf(" (Total Excess: %d L)\n", excessByZone[z]);

        if (spike > 0) {
            printf("  - [Spike Alert] Check for a leak or unexpected use around the flagged days.\n");
            hasAction = 1;
        }
        if (over >= 3) {
            printf("  - [High Over-Limit] Prioritise a water audit and reduction plan.\n");
            hasAction = 1;
        } else if (over == 1 || over == 2) {
            printf("  - [Moderate Over-Limit] Monitor those days and inspect taps or valves.\n");
            hasAction = 1;
        }
        if (hasAction == 0) {
            printf("  - [Optimal Usage] Maintain current good practices.\n");
        }
    }
    printf("\n====================================================================\n");
}

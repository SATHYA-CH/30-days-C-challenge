#include <stdio.h>

#define ZONES 5
#define DAYS 7

void inputData(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS]);
void displayData(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS]);
void calculateAverages(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS], float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES]);
void detectRiskZones(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS], int riskDays[ZONES]);
void computeGreenIndex(float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES], float greenIndex[ZONES]);
void displayRanking(float greenIndex[ZONES]);
void displayRecommendations(float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES], int riskDays[ZONES]);
void printZoneName(int zone);
void displayAverages(float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES]);
float absoluteValue(float x);
float makeZeroIfNegative(float x);

int main()
{
    float temp[ZONES][DAYS];
    float humidity[ZONES][DAYS];
    int aqi[ZONES][DAYS];
    float avgTemp[ZONES];
    float avgHumidity[ZONES];
    float avgAQI[ZONES];
    float greenIndex[ZONES];
    int riskDays[ZONES];
    int choice;
    int dataReady = 0;

    printf("ECOGUARD - Campus Monitor\n");
    printf("Note: values you type are SIMULATED data, not real measurements.\n");

    while (1)
    {
        printf("\nMENU\n");
        printf("1. Input / Update Data\n");
        printf("2. Display Data\n");
        printf("3. Zone-wise Averages\n");
        printf("4. Detect Risk Days\n");
        printf("5. Green Index and Ranking\n");
        printf("6. Recommendations\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 7)
        {
            printf("Thank you for using ECOGUARD. Goodbye!\n");
            break;
        }
        if (choice < 1 || choice > 7)
        {
            printf("Invalid choice! Please enter 1 to 7.\n");
            continue;
        }
        if (dataReady == 0 && choice != 1)
        {
            printf("No data yet! Please choose option 1 first.\n");
            continue;
        }
        if (choice == 1)
        {
            inputData(temp, humidity, aqi);
            dataReady = 1;
        }
        if (choice == 2)
        {
            displayData(temp, humidity, aqi);
        }
        if (choice == 3)
        {
            calculateAverages(temp, humidity, aqi, avgTemp, avgHumidity, avgAQI);
            displayAverages(avgTemp, avgHumidity, avgAQI);
        }
        if (choice == 4)
        {
            detectRiskZones(temp, humidity, aqi, riskDays);
        }
        if (choice == 5)
        {
            calculateAverages(temp, humidity, aqi, avgTemp, avgHumidity, avgAQI);
            computeGreenIndex(avgTemp, avgHumidity, avgAQI, greenIndex);
            displayRanking(greenIndex);
        }
        if (choice == 6)
        {
            calculateAverages(temp, humidity, aqi, avgTemp, avgHumidity, avgAQI);
            detectRiskZones(temp, humidity, aqi, riskDays);
            displayRecommendations(avgTemp, avgHumidity, avgAQI, riskDays);
        }
    }
    return 0;
}

void printZoneName(int zone)
{
    if (zone == 0)
        printf("Academic Block");
    if (zone == 1)
        printf("Hostel");
    if (zone == 2)
        printf("Library");
    if (zone == 3)
        printf("Cafeteria");
    if (zone == 4)
        printf("Sports Area");
}

float absoluteValue(float x)
{
    if (x < 0)
        return -x;
    else
        return x;
}

float makeZeroIfNegative(float x)
{
    if (x < 0)
        return 0;
    else
        return x;
}

void inputData(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS])
{
    int i, j;
    printf("\nEnter readings for 5 zones, 7 days\n");
    printf("Temperature: 10 to 50 | Humidity: 0 to 100 | AQI: 0 to 500\n");

    for (i = 0; i < ZONES; i++)
    {
        printf("\nZone %d: ", i + 1);
        printZoneName(i);
        printf("\n");
        for (j = 0; j < DAYS; j++)
        {
            printf("\nDay %d\n", j + 1);

            printf("Temperature (10-50): ");
            scanf("%f", &temp[i][j]);
            while (temp[i][j] < 10 || temp[i][j] > 50)
            {
                printf("Invalid! Enter again (10-50): ");
                scanf("%f", &temp[i][j]);
            }

            printf("Humidity (0-100): ");
            scanf("%f", &humidity[i][j]);
            while (humidity[i][j] < 0 || humidity[i][j] > 100)
            {
                printf("Invalid! Enter again (0-100): ");
                scanf("%f", &humidity[i][j]);
            }

            printf("AQI (0-500): ");
            scanf("%d", &aqi[i][j]);
            while (aqi[i][j] < 0 || aqi[i][j] > 500)
            {
                printf("Invalid! Enter again (0-500): ");
                scanf("%d", &aqi[i][j]);
            }
        }
    }
    printf("\nAll data saved successfully!\n");
}

void displayData(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS])
{
    int i, j;
    printf("\nTEMPERATURE\n");
    for (i = 0; i < ZONES; i++)
    {
        printf("Zone %d ", i + 1);
        printZoneName(i);
        printf(": ");
        for (j = 0; j < DAYS; j++)
            printf("%.1f ", temp[i][j]);
        printf("\n");
    }
    printf("\nHUMIDITY\n");
    for (i = 0; i < ZONES; i++)
    {
        printf("Zone %d ", i + 1);
        printZoneName(i);
        printf(": ");
        for (j = 0; j < DAYS; j++)
            printf("%.1f ", humidity[i][j]);
        printf("\n");
    }
    printf("\nAQI\n");
    for (i = 0; i < ZONES; i++)
    {
        printf("Zone %d ", i + 1);
        printZoneName(i);
        printf(": ");
        for (j = 0; j < DAYS; j++)
            printf("%d ", aqi[i][j]);
        printf("\n");
    }
}

void calculateAverages(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS], float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES])
{
    int i, j;
    float sumT, sumH, sumA;
    for (i = 0; i < ZONES; i++)
    {
        sumT = 0;
        sumH = 0;
        sumA = 0;
        for (j = 0; j < DAYS; j++)
        {
            sumT = sumT + temp[i][j];
            sumH = sumH + humidity[i][j];
            sumA = sumA + aqi[i][j];
        }
        avgTemp[i] = sumT / 7;
        avgHumidity[i] = sumH / 7;
        avgAQI[i] = sumA / 7;
    }
}

void displayAverages(float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES])
{
    int i;
    printf("\nZONE-WISE AVERAGES\n");
    for (i = 0; i < ZONES; i++)
    {
        printf("Zone %d ", i + 1);
        printZoneName(i);
        printf(" - Avg Temp: %.2f, Avg Humidity: %.2f, Avg AQI: %.2f\n", avgTemp[i], avgHumidity[i], avgAQI[i]);
    }
}

void detectRiskZones(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS], int riskDays[ZONES])
{
    int i, j;
    printf("\nRISK DAY REPORT\n");
    printf("Risk day: AQI > 150 OR Temp > 35 OR Humidity > 80\n");
    for (i = 0; i < ZONES; i++)
    {
        riskDays[i] = 0;
        printf("\nZone %d: ", i + 1);
        printZoneName(i);
        printf("\n");
        for (j = 0; j < DAYS; j++)
        {
            if (aqi[i][j] > 150 || temp[i][j] > 35 || humidity[i][j] > 80)
                riskDays[i] = riskDays[i] + 1;
        }
        printf("Risk days: %d\n", riskDays[i]);
        printf("Day numbers: ");
        if (riskDays[i] == 0)
            printf("None");
        for (j = 0; j < DAYS; j++)
        {
            if (aqi[i][j] > 150 || temp[i][j] > 35 || humidity[i][j] > 80)
                printf("%d ", j + 1);
        }
        printf("\n");
    }
}

void computeGreenIndex(float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES], float greenIndex[ZONES])
{
    int i;
    float aqiScore, tempScore, humidityScore;
    for (i = 0; i < ZONES; i++)
    {
        aqiScore = 100 - (avgAQI[i] / 5);
        tempScore = 100 - 4 * absoluteValue(avgTemp[i] - 25);
        humidityScore = 100 - 2 * absoluteValue(avgHumidity[i] - 50);
        aqiScore = makeZeroIfNegative(aqiScore);
        tempScore = makeZeroIfNegative(tempScore);
        humidityScore = makeZeroIfNegative(humidityScore);
        greenIndex[i] = 0.4 * aqiScore + 0.3 * tempScore + 0.3 * humidityScore;
    }
}

void displayRanking(float greenIndex[ZONES])
{
    int i, j, rank, r;
    printf("\nGREEN INDEX RANKING (best to worst)\n");
    for (r = 1; r <= ZONES; r++)
    {
        for (i = 0; i < ZONES; i++)
        {
            rank = 1;
            for (j = 0; j < ZONES; j++)
            {
                if (greenIndex[j] > greenIndex[i])
                    rank = rank + 1;
            }
            if (rank == r)
            {
                printf("Rank %d - Zone %d ", rank, i + 1);
                printZoneName(i);
                printf(" - Green Index: %.2f\n", greenIndex[i]);
            }
        }
    }
    printf("(Classroom comparison model, not an official rating.)\n");
}

void displayRecommendations(float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES], int riskDays[ZONES])
{
    int i;
    int problem;
    printf("\nRECOMMENDATIONS\n");
    for (i = 0; i < ZONES; i++)
    {
        problem = 0;
        printf("\nZone %d: ", i + 1);
        printZoneName(i);
        printf("\n");
        if (avgAQI[i] > 150)
        {
            printf("- Average AQI is high. Reduce vehicle idling or improve ventilation.\n");
            problem = 1;
        }
        if (avgTemp[i] > 35)
        {
            printf("- Average temperature is high. Add shade or green cover.\n");
            problem = 1;
        }
        if (avgHumidity[i] > 80)
        {
            printf("- Average humidity is high. Check ventilation or stagnant-water sources.\n");
            problem = 1;
        }
        if (problem == 0 && riskDays[i] > 0)
            printf("- Averages are fine, but %d risk day(s) were flagged. Review those dates.\n", riskDays[i]);
        if (problem == 0 && riskDays[i] == 0)
            printf("- No risk detected. Continue monitoring.\n");
    }
}

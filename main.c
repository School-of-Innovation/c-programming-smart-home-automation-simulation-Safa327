/*
 * 🚨 WARNING: CHALLENGE MODE ACTIVATED 🚨
 * 
 * 1️⃣ Sit back, take a deep breath, and **THINK**.
 * 2️⃣ For the next **10 minutes**, avoid using **Gen AI, ChatGPT, or any shortcuts**.
 * 3️⃣ Trust your **brain**—you’re smarter than you think!
 * 4️⃣ Consider yourself a **LOSER** if you cheat. Seriously, promise yourself you won't. 😤
 * 5️⃣ If you solve it on your own, **you WIN** and level up as a true programmer and come and meet me ! 
 * 
 * 
 * 💡 Remember: The best coders aren’t the ones who copy-paste. They are the ones who **struggle, think, fail, and then succeed.** 
 *    
 * Now, write your code! You got this! 💪🔥
 */

 #include <stdio.h>
#include <stdlib.h>

void initializeSystem(int rooms);
void displayMenu();
void controlLights(int rooms);
void readTemperature(int rooms);
void detectMotion(int rooms);
void securitySystem(int rooms);
void analyzeHouseStatus(int rooms);

int main() {
    int rooms;
    printf("Enter number of rooms: ");
    scanf("%d", &rooms);

    int *lights = (int *)calloc(rooms, sizeof(int));
    int *temperature = (int *)malloc(rooms * sizeof(int));
    int *motion = (int *)calloc(rooms, sizeof(int));
    int *locks = (int *)malloc(rooms * sizeof(int));
    
    if (!lights || !temperature || !motion || !locks) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    initializeSystem(rooms, lights, temperature, motion, locks);

    int choice, noMotionCount = 0;
    do {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: controlLights(rooms, lights); break;
            case 2: readTemperature(rooms, temperature); break;
            case 3: detectMotion(rooms, motion, locks, &noMotionCount); break;
            case 4: securitySystem(rooms, locks); break;
            case 5: analyzeHouseStatus(rooms, lights, temperature, motion, locks); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    free(lights);
    free(temperature);
    free(motion);
    free(locks);
    
    return 0;
}

void initializeSystem(int rooms, int *lights, int *temperature, int *motion, int *locks) {
    for (int i = 0; i < rooms; i++) {
        temperature[i] = 22;
        locks[i] = 1;
    }
    printf("System initialized.\n");
}

void displayMenu() {
    printf("\n===== Smart Home Menu =====\n");
    printf("1. Toggle Light\n2. Read Temperature\n3. Check Motion Sensor\n4. Lock/Unlock Security System\n5. House Status Summary\n6. Exit\nEnter your choice: ");
}

void controlLights(int rooms, int *lights) {
    int room;
    printf("Enter room number (1-%d) to toggle light: ", rooms);
    scanf("%d", &room);
    if (room >= 1 && room <= rooms) {
        lights[room - 1] = !lights[room - 1];
        printf("Light in Room %d is now %s.\n", room, lights[room - 1] ? "ON" : "OFF");
    } else {
        printf("Invalid room number!\n");
    }
}

void readTemperature(int rooms, int *temperature) {
    int room;
    printf("Enter room number (1-%d) to read temperature: ", rooms);
    scanf("%d", &room);
    if (room >= 1 && room <= rooms) {
        printf("Room %d Temperature: %d°C\n", room, temperature[room - 1]);
        if (temperature[room - 1] > 30) {
            printf("Warning: High temperature detected in Room %d!\n", room);
        }
    } else {
        printf("Invalid room number!\n");
    }
}

void detectMotion(int rooms, int *motion, int *locks, int *noMotionCount) {
    int room;
    printf("Enter room number (1-%d) to check motion sensor: ", rooms);
    scanf("%d", &room);
    if (room >= 1 && room <= rooms) {
        printf("Motion %s in Room %d.\n", motion[room - 1] ? "Detected" : "Not Detected", room);
        if (!motion[room - 1]) {
            (*noMotionCount)++;
            if (*noMotionCount >= 5) {
                for (int i = 0; i < rooms; i++) locks[i] = 1;
                printf("Auto-lock activated due to inactivity!\n");
                *noMotionCount = 0;
            }
        } else {
            *noMotionCount = 0;
        }
    } else {
        printf("Invalid room number!\n");
    }
}

void securitySystem(int rooms, int *locks) {
    int room;
    printf("Enter room number (1-%d) to lock/unlock: ", rooms);
    scanf("%d", &room);
    if (room >= 1 && room <= rooms) {
        locks[room - 1] = !locks[room - 1];
        printf("Room %d is now %s.\n", room, locks[room - 1] ? "Locked" : "Unlocked");
    } else {
        printf("Invalid room number!\n");
    }
}

void analyzeHouseStatus(int rooms, int *lights, int *temperature, int *motion, int *locks) {
    printf("House Status:\n");
    for (int i = 0; i < rooms; i++) {
        printf("- Room %d: Light %s, Temp %d°C, %s, %s\n", i + 1,
               lights[i] ? "ON" : "OFF", temperature[i],
               motion[i] ? "Motion Detected" : "No Motion",
               locks[i] ? "Locked" : "Unlocked");
    }
}

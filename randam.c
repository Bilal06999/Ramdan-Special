#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DAYS 30
#define PRAYERS 5
#define DUAS 10

/* ================= GLOBAL ARRAYS ================= */
int roza[DAYS] = {0};
int namaz[DAYS*PRAYERS] = {0};  // Flattened 2D array: namaz[day*5 + prayer_index]
float quran[DAYS] = {0};

/* ================= RANDOM DUAS / QUOTES / AYAT ================= */
char duas[DUAS][150] = {
    "Allahumma inni laka sumtu.",
    "Rabbighfir warham.",
    "Allahumma innaka afuwwun tuhibbul afwa.",
    "Ya Allah grant us sabr.",
    "Allah accept our fasting.",
    "Ya Rahman forgive us.",
    "Ya Allah guide us straight path.",
    "Ya Kareem bless our rizq.",
    "Allah make us consistent.",
    "Ya Allah accept our duas."
};

char quotes[DUAS][150] = {
    "Discipline builds character.",
    "Ramzan teaches patience.",
    "Consistency leads to success.",
    "Small deeds matter.",
    "Stay sincere.",
    "Control your nafs.",
    "Every effort counts.",
    "Focus on improvement.",
    "Be grateful.",
    "Keep your intentions pure."
};

char ayat[DUAS][200] = {
    "Indeed, Allah is with the patient. (2:153)",
    "Allah loves those who do good. (2:195)",
    "Remember Me; I will remember you. (2:152)",
    "Verily, with hardship comes ease. (94:6)",
    "Allah is Forgiving and Merciful. (2:173)",
    "Call upon Me; I will respond to you. (40:60)",
    "Allah is the best planner. (8:30)",
    "He is sufficient for us. (3:173)",
    "Allah is aware of what you do. (2:283)",
    "So remember Me; I will remember you. (2:152)"
};

/* ================= UTILITY FUNCTIONS ================= */
void clearScreen() { system("cls"); }

int validDay(int day) {
    if(day == 0) return 0;  // ESC exit
    if(day < 1 || day > DAYS) {
        printf("Invalid Day (1-30).\n");
        return -1;
    }
    return 1;
}

int validBinary(int val) {
    if(val == 0 || val == 1) return 1;
    printf("Only 0 or 1 allowed.\n");
    return 0;
}

/* ================= SEHRI / IFTARI ================= */
void sehriIftari() {
    printf("======== SEHRI / IFTARI SYSTEM ========\n");
    printf("Enter day (1-30), 0 to exit.\n");

    int day;
    printf("Day: "); scanf("%d",&day);
    int check = validDay(day);
    if(check <= 0) return;

    int sehri = 4*60 + 50 - (day/2);
    int iftari = 18*60 + 20 + (day/2);

    printf("\nSehri: %02d:%02d AM\n", sehri/60, sehri%60);
    printf("Iftari: %02d:%02d PM\n", (iftari/60)-12, iftari%60);

    srand(time(NULL));
    int r = rand() % DUAS;
    printf("Dua for Sehri/Iftari: %s\n", duas[r]);
}

/* ================= ROZA ENTRY ================= */
void rozaEntry() {
    printf("======== ROZA SYSTEM ========\n");
    printf("Enter day (1-30), 0 to exit.\n");

    int day,status;
    printf("Day: "); scanf("%d",&day);
    int check = validDay(day);
    if(check <= 0) return;

    printf("Roza Completed? (1=Yes 0=No): "); scanf("%d",&status);
    if(!validBinary(status)) return;

    roza[day-1] = status;
    printf("Saved.\n");
}

/* ================= NAMAZ ENTRY ================= */
void namazEntry() {
    printf("======== NAMAZ SYSTEM ========\n");
    printf("Enter day (1-30), 0 to exit.\n");

    int day; printf("Day: "); scanf("%d",&day);
    int check = validDay(day);
    if(check <= 0) return;

    printf("Enter 1=Prayed, 0=Missed\n");
    for(int i=0;i<PRAYERS;i++){
        printf("Prayer %d: ",i+1);
        scanf("%d",&namaz[(day-1)*PRAYERS + i]);
        if(!validBinary(namaz[(day-1)*PRAYERS + i])) return;
    }
    printf("Saved.\n");
}

/* ================= QURAN ENTRY ================= */
void quranEntry() {
    printf("======== QURAN SYSTEM ========\n");
    printf("Enter day (1-30), 0 to exit.\n");

    int day; float pages;
    printf("Day: "); scanf("%d",&day);
    int check = validDay(day);
    if(check <= 0) return;

    printf("Pages Read: "); scanf("%f",&pages);
    if(pages < 0) { printf("Invalid pages.\n"); return; }

    quran[day-1] = pages;
    printf("Saved.\n");
}

/* ================= DAILY ISLAMIC MESSAGE ================= */
void dailyMessage() {
    printf("======== DAILY MESSAGE ========\n");
    srand(time(NULL));
    int r = rand() % DUAS;
    printf("Dua: %s\n", duas[r]);
    printf("Quote: %s\n", quotes[r]);
    printf("Quran Ayat: %s\n", ayat[r]);
}

/* ================= ZAKAT SYSTEM ================= */
void zakatCalculator() {
    printf("======== ZAKAT SYSTEM ========\n");
    printf("Enter 0 if not applicable.\n");

    float cash,goldT,silverT,goldRate,silverRate,property,total;
    printf("Cash: "); scanf("%f",&cash); if(cash<0) return;

    printf("Gold (Tola): "); scanf("%f",&goldT); if(goldT<0) return;
    printf("Gold Rate/Tola: "); scanf("%f",&goldRate); if(goldRate<0) return;
    float goldVal = goldT*goldRate;

    printf("Silver (Tola): "); scanf("%f",&silverT); if(silverT<0) return;
    printf("Silver Rate/Tola: "); scanf("%f",&silverRate); if(silverRate<0) return;
    float silverVal = silverT*silverRate;

    printf("Unused Property Value: "); scanf("%f",&property); if(property<0) return;

    total = cash + goldVal + silverVal + property;
    printf("Total Assets: %.2f\n", total);
    printf("Zakat (2.5%%): %.2f\n", total*0.025);
}

/* ================= DASHBOARD ================= */
void dashboard() {
    printf("======== DASHBOARD ========\n");
    int totalRoza=0, totalNamaz=0; float totalQuran=0;

    for(int i=0;i<DAYS;i++) totalRoza+=roza[i];
    for(int i=0;i<DAYS*PRAYERS;i++) totalNamaz+=namaz[i];
    for(int i=0;i<DAYS;i++) totalQuran+=quran[i];

    printf("Roza Completion: %d%%\n", (totalRoza*100)/30);
    printf("Namaz Completion: %d%%\n", (totalNamaz*100)/(DAYS*PRAYERS));
    printf("Total Quran Pages: %.2f\n", totalQuran);
}

/* ================= MAIN ================= */
int main() {
    int choice;
    do {
        clearScreen();
        printf("==== RAMZAN MANAGEMENT SYSTEM ====\n");
        printf("1. Sehri / Iftari\n2. Roza\n3. Namaz\n4. Quran\n5. Daily Message\n6. Zakat\n7. Dashboard\n0. Exit\n");
        printf("Choose: "); 
        scanf("%d",&choice);
        clearScreen();

        switch(choice){
            case 1: sehriIftari(); break;
            case 2: rozaEntry(); break;
            case 3: namazEntry(); break;
            case 4: quranEntry(); break;
            case 5: dailyMessage(); break;
            case 6: zakatCalculator(); break;
            case 7: dashboard(); break;
        }

        printf("\nPress Enter to continue...");
        getchar(); getchar();
    } while(choice!=0);
    return 0;
}
#include <stdio.h>


#define FILE_NAME "Catalog.txt"


struct Catalog {
    char name[50];
    char author[50];
    int year;
    float price;
};

static struct Catalog SONGS[5];
static int count = 0;
//Sort the songs from year - working
void SortSongs(struct Catalog songs[], int total)
{
    int i;
    int j;

    for (i = 0; i < total - 1; i++) {
        for (j = 0; j < total - i - 1; j++) {
            if (songs[j].year < songs[j + 1].year) {
                struct Catalog temp = songs[j];
                songs[j] = songs[j + 1];
                songs[j + 1] = temp;
            }
        }
    }
}
// Menu for the user to operate - working
int main()
{
    int user_input = 0;

    while (user_input !=5)
    {
        printf("Please choose an option\n");
        printf("Enter data [1]\n");
        printf("Save data to file [2]\n");
        printf("Read data from file [3]\n");
        printf("Print out the catalogue to screen [4]\n");
        printf("Exit Program [5]\n");
        printf("Enter chosen mode: ");

        if (scanf("%d", &user_input) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            continue;
        }

        printf("YOU CHOSE: %d\n", user_input);
      //Option 1 - enter data -  possibly working
        if (user_input == 1) {
            if (count >= 5) {
                printf("Catalog is full.\n");
                continue;
            }

            printf("ENTER SONG DATA NOW:\n");
            printf("---------------------------------\n");
            printf("NAME OF BAND/SINGER: ");
            scanf("%49s", SONGS[count].name);

            printf("NAME OF SONG: ");
            scanf("%49s", SONGS[count].author);

            printf("YEAR OF RELEASE: ");
            scanf("%d", &SONGS[count].year);

            printf("PRICE: ");
            scanf("%f", &SONGS[count].price);
            printf("---------------------------------\n");

            count++;
        }
        //option 2 - save data to file - possibly working?
        else if (user_input == 2) {
            FILE *file = NULL;
            file = fopen(FILE_NAME, "w");
            if (file == NULL) {
                printf("Error opening file for writing.\n");
                continue;
            }

            for (int i = 0; i < count; i++) {
                fprintf(file, "%s\n%s\n%d\n%.2f\n",
                        SONGS[i].name,
                        SONGS[i].author,
                        SONGS[i].year,
                        SONGS[i].price);
            }

            fclose(file);
            printf("Data saved to file.\n");
        }
        //Option 3 - read data from file - possibly working?
        else if (user_input == 3) {
            FILE *file = NULL;
            file = fopen(FILE_NAME, "r");
            if (file == NULL) {
                printf("Error opening file for reading.\n");
                continue;
            }

            count = 0;
            while (count < 5 &&
                fscanf_s(file, "%49s", SONGS[count].name , (unsigned)sizeof(SONGS[count].name)) == 1 &&
                fscanf_s(file, "%49s", SONGS[count].author, (unsigned)sizeof(SONGS[count].author)) == 1 &&
                fscanf_s(file, "%d", &SONGS[count].year) == 1 &&    
                fscanf_s(file, "%f", &SONGS[count].price) == 1) {  
               
                count++;
            }

            fclose(file);
            printf("Data read from file.\n");
        }
        //Opttion 4 print out Catalogue to screen?
        else if (user_input == 4) {
            if (count == 0) {
                printf("No songs in the catalogue.\n");
                continue;
            }

            SortSongs(SONGS, count);
            for (int i = 0; i < count; i++) {
                printf("Band/Singer: %s\n", SONGS[i].name);
                printf("Song Name: %s\n", SONGS[i].author);
                printf("Year: %d\n", SONGS[i].year);
                printf("Price: %.2f\n", SONGS[i].price);
                printf("---------------------------------\n");
            }
        }
        else if (user_input == 5) {
            printf("Exiting program...\n");
            return 0;
        }
        else {
            printf("Invalid option.\n");
        }
    }

    return 0;
}

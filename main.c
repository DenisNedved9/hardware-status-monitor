#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    char full_text[200] = "";
    char jmeno[30] = "";
    char *status;
    char stupne[15] = "";
    char *posledni_text_znak = "xxxxx";
    char posledni_text[50] = "";
    char *nejhorsi_status = "";

    char status_char;
    int typ_vstupu = 0;
    int posledni_text_promenna = 0;
    int alerts = 0;
    int stupne_promenna = 0;

    FILE *pFile = fopen("hardware_status.txt", "r");
    FILE *pOutput = fopen("output.txt", "w");

    if (pFile == NULL)
    {
        return 1;
    }

    char buffer[1024] = "0";

    while (fgets(buffer, sizeof(buffer), pFile) != NULL)
    {

        buffer[strcspn(buffer, "\n")] = '\0';

        stupne_promenna = 0;
        typ_vstupu = 0;
        posledni_text_promenna = 0;
        memset(jmeno, 0, sizeof(jmeno));
        memset(posledni_text, 0, sizeof(posledni_text));
        memset(stupne, 0, sizeof(stupne));

        for (int i = 0; i < strlen(buffer); i++)
        {

            if (buffer[i] == ',')
            {

                typ_vstupu++;
                continue;
            }

            switch (typ_vstupu)
            {
            case 0:
                jmeno[i] = buffer[i];

                break;

            case 1:
                status_char = buffer[i];

                switch (status_char)
                {
                case 48: // číslo 0
                    status = "OK";
                    if (strcmp(nejhorsi_status, "WARNING") != 0 && strcmp(nejhorsi_status, "CRITICAL") != 0)
                    {
                        nejhorsi_status = "OK";
                    }
                    break;
                case 49: // číslo 1
                    status = "WARNING";
                    alerts++;
                    if (strcmp(nejhorsi_status, "CRITICAL") != 0)
                    {
                        nejhorsi_status = "WARNING";
                    }
                    break;
                case 52: // číslo 4
                    status = "CRITICAL";
                    nejhorsi_status = "CRITICAL";
                    alerts++;
                    break;
                }

                break;

            case 2:
                stupne[stupne_promenna] = buffer[i];
                stupne_promenna++;
                break;

            case 3:
                posledni_text[posledni_text_promenna] = buffer[i];
                posledni_text_promenna++;
                if (strcmp(jmeno, "RECEIVER") == 0 || strcmp(jmeno, "TRANSMITTER") == 0)
                {
                    posledni_text_znak = "V";
                }
                else if (strcmp(jmeno, "GPS") == 0)
                {
                    posledni_text_znak = "sat";
                }
                else if (strcmp(jmeno, "BATTERY") == 0)
                {
                    posledni_text_znak = "%";
                }
                break;
            }
        }
        printf("%s: ", jmeno);
        printf("%s ", status);
        printf("(%s C, ", stupne);
        printf("%s %s)", posledni_text, posledni_text_znak);

        fprintf(pOutput, "%s: ", jmeno);
        fprintf(pOutput, "%s ", status);
        fprintf(pOutput, "(%s C, ", stupne);
        fprintf(pOutput, "%s %s)", posledni_text, posledni_text_znak);

        printf("\n");
        fprintf(pOutput, "\n");
    }
    printf("\n");
    printf("SYSTEM STATUS: %s\n", nejhorsi_status);
    printf("Active alerts: %d\n", alerts);
    printf("Report saved to 'output.txt'.");

    fprintf(pOutput, "\n");
    fprintf(pOutput, "SYSTEM STATUS: %s\n", nejhorsi_status);
    fprintf(pOutput, "Active alerts: %d\n", alerts);

    fclose(pFile);
    fclose(pOutput);

    return 0;
}
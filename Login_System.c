#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define VIGENERE_KEY "MYSECRETKEY"

#define PASSWORD_FILE "password.txt"

#define FILE_NAME "users_pass.txt"

#define Max_Users_In_System 150

#define TIMEOUT_SECONDS 10

#define PASSWORD_LENGTH 12

#define MIN_PASSWORD_LENGTH 10

#define SHIFT 3


bool isLoggedIn = false;

int loginAttempts = 0;

typedef struct
{
    int YearOfBirth;
    int MonthOfBirth;
    int DayOfBirth;
} BirthDetails;

typedef struct
{
    int zipCode;
    char country[30];
    char city[30];
} LocationDetails;

typedef struct
{
    char name[30];
    char password[31];
    BirthDetails AgeInfo;
    LocationDetails LocationInfo;
    char Email[40];
} User;

typedef struct
{
    User users[Max_Users_In_System];
} Users_In_System;

typedef struct
{
    int Year;
    int Month;
    int Day;
} Date;


//######################------START OF FUNCTION DEFENITION--------##############################


void DisplaySystemOption(User *user);

bool isValidPassword(const char *password);

void PasswordLevel(const char *password);

bool IsValidUserName(const char *username);

bool isValidMonth(int month);

bool isValidDayOfBirth(int day, int month, int year);

bool isValidYear(int year);

bool isValidEmail(const char *email);

void ViewUserDetails(const User *user);

bool IsExistInSystem(const char *username, const char *password);

int Register();

void Login();


//-------------END OF BASIC VALIDATION FUNCTIONS-------------//


void MovePasswordIfLeak(char* password);

void StorePassword(char *website, char *password);

bool IsWebsiteReal(char* website);

void HideFile(FILE* file);

char* OfferStrongPassword();

//void UserOption(char *username , char *password);

//void InsertNewPassword(char *username, char *password);

void DeleteAccount(char *username, char *password);

//void ViewPasswords(char *username,char *password);

unsigned long HashPassword(const char *str);

char* encrypt_password(const char* password);

char* decrypt_password(const char* encrypted_password);

char* add_salt_encryption(char *passwordToBeSalted);

//#####################-----END OF FUNCTION DEFENITION------################################


int main()
{
    User newUser; // Create a new user object
    DisplaySystemOption(&newUser);

    if(isLoggedIn)
    {
        UserOption(newUser.name,newUser.password);
    }


}


//#########-------------- START OF FUNCTION IMPLEMENTION-------------------##################################



void DisplaySystemOption(User *user)
{
    printf("\t\t\t\t\t\t******************\n");
    printf("\t\t\t\t\t\t***LOGIN-SYSTEM***\n");
    printf("\t\t\t\t\t\t******************\n");

    printf("\t\t\t\t\t\t ________________\n");
    printf("\t\t\t\t\t\t|    OPTIONS\t |\n");
    printf("\t\t\t\t\t\t|                |\n");
    printf("\t\t\t\t\t\t|    1:Register\t |\n");
    printf("\t\t\t\t\t\t|    2:Log-In\t |\n");
    printf("\t\t\t\t\t\t|    3:Privacy\t |\n");
    printf("\t\t\t\t\t\t|________________|\n");

    printf("\t\t\t\t\t\t   Your Choice:");
    int x;
    scanf("%d", &x);

    switch (x)
    {
    case 1:
        Register(); // Calls the Register function to register a new user
        break;
    case 2:
        Login(); // Calls the Login function to perform user login
        break;
    case 3:
        // Privacy_Policy(); // Calls the Privacy_Policy function to display the privacy policy
        break;
    default:
        printf("\t\t\t\t\t  Invalid Choice try again later\n");
    }
}

bool isValidPassword(const char *password)
{
    int length = strlen(password);
    bool hasLetter = false;
    bool hasDigit = false;

    // Check each character in the password
    for (int i = 0; i < length; i++)
    {
        if (isalpha(password[i]))
        {
            hasLetter = true;
        }
        else if (isdigit(password[i]))
        {
            hasDigit = true;
        }
    }

    // Check if password meets all criteria
    return length >= 8 && length <= 30 && hasLetter && hasDigit;
}

void PasswordLevel(const char *password)
{
    int length = strlen(password);
    bool hasLowerCase = false;
    bool hasUpperCase = false;
    bool hasDigit = false;
    bool hasSpecialChar = false;

    // Check each character in the password
    for (int i = 0; i < length; i++)
    {
        if (islower(password[i]))
        {
            hasLowerCase = true;
        }
        else if (isupper(password[i]))
        {
            hasUpperCase = true;
        }
        else if (isdigit(password[i]))
        {
            hasDigit = true;
        }
        else if (!isalnum(password[i]))
        {
            hasSpecialChar = true;
        }
    }

    int points = 0;

    // Assign points based on password length
    if (length >= 8 && length <= 15)
    {
        points += 4;
    }
    else if (length >= 16 && length <= 23)
    {
        points += 7;
    }
    else if (length >= 24 && length <= 30)
    {
        points += 10;
    }

    // Assign points based on presence of special characters and capital letters
    if (hasSpecialChar)
    {
        points += 5;
    }
    if (hasUpperCase)
    {
        points += 5;
    }

    // Split the points in half
    points /= 2;

    // Print the password level based on the points
    if (points >= 9)
    {
        printf("Strong password.\n");
    }
    else if (points >= 6)
    {
        printf("Good password.\n");
    }
    else
    {
        printf("Weak password.\n");
    }
}

bool IsValidUserName(const char *username)
{
    int length = strlen(username);
    return length > 0 && length <= 30; // Username must not be empty and not exceed 30 characters
}

bool isValidMonth(int month)
{
    return month >= 1 && month <= 12; // Month must be between 1 and 12
}

bool isValidDayOfBirth(int day, int month, int year)
{
    // Basic validation for day of birth based on the month and year (leap year not considered here)
    if (day < 1 || month < 1 || month > 12)
    {
        return false;
    }
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2)
    {
        // Check for February (assuming non-leap year)
        if (year % 4 == 0)
        {
            daysInMonth[1] = 29; // Leap year
        }
    }
    return day >= 1 && day <= daysInMonth[month - 1];
}

bool isValidYear(int year)
{
    return year >= 1900 && year <= 2023; // Year must be between 1900 and 2023
}

bool isValidEmail(const char *email)
{
    int length = strlen(email);
    // Very basic email validation: must contain '@' and at least one '.' after '@'
    bool hasAtSymbol = false;
    for (int i = 0; i < length; i++)
    {
        if (email[i] == '@')
        {
            hasAtSymbol = true;
        }
        if (hasAtSymbol && email[i] == '.')
        {
            return true;
        }
    }
    return false;
}

void ViewUserDetails(const User *user)
{
    printf("\nUser Details:\n");
    printf("Name: %s\n", user->name);
    printf("Date of Birth: %d/%d/%d\n", user->AgeInfo.DayOfBirth, user->AgeInfo.MonthOfBirth, user->AgeInfo.YearOfBirth);
    printf("Location: %s, %s, Zip Code: %d\n", user->LocationInfo.city, user->LocationInfo.country, user->LocationInfo.zipCode);
    printf("Email: %s\n", user->Email);
}

bool IsExistInSystem(const char *username, const char *password)
{
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return false;
    }

    char line[100];
    bool found = false;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (strstr(line, "Name: ") == line)
        {
            char *name = line + strlen("Name: ");
            strtok(name, "\n"); // Remove newline character

            if (strcmp(name, username) == 0)
            {
                // Found matching username, now check password
                if (fgets(line, sizeof(line), file) != NULL && strstr(line, "Password: ") == line)
                {
                    char *storedPassword = line + strlen("Password: ");
                    strtok(storedPassword, "\n"); // Remove newline character

                    if (strcmp(storedPassword, password) == 0)
                    {
                        found = true;
                        break;
                    }
                }
            }
        }
    }

    fclose(file);
    return found;
}

int Register()
{
    FILE *file = fopen(FILE_NAME, "a+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    char username[30];
    char password[31];
    char email[40];
    int year, month, day;
    int zipCode;
    char country[30];
    char city[30];
    bool isValidInput = false;

    while (!isValidInput) {
        printf("Write Name: ");
        scanf("%s", username);

        printf("Write Password (8-30 characters, must contain letters and numbers): ");
        scanf("%s", password);

        if (IsExistInSystem(username, password)) {
            printf("User already exists in the system. Do you want to log in?\n");
            printf("1: Yes\n");
            printf("2: No\n");

            int choice;
            scanf("%d", &choice);

            if (choice == 1) {
                Login();
                fclose(file);
                return 2;
            } else {
                fclose(file);
                return 1;
            }
        }

        if (!IsValidUserName(username)) {
            printf("Invalid username, please try again.\n");
        } else if (!isValidPassword(password)) {
            printf("Invalid password, please try again.\n");
        } else {
            isValidInput = true;
            fprintf(file, "Name: %s\n", username);
            fprintf(file, "Password: %s\n", password);
        }
    }

    PasswordLevel(password);

    while (true) {
        printf("Write Year of Birth: ");
        if (scanf("%d", &year) == 1 && isValidYear(year)) {
            fprintf(file, "Year of Birth: %d\n", year);
            break;
        }
        printf("Invalid year of birth! Please try again.\n");
    }

    while (true) {
        printf("Write Month of Birth: ");
        if (scanf("%d", &month) == 1 && isValidMonth(month)) {
            fprintf(file, "Month of Birth: %d\n", month);
            break;
        }
        printf("Invalid month of birth! Please try again.\n");
    }

    while (true) {
        printf("Write Day of Birth: ");
        if (scanf("%d", &day) == 1 && isValidDayOfBirth(day, month, year)) {
            fprintf(file, "Day of Birth: %d\n", day);
            break;
        }
        printf("Invalid day of birth! Please try again.\n");
    }

    while (true) {
        printf("Write Email: ");
        scanf("%s", email);
        if (isValidEmail(email)) {
            fprintf(file, "Email: %s\n", email);
            break;
        }
        printf("Invalid email format! Please try again.\n");
    }

    printf("Write Zip Code: ");
    scanf("%d", &zipCode);
    fprintf(file, "Zip Code: %d\n", zipCode);

    printf("Write Country: ");
    scanf("%s", country);
    fprintf(file, "Country: %s\n", country);

    printf("Write City: ");
    scanf("%s", city);
    fprintf(file, "City: %s\n", city);

    fprintf(file, "---------------------------------\n");
    fclose(file);
    printf("User registered successfully!\n");

    int choice_see;
    printf("Would you like to see your details: 1:yes 2:no\n");
    scanf("%d", &choice_see);
    if (choice_see == 1) {
        ViewUserDetails(username);
    }

    return 0;
}

void Login()
{
    char username[30];
    char password[31];

    printf("Enter Username: ");
    if (scanf("%29s", username) != 1) {
        printf("Error reading username.\n");
        return;
    }

    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int found = 0;
    char line[100];

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "Name: ", 6) == 0) {
            char *name = line + 6;
            name[strcspn(name, "\n")] = '\0'; // Remove newline character
            if (strcmp(name, username) == 0) {
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("User does not exist.\n");
        fclose(file);
        return;
    }

    if (fgets(line, sizeof(line), file) != NULL && strncmp(line, "Password: ", 10) == 0) {
        char *storedPassword = line + 10;
        storedPassword[strcspn(storedPassword, "\n")] = '\0'; // Remove newline character

        while (loginAttempts < 3) {
            printf("Enter Password: ");
            if (scanf("%30s", password) != 1) {
                printf("Error reading password.\n");
                continue;
            }

            if (strcmp(storedPassword, password) == 0) {
                printf("User successfully logged in.\n");
                loginAttempts = 0;
                fclose(file);
                isLoggedIn = true;
                return;
            } else {
                printf("Incorrect password. Please try again.\n");
                loginAttempts++;
            }
        }

        printf("Too many incorrect login attempts. Account locked.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    } else {
        printf("Error reading user data.\n");
    }

    fclose(file);
}

char* OfferStrongPassword()
 {
    static char password[PASSWORD_LENGTH + 1];
    const char lower[] = "abcdefghijklmnopqrstuvwxyz";
    const char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char digits[] = "0123456789";
    const char special[] = "!@#$%^&*()_+[]{}|;:,.<>?";

    const int lower_len = strlen(lower);
    const int upper_len = strlen(upper);
    const int digits_len = strlen(digits);
    const int special_len = strlen(special);

    srand(time(NULL));

    int length = MIN_PASSWORD_LENGTH + rand() % (PASSWORD_LENGTH - MIN_PASSWORD_LENGTH + 1);

    int i;
    for (i = 0; i < length; i++) {
        int category = rand() % 4;
        switch (category) {
            case 0:
                password[i] = lower[rand() % lower_len];
                break;
            case 1:
                password[i] = upper[rand() % upper_len];
                break;
            case 2:
                password[i] = digits[rand() % digits_len];
                break;
            case 3:
                password[i] = special[rand() % special_len];
                break;
        }
    }
    password[length] = '\0';

    return password;
}

void UserOption(char *username,char *password)
{
    int choice;
    printf("Insert Your Option: 1: Insert New Password , 2: See My Passwords, 3: Delete account\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        InsertNewPassword(username,password);
        break;
    case 2:
        ViewPasswords(username,password);
        break;
    case 3:
        DeleteAccount(username, password);
        break;
    default:
        printf("Invalid choice, try again later\n");
    }
}

unsigned long HashPassword(const char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
}

void DeleteAccount(char *username, char *password)
{
    FILE *file = fopen(FILE_NAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    char line[100];
    bool skipUser = false;

    if (file == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "Name: ") == line) {
            char *name = line + strlen("Name: ");
            strtok(name, "\n"); // Remove newline character

            if (strcmp(name, username) == 0) {
                skipUser = true; // Skip lines until the next user
                continue;
            }
        }

        if (!skipUser) {
            fputs(line, tempFile);
        } else if (strstr(line, "---------------------------------") == line) {
            skipUser = false; // Stop skipping lines after user block ends
        }
    }

    fclose(file);
    fclose(tempFile);

    // Replace the old file with the new file
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    printf("Account and associated data deleted successfully.\n");
}

char* encrypt_password(const char* password)
{
    char key = 'K'; // Simple XOR key for demonstration
    size_t len = strlen(password);
    char* encrypted = (char*)malloc(len + 1);
    for (size_t i = 0; i < len; ++i) {
        encrypted[i] = password[i] ^ key;
    }
    encrypted[len] = '\0';
    return encrypted;
}

char* decrypt_password(const char* encrypted_password)
{
    char key = 'K'; // Same XOR key used for encryption
    size_t len = strlen(encrypted_password);
    char* decrypted = (char*)malloc(len + 1); // Allocate memory for decrypted password

    for (size_t i = 0; i < len; ++i) {
        decrypted[i] = encrypted_password[i] ^ key; // XOR decryption
    }
    decrypted[len] = '\0'; // Null-terminate the string

    return decrypted;
}

void InsertNewPassword(char *username, char *password)
{
    char website[30];
    char new_password[30];
    FILE *file;
    FILE *tempFile;
    char line[100];
    bool userFound = false;

    printf("Enter the website: ");
    scanf("%s", website);

    printf("Enter the password: ");
    scanf("%s", new_password);

    char* encrypted_password = encrypt_password(new_password);

    // Open the password file in read mode
    file = fopen(PASSWORD_FILE, "r");
    if (file == NULL) {
        // If the file does not exist, create it and write the new password
        file = fopen(PASSWORD_FILE, "a");
        if (file == NULL) {
            printf("Error opening file!\n");
            return;
        }
        fprintf(file, "Name: %s\n", username);
        fprintf(file, "Passwords:\n");
        fprintf(file, "Website: %s, Password: %s\n", website, encrypted_password);
        fprintf(file, "---------------------------------\n");
        fclose(file);
        printf("Password saved successfully!\n");
        free(encrypted_password);
        return;
    }

    // Create a temporary file to store the updated content
    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file!\n");
        fclose(file);
        free(encrypted_password);
        return;
    }

    // Read through the file and copy lines to the temporary file
    while (fgets(line, sizeof(line), file) != NULL) {
        fputs(line, tempFile);
        if (strstr(line, "Name: ") == line) {
            char *name = line + strlen("Name: ");
            strtok(name, "\n"); // Remove newline character
            if (strcmp(name, username) == 0) {
                userFound = true;
                // Skip "Passwords:" line
                fgets(line, sizeof(line), file);
                fputs(line, tempFile);

                // Append the new password within the user's section
                fprintf(tempFile, "Website: %s, Password: %s\n", website, encrypted_password);
            }
        }
    }

    if (!userFound) {
        // If the user was not found, create a new section for them
        fprintf(tempFile, "Name: %s\n", username);
        fprintf(tempFile, "Passwords:\n");
        fprintf(tempFile, "Website: %s, Password: %s\n", website, encrypted_password);
        fprintf(tempFile, "---------------------------------\n");
    }

    fclose(file);
    fclose(tempFile);
    free(encrypted_password);

    // Replace the old file with the new file
    remove(PASSWORD_FILE);
    rename("temp.txt", PASSWORD_FILE);

    printf("Password saved successfully!\n");
}

bool IsWebsiteReal(char* website)
{
    char command[256];
    // Create the ping command, limiting to 1 ping and suppressing output
    snprintf(command, sizeof(command), "ping -c 1 %s > /dev/null 2>&1", website);

    // Execute the command
    int result = system(command);

    // If result is 0, the website is reachable
    return result == 0;
}

void ViewPasswords(char *username, const char *password)
{
    FILE *file = fopen(PASSWORD_FILE, "r");
    if (file == NULL) {
        printf("Error opening password file!\n");
        return;
    }

    char line[100];
    bool userFound = false;

    printf("Stored Passwords:\n");

    while (fgets(line, sizeof(line), file) != NULL) {
        // Look for the user's section based on the username
        if (strstr(line, "Name: ") == line) {
            char *name = line + strlen("Name: ");
            strtok(name, "\n"); // Remove newline character
            if (strcmp(name, username) == 0) {
                userFound = true;
                // Skip "Passwords:" line
                fgets(line, sizeof(line), file);
                while (fgets(line, sizeof(line), file) != NULL && strstr(line, "---------------------------------") != line) {
                    // Assuming passwords are stored in the format: "Website: <website>, Password: <encrypted_password>"
                    if (strstr(line, "Website: ") == line) {
                        char *website = strtok(line + strlen("Website: "), ",");
                        char *enc_password = strtok(NULL, " ") + strlen("Password: ");
                        char* decrypted_password = decrypt_password(enc_password);
                        printf("Website: %s, Password: %s\n", website, decrypted_password);
                        free(decrypted_password);
                    }
                }
                break; // Exit loop after finding user's section
            }
        }
    }

    if (!userFound) {
        printf("No passwords found for the user: %s\n", username);
    }

    fclose(file);
}


//##############-----------END OF FUCNTION IMPLEMENTION---------###########################



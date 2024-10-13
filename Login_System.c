#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h> // Include ctype.h for isalpha and islower/isupper functions
#include <conio.h>

#define SHIFT 3 // Define the shift value for encryption and decryption
#define PASSWORD_FILE "password.txt"
#define FILE_NAME "users_pass.txt"
#define Max_Users_In_System 150
#define TIMEOUT_SECONDS 10 // Timeout duration in seconds


bool isLoggedIn = false; // Global variable to track login state

int loginAttempts = 0;

//need to add the fucntion that the user could change the details if their are wrong!

typedef struct
{
    int YearOfBirth;
    int MonthOfBirth;
    int DayOfBirth;

}BirthDetails;

typedef struct
{
    int zipCode;
    char country[30];
    char city[30];

}LocationDetails;

typedef struct
{
    char name[30];
    char password[31];
    BirthDetails AgeInfo;
    LocationDetails LocationInfo;
    char Email[40];

}User;

typedef struct
{
    User users[Max_Users_In_System];

}Users_In_System;


//system Functions

void Login(User* user);//done

int Register(User *user);//done

bool IsExistInSystem(const char *username, const char *password);//done

void DeleteAccount(const char *username, const char *password);//done-but it dont work

void ChangePassword(const char *username, const char *oldPassword, const char *newPassword);//done-but it dont work

void Logout();//done

void Unfollow();
//end of system functions


//Display Details Functions

void ViewSystem(User* user);

void ViewSettings(User* user);//almost done but need to clear the screen before diplay the settings!

void ViewInbox();

void ViewUserDetails(const User *user);//done

void SendDetailsUsingEmail(User *user);//did not find a way yet-so wait till the end of the project

void MultiLanguegeSupport(); // maybe later

void Privacy_Policy();//done

void DisplaySystemOption();//done

//end Of display details fincions


//Secuiry Functions

void CheckActivity(); //done- nut need to be fixed because it dont work

bool ForgetPassword();//dont know it do it because i dont have another way to verify the identity of the user

void AccountLockOut();//done

void SendVarificationEmail();//still dont figure out how to send emails

bool IsVarificationCorrect();//still cant be done

void EncryptPassword(char *plaintext, char *ciphertext); // done , but dont use it-maye in the future

void DecryptPassword(char *ciphertext, char *plaintext); // done, but dont use it- maybe in the future

bool IsPasswordStrong(const char *password);//done

void PasswordLevel(const char *password);//done

bool isValidPassword(const char *password);//done

bool IsValidUserName();//done

bool isValidMonth();//done

bool isValidDayOfBirth();//done

bool isValidYear();//done

bool isValidEmail();//done

bool IsWithoutDuplicateDetails();//should expand more

//end of security functions

//user interaction functions

void SendFriendRequest();

void SendMassageToUsers();

//end of user interaction functions


int main() {


    User newUser;  // Create a new user object

     DisplaySystemOption(&newUser);

    // Call the Register function to save user information


    return 0;
}


void Privacy_Policy() {
    // Clear the screen
    printf("\033[2J\033[1;1H");

    // Define the content of the Privacy Policy
    char* policy =
        "***************************************************\n"
        "*                Privacy Policy                   *\n"
        "***************************************************\n"
        "\n"
        "Welcome to our Login-Register System!\n"
        "\n"
        "This system is designed to provide a secure platform\n"
        "for user authentication and registration. Below are\n"
        "the rules and guidelines:\n"
        "\n"
        "1. User data such as usernames, passwords, and\n"
        "   personal information will be stored securely.\n"
        "\n"
        "2. Users are responsible for maintaining the\n"
        "   confidentiality of their login credentials.\n"
        "\n"
        "3. Unauthorized access or misuse of this system is\n"
        "   strictly prohibited.\n"
        "\n"
        "4. Any suspicious activity should be reported\n"
        "   immediately to the system administrators.\n"
        "\n"
        "Thank you for using our system!\n"
        "\n";

    // Calculate the number of newlines in the policy
    int num_lines = 0;
    for (int i = 0; policy[i] != '\0'; i++) {
        if (policy[i] == '\n') {
            num_lines++;
        }
    }

    // Determine the number of lines to center the content
    int start_line = (25 - num_lines) / 2;

    // Print newlines to center the content vertically
    for (int i = 0; i < start_line; i++) {
        printf("\n");
    }

    // Print the Privacy Policy content
    printf("%s", policy);
}


void DisplaySystemOption(User *user) {
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
    scanf("%d",&x);

    switch(x) {
        case 1:
            Register(user); // Calls the Register function to register a new user
            break;
        case 2:
            Login(user); // Calls the Login function to perform user login
            break;
        case 3:
            Privacy_Policy(); // Calls the Privacy_Policy function to display the privacy policy
            break;
        default:
            printf("\t\t\t\t\t  Invalid Choice try again later\n");
    }
}


bool isValidPassword(const char *password) {
    int length = strlen(password);
    bool hasLetter = false;
    bool hasDigit = false;

    // Check each character in the password
    for (int i = 0; i < length; i++) {
        if (isalpha(password[i])) {
            hasLetter = true;
        } else if (isdigit(password[i])) {
            hasDigit = true;
        }
    }

    // Check if password meets all criteria
    return length >= 8 && length <= 30 && hasLetter && hasDigit;
}


bool IsPasswordStrong(const char *password) {// Do not use this , need to check what to do with this
    int length = strlen(password);
    bool hasUpperCase = false;
    bool hasLowerCase = false;
    bool hasDigit = false;
    bool hasSpecialChar = false;

    for (int i = 0; i < length; i++) {
        if (isupper(password[i])) {
            hasUpperCase = true;
        } else if (islower(password[i])) {
            hasLowerCase = true;
        } else if (isdigit(password[i])) {
            hasDigit = true;
        } else {
            hasSpecialChar = true;
        }
    }

    // Check if password meets strong criteria
    return hasUpperCase && hasLowerCase && hasDigit && hasSpecialChar;
}


void PasswordLevel(const char *password) {
    int length = strlen(password);
    bool hasLowerCase = false;
    bool hasUpperCase = false;
    bool hasDigit = false;
    bool hasSpecialChar = false;

    // Check each character in the password
    for (int i = 0; i < length; i++) {
        if (islower(password[i])) {
            hasLowerCase = true;
        } else if (isupper(password[i])) {
            hasUpperCase = true;
        } else if (isdigit(password[i])) {
            hasDigit = true;
        } else if (!isalnum(password[i])) {
            hasSpecialChar = true;
        }
    }

    int points = 0;

    // Assign points based on password length
    if (length >= 8 && length <= 15) {
        points += 4;
    } else if (length >= 16 && length <= 23) {
        points += 7;
    } else if (length >= 24 && length <= 30) {
        points += 10;
    }

    // Assign points based on presence of special characters and capital letters
    if (hasSpecialChar) {
        points += 5;
    }
    if (hasUpperCase) {
        points += 5;
    }

    // Split the points in half
    points /= 2;

    // Print the password level based on the points
    if (points >= 9) {
        printf("Strong password.\n");
    } else if (points >= 6) {
        printf("Good password.\n");
    } else {
        printf("Weak password.\n");
    }
}


bool IsValidUserName(const char *username) {
    int length = strlen(username);
    return length > 0 && length <= 30; // Username must not be empty and not exceed 30 characters
}


bool isValidMonth(int month) {
    return month >= 1 && month <= 12; // Month must be between 1 and 12
}


bool isValidDayOfBirth(int day, int month, int year) {
    // Basic validation for day of birth based on the month and year (leap year not considered here)
    if (day < 1 || month < 1 || month > 12) {
        return false;
    }
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2) {
        // Check for February (assuming non-leap year)
        if (year % 4 == 0) {
            daysInMonth[1] = 29; // Leap year
        }
    }
    return day >= 1 && day <= daysInMonth[month - 1];
}


bool isValidYear(int year) {
    return year >= 1900 && year <= 2023; // Year must be between 1900 and 2023
}


bool isValidEmail(const char *email) {
    int length = strlen(email);
    // Very basic email validation: must contain '@' and at least one '.' after '@'
    bool hasAtSymbol = false;
    for (int i = 0; i < length; i++) {
        if (email[i] == '@') {
            hasAtSymbol = true;
        }
        if (hasAtSymbol && email[i] == '.') {
            return true;
        }
    }
    return false;
}


void ViewUserDetails(const User *user) {
    printf("\nUser Details:\n");
    printf("Name: %s\n", user->name);
    printf("Date of Birth: %d/%d/%d\n", user->AgeInfo.DayOfBirth, user->AgeInfo.MonthOfBirth, user->AgeInfo.YearOfBirth);
    printf("Location: %s, %s, Zip Code: %d\n", user->LocationInfo.city, user->LocationInfo.country, user->LocationInfo.zipCode);
    printf("Email: %s\n", user->Email);
}


bool IsExistInSystem(const char *username, const char *password) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return false;
    }

    char line[100];
    bool found = false;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "Name: ") == line) {
            char *name = line + strlen("Name: ");
            strtok(name, "\n"); // Remove newline character

            if (strcmp(name, username) == 0) {
                // Found matching username, now check password
                if (fgets(line, sizeof(line), file) != NULL && strstr(line, "Password: ") == line) {
                    char *storedPassword = line + strlen("Password: ");
                    strtok(storedPassword, "\n"); // Remove newline character

                    if (strcmp(storedPassword, password) == 0) {
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


int Register(User *user) {


    FILE *file = fopen(FILE_NAME, "a+"); // Open file for reading and appending
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    bool isValidInput = false;

    while (!isValidInput) {
        // Get username
        printf("Write Name: ");
        scanf("%s", user->name);

        // Get password
        char password[31];
        printf("Write Password (8-30 characters, must contain letters and numbers): ");
        scanf("%s", password);

        // Check if user exists
        if (IsExistInSystem(user->name, password)) {
            printf("User already exists in the system. Do you want to log in?\n");
            printf("1: Yes\n");
            printf("2: No\n");

            int choice;
            scanf("%d", &choice);

            if (choice == 1) {
                // Implement Login function here
                // Login(user);
                printf("Login function placeholder.\n");
                fclose(file);
                return 2;
            } else {
                fclose(file);
                return 1;
            }
        }

        if (!IsValidUserName(user->name)) {
            printf("Invalid username, please try again.\n");
        } else if (!isValidPassword(password)) {
            printf("Invalid password, please try again.\n");
        } else {
            isValidInput = true; // Valid input, exit the loop
            fprintf(file, "Name: %s\n", user->name);
            fprintf(file, "Password: %s\n", password);
        }
    }

    PasswordLevel(user->password);



    int year, month, day;
    while (true) {
        printf("Write Year of Birth: ");
        scanf("%d", &year);
        if (!isValidYear(year)) {
            printf("Invalid year of birth! Please try again.\n");
            continue; // Prompt user again for a valid year
        }
        user->AgeInfo.YearOfBirth = year;
        fprintf(file, "Year of Birth: %d\n", user->AgeInfo.YearOfBirth);
        break;
    }

    while (true) {
        printf("Write Month of Birth: ");
        scanf("%d", &month);
        if (!isValidMonth(month)) {
            printf("Invalid month of birth! Please try again.\n");
            continue; // Prompt user again for a valid month
        }
        user->AgeInfo.MonthOfBirth = month;
        fprintf(file, "Month of Birth: %d\n", user->AgeInfo.MonthOfBirth);
        break;
    }

    while (true) {
        printf("Write Day of Birth: ");
        scanf("%d", &day);
        if (!isValidDayOfBirth(day, month, year)) {
            printf("Invalid day of birth! Please try again.\n");
            continue; // Prompt user again for a valid day
        }
        user->AgeInfo.DayOfBirth = day;
        fprintf(file, "Day of Birth: %d\n", user->AgeInfo.DayOfBirth);
        break;
    }

    while (true) {
        printf("Write Email: ");
        scanf("%s", user->Email);
        if (!isValidEmail(user->Email)) {
            printf("Invalid email format! Please try again.\n");
            continue; // Prompt user again for a valid email
        }
        fprintf(file, "Email: %s\n", user->Email);
        break;
    }

    printf("Write Zip Code: ");
    scanf("%d", &user->LocationInfo.zipCode);
    fprintf(file, "Zip Code: %d\n", user->LocationInfo.zipCode);

    printf("Write Country: ");
    scanf("%s", user->LocationInfo.country);
    fprintf(file, "Country: %s\n", user->LocationInfo.country);

    printf("Write City: ");
    scanf("%s", user->LocationInfo.city);
    fprintf(file, "City: %s\n", user->LocationInfo.city);

    fprintf(file, "---------------------------------\n");
    fclose(file);
    printf("User registered successfully!\n");


    int choice_see;
    printf("would you like to see your details: 1:yes 2:no\n");
    scanf("%d",&choice_see);
    if(choice_see==1)
    {
        ViewUserDetails(user);
    }

    return 0;
}


void Login(User *user) {
    char username[30];
    char password[31];

    printf("Enter Username: ");
    scanf("%s", username);

    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int found = 0;
    char line[100];

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "Name: ") == line) {
            char *name = line + strlen("Name: ");
            strtok(name, "\n"); // Remove newline character
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

    // Check the password
    if (fgets(line, sizeof(line), file) != NULL && strstr(line, "Password: ") == line) {
        char *storedPassword = line + strlen("Password: ");
        strtok(storedPassword, "\n"); // Remove newline character

        while (loginAttempts < 3) {
            printf("Enter Password: ");
            scanf("%s", password);

            if (strcmp(storedPassword, password) == 0) {
                printf("User successfully logged in.\n");
                loginAttempts = 0; // Reset login attempts on successful login
                ViewSettings(user);
                fclose(file);
                return;
            } else {
                printf("Incorrect password. Please try again.\n");
                loginAttempts++;
            }
        }

        // Account lockout
        printf("Too many incorrect login attempts. Account locked.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    } else {
        printf("Error reading user data.\n");
    }

    fclose(file);

    isLoggedIn = true;
    printf("User logged in.\n");
    CheckActivity(); // Start monitoring for user activity after login

}


void EncryptPassword(char *plaintext, char *ciphertext) {
    char c;
    while (*plaintext) {
        c = *plaintext;
        if (isalpha(c)) {
            if (islower(c)) {
                *ciphertext = 'a' + (c - 'a' + SHIFT) % 26;
            } else {
                *ciphertext = 'A' + (c - 'A' + SHIFT) % 26;
            }
        } else {
            *ciphertext = c; // Non-alphabetic characters remain unchanged
        }
        plaintext++;
        ciphertext++;
    }
    *ciphertext = '\0'; // Add null terminator to end the string
}


void DecryptPassword(char *ciphertext, char *plaintext) {
    char c;
    while (*ciphertext) {
        c = *ciphertext;
        if (isalpha(c)) {
            if (islower(c)) {
                *plaintext = 'a' + (c - 'a' - SHIFT + 26) % 26;
            } else {
                *plaintext = 'A' + (c - 'A' - SHIFT + 26) % 26;
            }
        } else {
            *plaintext = c; // Non-alphabetic characters remain unchanged
        }
        ciphertext++;
        plaintext++;
    }
    *plaintext = '\0'; // Add null terminator to end the string
}


void DeleteAccount(const char *username, const char *password) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    char line[100];
    bool userFound = false;
    bool deleted = false;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "Name: ") == line) {
            char *name = line + strlen("Name: ");
            strtok(name, "\n");

            if (strcmp(name, username) == 0) {
                userFound = true;

                // Check the password
                fgets(line, sizeof(line), file); // Read the password line
                char *storedPassword = line + strlen("Password: ");
                strtok(storedPassword, "\n");

                if (strcmp(storedPassword, password) == 0) {
                    deleted = true;
                    // Skip this user's details in the original file
                    for (int i = 0; i < 5; i++) {
                        fgets(line, sizeof(line), file);
                    }
                    continue; // Skip writing this user to the temp file
                }
            }
        }
        fprintf(tempFile, "%s", line); // Write non-matching lines to temp file
    }

    fclose(file);
    fclose(tempFile);

    if (userFound && deleted) {
        remove(FILE_NAME); // Remove the original file
        rename("temp.txt", FILE_NAME); // Rename temp file to original file
        printf("Account deleted successfully.\n");
    } else if (userFound) {
        printf("Incorrect password. Account deletion failed.\n");
        remove("temp.txt"); // Remove the temp file
    } else {
        printf("User not found.\n");
        remove("temp.txt"); // Remove the temp file
    }
}


void ChangePassword(const char *username, const char *oldPassword, const char *newPassword) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    char line[100];
    bool userFound = false;
    bool passwordChanged = false;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "Name: ") == line) {
            char *name = line + strlen("Name: ");
            strtok(name, "\n");

            if (strcmp(name, username) == 0) {
                userFound = true;

                // Check the password
                fgets(line, sizeof(line), file); // Read the password line
                char *storedPassword = line + strlen("Password: ");
                strtok(storedPassword, "\n");

                if (strcmp(storedPassword, oldPassword) == 0) {
                    passwordChanged = true;
                    // Write updated password to temp file
                    fprintf(tempFile, "Name: %s\n", username);
                    fprintf(tempFile, "Password: %s\n", newPassword);

                    // Copy the remaining user details from the original file to temp file
                    for (int i = 0; i < 4; i++) {
                        fgets(line, sizeof(line), file);
                        fprintf(tempFile, "%s", line);
                    }
                    continue; // Skip writing old user details to the temp file
                }
            }
        }
        fprintf(tempFile, "%s", line); // Write non-matching lines to temp file
    }

    fclose(file);
    fclose(tempFile);

    if (userFound && passwordChanged) {
        remove(FILE_NAME); // Remove the original file
        rename("temp.txt", FILE_NAME); // Rename temp file to original file
        printf("Password changed successfully.\n");
    } else if (userFound) {
        printf("Incorrect password. Password change failed.\n");
        remove("temp.txt"); // Remove the temp file
    } else {
        printf("User not found.\n");
        remove("temp.txt"); // Remove the temp file
    }
}


void ViewSettings(User *user) {
    printf("\nSettings Menu\n");
    printf("1. Delete Account\n");
    printf("2. Change Password\n");
    printf("3. Send Message\n");
    printf("4. Log Out\n");

    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            DeleteAccount(user->name, user->password); // Call DeleteAccount with username and password
            break;
        case 2: {
            char newPassword[31];
            printf("Enter new password: ");
            scanf("%s", newPassword);
            ChangePassword(user->name, user->password, newPassword); // Call ChangePassword with username, old password, and new password
            break;
        }
        case 3:
            // SendMassageToUsers(username);
            break;
        case 4:
            printf("Logging out...\n");
            sleep(2);
            Logout();
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}


void Logout() {
    isLoggedIn = false;
    printf("User logged out due to inactivity.\n");
    DisplaySystemOption(NULL); // Redirect to system option display after logout
}


void CheckActivity() {
    time_t startTime = time(NULL);

    while (isLoggedIn) {
        // Calculate elapsed time since last activity check
        time_t currentTime = time(NULL);
        if (currentTime - startTime >= TIMEOUT_SECONDS) {
            Logout(); // Trigger logout if timeout is reached
            break;
        }

        // Check for user input using getchar() (waits for Enter key press)
        printf("Press any key (1, 2, 3, 4) to reset the timer: ");
        int ch = getchar();

        // Consume any extra characters in the input buffer (clear stdin)
        while (getchar() != '\n');

        if (ch != EOF && (ch == '1' || ch == '2' || ch == '3' || ch == '4')) {
            startTime = time(NULL); // Reset timer on valid key press
            printf("Button %c pressed. Activity detected. Timer reset.\n", ch);
        } else {
            printf("Invalid key pressed. Logging out due to inactivity.\n");
            Logout(); // Logout on invalid key press
        }

        // Sleep for 1 second (simulating continuous activity check loop)
        sleep(1);
    }
}


void ViewSystem(User* user)
{

    printf("1:Send Massage\n2:View Inbox\n3:Send Friend Request\n4:Unfollow SomeOne\n");
    int choice;
    scanf("%d",&choice);

    switch (choice)
    {
    case 1:
        //SendMassageToUsers();
    case 2:
        //ViewInbox();
    case 3:
        //SendFriendRequest();
    case 4:
        //Unfollow();
    default:
        printf("Invalid Choice!!!1");
    }
}


/*things left to finish!!!

1:send massage to users
2:see inbox(friends requests and massages)
3:send friend requests
4:unfollow someone
5:all of this would be in a viewSystem function- where you could press through the settings function!

*/

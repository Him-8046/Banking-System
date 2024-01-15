#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ACCOUNT_NUMBER_LENGTH 10
#define MAX_ACCOUNTS 100

struct BankAccount {
  char bankName[50];
  char ifscCode[12];
  long long accountNumber;
  char accountHolderName[50];
  int age;
  char gender;
  char dob[11];
  char address[100];
  char city[50];
  char typeOfAccount[20];
  double balance;
  char panCardNumber[10];
  long long aadharNumber;
};

struct BankAccount allAccounts[MAX_ACCOUNTS];
int validatePanCard(char *panCard);
int validateAadharNumber(long long aadharNumber);
long long generateUniqueAccountNumber();
void searchByAccountNumber(struct BankAccount *account);
void searchByName(struct BankAccount *account);
void searchByAccountType(struct BankAccount *account);
void createAccount();
void generateAccountNumber();
int findAccountIndexByNumber(long long accountNumber);

int numberOfAccounts = 0;

void updateAccountDetails();
void deposit();
void withdraw();
void fundsTransfer();
void searchDetails();
void balanceEnquiry();
void displayAccountDetails(struct BankAccount *account);

//-----------------------------------------------------------------------------------
void createAccount(struct BankAccount *account) {

  printf("Enter Bank Name: ");
  scanf("%s", account->bankName);

  printf("Enter IFSC Code: ");
  scanf("%s", account->ifscCode);

  // Validating name
  do {
    printf("Enter Account Holder Name: ");
    scanf("%s", account->accountHolderName);
    if (strlen(account->accountHolderName) < 2) {
      printf("Invalid name. Please enter a valid name.\n");
    }
  } while (strlen(account->accountHolderName) < 2);

  // Validating  gender
  do {
    printf("Enter Gender (M/F): ");
    scanf(" %c", &account->gender);
    if (account->gender != 'M' && account->gender != 'F') {
      printf("Invalid gender. Please enter either 'Male' or 'Female'.\n");
    }
  } while (account->gender != 'M' && account->gender != 'F');

  printf("Enter Date of Birth (DD/MM/YYYY): ");
  scanf("%s", account->dob);

  printf("Enter Address: ");
  scanf("%s", account->address);

  printf("Enter City: ");
  scanf("%s", account->city);

  do {
    printf("Enter Type of Account (Saving/Current): ");
    scanf("%s", account->typeOfAccount);
    if (strcmp(account->typeOfAccount, "Saving") != 0 &&
        strcmp(account->typeOfAccount, "Current") != 0) {
      printf(
          "Invalid account type. Please enter either 'Saving' or 'Current'.\n");
    }
  } while (strcmp(account->typeOfAccount, "Saving") != 0 &&
           strcmp(account->typeOfAccount, "Current") != 0);

  // Validating and taking initial balance
  do {
    printf("Enter Initial Balance: ");
    scanf("%lf", &account->balance);
    if (account->balance < 0) {
      printf("Invalid balance. Please enter a non-negative balance.\n");
    }
  } while (account->balance < 0);

  // Validating  PAN card number
  do {
    printf("Enter PAN Card Number: ");
    scanf("%s", account->panCardNumber);
    if (validatePanCard(account->panCardNumber) == 0) {
      printf("Invalid PAN Card Number. Please enter a valid PAN.\n");
    }
  } while (validatePanCard(account->panCardNumber) == 0);

  // Validating  Aadhar number
  do {
    printf("Enter Aadhar Number: ");
    scanf("%lld", &account->aadharNumber);
    if (validateAadharNumber(account->aadharNumber) == 0) {
      printf("Invalid Aadhar Number. Please enter a valid 12-digit Aadhar "
             "number.\n");
    }
  } while (validateAadharNumber(account->aadharNumber) == 0);

  // Generating a unique account number
  account->accountNumber = generateUniqueAccountNumber();

  // Displaying the unique account number
  printf("\nAccount created successfully!\n");
  printf("Your Unique Account Number: %lld\n", account->accountNumber);
}

int validatePanCard(char *panCard) {
  // PAN card should have the format: ABCDE1234F
  int i;

  // Checking if the first five characters are alphabets
  for (i = 0; i < 5; i++) {
    if (!isalpha(panCard[i])) {
      return 0;
    }
  }

  // Checking if the next four characters are digits
  for (; i < 9; i++) {
    if (!isdigit(panCard[i])) {
      return 0;
    }
  }

  // Checking if the last character is an alphabet
  if (!isalpha(panCard[i])) {
    return 0;
  }

  // Checking if the total length is 10
  if (strlen(panCard) != 10) {
    return 0;
  }

  return 1;
}

int validateAadharNumber(long long aadharNumber) {

  if (aadharNumber >= 100000000000 && aadharNumber <= 999999999999) {
    return 1;
  }
  return 0;
}

long long generateUniqueAccountNumber() {
  long long timestamp = time(NULL);
  srand(timestamp);
  long long randomPart = rand() % 900 + 100;
  return timestamp * 1000000 + randomPart;
}

void generateAccountNumber(char first_name[], char account_number[]) {

  char first_letter[2];
  first_letter[0] = toupper(first_name[0]);
  first_letter[1] = '\0';

  srand(time(NULL));
  int random_digits = rand() % 900000000 + 100000000;

  char random_digits_str[10];
  printf(random_digits_str, "%d", random_digits);

  printf(account_number, ACCOUNT_NUMBER_LENGTH + 1, "%c%c%s", first_letter,
         random_digits_str);
  strcat(first_letter, random_digits_str);
  printf("%s", first_letter);
}

void updateAccountHolderNameByNumber() {
  long long enteredAccountNumber;

  printf("\nEnter the Account Number to update the name: ");
  scanf("%lld", &enteredAccountNumber);

  // Call the function to find the index
  int index = findAccountIndexByNumber(enteredAccountNumber);

  if (index != -1) {
    // Prompt for the new name
    printf("Enter the new name: ");
    scanf("%s", allAccounts[index].accountHolderName);
    printf("Name updated successfully!\n");
  } else {
    printf("Account not found. Update failed.\n");
  }
}

void updateAccountDetails(struct BankAccount *account) {
  char choice;
  long long enteredAccountNumber;

  printf("\nEnter the Account Number to update details: ");
  scanf("%lld", &enteredAccountNumber);

  // Call the function to find the index
  int index = findAccountIndexByNumber(enteredAccountNumber);

  if (index != -1) {
    printf("\nUpdate Account Details Menu:\n");
    printf("a. Update name of account holder\n");
    printf("b. Update address of account holder\n");
    printf("c. Update DOB of account holder\n");

    printf("\nEnter your choice: ");
    scanf(" %c", &choice);

    switch (choice) {
    case 'a':
      // Update name
      updateAccountHolderNameByNumber();
      break;
    case 'b':
      // Update address
      printf("Enter new address: ");
      scanf("%s", allAccounts[index].address);
      printf("Address updated successfully!\n");
      break;
    case 'c':
      // Update date of birth
      printf("Enter new Date of Birth (DD/MM/YYYY): ");
      scanf("%s", allAccounts[index].dob);
      printf("Date of Birth updated successfully!\n");
      break;
    default:
      printf("Invalid choice. No updates performed.\n");
    }
  } else {
    printf("Account not found. Update failed.\n");
  }
}

void deposit(struct BankAccount *account) {
  long long enteredAccountNumber;
  double depositAmount;

  printf("\nEnter your Account Number: ");
  scanf("%lld", &enteredAccountNumber);

  // Checking if the entered account number matches the account's unique account

  if (enteredAccountNumber != account->accountNumber) {
    printf("Invalid Account Number. Deposit canceled.\n");
    return;
  }

  printf("Enter the amount to deposit: ");
  scanf("%lf", &depositAmount);

  // Checking if deposit amount is valid
  if (depositAmount <= 0) {
    printf("Invalid deposit amount. Please enter a positive amount.\n");
    return;
  }

  // Perform the deposit
  account->balance += depositAmount;

  // Displaying the current balance
  printf("Deposit successful!\n");
  printf("Current Balance: %.2lf\n", account->balance);
}

void withdraw(struct BankAccount *allAccounts) {
  long long enteredAccountNumber;
  double withdrawAmount;

  printf("\nEnter your Account Number: ");
  scanf("%lld", &enteredAccountNumber);

  // Finding the account with the entered account number
  int index = findAccountIndexByNumber(enteredAccountNumber);

  if (index != -1) {
    // Rest of the withdrawal logic...

    printf("Enter the amount to withdraw: ");
    scanf("%lf", &withdrawAmount);

    // Checking if withdrawal amount is valid
    if (withdrawAmount <= 0) {
      printf("Invalid withdrawal amount. Please enter a positive amount.\n");
      return;
    }

    // Checking if the withdrawal amount is within the allowed limit
    if ((strcmp(allAccounts[index].typeOfAccount, "Saving") == 0 ||
         strcmp(allAccounts[index].typeOfAccount, "Current") == 0) &&
        withdrawAmount > 2000) {
      printf(
          "Withdrawal amount exceeds the allowed limit for Saving and Current "
          "accounts. Maximum limit is 2000.\n");
      return;
    }

    // Checking if there are sufficient funds for withdrawal
    if (allAccounts[index].balance < withdrawAmount) {
      printf("Insufficient funds. Withdrawal canceled.\n");
      return;
    }

    // Performing the withdrawal
    allAccounts[index].balance -= withdrawAmount;

    printf("Withdrawal successful!\n");
    printf("Current Balance: %.2lf\n", allAccounts[index].balance);
  } else {
    printf("Account not found. Withdrawal canceled.\n");
  }
}

void fundsTransfer(struct BankAccount *allAccounts) {
  long long senderAccountNumber, receiverAccountNumber;
  double transferAmount;

  printf("\nEnter your Account Number (Sender): ");
  scanf("%lld", &senderAccountNumber);

  // Finding the account with the entered sender's account number
  int senderIndex = findAccountIndexByNumber(senderAccountNumber);

  if (senderIndex != -1) {
    printf("Enter the Receiver's Account Number: ");
    scanf("%lld", &receiverAccountNumber);

    // Checking if the entered receiver's account number matches any account's
    // unique account number
    int receiverIndex = findAccountIndexByNumber(receiverAccountNumber);

    if (receiverIndex != -1) {
      printf("Enter the amount to transfer: ");
      scanf("%lf", &transferAmount);

      // Checking if transfer amount is valid
      if (transferAmount <= 0) {
        printf("Invalid transfer amount. Please enter a positive amount.\n");
        return;
      }

      // Checking if there are sufficient funds for transfer
      if (allAccounts[senderIndex].balance < transferAmount) {
        printf("Insufficient funds. Transfer canceled.\n");
        return;
      }

      // Deducting the amount from the sender's account
      allAccounts[senderIndex].balance -= transferAmount;

      // Depositing the amount into the receiver's account
      allAccounts[receiverIndex].balance += transferAmount;

      // Displaying the transfer details
      printf("Transfer successful!\n");
      printf("Amount Transferred: %.2lf\n", transferAmount);
      printf("Remaining Balance (Sender): %.2lf\n",
             allAccounts[senderIndex].balance);
      printf("Updated Balance (Receiver): %.2lf\n",
             allAccounts[receiverIndex].balance);
    } else {
      printf("Receiver's account not found. Transfer canceled.\n");
    }
  } else {
    printf("Sender's account not found. Transfer canceled.\n");
  }
}

void searchDetails(struct BankAccount *account) {
  char choice;

  printf("\nSearch Details Menu:\n");
  printf("a. Search by account number\n");
  printf("b. Search by name\n");
  printf("c. Search by Type of Account\n");

  printf("\nEnter your choice: ");
  scanf(" %c", &choice);

  switch (choice) {
  case 'a':
    searchByAccountNumber(account);
    break;
  case 'b':
    searchByName(account);
    break;
  case 'c':
    searchByAccountType(account);
    break;
  default:
    printf("Invalid choice. No search performed.\n");
  }
}

void searchByAccountNumber(struct BankAccount *account) {
  long long enteredAccountNumber;

  printf("\nEnter the Account Number to search: ");
  scanf("%lld", &enteredAccountNumber);

  // Finding the account with the entered account number
  int index = -1;
  for (int i = 0; i < numberOfAccounts; i++) {
    if (allAccounts[i].accountNumber == enteredAccountNumber) {
      index = i;
      break;
    }
  }

  if (index != -1) {

    printf("\nAccount Details:\n");
    displayAccountDetails(&allAccounts[index]);
  } else {
    printf("Account not found.\n");
  }
}

void searchByName(struct BankAccount *account) {
  char enteredName[50];

  printf("\nEnter the Name to search: ");
  scanf("%s", enteredName);

  // Finding the account with the entered name
  int found = 0;
  for (int i = 0; i < numberOfAccounts; i++) {
    if (strcmp(allAccounts[i].accountHolderName, enteredName) == 0) {

      displayAccountDetails(&allAccounts[i]);
      found = 1;
    }
  }

  if (!found) {
    printf("Account not found.\n");
  }
}

void searchByAccountType(struct BankAccount *account) {
  char enteredAccountType[20];

  printf("\nEnter the Type of Account to search (Saving/Current): ");
  scanf("%s", enteredAccountType);

  // Finding the accounts with the entered account type
  int found = 0;
  for (int i = 0; i < numberOfAccounts; i++) {
    if (strcmp(allAccounts[i].typeOfAccount, enteredAccountType) == 0) {

      displayAccountDetails(&allAccounts[i]);
      found = 1;
    }
  }

  if (!found) {
    printf("No accounts found with the specified account type.\n");
  }
}

void displayAccountDetails(struct BankAccount *account) {
  printf("\nAccount Holder Name: %s\n", account->accountHolderName);
  printf("Account Number: %lld\n", account->accountNumber);
  printf("Type of Account: %s\n", account->typeOfAccount);
  printf("Balance: %.2lf\n", account->balance);
}

void balanceEnquiry(struct BankAccount *account) {
  long long enteredAccountNumber;

  printf("\nEnter your Account Number: ");
  scanf("%lld", &enteredAccountNumber);

  // Finding the account with the entered account number
  int index = -1;
  for (int i = 0; i < numberOfAccounts; i++) {
    if (allAccounts[i].accountNumber == enteredAccountNumber) {
      index = i;
      break;
    }
  }

  if (index != -1) {

    printf("\nAccount Balance: %.2lf\n", allAccounts[index].balance);
  } else {
    printf("Account not found. Balance inquiry failed.\n");
  }
}

int findAccountIndexByNumber(long long accountNumber) {
  for (int i = 0; i < numberOfAccounts; i++) {
    if (allAccounts[i].accountNumber == accountNumber) {
      return i;
    }
  }
  return -1; // Account not found
}

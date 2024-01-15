#include "validate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initializeTestData() {
  // Initialize some test data for accounts
  struct BankAccount account1 = {.bankName = "TestBank",
                                 .ifscCode = "TEST123456",
                                 .accountNumber = 1234567890,
                                 .accountHolderName = "John Doe",
                                 .age = 30,
                                 .gender = 'M',
                                 .dob = "01/01/1990",
                                 .address = "123 Main St",
                                 .city = "TestCity",
                                 .typeOfAccount = "Saving",
                                 .balance = 1000.0,
                                 .panCardNumber = "ABCDE1234F",
                                 .aadharNumber = 123456789012};

  struct BankAccount account2 = {.bankName = "TestBank",
                                 .ifscCode = "TEST123456",
                                 .accountNumber = 1234567899,
                                 .accountHolderName = "Jane Doe",
                                 .age = 25,
                                 .gender = 'F',
                                 .dob = "02/02/1995",
                                 .address = "456 Oak St",
                                 .city = "TestCity",
                                 .typeOfAccount = "Current",
                                 .balance = 2000.0,
                                 .panCardNumber = "FGHIJ5678K",
                                 .aadharNumber = 987654321098};

  // Assign test data to allAccounts array
  allAccounts[0] = account1;
  allAccounts[1] = account2;

  numberOfAccounts = 2; // Update the number of accounts
}

int main() {
  int choice;
  initializeTestData();
  do {
    printf("\nMenu:\n");
    printf("1. Create Account\n");
    printf("2. Update Account Details\n");
    printf("3. Deposit\n");
    printf("4. Withdraw\n");
    printf("5. Funds Transfer\n");
    printf("6. Search Details of Account Holder\n");
    printf("7. Balance Enquiry\n");
    printf("8. Exit\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      createAccount(&allAccounts[numberOfAccounts]);
      numberOfAccounts++;
      break;
    case 2:
      updateAccountDetails(allAccounts);
      break;
    case 3:
      deposit(allAccounts);
      break;
    case 4:
      withdraw(allAccounts);
      break;
    case 5:
      fundsTransfer(allAccounts);
      break;
    case 6:
      searchDetails(allAccounts);
      break;
    case 7:
      balanceEnquiry(allAccounts);
      break;
    case 8:
      printf("Exiting the program. Goodbye!\n");
      exit(0);
    default:
      printf("Invalid choice. Please enter a valid option.\n");
    }
  } while (1);

  return 0;
}

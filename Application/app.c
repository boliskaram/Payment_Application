#include "app.h"

void appStart(void) {

	uint32_t option;
	uint8_t opt = 'y';

	while ((opt == 'y') || (opt == 'Y')) {
		printf("What Do You Want\n");
		printf("Enter 1 : If Want To Withdraw An Amount\n");
		printf("Enter 2 : If Want To Print All Transactions\n");
		printf("Enter 3 : If Want To show Balance\n");
		printf("Please, Enter Your Choice : ");
		scanf_s("%d", &option);
		printf("\n");
		switch (option)
		{
		case 1:
			withdrawAnAmount();
			break;
		case 2:
			listSavedTransactions();
			break;
		case 3:
			showBalance();
			break;
		default:
			printf("Bye Bye");
			break;
		}
		printf("\n\n");
		printf("If you Want To Continue Press y/Y If Not Press Any Key : ");
		scanf_s(" %c", &opt, 1);
	}
}

void withdrawAnAmount(void) {
	EN_cardError_t cardError = CARD_OK;
	EN_terminalError_t terminalError = TERMINAL_OK;
	EN_transState_t transactionError = APPROVED;
	float maxAmount;


	cardError = getCardHolderName(&Server.cardHolderData);
	if (cardError == WRONG_NAME) {
		printf("Wrong Name Lenght\n");
	}
	else {
		cardError = getCardExpiryDate(&Server.cardHolderData);
		//printf("2: %s\n", Server.cardHolderData.cardExpirationDate);
		if (cardError == WRONG_EXP_DATE) {
			printf("Wrong Card Expiration Date Format\n");
		}
		else {
			cardError = getCardPAN(&Server.cardHolderData);
			if (cardError == WRONG_PAN) {
				printf("Wrong PAN Lenght\n");
			}
			else {
				//printf("22: %s\n", Server.cardHolderData.cardExpirationDate);
				terminalError = isValidCardPAN(&Server.cardHolderData);
				if (terminalError == INVALID_CARD) {
					printf("Invalid Card\n");
				}
				else {
					//printf("23: %s\n", Server.cardHolderData.cardExpirationDate);
					terminalError = getTransactionDate(&Server.terminalData);
					if (terminalError == WRONG_DATE) {
						printf("Wrong Transaction Date Format\n");
					}
					else {
						terminalError = isCardExpired(&Server.cardHolderData, &Server.terminalData);
						if (terminalError == EXPIRED_CARD) {
							printf("Sorry, Card Is Expired\n");
						}
						else {
							terminalError = getTransactionAmount(&Server.terminalData);
							if (terminalError == INVALID_AMOUNT) {
								printf("Invalid Amount\n");
							}
							else {
								printf("Enter What is Max Amount Of Transaction : ");
								scanf_s(" %f", &maxAmount);
								terminalError = setMaxAmount(&Server.terminalData, maxAmount);
								if (terminalError == INVALID_MAX_AMOUNT) {
									printf("Invalid Max Amount\n");
									printf("Insufficient Amount For Draw\n");
								}
								else {
									terminalError = isBelowMaxAmount(&Server.terminalData);
									if (terminalError == EXCEED_MAX_AMOUNT) {
										printf("Exceed Max Amount\n");
									}
									else {
										//printf("3: %s\n", Server.cardHolderData.cardExpirationDate);
										transactionError = recieveTransactionData(&Server);
										if (transactionError == FRAUD_CARD) {
											printf("Sorry, The Account Not Found\n");
										}
										else if (transactionError == DECLINED_STOLEN_CARD) {
											printf("Sorry, The Account Is Blocking\n");
										}
										else if (transactionError == DECLINED_INSUFFECIENT_FUND) {
											printf("Sorry, Amount Larger Than Balance\n");
										}
										else if (transactionError == INTERNAL_SERVER_ERROR) {
											printf("Sorry, Not Available Transactions\n");
										}
										else {
											printf("The Operation Was Completed Successfully\n");
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}


void showBalance() {
	EN_cardError_t cardError = CARD_OK;
	EN_terminalError_t terminalError = TERMINAL_OK;
	EN_transState_t transactionError = APPROVED;

	float balance;

	cardError = getCardPAN(&Server.cardHolderData);
	if (cardError == WRONG_PAN) {
		printf("Wrong PAN Lenght\n");
	}
	else {
		//printf("22: %s\n", Server.cardHolderData.cardExpirationDate);
		terminalError = isValidCardPAN(&Server.cardHolderData);
		if (terminalError == isValidCardPAN) {
			printf("Invalid Card\n");
		}
		else {
			transactionError = getBalance(&Server, &balance);
			if (transactionError == FRAUD_CARD) {
				printf("Sorry, The Account Not Found\n");
			}
			else if (transactionError == DECLINED_STOLEN_CARD) {
				printf("Sorry, The Account is Blocked\n");
			}
			else {
				printf("Balance : %f\n", balance);
			}
		}
	}
}
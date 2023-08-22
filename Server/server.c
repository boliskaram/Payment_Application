#include "server.h"

ST_accountsDB_t accountsDB[255] = {{89473.0,   RUNNING, "4049678739263564988" },
									{3000.0,   RUNNING, "140920138399124246"  },
									{6745.0,   RUNNING, "206406446907051021"  },
									{1828.5,   RUNNING, "572692717464884824"  },
									{23405.5,  BLOCKED, "85873138797802637"   },
									{531.0,    RUNNING, "41877743878996239"   },
									{12000.0,  RUNNING, "1364514816054975"    },
									{89473.0,  BLOCKED, "9047662884040810"	  }};

// accountIndex, it is which account I make check if  exist in database
uint32_t accountIndex = 0;

// transactionIndex, it's number of transaction in database
uint32_t transactionIndex = 0;

//transactionsDB, database for any transactions happened;
ST_transaction_t transactionsDB[255] = { 0 };



/* Description:
 * - This function takes a reference to an structure of transaction data 
 * - check if account is exist and status and amount and save data 
 * Return
 * - returns APPROVED if all checks passed 
 * - returns FRAUD_CARD if account doesn't exist in database
 * - returns DECLINED_STOLEN_CARD if account is Blocked
 * - returns DECLINED_INSUFFECIENT_FUND if account hasn't sufficient amount to draw
 * - returns INTERNAL_SERVER_ERROR if internal server error happened
 */
EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	accountIndex = 0;
	EN_transState_t HandlerecieveTransactionError = APPROVED;
	EN_serverError_t  serverStatus = SERVER_OK;
	serverStatus = isValidAccount(&transData->cardHolderData, accountsDB);
	//printf("DEBUG 1 \n");
	if (serverStatus == ACCOUNT_NOT_FOUND) {
		//printf("DEBUG 2 \n");
		HandlerecieveTransactionError = FRAUD_CARD;
	}
	else {
		serverStatus = isBlockedAccount(accountsDB);
		//printf("DEBUG 3 \n");
		if (serverStatus == BLOCKED_ACCOUNT) {
			//printf("DEBUG 4 \n");
			HandlerecieveTransactionError = DECLINED_STOLEN_CARD;
		}
		else {
			serverStatus = isAmountAvailable(&transData->terminalData, accountsDB);
			//printf("DEBUG 5 \n");
			if (serverStatus == LOW_BALANCE) {
				//printf("DEBUG 6 \n");
				HandlerecieveTransactionError = DECLINED_INSUFFECIENT_FUND;
			}
			else {
				//printf("DEBUG 7 \n");
				transData->transactionSequenceNumber = transactionIndex + 1;
				if (transData->transactionSequenceNumber >= 255) {
					//printf("DEBUG 8 \n");
					HandlerecieveTransactionError = INTERNAL_SERVER_ERROR;
				}
				else {
					//printf("DEBUG 9 \n");
					HandlerecieveTransactionError = APPROVED;
					accountsDB[accountIndex].balance = accountsDB[accountIndex].balance - transData->terminalData.transAmount;
				}
			}
		}
	}
	
	transData->transState = HandlerecieveTransactionError;
	saveTransaction(transData);

	return HandlerecieveTransactionError;
}

/* Description:
 * - test all possible scenarios, happy-case, and worst-case scenarios for recieveTransactionData function.
 * - Print all results of your test cases on the console window.
 */
void recieveTransactionDataTest(void) {

	EN_transState_t recieveTransactionDataStatus = APPROVED;

	printf("Tester Name : Bolis Karam\n");
	printf("Function Name : recieveTransactionData\n\n");
	
	//Test Case 1 PAN & Amount Valid 
	printf("Test Case 1 : \n");
	printf("Input Data  : 4049678739263564988\n");
	printf("Input Data  : 4500\n");
	printf("Input Data  : 244\n");
	getCardPAN(&Server.cardHolderData);
	getTransactionAmount(&Server.terminalData);
	printf("Enter Transaction Sequence Number : ");
	scanf_s("%d", &Server.transactionSequenceNumber);
	recieveTransactionDataStatus = recieveTransactionData(&Server);
	printf("Expected Result : APPROVED\n");
	if (recieveTransactionDataStatus == APPROVED) {
		printf("Actual Result	: APPROVED \n\n");
	}
	else {
		printf("Actual Result	: OTHER \n\n");
	}

	//Test Case 2 PAN Invalid 
	printf("Test Case 2 : \n");
	printf("Input Data  : 14092013839924746\n");
	printf("Input Data  : 1200\n");
	printf("Input Data  : 50\n");
	getCardPAN(&Server.cardHolderData);
	getTransactionAmount(&Server.terminalData);
	printf("Enter Transaction Sequence Number : ");
	scanf_s("%d", &Server.transactionSequenceNumber);
	recieveTransactionDataStatus = recieveTransactionData(&Server);
	printf("Expected Result : FRAUD_CARD\n");
	if (recieveTransactionDataStatus == APPROVED) {
		printf("Actual Result	: APPROVED \n\n");
	}
	else {
		printf("Actual Result	: FRAUD_CARD \n\n");
	}

	//Test Case 3 PAN Valid & Amount Invalid 
	printf("Test Case 3 : \n");
	printf("Input Data  : 140920138399124246\n");
	printf("Input Data  : 4250\n");
	printf("Input Data  : 200\n");
	getCardPAN(&Server.cardHolderData);
	getTransactionAmount(&Server.terminalData);
	printf("Enter Transaction Sequence Number : ");
	scanf_s("%d", &Server.transactionSequenceNumber);
	recieveTransactionDataStatus = recieveTransactionData(&Server);
	printf("Expected Result : DECLINED_INSUFFECIENT_FUND\n");
	if (recieveTransactionDataStatus == APPROVED) {
		printf("Actual Result	: APPROVED \n\n");
	}
	else {
		printf("Actual Result	: DECLINED_INSUFFECIENT_FUND \n\n");
	}

	//Test Case 4 BLOCKED account 
	printf("Test Case 4 : \n");
	printf("Input Data  : 85873138797802637\n");
	printf("Input Data  : 7000\n");
	printf("Input Data  : 125\n");
	getCardPAN(&Server.cardHolderData);
	getTransactionAmount(&Server.terminalData);
	printf("Enter Transaction Sequence Number : ");
	scanf_s("%d", &Server.transactionSequenceNumber);
	recieveTransactionDataStatus = recieveTransactionData(&Server);
	printf("Expected Result : DECLINED_STOLEN_CARD\n");
	if (recieveTransactionDataStatus == APPROVED) {
		printf("Actual Result	: APPROVED \n\n");
	}
	else {
		printf("Actual Result	: DECLINED_STOLEN_CARD \n\n");
	}

	//Test Case 5 transactionSequenceNumber > 255
	printf("Test Case 5 : \n");
	printf("Input Data  : 41877743878996239\n");
	printf("Input Data  : 200\n");
	printf("Input Data  : 268\n");
	getCardPAN(&Server.cardHolderData);
	getTransactionAmount(&Server.terminalData);
	printf("Enter Transaction Sequence Number : ");
	scanf_s("%d", &Server.transactionSequenceNumber);
	recieveTransactionDataStatus = recieveTransactionData(&Server);
	printf("Expected Result : INTERNAL_SERVER_ERROR\n");
	if (recieveTransactionDataStatus == APPROVED) {
		printf("Actual Result	: APPROVED \n\n");
	}
	else {
		printf("Actual Result	: INTERNAL_SERVER_ERROR \n\n");
	}
}

/* Description:
 * - This function takes a reference to an structure of Card Data and accounts database
 * - Search if account exist in database or not 
 * Return
 * - returns SERVER_OK if account exist in database
 * - returns ACCOUNT_NOT_FOUND if account doesn't exist in database
 */
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {

	EN_serverError_t HandleValidAccountError = SERVER_OK;

	for (accountIndex; accountIndex < accountNumber; accountIndex++) {
		if (strcmp(cardData->primaryAccountNumber, accountRefrence[accountIndex].primaryAccountNumber) == 0) {
			HandleValidAccountError = SERVER_OK;
			break;
		}
		else {
			HandleValidAccountError = ACCOUNT_NOT_FOUND;
		}
	}
	return HandleValidAccountError;
}

/* Description:
 * - test all possible scenarios, happy-case, and worst-case scenarios for isValidAccount function.
 * - Print all results of your test cases on the console window.
 */
void isValidAccountTest(void) {

	EN_serverError_t HandleValidAccountStatus = SERVER_OK;

	printf("Tester Name : Bolis Karam\n");
	printf("Function Name :isValidAccount \n\n");
	
	//Test Case 1 Valid PAN 
	printf("Test Case 1 : \n");
	printf("Input Data  : 206406446907051021\n");
	getCardPAN(&Server.cardHolderData);
	HandleValidAccountStatus = isValidAccount(&Server.cardHolderData, accountsDB);
	printf("Expected Result : SERVER_OK\n");
	if (HandleValidAccountStatus == ACCOUNT_NOT_FOUND) {
		printf("Actual Result	: ACCOUNT_NOT_FOUND\n\n");
	}
	else {
		printf("Actual Result	: SERVER_OK \n\n");
	}

	//Test Case 2 Invalid PAN 
	printf("Test Case 2 : \n");
	printf("Input Data  : 4049678739263524788\n");
	getCardPAN(&Server.cardHolderData);
	HandleValidAccountStatus = isValidAccount(&Server.cardHolderData, accountsDB);
	printf("Expected Result : ACCOUNT_NOT_FOUND\n");
	if (HandleValidAccountStatus == ACCOUNT_NOT_FOUND) {
		printf("Actual Result	: ACCOUNT_NOT_FOUND\n\n");
	}
	else {
		printf("Actual Result	: SERVER_OK \n\n");
	}
}

/* Description:
 * - This function takes a reference to an accounts database
 * - check if account is Blocked or not
 * Return
 * - returns SERVER_OK if account is Running
 * - returns BLOCKED_ACCOUNT if account is Blocked
 */
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {

	EN_serverError_t BlockedAccountError = SERVER_OK;

	if (accountRefrence[accountIndex].state == BLOCKED) {
		BlockedAccountError = BLOCKED_ACCOUNT;
	}
	else {
		BlockedAccountError = SERVER_OK;
	}
	return BlockedAccountError;
}

/* Description:
 * - test all possible scenarios, happy-case, and worst-case scenarios for isBlockedAccount function.
 * - Print all results of your test cases on the console window.
 */
void isBlockedAccountTest(void){

	EN_serverError_t HandleBlockedAccountStatus = SERVER_OK;

	printf("Tester Name : Bolis Karam\n");
	printf("Function Name : isBlockedAccount \n\n");

	//Test Case 1 Valid PAN 
	printf("Test Case 1 : \n");
	printf("Input Data  : 140920138399124246\n");
	getCardPAN(&Server.cardHolderData);
	isValidAccount(&Server.cardHolderData, accountsDB);
	HandleBlockedAccountStatus = isBlockedAccount(accountsDB);
	printf("Expected Result : SERVER_OK\n");
	if (HandleBlockedAccountStatus == BLOCKED_ACCOUNT) {
		printf("Actual Result	: BLOCKED_ACCOUNT\n\n");
	}
	else {
		printf("Actual Result	: SERVER_OK \n\n");
	}

	//Test Case 2 Invalid PAN 
	printf("Test Case 2 : \n");
	printf("Input Data  : 85873138797802637\n");
	getCardPAN(&Server.cardHolderData);
	isValidAccount(&Server.cardHolderData, accountsDB);
	HandleBlockedAccountStatus = isBlockedAccount(accountsDB);
	printf("Expected Result : BLOCKED_ACCOUNT\n");
	if (HandleBlockedAccountStatus == BLOCKED_ACCOUNT) {
		printf("Actual Result	: BLOCKED_ACCOUNT\n\n");
	}
	else {
		printf("Actual Result	: SERVER_OK \n\n");
	}
}

/* Description:
 * - This function takes a reference to an structure of Terminal Data and accounts database
 * - check if account has sufficient amount to draw or not
 * Return
 * - returns SERVER_OK if account has sufficient amount to draw
 * - returns LOW_BALANCE if account hasn't sufficient amount to draw
 */
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {
	
	EN_serverError_t HandleAmountAvailableError = SERVER_OK;

	if (termData->transAmount < accountRefrence[accountIndex].balance) {
		HandleAmountAvailableError = SERVER_OK;
	}
	else {
		HandleAmountAvailableError = LOW_BALANCE;
	}
	return HandleAmountAvailableError;
}

/* Description:
 * - test all possible scenarios, happy-case, and worst-case scenarios for isAmountAvailable function.
 * - Print all results of your test cases on the console window.
 */
void isAmountAvailableTest(void) {
	EN_serverError_t HandleAmountAvailableStatus = SERVER_OK;

	printf("Tester Name : Bolis Karam\n");
	printf("Function Name : isAmountAvailable\n\n");

	//Test Case 1 Valid PAN 
	printf("Test Case 1 : \n");
	printf("Input Data  : 4049678739263564988\n");
	printf("Input Data  : 10000\n");
	getCardPAN(&Server.cardHolderData);
	isValidAccount(&Server.cardHolderData, accountsDB);
	getTransactionAmount(&Server.terminalData.transAmount);
	HandleAmountAvailableStatus = isAmountAvailable(&Server.terminalData,accountsDB);
	printf("Expected Result : SERVER_OK\n");
	if (HandleAmountAvailableStatus == SERVER_OK) {
		printf("Actual Result	: SERVER_OK \n\n");
	}
	else {
		printf("Actual Result	: LOW_BALANCE\n\n");
	}

	//Test Case 2 Invalid PAN 
	printf("Test Case 2 : \n");
	printf("Input Data  : 572692717464884824\n");
	printf("Input Data  : 2540\n");
	getCardPAN(&Server.cardHolderData);
	isValidAccount(&Server.cardHolderData, accountsDB);
	getTransactionAmount(&Server.terminalData.transAmount);
	HandleAmountAvailableStatus = isAmountAvailable(&Server.terminalData, accountsDB);
	printf("Expected Result : LOW_BALANCE\n");
	if (HandleAmountAvailableStatus == SERVER_OK) {
		printf("Actual Result	: SERVER_OK \n\n");
	}
	else {
		printf("Actual Result	: LOW_BALANCE\n\n");
	}
}

/* Description:
 * - This function takes a reference to an structure of Server data
 * - this function store all data of transaction in database
 * Return
 * - returns SERVER_OK all time
 */
EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	
	EN_serverError_t HandlesaveTransactionError = SERVER_OK;
	
	if (transData->transactionSequenceNumber <= 255) {
		strcpy_s(transactionsDB[transactionIndex].terminalData.transactionDate,11, transData->terminalData.transactionDate);
		transactionsDB[transactionIndex].terminalData.transAmount = transData->terminalData.transAmount;
		transactionsDB[transactionIndex].transState = transData->transState;
		transactionsDB[transactionIndex].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
		strcpy_s(transactionsDB[transactionIndex].cardHolderData.cardHolderName,25, transData->cardHolderData.cardHolderName);
		strcpy_s(transactionsDB[transactionIndex].cardHolderData.primaryAccountNumber,20, transData->cardHolderData.primaryAccountNumber);
		strcpy_s(transactionsDB[transactionIndex].cardHolderData.cardExpirationDate, 6, transData->cardHolderData.cardExpirationDate);
		transactionIndex++;
		HandlesaveTransactionError = SERVER_OK;
	}
	else {
		HandlesaveTransactionError = SAVING_FAILED;
	}
	return HandlesaveTransactionError;
}

/* Description:
 * - test all possible scenarios, happy-case, and worst-case scenarios saveTransaction function.
 * - Print all results of your test cases on the console window.
 */
void saveTransactionTest(void) {
	
	uint32_t Status;

	printf("Tester Name : Bolis Karam\n");
	printf("Function Name : saveTransaction\n\n");
	//Test Case 1 
	printf("Test Case 1 : \n");
	printf("Input Data  : 15/01/2007\n");
	printf("Input Data  : 500\n");
	printf("Input Data  : APPROVAL = 0\n");
	printf("Input Data  : 3000\n");
	printf("Input Data  : KaramBolisBeshoyKaram\n");
	printf("Input Data  : 572692717464884824\n");
	printf("Input Data  : 11/08\n");
	getTransactionDate(&Server.terminalData);
	getTransactionAmount(&Server.terminalData);
	printf("Enter Status Number : ");
	scanf_s("%d", &Status);
	Server.transState = Status;
	setMaxAmount(&Server.terminalData, 9000);
	getCardHolderName(&Server.cardHolderData);
	getCardPAN(&Server.cardHolderData);
	getCardExpiryDate(&Server.cardHolderData);

	saveTransaction(&Server);
	
	listSavedTransactions();

	//Test Case 2   
	printf("Test Case 2 : \n");
	printf("Input Data  : 25/12/2014\n");
	printf("Input Data  : 1250\n");
	printf("Input Data  : DECLINED_STOLEN_CARD = 2\n");
	printf("Input Data  : 5000\n");
	printf("Input Data  : BeshoyKaramBolisKaram\n");
	printf("Input Data  : 85873138797802637\n");
	printf("Input Data  : 27/19\n");
	getTransactionDate(&Server.terminalData);
	getTransactionAmount(&Server.terminalData);
	printf("Enter Status Number : ");
	scanf_s("%d", &Status);
	Server.transState = Status;
	setMaxAmount(&Server.terminalData, 9000);
	getCardHolderName(&Server.cardHolderData);
	getCardPAN(&Server.cardHolderData);
	getCardExpiryDate(&Server.cardHolderData);
	
	saveTransaction(&Server);
	
	listSavedTransactions();
}


/* Description:
 * - this function print all data of transaction in database
 * Return
 * - returns nothing
 */
void listSavedTransactions(void) {

	uint32_t index = 0;
	for (index; index < transactionIndex; index++) {
		printf("Transaction Number %d\n", index + 1);
		printf("Transaction Date       : %s\n", transactionsDB[index].terminalData.transactionDate);
		printf("Transaction Amount     : %f\n", transactionsDB[index].terminalData.transAmount);
		if (transactionsDB[index].transState == 0) {
			printf("Transaction State      : APPROVED\n");
		}
		else if (transactionsDB[index].transState == 1) {
			printf("Transaction State      : DECLINED_INSUFFECIENT_FUND\n");
		}
		else if (transactionsDB[index].transState == 2) {
			printf("Transaction State      : DECLINED_STOLEN_CARD\n");
		}
		else if (transactionsDB[index].transState == 3) {
			printf("Transaction State      : FRAUD_CARD\n");
		}
		else if (transactionsDB[index].transState == 4) {
			printf("Transaction State      : INTERNAL_SERVER_ERROR\n");
		}
		printf("Transaction Max Amount : %f\n", transactionsDB[index].terminalData.maxTransAmount);
		printf("Card Name              : %s\n", transactionsDB[index].cardHolderData.cardHolderName);
		printf("Card PAN               : %s\n", transactionsDB[index].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date   : %s\n", transactionsDB[index].cardHolderData.cardExpirationDate);
		printf("\n");
	}
}

/* Description:
 * - test all possible scenarios, happy-case, and worst-case scenarios listSavedTransactions function.
 * - Print all results of your test cases on the console window.
 */
void listSavedTransactionsTest(void) {

	uint32_t Status;

	printf("Tester Name : Bolis Karam\n");
	printf("Function Name : listSavedTransactions\n\n");
	
	//Test Case 1 
	printf("Test Case 1 : \n");
	printf("Input Data  : 22/10/2022\n");
	printf("Input Data  : 1000\n");
	printf("Input Data  : DECLINED_INSUFFECIENT_FUND = 1\n");
	printf("Input Data  : 9000\n");
	printf("Input Data  : BoliskaramSolimanBolis\n");
	printf("Input Data  : 140920138399124246\n");
	printf("Input Data  : 05/23\n");
	getTransactionDate(&Server.terminalData);
	getTransactionAmount(&Server.terminalData);
	printf("Enter Status Number : ");
	scanf_s("%d", &Status);
	Server.transState = Status;
	setMaxAmount(&Server.terminalData, 9000);
	getCardHolderName(&Server.cardHolderData);
	getCardPAN(&Server.cardHolderData);
	getCardExpiryDate(&Server.cardHolderData);
	saveTransaction(&Server);
	
	//Test Case 2   
	printf("Test Case 2 : \n");
	printf("Input Data  : 06/07/2005\n");
	printf("Input Data  : 5000\n");
	printf("Input Data  : FRAUD_CARD = 3\n");
	printf("Input Data  : 20000\n");
	printf("Input Data  : MaherBeshoyKaramSoliman\n");
	printf("Input Data  : 1409216587529124246\n");
	printf("Input Data  : 11/11\n");
	getTransactionDate(&Server.terminalData);
	getTransactionAmount(&Server.terminalData);
	printf("Enter Status Number : ");
	scanf_s("%d", &Status);
	Server.transState = Status;
	setMaxAmount(&Server.terminalData, 9000);
	getCardHolderName(&Server.cardHolderData);
	getCardPAN(&Server.cardHolderData);
	getCardExpiryDate(&Server.cardHolderData);
	saveTransaction(&Server);
	
	listSavedTransactions();
}

/* Description:
 * - This function takes a reference to an structure of transaction data and address of variable to return balance
 * - check if PAN is exist in database and not block and return balance 
 * Return
 * - returns APPROVED if all checks passed
 * - returns FRAUD_CARD if account doesn't exist in database
 * - returns DECLINED_STOLEN_CARD if account is Blocked
 */
EN_transState_t getBalance(ST_transaction_t* transData,float* balanceReturn) {

	EN_transState_t HandleError = APPROVED;
	EN_serverError_t serverError = SERVER_OK;

	serverError = isValidAccount(&transData->cardHolderData, accountsDB); 
	if (serverError == ACCOUNT_NOT_FOUND) { 
		HandleError = FRAUD_CARD; 
	}
	else {
		serverError = isBlockedAccount(accountsDB);
		if (serverError == BLOCKED_ACCOUNT) {
			HandleError = DECLINED_STOLEN_CARD;
		}
		else {
			*balanceReturn = accountsDB[accountIndex].balance;
			HandleError = APPROVED;
		}
	}
	return HandleError;
}
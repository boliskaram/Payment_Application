#include "terminal.h"

/* Description:
 * - This function takes a reference to an structure of Terminal Data
 * - Get Transaction Date from user and store in transactionDate and check the Date entry
 * Return:
 * - returns Terminal_OK if the Date length equal 10 and same date format DD/MM/YYYY
 * - returns WRONG_DATE if the Date length isnot equal 10 or different date format
 */
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	
	EN_terminalError_t HandleTransactionDateError = TERMINAL_OK;
	uint8_t inputStr[15] ="";
	printf("Please, Enter Transaction Date : ");
	scanf_s("%s", inputStr,15);
	//gets_s(inputStr,15);

	if (strlen(inputStr) != 10 ) {
		HandleTransactionDateError = WRONG_DATE;
	}
	else {
		strcpy_s(termData->transactionDate, 11, inputStr);
		if ( ( (termData->transactionDate[0] == 0 + '0') && ( (termData->transactionDate[1] > 0 + '0') && (termData->transactionDate[1] <= 9 + '0') ) ) ||
			 ( ( (termData->transactionDate[0] == 1 + '0') || (termData->transactionDate[0] == 2 + '0') ) && ( (termData->transactionDate[1] >= 0 + '0') && (termData->transactionDate[1] <= 9 + '0') ) ) ||
			 ( (termData->transactionDate[0] == 3 + '0') && ( (termData->transactionDate[1] >= 0 + '0') && (termData->transactionDate[1] <= 1 + '0') ) ) ) {
				
			if (termData->transactionDate[2] == '/') {

				if (((termData->transactionDate[3] == 0 + '0') && ((termData->transactionDate[4] > 0 + '0') && (termData->transactionDate[4] <= 9 + '0'))) ||
					((termData->transactionDate[3] == 1 + '0') && ((termData->transactionDate[4] >= 0 + '0') && (termData->transactionDate[4] <= 2 + '0')))) {
							
					if (termData->transactionDate[5] == '/') {
								
						if ((termData->transactionDate[6] >= 0 + '0') && (termData->transactionDate[6] <= 9 + '0')) {
									
							if ((termData->transactionDate[7] >= 0 + '0') && (termData->transactionDate[7] <= 9 + '0')) {
										
								if ((termData->transactionDate[8] >= 0 + '0') && (termData->transactionDate[8] <= 9 + '0')) {
									
									if ((termData->transactionDate[9] >= 0 + '0') && (termData->transactionDate[9] <= 9 + '0')) {
										HandleTransactionDateError = TERMINAL_OK;
									}
									else {
										HandleTransactionDateError = WRONG_DATE;
									}
								}
								else {
									HandleTransactionDateError = WRONG_DATE;
								}
							}
							else {
								HandleTransactionDateError = WRONG_DATE;
							}
						}
						else {
							HandleTransactionDateError = WRONG_DATE;
						}
					}
					else {
						HandleTransactionDateError = WRONG_DATE;
					}
				}
				else {
					HandleTransactionDateError = WRONG_DATE;
				}
			}
			else {
				HandleTransactionDateError = WRONG_DATE;
			}
		}
		else {
			HandleTransactionDateError = WRONG_DATE;
		}
	}
	return HandleTransactionDateError;
}

/* Description:
 * - test all possible scenarios, happy-case, and worst-case scenarios for getTransactionDate function.
 * - Print all results of your test cases on the console window.
 */
void getTransactionDateTest(void) {

	EN_terminalError_t getTransactionDateStatus = TERMINAL_OK;

	printf("Tester Name : Bolis Karam\n");
	printf("Function Name : getTransactionDate\n\n");

	//Test Case 1 Valid Date
	printf("Test Case 1 : \n");
	printf("Input Data  : 31/10/1996\n");
	getTransactionDateStatus = getTransactionDate(&Terminal);
	printf("Expected Result : TERMINAL_OK\n");
	if (getTransactionDateStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: WRONG_DATE \n\n");
	}

	//Test Case 2 Invalid Date (Month)
	printf("Test Case 2 : \n");
	printf("Input Data  : 31/58/1996\n");
	getTransactionDateStatus = getTransactionDate(&Terminal);
	printf("Expected Result : WRONG_DATE\n");
	if (getTransactionDateStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: WRONG_DATE \n\n");
	}

	//Test Case 3 Invalid Date (Day)
	printf("Test Case 3 : \n");
	printf("Input Data  : 65/12/1996\n");
	getTransactionDateStatus = getTransactionDate(&Terminal);
	printf("Expected Result : WRONG_DATE\n");
	if (getTransactionDateStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: WRONG_DATE \n\n");
	}

	//Test Case 4 Invalid Date Length > 10
	printf("Test Case 4 : \n");
	printf("Input Data  : 615/125/19962\n");
	getTransactionDateStatus = getTransactionDate(&Terminal);
	printf("Expected Result : WRONG_DATE\n");
	if (getTransactionDateStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: WRONG_DATE \n\n");
	}

	//Test Case 5 Invalid Date Length < 10
	printf("Test Case 5 : \n");
	printf("Input Data  : 65/15/19\n");
	getTransactionDateStatus = getTransactionDate(&Terminal);
	printf("Expected Result : WRONG_DATE\n");
	if (getTransactionDateStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: WRONG_DATE \n\n");
	}

	//Test Case 6 Invalid Date NULL
	printf("Test Case 6 : \n");
	printf("Input Data  : \n");
	getTransactionDateStatus = getTransactionDate(&Terminal);
	printf("Expected Result : WRONG_DATE\n");
	if (getTransactionDateStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: WRONG_DATE \n\n");
	}
}

/* Description:
 * - This function takes a reference to an structure of Terminal Data and Card Data
 * - compares the expiry date with the transaction date
 * Return:
 * - returns Terminal_OK if the expiry date > transaction date
 * - returns EXPIRED_CARD if the expiry date < transaction date
 */
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {
	
	EN_terminalError_t HandleCardExpiredError = TERMINAL_OK;

	uint32_t cardMonth			= (cardData->cardExpirationDate[0] - '0') * 10 + (cardData->cardExpirationDate[1] - '0');
	uint32_t cardYear			= (cardData->cardExpirationDate[3] - '0') * 10 + (cardData->cardExpirationDate[4] - '0');
	uint32_t transactionMonth	= (termData->transactionDate[3] - '0') * 10 + (termData->transactionDate[4] - '0');
	uint32_t transactionYear	= (termData->transactionDate[8] - '0') * 10 + (termData->transactionDate[9] - '0');
	
	

	if (cardYear < transactionYear) {
		HandleCardExpiredError = EXPIRED_CARD;
	}
	else if(cardYear > transactionYear){

		HandleCardExpiredError = TERMINAL_OK;
	}
	else if((cardYear == transactionYear) &&(cardMonth > transactionMonth)){
		HandleCardExpiredError = TERMINAL_OK;
	}
	else {
		HandleCardExpiredError = EXPIRED_CARD;
	}
	return HandleCardExpiredError;
}

/* Description:
 * - test all possible scenarios, happy-case, and worst-case scenarios for isCardExpired function.
 * - Print all results of your test cases on the console window.
 */
void isCardExpriedTest(void) {

	EN_terminalError_t isCardExpiredStatus = TERMINAL_OK;

	printf("Tester Name : Bolis Karam\n");
	printf("Function Name : isCardExpired\n\n");

	//Test Case 1 CardExpiry Month > transactionDateMonth with same year 
	printf("Test Case 1 : \n");
	printf("Input Data  : cardExpiry 11/23  transactionDate 25/10/2023 \n");

	getCardExpiryDate(&Card);
	getTransactionDate(&Terminal);

	printf("Expected Result : TERMINAL_OK\n");
	isCardExpiredStatus = isCardExpired(&Card,&Terminal);

	if (isCardExpiredStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: EXPIRED_CARD \n\n");
	}

	//Test Case 2 CardExpiry year > transactionDate year
	//			  CardExpiry Month < transactionDate Month
	printf("Test Case 2 : \n");
	printf("Input Data  : cardExpiry 06/23  transactionDate 30/10/2020 \n");

	getCardExpiryDate(&Card);
	getTransactionDate(&Terminal);

	printf("Expected Result : TERMINAL_OK\n");
	isCardExpiredStatus = isCardExpired(&Card, &Terminal);

	if (isCardExpiredStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: EXPIRED_CARD \n\n");
	}

	//Test Case 3 CardExpiry year > transactionDate year
	//			  CardExpiry Month > transactionDate Month
	printf("Test Case 3 : \n");
	printf("Input Data  : cardExpiry 09/23  transactionDate 30/05/2020 \n");

	getCardExpiryDate(&Card);
	getTransactionDate(&Terminal);

	printf("Expected Result : TERMINAL_OK\n");
	isCardExpiredStatus = isCardExpired(&Card, &Terminal);

	if (isCardExpiredStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: EXPIRED_CARD \n\n");
	}

	//Test Case 4 CardExpiry year < transactionDate year
	//			  CardExpiry Month > transactionDate Month
	printf("Test Case 4 : \n");
	printf("Input Data  : cardExpiry 12/15  transactionDate 05/11/2021 \n");

	getCardExpiryDate(&Card);
	getTransactionDate(&Terminal);

	printf("Expected Result : EXPIRED_CARD\n");
	isCardExpiredStatus = isCardExpired(&Card, &Terminal);

	if (isCardExpiredStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: EXPIRED_CARD \n\n");
	}

	//Test Case 5 CardExpiry year < transactionDate year
	//			  CardExpiry Month < transactionDate Month
	printf("Test Case 5 : \n");
	printf("Input Data  : cardExpiry 06/15  transactionDate 13/10/2017 \n");

	getCardExpiryDate(&Card);
	getTransactionDate(&Terminal);

	printf("Expected Result : EXPIRED_CARD\n");
	isCardExpiredStatus = isCardExpired(&Card, &Terminal);

	if (isCardExpiredStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: EXPIRED_CARD \n\n");
	}
}

/* Description:
 * - This function takes a reference to an structure of Terminal Data
 * - Get Transaction Amount from user and store in transAmount and check the Amount entry
 * Return:
 * - returns Terminal_OK if the Amount > 0 
 * - returns INVALID_AMOUNT if the Amount <= 0 
 */
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	
	EN_terminalError_t HandleAmountError = TERMINAL_OK;

	printf("Please, Enter Transaction Amount : "); 
	scanf_s(" %f", &termData->transAmount);
	if ( termData->transAmount <= 0) {
		HandleAmountError = INVALID_AMOUNT;
	}
	else {
		HandleAmountError = TERMINAL_OK;
	}

	return HandleAmountError;
}

/* Description:
 * - test all possible scenarios, happy-case, and worst-case scenarios for getTransactionAmount function.
 * - Print all results of your test cases on the console window.
 */
void getTransactionAmountTest(void) {

	EN_terminalError_t getTransactionAmountStatus = TERMINAL_OK;

	printf("Tester Name : Bolis Karam\n");
	printf("Function Name : getTransactionAmount\n\n");

	//Test Case 1 Valid Amount
	printf("Test Case 1 : \n");
	printf("Input Data  : 1254\n");
	getTransactionAmountStatus = getTransactionAmount(&Terminal);
	printf("Expected Result : TERMINAL_OK\n");
	if (getTransactionAmountStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: INVALID_AMOUNT \n\n");
	}

	//Test Case 2 Valid Amount
	printf("Test Case 2 : \n");
	printf("Input Data  : 2579.5\n");
	getTransactionAmountStatus = getTransactionAmount(&Terminal);
	printf("Expected Result : TERMINAL_OK\n");
	if (getTransactionAmountStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: INVALID_AMOUNT \n\n");
	}

	//Test Case 3 Invalid Amount = 0
	printf("Test Case 3 : \n");
	printf("Input Data  : 0.0\n");
	getTransactionAmountStatus = getTransactionAmount(&Terminal);
	printf("Expected Result : INVALID_AMOUNT\n");
	if (getTransactionAmountStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: INVALID_AMOUNT \n\n");
	}

	//Test Case 4 Invalid Amount < 0
	printf("Test Case 4 : \n");
	printf("Input Data  : -500\n");
	getTransactionAmountStatus = getTransactionAmount(&Terminal);
	printf("Expected Result : INVALID_AMOUNT\n");
	if (getTransactionAmountStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: INVALID_AMOUNT \n\n");
	}
}

/* Description:
 * - This function takes a reference to an structure of Terminal Data and maximum allowed amount
 * - set maximum allowed amount into Terminal Data and check the maximum allowed amount entry
 * Return:
 * - returns Terminal_OK if the maximum allowed amount > 0
 * - returns INVALID_AMOUNT if the maximum allowed amount <= 0
 */
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount) {

	EN_terminalError_t HandleMaxAmountError = TERMINAL_OK;

	termData->maxTransAmount = maxAmount;

	if (termData->maxTransAmount <= 0) {
		HandleMaxAmountError = INVALID_MAX_AMOUNT;
	}
	else {		
		HandleMaxAmountError = TERMINAL_OK;
	}

	return HandleMaxAmountError;
}

/* Description:
 * - test all possible scenarios, happy-case, and worst-case scenarios for setMaxAmount function.
 * - Print all results of your test cases on the console window.
 */
void setMaxAmountTest(void) {

	EN_terminalError_t setMaxAmountTestStatus = TERMINAL_OK;
	float maxAmount; 

	printf("Tester Name : Bolis Karam\n");
	printf("Function Name : setMaxAmount\n\n");

	//Test Case 1 Valid Amount
	printf("Test Case 1 : \n");
	printf("Input Data  : 9546\n");
	printf("Please, Enter Maximum Allowed Amount : ");
	scanf_s("%f", &maxAmount);
	setMaxAmountTestStatus = setMaxAmount(&Terminal,maxAmount);
	printf("Expected Result : TERMINAL_OK\n");
	if (setMaxAmountTestStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: INVALID_MAX_AMOUNT \n\n");
	}

	//Test Case 2 Valid Amount
	printf("Test Case 2 : \n");
	printf("Input Data  : 1379.5\n");
	printf("Please, Enter Maximum Allowed Amount : ");
	scanf_s("%f", &maxAmount);
	setMaxAmountTestStatus = setMaxAmount(&Terminal, maxAmount);
	printf("Expected Result : TERMINAL_OK\n");
	if (setMaxAmountTestStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: INVALID_MAX_AMOUNT \n\n");
	}

	//Test Case 3 Invalid Amount = 0
	printf("Test Case 3 : \n");
	printf("Input Data  : 0\n");
	printf("Please, Enter Maximum Allowed Amount : ");
	scanf_s("%f", &maxAmount);
	setMaxAmountTestStatus = setMaxAmount(&Terminal, maxAmount);
	printf("Expected Result : INVALID_MAX_AMOUNT\n");
	if (setMaxAmountTestStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: INVALID_MAX_AMOUNT \n\n");
	}

	//Test Case 4 Invalid Amount < 0
	printf("Test Case 4 : \n");
	printf("Input Data  : -128\n");
	printf("Please, Enter Maximum Allowed Amount : ");
	scanf_s("%f", &maxAmount);
	setMaxAmountTestStatus = setMaxAmount(&Terminal, maxAmount);
	printf("Expected Result : INVALID_MAX_AMOUNT\n");
	if (setMaxAmountTestStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: INVALID_MAX_AMOUNT \n\n");
	}

}

/* Description:
 * - This function takes a reference to an structure of Terminal Data 
 * - compares the transaction amount with the terminal max allowed amount
 * Return:
 * - returns Terminal_OK if the transaction amount Smaller than terminal max allowed amount
 * - returns INVALID_AMOUNT if the transaction amount larger than terminal max allowed amount
 */
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	
	EN_terminalError_t HandleBelowMaxAmountError = TERMINAL_OK;

	if (termData->transAmount > termData->maxTransAmount) {
		HandleBelowMaxAmountError = EXCEED_MAX_AMOUNT;
	}
	else {
		HandleBelowMaxAmountError = TERMINAL_OK;
	}
	return HandleBelowMaxAmountError;
}

/* Description:
 * - test all possible scenarios, happy-case, and worst-case scenarios for isBelowMaxAmount function.
 * - Print all results of your test cases on the console window.
 */
void isBelowMaxAmountTest(void) {

	EN_terminalError_t isBelowMaxAmountStatus = TERMINAL_OK;
	float maxAmount;
	printf("Tester Name : Bolis Karam\n");
	printf("Function Name : isBelowMaxAmount\n\n");

	//Test Case 1 transaction < Max
	printf("Test Case 1 : \n");
	printf("Input Data  : TransactionAmount 1000  MaxAmount 5000 \n");

	getTransactionAmount(&Terminal);
	printf("Please, Enter Maximum Allowed Amount : ");
	scanf_s("%f", &maxAmount);
	setMaxAmount(&Terminal, maxAmount);

	printf("Expected Result : TERMINAL_OK\n");
	isBelowMaxAmountStatus = isBelowMaxAmount(&Terminal);
	if (isBelowMaxAmountStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: EXCEED_MAX_AMOUNT \n\n");
	}

	//Test Case 2 transaction > Max
	printf("Test Case 2 : \n");
	printf("Input Data  : TransactionAmount 5000  MaxAmount 1000 \n");

	getTransactionAmount(&Terminal);
	printf("Please, Enter Maximum Allowed Amount : ");
	scanf_s("%f", &maxAmount);
	setMaxAmount(&Terminal, maxAmount);

	printf("Expected Result : EXCEED_MAX_AMOUNT\n");
	isBelowMaxAmountStatus = isBelowMaxAmount(&Terminal);
	if (isBelowMaxAmountStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: EXCEED_MAX_AMOUNT \n\n");
	}

}


/* Description:
 * - This function takes a reference to an structure of Card Data
 * - check if PAN valid using checksum
 * Return:
 * - returns Terminal_OK if PAN Valid
 * - returns INVALID_CARD if PAN Invalid
 */
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData) {

	EN_terminalError_t handleValidCardPANError = TERMINAL_OK;

	int32_t PANLength = strlen(cardData->primaryAccountNumber) -1; 
	uint8_t CheckSumVerify = cardData->primaryAccountNumber[PANLength] - '0';
	PANLength--;
	uint8_t temp = 0;
	uint8_t sum = 0 ;
	uint8_t checkSum = 0;


	while (PANLength >= 0) {
		temp = (cardData->primaryAccountNumber[PANLength] - '0') * 2;

		if (temp < 10) {
			sum += temp;
			if (PANLength > 0) {
				sum += cardData->primaryAccountNumber[PANLength - 1] - '0';
			}
			//printf("DEBUG :1 Sum %d\n", sum);
		}
		else {
			sum += (temp%10);
			sum += (temp / 10);
			if (PANLength > 0) {
				sum += cardData->primaryAccountNumber[PANLength - 1] - '0';
			}
			//printf("DEBUG :2 Sum %d\n", sum);
		}
		PANLength -= 2;
		
	}

	checkSum = (10 - (sum % 10)) % 10; 
	//printf("DEBUG :3 checkSum %d\n", checkSum);
	if (CheckSumVerify != checkSum) {
		handleValidCardPANError = INVALID_CARD;
	}
	else {
		handleValidCardPANError = TERMINAL_OK;
	}
	return handleValidCardPANError;
} 

void isValidCardPANTest(void) {

	EN_terminalError_t ValidCardPANStatus = TERMINAL_OK;


	printf("Tester Name : Bolis Karam\n");
	printf("Function Name : isValidCardPAN\n\n");

	//Test Case 1 Valid PAN odd
	printf("Test Case 1 : \n");
	printf("Input Data  : 1364514816054975\n");
	getCardPAN(&Card);
	ValidCardPANStatus = isValidCardPAN(&Card);
	printf("Expected Result : TERMINAL_OK\n");
	if (ValidCardPANStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: INVALID_CARD \n\n");
	}

	//Test Case 2 Invalid PAN odd
	printf("Test Case 2 : \n");
	printf("Input Data  : 1364514816052876\n");
	getCardPAN(&Card);
	ValidCardPANStatus = isValidCardPAN(&Card);
	printf("Expected Result : INVALID_CARD\n");
	if (ValidCardPANStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: INVALID_CARD \n\n");
	}

	//Test Case 3 Valid PAN even
	printf("Test Case 3 : \n");
	printf("Input Data  : 572692717464884824\n");
	getCardPAN(&Card);
	ValidCardPANStatus = isValidCardPAN(&Card);
	printf("Expected Result : TERMINAL_OK\n");
	if (ValidCardPANStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: INVALID_CARD \n\n");
	}

	//Test Case 4 Invalid PAN even
	printf("Test Case 4 : \n");
	printf("Input Data  : 471652767464784825\n");
	getCardPAN(&Card);
	ValidCardPANStatus = isValidCardPAN(&Card);
	printf("Expected Result : INVALID_CARD\n");
	if (ValidCardPANStatus == TERMINAL_OK) {
		printf("Actual Result	: TERMINAL_OK \n\n");
	}
	else {
		printf("Actual Result	: INVALID_CARD \n\n");
	}

}
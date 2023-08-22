#include "card.h"
//char inputStr[100];

/* Description:
 * - This function takes a reference to an structure of Card Data
 * - Get Cardholder Name from user and store in cardHolderName and check the name entry
 * Return:
 * - returns CARD_OK if the name length within 20 : 24 characters
 * - returns WRONG_NAME if the name length is <20 or >24 or Null
 */
EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	
	EN_cardError_t HandleNameError = CARD_OK;

	uint8_t inputStr[40] = "";
	
	printf("Please, Enter Cardholder Name : ");
	scanf_s("%s",inputStr,40);
	//gets_s(inputStr,40);
	
	if (strlen(inputStr) < 20 || strlen(inputStr) > 24){
		HandleNameError = WRONG_NAME;
	}
	else {
		strcpy_s(cardData->cardHolderName, 25, inputStr);
		HandleNameError = CARD_OK;
	}
	return HandleNameError;
}


/* Description:
 * - test all possible scenarios, happy-case, and worst-case scenarios for getCardHolderName function.
 * - Print all results of your test cases on the console window.
 */
 void getCardHolderNameTest(void) {

	EN_cardError_t getCardHolderNameStatus = CARD_OK;

	printf("Tester Name : Bolis Karam\n");
	printf("Function Name : getCardHolderName\n\n");

	//Test Case 1 Valid Name
	printf("Test Case 1 : \n");
	printf("Input Data  : BolisKaramSolimanSamaan\n");
	getCardHolderNameStatus = getCardHolderName(&Card);
	printf("Expected Result : CARD_OK\n");
	if (getCardHolderNameStatus == CARD_OK) {
		printf("Actual Result	: CARD_OK \n\n");
	}
	else{
		printf("Actual Result	: WRONG_NAME \n\n");
	}
	
	//Test Case 2 Invalid Name Length > 24 
	printf("Test Case 2 : \n");
	printf("Input Data  : BolisKaramSolimanSamaanBolis\n");
	getCardHolderNameStatus = getCardHolderName(&Card);
	printf("Expected Result : WRONG_NAME\n");
	if (getCardHolderNameStatus == CARD_OK) {
		printf("Actual Result	 : CARD_OK \n\n");
	}
	else {
		printf("Actual Result	: WRONG_NAME \n\n");
	}

	//Test Case 3 Invalid Name Length < 20
	printf("Test Case 3 : \n");
	printf("Input Data  : BolisKaram\n");
	getCardHolderNameStatus = getCardHolderName(&Card);
	printf("Expected Result : WRONG_NAME\n");
	if (getCardHolderNameStatus == CARD_OK) {
		printf("Actual Result	: CARD_OK \n\n");
	}
	else {
		printf("Actual Result	: WRONG_NAME \n\n");
	}

	//Test Case 4 Invalid Name NULL
	printf("Test Case 4 : \n");
	printf("Input Data  : \n");
	getCardHolderNameStatus = getCardHolderName(&Card);
	printf("Expected Result : WRONG_NAME\n");
	if (getCardHolderNameStatus == CARD_OK) {
		printf("Actual Result	: CARD_OK \n\n");
	}
	else {
		printf("Actual Result	: WRONG_NAME \n\n");
	}
}


/* Description:
 * - This function takes a reference to an structure of Card Data
 * - Get Card Expiry Date from user and store in cardExpiryDate and check the date format entry 
 * Return:
 * - returns CARD_OK if the date length equal 5 and same date format MM/YY
 * - returns WRONG_EXP_DATE if the date length not equal 5 or different date format
 */
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {

	EN_cardError_t HandleDateError = CARD_OK;
	
	uint8_t inputStr[10] = "";
	printf("Please, Enter Card Expiry Date : ");
	scanf_s("%s", inputStr, 10);
	//gets_s(inputStr, 10);
	
	if (strlen(inputStr) != 5) {
		HandleDateError = WRONG_EXP_DATE;
	}
	else {
		strcpy_s(cardData->cardExpirationDate, 6, inputStr);
		if ( ( (cardData->cardExpirationDate[0] == 0+'0') && ( (cardData->cardExpirationDate[1] > 0 + '0') && (cardData->cardExpirationDate[1] <= 9 + '0'))) ||
			 ( (cardData->cardExpirationDate[0] == 1+'0') && ( (cardData->cardExpirationDate[1] >= 0 + '0') && (cardData->cardExpirationDate[1] <= 2 + '0')))) {
				
			if (cardData->cardExpirationDate[2] == '/') {
				
				if (( (cardData->cardExpirationDate[3] == 0 + '0') && ((cardData->cardExpirationDate[4] > 0 + '0') && (cardData->cardExpirationDate[4] <= 9 + '0'))) ||
					( ((cardData->cardExpirationDate[3] >= 1 + '0') && (cardData->cardExpirationDate[3] <= 9 + '0')) && ((cardData->cardExpirationDate[4] >= 0 + '0') && (cardData->cardExpirationDate[4] <= 9 + '0')))) {
						HandleDateError = CARD_OK;
				}
				else {
							HandleDateError = WRONG_EXP_DATE;
				}
			}
			else {
						HandleDateError = WRONG_EXP_DATE;
			}
		}
		else {
					HandleDateError = WRONG_EXP_DATE;
		}
	}
	return HandleDateError;
}


/* Description:
 * - test all possible scenarios, happy-case, and worst-case scenarios for getCardExpiryDate function.
 * - Print all results of your test cases on the console window.
 */
void getCardExpiryDateTest(void) {

	EN_cardError_t getCardExpiryDateStatus = CARD_OK;

	printf("Tester Name : Bolis Karam\n");
	printf("Function Name : getCardExpiryDate\n\n");

	//Test Case 1 Valid Date
	printf("Test Case 1 : \n");
	printf("Input Data  : 11/96\n");
	getCardExpiryDateStatus = getCardExpiryDate(&Card);
	printf("Expected Result : CARD_OK\n");
	if (getCardExpiryDateStatus == CARD_OK) {
		printf("Actual Result	: CARD_OK \n\n");
	}
	else {
		printf("Actual Result	: WRONG_EXP_DATE \n\n");
	}

	//Test Case 2 Invalid Date  
	printf("Test Case 2 : \n");
	printf("Input Data  : 55/23\n");
	getCardExpiryDateStatus = getCardExpiryDate(&Card);
	printf("Expected Result : WRONG_EXP_DATE\n");
	if (getCardExpiryDateStatus == CARD_OK) {
		printf("Actual Result	: CARD_OK \n\n");
	}
	else {
		printf("Actual Result	: WRONG_EXP_DATE \n\n");
	}

	//Test Case 3 Invalid Date Length < 5
	printf("Test Case 3 : \n");
	printf("Input Data  : 5/3\n");
	getCardExpiryDateStatus = getCardExpiryDate(&Card);
	printf("Expected Result : WRONG_EXP_DATE\n");
	if (getCardExpiryDateStatus == CARD_OK) {
		printf("Actual Result	: CARD_OK \n\n");
	}
	else {
		printf("Actual Result	: WRONG_EXP_DATE \n\n");
	}

	//Test Case 4 Invalid Date Length > 5
	printf("Test Case 4 : \n");
	printf("Input Data  : 523/332\n");
	getCardExpiryDateStatus = getCardExpiryDate(&Card);
	printf("Expected Result : WRONG_EXP_DATE\n");
	if (getCardExpiryDateStatus == CARD_OK) {
		printf("Actual Result	: CARD_OK \n\n");
	}
	else {
		printf("Actual Result	: WRONG_EXP_DATE \n\n");
	}

	//Test Case 5 Invalid Date NULL
	printf("Test Case 5 : \n");
	printf("Input Data  : \n");
	getCardExpiryDateStatus = getCardExpiryDate(&Card);
	printf("Expected Result : WRONG_EXP_DATE\n");
	if (getCardExpiryDateStatus == CARD_OK) {
		printf("Actual Result	: CARD_OK \n\n");
	}
	else {
		printf("Actual Result	: WRONG_EXP_DATE \n\n");
	}

	//Test Case 6 Invalid Date (Month > 12)
	printf("Test Case 6 : \n");
	printf("Input Data  : 13/96 \n");
	getCardExpiryDateStatus = getCardExpiryDate(&Card);
	printf("Expected Result : WRONG_EXP_DATE\n");
	if (getCardExpiryDateStatus == CARD_OK) {
		printf("Actual Result	: CARD_OK \n\n");
	}
	else {
		printf("Actual Result	: WRONG_EXP_DATE \n\n");
	}

	//Test Case 7 Invalid Date (Month = 0)
	printf("Test Case 7 : \n");
	printf("Input Data  : 00/55\n");
	getCardExpiryDateStatus = getCardExpiryDate(&Card);
	printf("Expected Result : WRONG_EXP_DATE\n");
	if (getCardExpiryDateStatus == CARD_OK) {
		printf("Actual Result	: CARD_OK \n\n");
	}
	else {
		printf("Actual Result	: WRONG_EXP_DATE \n\n");
	}

	//Test Case 8 Invalid Date (Year = 0)
	printf("Test Case 8 : \n");
	printf("Input Data  : 10/00\n");
	getCardExpiryDateStatus = getCardExpiryDate(&Card);
	printf("Expected Result : WRONG_EXP_DATE\n");
	if (getCardExpiryDateStatus == CARD_OK) {
		printf("Actual Result	: CARD_OK \n\n");
	}
	else {
		printf("Actual Result	: WRONG_EXP_DATE \n\n");
	}
}

/* Description:
 * - This function takes a reference to an structure of Card Data
 * - Get Card PAN from user and store in cardPAN and check the PAN entry
 * Return:
 * - returns CARD_OK if the PAN length within 16 : 19 Numbers
 * - returns WRONG_PAN if the PAN length is <16 or >19 or Null
 */
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	
	EN_cardError_t HandlePANError = CARD_OK;
	
	uint8_t inputStr[30] = "";
	printf("Please, Enter Card PAN : ");
	scanf_s("%s", inputStr, 30);
	//gets_s(inputStr, 30);

	if (strlen(inputStr) < 16 || strlen(inputStr) > 19) {
		HandlePANError = WRONG_PAN;
	}
	else {
		strcpy_s(cardData->primaryAccountNumber, 20, inputStr);
		HandlePANError = CARD_OK;
	}
	return HandlePANError;
}


/* Description:
 * - test all possible scenarios, happy-case, and worst-case scenarios for getCardPAN function.
 * - Print all results of your test cases on the console window.
 */
void getCardPANTest(void) {

	EN_cardError_t getCardPANStatus = CARD_OK;

	printf("Tester Name : Bolis Karam\n");
	printf("Function Name : getCardPAN\n\n");

	//Test Case 1 Valid PAN
	printf("Test Case 1 : \n");
	printf("Input Data  : 234568712593678158\n");
	getCardPANStatus = getCardPAN(&Card);
	printf("Expected Result : CARD_OK\n");
	if (getCardPANStatus == CARD_OK) {
		printf("Actual Result	: CARD_OK \n\n");
	}
	else {
		printf("Actual Result	: WRONG_PAN \n\n");
	}

	//Test Case 2 Invalid PAN > 19  
	printf("Test Case 2 : \n");
	printf("Input Data  : 2345687125936781581437\n");
	getCardPANStatus = getCardPAN(&Card);
	printf("Expected Result : WRONG_PAN\n");
	if (getCardPANStatus == CARD_OK) {
		printf("Actual Result	: CARD_OK \n\n");
	}
	else {
		printf("Actual Result	: WRONG_PAN \n\n");
	}

	//Test Case 3 Invalid PAN Length < 16
	printf("Test Case 3 : \n");
	printf("Input Data  : 23456871259367\n");
	getCardPANStatus = getCardPAN(&Card);
	printf("Expected Result : WRONG_PAN\n");
	if (getCardPANStatus == CARD_OK) {
		printf("Actual Result	: CARD_OK \n\n");
	}
	else {
		printf("Actual Result	: WRONG_PAN \n\n");
	}

	//Test Case 4 Invalid PAN NULL
	printf("Test Case 4 : \n");
	printf("Input Data  : \n");
	getCardPANStatus = getCardPAN(&Card);
	printf("Expected Result : WRONG_PAN\n");
	if (getCardPANStatus == CARD_OK) {
		printf("Actual Result	: CARD_OK \n\n");
	}
	else {
		printf("Actual Result	: WRONG_PAN \n\n");
	}
}
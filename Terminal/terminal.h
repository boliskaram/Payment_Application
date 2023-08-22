//#pragma once


#ifndef TERMINAL_H_
#define TERMINAL_H_

#include "../Source Files/Types.h"
#include "../Card/card.h"
#define _CRT_SECURE_NO_WARNINGS

typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;

// For Test Terminal APIs 
ST_terminalData_t Terminal;

typedef enum EN_terminalError_t
{
    TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
void getTransactionDateTest(void);
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData);
void isCardExpriedTest(void);
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
void getTransactionAmountTest(void);
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount);
void setMaxAmountTest(void);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
void isBelowMaxAmountTest(void);
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData); // Optional
void isValidCardPANTest(void);

#endif /* TERMINAL_H_ */
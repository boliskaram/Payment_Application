#ifndef SERVER_H_
#define SERVER_H_
#define _CRT_NONSTDC_NO_WARNINGS
#include "../Source Files/Types.h"
#include "../Terminal/terminal.h"

#define accountNumber (8)
typedef enum EN_transState_t
{
    APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;
typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
}ST_transaction_t;

ST_transaction_t Server;

typedef enum EN_serverError_t
{
    SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t;
typedef enum EN_accountState_t
{
    RUNNING,
    BLOCKED
}EN_accountState_t;
typedef struct ST_accountsDB_t
{
    float balance;
    EN_accountState_t state;
    uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

EN_transState_t recieveTransactionData(ST_transaction_t* transData);
void recieveTransactionDataTest(void);
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence);
void isValidAccountTest(void);
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence);
void isBlockedAccountTest(void);
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence);
void isAmountAvailableTest(void);
EN_serverError_t saveTransaction(ST_transaction_t* transData);
void saveTransactionTest(void);
void listSavedTransactions(void);
void listSavedTransactionsTest(void);

EN_transState_t getBalance(ST_transaction_t* transData , float* balanceReturn);

#endif /* SERVER_H_ */

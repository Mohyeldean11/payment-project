#include "D:\payment project\server\server.c"
#include "app.h"

void appStart(void)
{
    /********************************************VARIABLES USED*******************************************/
    EN_cardError_t card_error_Status;
    EN_terminalError_t term_error_Status;
    EN_serverError_t server_error_status;
    EN_transState_t transaction_error_status;

    ST_cardData_t card_info;
    ST_cardData_t *cardptr;
    cardptr = &card_info;

    ST_terminalData_t term_info;
    ST_terminalData_t *termptr;
    termptr = &term_info;

    ST_transaction_t *transptr;

    /*******************************************card module*********************************/

    /*card holder name*/
    card_error_Status = getCardHolderName(cardptr);
    printf("the card error status is %d\n", card_error_Status);
    if (card_error_Status != 0)
    {
        puts("error regarding the card name");
        puts("FAILED");

        exit(0);
    }

    /*card expiry date*/
    card_error_Status = getCardExpiryDate(cardptr);
    printf("the card error status is %d\n", card_error_Status);
    if (card_error_Status != 0)
    {
        puts("error regarding the card date");
        puts("FAILED");

        exit(0);
    }

    card_error_Status = getCardPAN(cardptr);
    printf("the card error status is %d\n", card_error_Status);
    /*card pan number*/
    if (card_error_Status != 0)
    {
        puts("error regarding the card number");
        puts("FAILED");

        exit(0);
    }
    /*printing the information of the card*/
    print_card_details(cardptr);

    /**************************************terminal module*********************************/

    /*term max amount*/
    termptr->maxTransAmount = 20000;
    term_error_Status = setMaxAmount(termptr);
    printf("the terminal error status is %d\n", term_error_Status);
    if (term_error_Status != 0)
    {
        puts("error regarding the terminal max amount");
        puts("FAILED");

        exit(0);
    }

    /*term trans date*/
    strcpy(termptr->transactionDate, "13/07/2022");
    term_error_Status = getTransactionDate(termptr);
    printf("the terminal error status is %d\n", term_error_Status);
    if (term_error_Status != 0)
    {
        puts("error regarding the terminal date");
        puts("FAILED");

        exit(0);
    }
    /*checking the expiration of the card*/
    term_error_Status = isCardExpired(cardptr,termptr);
    printf("the terminal error status is %d\n", term_error_Status);
    if (term_error_Status != 0)
    {
        puts("error regarding the card expiration date");
        puts("FAILED");

        exit(0);
    }

    /*term transaction needed*/
    term_error_Status = getTransactionAmount(termptr);
    printf("the terminal error status is %d\n", term_error_Status);
    if (term_error_Status != 0)
    {
        puts("error regarding the transaction amount");
        puts("FAILED");

        exit(0);
    }

    /*term checking the amount*/
    term_error_Status = isBelowMaxAmount(termptr);
    printf("the terminal error status is %d\n", term_error_Status);
    if (term_error_Status != 0)
    {
        puts("error regarding the amount of transaction isnt below max");
        puts("FAILED");

        exit(0);
    }

    /*copying the information to the data base*/
    TRANSACTION_DB[0].cardHolderData = card_info;
    TRANSACTION_DB[0].terminalData = term_info;
    TRANSACTION_DB[0].transactionSequenceNumber = 254;

    transptr = TRANSACTION_DB;

    /**************************************server module*********************************/

    /*checking if the account is valid*/
    server_error_status = isValidAccount(cardptr);
    printf("the server error status is %d\n", server_error_status);
    if (server_error_status != 0)
    {
        puts("the error is regarding the account");
        puts("FAILED");

        exit(0);
    }

    /*checking if the amount is available in the account*/
    server_error_status = isAmountAvailable(termptr);
    printf("the server error status is %d\n", server_error_status);
    if (server_error_status != 0)
    {
        puts("the error is regarding the amount available in the account");
        puts("FAILED");

        exit(0);
    }

    /*completing the transaction and updating the balance*/
    transaction_error_status = recieveTransactionData(transptr);
    printf("the transaction error status is %d\n", transaction_error_status);
    if (transaction_error_status != 0)
    {
        puts("the error is regarding the transaction");
        puts("FAILED");
        exit(0);
    }

    /*saving the transaction and giving it a transaction sequence*/
    server_error_status = getTransaction(transptr->transactionSequenceNumber, transptr);
    printf("the server error status is %d\n", server_error_status);
    if (server_error_status != 0)
    {
        puts("the error is regarding the transaction saving op");
        exit(0);
    }
    puts("PASSED");
}
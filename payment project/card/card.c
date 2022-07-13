/*includes*/
#include "D:\payment project\datatypes.h"
#include "card.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*a function to get the  card holder name*/
EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    puts("please enter the name of the card holder");
    gets(cardData->cardHolderName);                                                     // getting the name
    if (strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) > 24) // checking  if the name doesnt meet the requirements
    {
        return WRONG_NAME; // returning the error status
    }
    else
    {
        return OK;
    }
}

/*a function to get the card  expiry date and return a status error*/
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{

    puts("please enter the expiry date of the card in MM/YY form");
    gets(cardData->cardExpirationDate); // getting the card expiration date

    ST_cardData_t data_copy = *(cardData); // copying the data of the card in temp struct to manipulate it without affecting the main data

    uint8_t month = atoi(data_copy.cardExpirationDate); // creating a token for the month to check it

    strrev(data_copy.cardExpirationDate);                       // reversing the date to get the year at the beginning
    uint8_t *token = strtok(data_copy.cardExpirationDate, "/"); // creating a token for the year but reversed
    strrev(token);                                              // re reversing the token to get the year
    uint8_t year = atoi(token);                                 // assigning the token to year value to compareit

    /*checking if the date does meet the requirements or not! */ 
    if (cardData->cardExpirationDate == NULL || strlen(cardData->cardExpirationDate) != 5 || month <= 0 || month > 12 || year <= 0 || *((cardData->cardExpirationDate) + 2) != '/')
    {
        return WRONG_EXP_DATE;
    }

    else
    {
        return OK;
    }
}

/*a function to get the card pan and return a status error*/
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    puts("please enter the card Pan number ");      
    gets(cardData->primaryAccountNumber);        //getting the card pan number from the user

    /*checking if the pan number meet the requirements or not*/
    if (cardData->primaryAccountNumber == NULL || strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19)
    {
        return WRONG_PAN;
    }
    else
    {
        return OK;
    }
}

/*a function to print the card details that was entered on the screen*/
void print_card_details(ST_cardData_t *cardData)
{
    puts("the data u entered is:\n");   
    printf(" card name is %s\n", cardData->cardHolderName);
    printf(" card number is %s\n", cardData->primaryAccountNumber);
    printf(" card date is %s\n", cardData->cardExpirationDate);
}


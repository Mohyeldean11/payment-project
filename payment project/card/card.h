#ifndef CARD_h_
#define CARD_h_

/*defining a struct name for the card data*/
typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
} ST_cardData_t;

/*defining a enumerator for the error status*/
typedef enum EN_cardError_t
{
	OK,
	WRONG_NAME,
	WRONG_EXP_DATE,
	WRONG_PAN
} EN_cardError_t;
/*FUNCTION PROTOTYPES*/

/*a function to get the card holder name and return a status error*/
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);

/*a function to get the card  expiry date and return a status error*/
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);

/*a function to get the card pan and return a status error*/
EN_cardError_t getCardPAN(ST_cardData_t *cardData);

/*a function to print the details of the card that was entered*/
void print_card_details(ST_cardData_t *cardData);

#endif
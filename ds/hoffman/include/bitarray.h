/*******************************************************************************/
/*		Descriptions - Bitarray API Functions						    */
/*		Date: 25.10.2020										    */
/*		Group: OL96											    */
/*******************************************************************************/

#ifndef __BITARRAY_H__
#define __BITARRAY_H__

#include <stddef.h>

typedef size_t bitarr_t;

typedef enum 
{ 
    OFF, 
    ON 
} state_t;

/* 
* Description: Sets all bits in arr to 1
* Return value: Bitarray with set bits
* Errors: none
* complexity: O(1)
*/
bitarr_t BitsArrSetAll(bitarr_t arr);

/* 
* Description: Sets all bits in arr to 0
* Return value: Bitarray with unset bits
* Errors: none
* Complexity: O(1)
*/
bitarr_t BitsArrResetAll(bitarr_t arr);

/* 
* Description: Converts bittaray to string representations of bits.
* Return value: Pointer to string.
* Errors: dest must be big enough to contain size_t length. Otherwise undefined.
* Complexity: O(n)
*/
char *BitArrToString(bitarr_t arr, char *dest);

/* 
* Description: Set specific bit "on". 
* Return value: Bitarray with desired bit set.
* Errors: Index value should not exceed size_t range.
* Complexity: O(1)
*/
bitarr_t BitsArrSetOn(bitarr_t arr, size_t index);

/* 
* Description: Set specific bit "off".
* Return value: Bitarray with desired bit unset.
* Errors: Index value should not exceed size_t range.
* Complexity: O(1)
*/
bitarr_t BitsArrSetOff(bitarr_t arr, size_t index);

/* 
* Description: Set specific bit to desired state.
* Return value: Bitarray with desired state of bit.
* Errors: Index value should not exceed size_t range.
* bit_state should be either 0/1 or ON/OFF.
* Complexity: O(1)
*/
bitarr_t BitsArrSetBit(bitarr_t arr , size_t index, state_t bit_state); 

/* 
* Description: Get the state of specific bit.
* Return value: State of desired bit 0/1.
* Errors: Index value should not exceed size_t range.
* Complexity: O(1)
*/
state_t BitsArrGetVal(bitarr_t arr, size_t index);

/* 
* Description: Flip state of specific bit.
* Return value: Bitarray with flipped state bit.
* Errors: Index value should not exceed size_t range.
* Complexity: O(1)
*/
bitarr_t BitsArrFlipBit(bitarr_t arr, size_t index);

/* 
* Description: Mirror all bits representation.
* Return value: Mirrored bitarray.
* Errors: None.
* Complexity: O(log(n))
*/
bitarr_t BitsArrMirror(bitarr_t arr);

/* 
* Description: Rotate arr to the right in number of rotate_times.
* Return value: Rotated bitarray.
* Errors: Negative rotate_times is not valid.
* complexity: O(n)
*/
bitarr_t BitsArrRotR(bitarr_t arr, size_t rotate_times); 

/* 
* Description: Rotate arr to the left in number of rotate_times.
* Return value: Rotated bitarray.
* Errors: Negative rotate_times is not valid.
* complexity: O(n)
*/
bitarr_t BitsArrRotL(bitarr_t arr, size_t rotate_times); 

/* 
* Description: Counts number of set bits. 
* Return value: Number of set bits.
* Errors: None.
* Complexity: O(log(n))
*/
size_t BitsArrCountOn(bitarr_t arr);

/* 
* Description: Counts number of unset bits. 
* Return value: Number of unset bits.
* Errors: None.
* Complexity: O(log(n))
*/
size_t BitsArrCountOff(bitarr_t arr);


#endif /* __BITARRAY_H__ */

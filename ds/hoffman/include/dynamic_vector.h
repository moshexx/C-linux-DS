/******************************************************************************/
/*		Descriptions - Dynamic Vector API Functions	V4		         		  */
/*		Date: 27.10.2020					    							  */
/*		Group: OL96						    								  */
/******************************************************************************/
#ifndef DYNAMIC_VECTOR_H
#define DYNAMIC_VECTOR_H

#include <stddef.h>

typedef	struct dynamic_vector dvector_t;

/*
* Description: Allocate memory for dvector.
* Return value: Pointer to dvector_t.
* Errors: If allocation failed NULL will be returned.
* Undefined behavior: capacity must be greater than 0.
*	      			   elem_size must be greater than 0 (in bytes).
* Complexity: O(1).
*/
dvector_t *DVectorCreate(size_t capacity, size_t elem_size);

/*
* Description: Free dvector allocation.
* Return value: none.
* Errors:
* Undefined behavior: dvector pointer cannot be NULL.
* Complexity: O(1).
*/
void DVectorDestroy(dvector_t *dvector);

/*
* Description: Return the current size of dvector.
* Return value: size_t number.
* Errors:
* Undefined behavior: dvector pointer cannot be NULL.
* Complexity: O(1).
*/
size_t DVectorSize(const dvector_t *dvector);

/*
* Description: Increase size of dvector by one and add element.
* Return value: Pointer to dvector_t.
* Errors: If allocation failed NULL will be returned.
* Undefined behavior: dvector pointer cannot be NULL.
* Complexity: O(1).
*/
dvector_t *DVectorPushBack(dvector_t *dvector, void *element);

/*
* Description: Decrease size of DVector by one.
* Return value: Pointer to dvector_t.
* Errors:If allocation failed NULL will be returned.
* Undefined behavior: dvector pointer cannot be NULL.
*		               dvector cannot be empty.
* Complexity: O(1).
*/

dvector_t *DVectorPopBack(dvector_t *dvector);
/*
* Description: Return the element at index.
* Return value: Wanted element.
* Errors:
* Undefined behavior: dvector pointer cannot be NULL.
*             		   dvector cannot be empty.
*		               index must be greater than 0 and smaller than
*		               size of dvector.
* Complexity: O(1).
*/
void *DVectorAccessElement(const dvector_t *dvector, size_t index);

/*
* Description: Return the capacity of the dvector.
* Return value: size_t number.
* Errors:
* Undefined behavior: dvector pointer cannot be NULL.
* Complexity: O(1).
*/
size_t DVectorCapacity(const dvector_t *dvector);

/*
* Description: Set the capacity of the dvector to new size.
* Return value: Pointer to dvector_t.
* Errors: If allocation failed NULL will be returned.
* Undefined behavior: dvector pointer cannot be NULL.
*                      new capacity must be greater than current size.
* Complexity: O(n).
*/
dvector_t *DVectorRecapacity(dvector_t *dvector, size_t new_capacity);


#endif /* DYNAMIC_VECTOR_H */

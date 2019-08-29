/* Contains macros and functions for common operations
*/

/* Given a pointer to a struct contained within another, and type information
 * about the exterior struct, evaluates to a pointer to the exterior struct.
 * 
 * ptr: A pointer to the interior struct
 * type: The type name of the outer structure
 * memberName: The member name of the interior struct in the exterior struct
 */
#define CONTAINER_OF(ptr, type, member_name) \
	(type *) ((uint8_t *) (ptr) - offsetof(type, member_name))

/* Some commentary about this function:
	In its current state, it includes no type checking. You could theoretically
	put in potentially incompatible types into ptr and member_name. This would 
	only really be a problem if you put the wrong field in for member_name, you
	get an incorrect offset, and a bad pointer to the exterior struct.

	I have not included it here because it seems to me that the window for making
	such an error is extremely small. You would either need to put an incorrect 
	member from the same struct, or a member included in a completely different
	struct. And type checking of the kind that is done in the implementations below
	don't even check for the,in my opinion, more likely mistake of using an incorrect
	member name of the same type as your pointer (for instance, having two linked list
	nodes as members in your struct.). Checking for this problem would require checking
	equality between the supplied interior pointer (ptr) and the resultant ptr + the 
	calculated offset offset. 

	In conclusion you, would have to be a pretty big dumb to run into the errors that these
	methods would catch, and the methods don't even catch the errors which require less
	stupidity to make on the part of the user. 

	I will include the error checking methods from wikipedia and linux here anyways:

	linux
		#define container_of(ptr, type, member) ({ \
	                const typeof( ((type *)0)->member ) *__mptr = (ptr); \
	                (type *)( (char *)__mptr - offsetof(type,member) );})

    wikipedia abusing the fact that pointers in ternary operators must all be of 
    the same type by mandate of the c standard.
	    #define container_of(ptr, type, member) \
	    	((type *)((char *)(1 ? (ptr) : &((type *)0)->member) - offsetof(type, member)))

*/

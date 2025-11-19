#include "enclave.h"

#include "enclave_t.h"

/*
*   sgx_status_t sgx_read_rand 
*   (
*       unsigned char *rand,
*       size_t length_in_bytes
*
*   );
*
*   rand[out] - Pointer to the buffer that receives the random number
*   length_in_bytes [in] - the length of the buffer in bytes
*     
*   SGX_SUCCESS - return val that indicates success
*   SGX_ERROR_INVALID_PARAMETER - return val that indicates invalid input parameters detected
*
*/
int ecall_get_secure_random_init(void)
{
    int n;
    sgx_read_rand((unsigned char *)&n, sizeof(n));

    return n;
}


int ecall_is_prime( int n ) {

	int p = 1;

	if ( n <= 1 ) {
		p = 0;
	} else if ( n != 2 && (n % 2) == 0) {
		p = 0;
	} else {
		for ( int i = 2; i <= sqrt(n); ++i ) {
	 		// If n is divisible by any number between 2 and n/2, it is not prime
			if ( n % i == 0 ) {
				p = 0;
				break;
			}
		}
	}

    return p;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "app.h"

#include "sgx_urts.h"
#include "enclave_u.h"

sgx_enclave_id_t global_eid = 0;

#define ENCLAVE_FILENAME "enclave.signed.so"

void ocall_print_string(const char* str)
{
    printf("%s", str);
}

int main( int argc, char *argv[] )
{
	(void)(argc);
	(void)(argv);

	sgx_status_t ret = SGX_SUCCESS;

    ret = sgx_create_enclave(ENCLAVE_FILENAME, SGX_DEBUG_FLAG, NULL, NULL, &global_eid, NULL);

    if (ret != SGX_SUCCESS) 
    
    {
        printf("Error: failed at Enclave creation. Code: 0x%x\n", ret);
        return -1;
    }

	printf("Enclave's creation SUCCESSFUL!\n");

	sgx_status_t ecall_status = SGX_SUCCESS;

    int is_prime_result = 0;
    int random_number = 0;

	do
	{
		ecall_status = ecall_get_secure_random_init(global_eid, &random_number);
		if( ecall_status != SGX_SUCCESS )
		{
			printf("ERROR: ecall_get_secure_random_init FAILED. Code: 0x%x\n", ecall_status);
			sgx_destroy_enclave(global_eid); // Clean up
            return -1;
		}

		ecall_status = ecall_is_prime(global_eid, &is_prime_result, random_number);
		if ( ecall_status != SGX_SUCCESS )
		{
			printf("ERROR: ecall_is_prime FAILED. Code: 0x%x\n", ecall_status);
			sgx_destroy_enclave(global_eid); // Clean up
			return -1;
		}

		printf("%d is%s a prime number.\n", random_number, (is_prime_result == 0) ? "n't" : "" );	

	}
	while( is_prime_result != 1 );

    printf("Success.\n");

    sgx_destroy_enclave(global_eid);

	return 0;

}

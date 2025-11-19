#include "enclave_u.h"
#include <errno.h>

typedef struct ms_ecall_get_secure_random_init_t {
	int ms_retval;
} ms_ecall_get_secure_random_init_t;

typedef struct ms_ecall_is_prime_t {
	int ms_retval;
	int ms_n;
} ms_ecall_is_prime_t;

typedef struct ms_ocall_print_string_t {
	const char* ms_str;
} ms_ocall_print_string_t;

static sgx_status_t SGX_CDECL enclave_ocall_print_string(void* pms)
{
	ms_ocall_print_string_t* ms = SGX_CAST(ms_ocall_print_string_t*, pms);
	ocall_print_string(ms->ms_str);

	return SGX_SUCCESS;
}

static const struct {
	size_t nr_ocall;
	void * table[1];
} ocall_table_enclave = {
	1,
	{
		(void*)enclave_ocall_print_string,
	}
};
sgx_status_t ecall_get_secure_random_init(sgx_enclave_id_t eid, int* retval)
{
	sgx_status_t status;
	ms_ecall_get_secure_random_init_t ms;
	status = sgx_ecall(eid, 0, &ocall_table_enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t ecall_is_prime(sgx_enclave_id_t eid, int* retval, int n)
{
	sgx_status_t status;
	ms_ecall_is_prime_t ms;
	ms.ms_n = n;
	status = sgx_ecall(eid, 1, &ocall_table_enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}


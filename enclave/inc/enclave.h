#ifndef _ENCLAVE_H_
#define _ENCLAVE_H_

#include <math.h>
#include "sgx_trts.h"

int get_secure_random_init(void);
int is_prime(int n);

#endif /* _ENCLAVE_H_ */
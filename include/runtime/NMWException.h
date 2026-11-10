#ifndef RUNTIME_NMWEXCEPTION_H
#define RUNTIME_NMWEXCEPTION_H
#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif

void __construct_array(void* pBlock, funcptr_t ctor, funcptr_t dtor, size_t size, size_t n);
void* __construct_new_array(void* block, funcptr_t ctor, funcptr_t dtor, size_t size, size_t n);
void __destroy_arr(void* pArraySource, funcptr_t dtor, size_t size, size_t num);

#ifdef __cplusplus
}
#endif
#endif

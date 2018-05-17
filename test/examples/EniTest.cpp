/*==- test/examples/EniTest.cpp --------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include <skypat/skypat.h>
#include <json/Parser.h>
#include <dlfcn.h>
#include <cstdlib>
#include <cstring>

namespace {

typedef void* eni_create_t(char* pArgStr);
typedef void  eni_destroy_t(void* pFunctor);

extern "C" uint64_t eni_gas(void* pFunctor);
extern "C" char*    eni_run(void *pFunctor);

} // annonymous namespace

SKYPAT_F(EniTest, eni_reverse)
{
  // Initialize.
  void* handle = ::dlopen("./eni/eni_reverse.so", RTLD_LAZY);
  ASSERT_NE(handle, NULL);

  // Loading symbols from shared library.
  eni_create_t*  eni_create  = (eni_create_t*)::dlsym(handle, "reverse_create");
  eni_destroy_t* eni_destroy = (eni_destroy_t*)::dlsym(handle, "reverse_destroy");
  ASSERT_NE(eni_create, NULL);
  ASSERT_NE(eni_destroy, NULL);

  // Simulate calling an ENI function.
  char params[] = "[\"Hello World!\"]";
  void* functor = eni_create(params);
  ASSERT_NE(functor, NULL);

  uint64_t gas = eni_gas(functor);
  char *retval = eni_run(functor);
  EXPECT_EQ(gas, 12);

  // Parse return value.
  json::Parser ps(retval);
  json::Value val = ps.getRoot();
  ASSERT_TRUE(val.isArray());
  EXPECT_EQ(val[0].toString(), "!dlroW olleH");

  // Finalize.
  eni_destroy(functor);
  delete retval;
  ::dlclose(handle);
}

SKYPAT_F(EniTest, eni_caesar_encrypt)
{
  // Initialize.
  void* handle = ::dlopen("./eni/eni_caesar_cipher.so", RTLD_LAZY);
  ASSERT_NE(handle, NULL);

  // Loading symbols from shared library.
  eni_create_t*  eni_create  = (eni_create_t*)::dlsym(handle, "caesar_encrypt_create");
  eni_destroy_t* eni_destroy = (eni_destroy_t*)::dlsym(handle, "caesar_encrypt_destroy");
  ASSERT_NE(eni_create, NULL);
  ASSERT_NE(eni_destroy, NULL);

  // Simulate calling an ENI function.
  char params[] = "[\"Hello World!\",\"HELLOGCC\"]";
  void* functor = eni_create(params);
  ASSERT_NE(functor, NULL);

  uint64_t gas = eni_gas(functor);
  char *retval = eni_run(functor);
  EXPECT_EQ(gas, 12);

  // Parse return value.
  json::Parser ps(retval);
  json::Value val = ps.getRoot();
  ASSERT_TRUE(val.isArray());
  EXPECT_EQ(val[0].toString(), "Olssv Dvysk!");

  // Finalize.
  eni_destroy(functor);
  delete retval;
  ::dlclose(handle);
}

SKYPAT_F(EniTest, eni_caesar_decrypt)
{
  // Initialize.
  void* handle = ::dlopen("./eni/eni_caesar_cipher.so", RTLD_LAZY);
  ASSERT_NE(handle, NULL);

  // Loading symbols from shared library.
  eni_create_t*  eni_create  = (eni_create_t*)::dlsym(handle, "caesar_decrypt_create");
  eni_destroy_t* eni_destroy = (eni_destroy_t*)::dlsym(handle, "caesar_decrypt_destroy");
  ASSERT_NE(eni_create, NULL);
  ASSERT_NE(eni_destroy, NULL);

  // Simulate calling an ENI function.
  char params[] = "[\"Olssv Dvysk!\",\"HELLOGCC\"]";
  void* functor = eni_create(params);
  ASSERT_NE(functor, NULL);

  uint64_t gas = eni_gas(functor);
  char *retval = eni_run(functor);
  EXPECT_EQ(gas, 12);

  // Parse return value.
  json::Parser ps(retval);
  json::Value val = ps.getRoot();
  ASSERT_TRUE(val.isArray());
  EXPECT_EQ(val[0].toString(), "Hello World!");

  // Finalize.
  eni_destroy(functor);
  delete retval;
  ::dlclose(handle);
}

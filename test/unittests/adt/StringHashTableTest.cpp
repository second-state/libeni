/*==- test/unittests/adt/StringHashTableTest.cpp ---------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include <skypat/skypat.h>
#include <adt/StringHashTable.h>

using namespace eni;

/*==------------------------------------------------------------------------==
  StringHashTableTest
==------------------------------------------------------------------------==*/
SKYPAT_F(StringHashTableTest, string_hash_table)
{
  typedef StringHashTable<int> HashTable;
  HashTable* table = new HashTable(22);

  bool exist;
  const char* key = "key";
  HashTable::entry_type* val = table->insert(key, exist);
  val->setValue(999);

  EXPECT_FALSE(table->empty());
  EXPECT_FALSE(exist);
  EXPECT_TRUE(NULL != val);

  HashTable::const_iterator entry = table->find(key);
  EXPECT_EQ(entry->value(), 999);

  delete table;
}

SKYPAT_F(StringHashTableTest, conflict_perform_test)
{
  typedef StringHashTable<int> HashTableType;
  HashTableType *table = new HashTableType();

  bool exist;
  HashTableType::entry_type* entry = NULL;
  PERFORM(skypat::CONTEXT_SWITCHES) {
    const char* key = "key";
    for (unsigned int counter = 0; counter < 400000; ++counter) {
      entry = table->insert(key, exist);
      entry->setValue(counter+10);
    }
  }

  HashTableType::const_iterator iter;
  PERFORM(skypat::CONTEXT_SWITCHES) {
    const char* key = "key";
    for (int counter = 0; counter < 400000; ++counter) {
      iter = table->find(key);
    }
  }

  delete table;
}

SKYPAT_F(StringHashTableTest, copy_constructor)
{
  typedef StringHashTable<int> HashTable;
  HashTable* table = new HashTable(22);

  bool exist;
  const char* key = "key";
  HashTable::entry_type* val = table->insert(key, exist);
  val->setValue(999);

  HashTable table2(*table);

  EXPECT_FALSE(table2.empty());
  HashTable::const_iterator entry = table2.find(key);
  EXPECT_EQ(entry->value(), 999);

  delete table;
}

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
  HashTable::entry_type* entry = table->insert(key, exist);
  entry->setValue(999);

  EXPECT_FALSE(table->empty());
  EXPECT_FALSE(exist);
  EXPECT_TRUE(NULL != entry);

  HashTable::const_iterator it = table->find(key);
  EXPECT_EQ(it->value(), 999);

  delete table;
}

SKYPAT_F(StringHashTableTest, copy_constructor)
{
  typedef StringHashTable<int> HashTable;
  HashTable* table = new HashTable(22);

  bool exist;
  const char* key = "key";
  HashTable::entry_type* entry = table->insert(key, exist);
  entry->setValue(999);

  HashTable table2(*table);

  ASSERT_FALSE(table2.empty());
  HashTable::const_iterator it = table2.find(key);
  EXPECT_EQ(it->value(), 999);

  delete table;
}

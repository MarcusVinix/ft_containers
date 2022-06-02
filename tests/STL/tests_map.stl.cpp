#include <gtest/gtest.h>
#include <map>
#include <utility>

class TestMap : public ::testing::Test {
	
	public:
		

		void SetUp() {

			MyMap['a'] = 10;
			MyMap['b'] = 20;
			MyMap['c'] = 30;
			MyMap['d'] = 40;

			itb = MyMap.begin();
			ite = MyMap.end();
			ite--;
			
			ritb = MyMap.rbegin();
			rite = MyMap.rend();
			rite--;

			key[0] = 'a';
			key[1] = 'b';
			key[2] = 'c';
			key[3] = 'd';

			val[0] = 10;
			val[1] = 20;
			val[2] = 30;
			val[3] = 40;
		}

		std::map<char, int> MyMap;
		char key[4];
		int val[4];
		std::map<char, int>::iterator itb;
		std::map<char, int>::iterator ite;
		std::map<char, int>::reverse_iterator ritb;
		std::map<char, int>::reverse_iterator rite;

};

TEST_F(TestMap, TestMapConstructDefault) {
	std::map<char, int> first;

	EXPECT_EQ(first.size(), 0);
	EXPECT_TRUE(first.empty());
}

TEST_F(TestMap, TestMapConstructRange) {
	std::map<char, int> first(MyMap.begin(), MyMap.end());

	EXPECT_EQ(first.size(), 4);
	EXPECT_FALSE(first.empty());

	EXPECT_EQ(first['a'], 10);
	EXPECT_EQ(first['b'], 20);
	EXPECT_EQ(first['c'], 30);
	EXPECT_EQ(first['d'], 40);
}

TEST_F(TestMap, TestMapConstructCopy) {
	std::map<char, int> copy(MyMap);

	EXPECT_EQ(copy.size(), 4);
	EXPECT_FALSE(copy.empty());

	EXPECT_EQ(copy['a'], 10);
	EXPECT_EQ(copy['b'], 20);
	EXPECT_EQ(copy['c'], 30);
	EXPECT_EQ(copy['d'], 40);
}

TEST_F(TestMap, TestMapAssignmentOperator) {
	std::map<char, int> assign;

	assign = MyMap;
	EXPECT_EQ(assign.size(), 4);
	EXPECT_FALSE(assign.empty());

	EXPECT_EQ(assign['a'], 10);
	EXPECT_EQ(assign['b'], 20);
	EXPECT_EQ(assign['c'], 30);
	EXPECT_EQ(assign['d'], 40);
}

TEST_F(TestMap, TestMapIteratorBegin) {
	EXPECT_EQ(MyMap.begin()->first, 'a');
	EXPECT_EQ(MyMap.begin()->second, 10);

	for (int i = 0; i < 4; itb++, i++) {
		EXPECT_EQ(itb->first, key[i]);
		EXPECT_EQ(itb->second, val[i]);
	}
}

TEST_F(TestMap, TestMapIteratorEnd) {
	for (int i = 3; i >= 0; ite--, i--) {
		EXPECT_EQ(ite->first, key[i]);
		EXPECT_EQ(ite->second, val[i]);
	}
}

TEST_F(TestMap, TestMapIteratorRBegin) {
	EXPECT_EQ(MyMap.rbegin()->first, 'd');
	EXPECT_EQ(MyMap.rbegin()->second, 40);

	for (int i = 3; i >= 0; ritb++, i--) {
		EXPECT_EQ(ritb->first, key[i]);
		EXPECT_EQ(ritb->second, val[i]);
	}
}

TEST_F(TestMap, TestMapIteratorREnd) {
	for (int i = 0; i < 4; rite--, i++) {
		EXPECT_EQ(rite->first, key[i]);
		EXPECT_EQ(rite->second, val[i]);
	}
}

TEST_F(TestMap, TestMapEmpty) {
	std::map<char, int> emptyMap;

	EXPECT_FALSE(MyMap.empty());
	EXPECT_TRUE(emptyMap.empty());
}

TEST_F(TestMap, TestMapSize) {
	std::map<char, int> emptyMap;

	EXPECT_EQ(MyMap.size(), 4);
	EXPECT_EQ(emptyMap.size(), 0);

	MyMap['e'] = 50;
	EXPECT_EQ(MyMap.size(), 5);
	MyMap['f'] = 60;
	EXPECT_EQ(MyMap.size(), 6);
}

// TEST_F(TestMap, TestMapMaxSize) {
// 	EXPECT_EQ(MyMap.max_size(), std::numeric_limits<std::size_t>::max());
// }

TEST_F(TestMap, TestMapAccessElement) {
	EXPECT_EQ(MyMap['a'], 10);
	EXPECT_EQ(MyMap['b'], 20);
	EXPECT_EQ(MyMap['c'], 30);
	EXPECT_EQ(MyMap['d'], 40);
	EXPECT_EQ(MyMap['e'], 0);
	EXPECT_EQ(MyMap['f'], 0);

	MyMap['a'] = 100;
	MyMap['c'] = 300;
	MyMap['z'] = 2700;
	EXPECT_EQ(MyMap['a'], 100);
	EXPECT_EQ(MyMap['c'], 300);
	EXPECT_EQ(MyMap['z'], 2700);
	EXPECT_EQ(MyMap.size(), 7);
}

TEST_F(TestMap, TestMapInsert) {
	std::map<char, int> map;

	EXPECT_EQ(map.size(), 0);
	map.insert(std::pair<char, int>('h', 80));
	map.insert(std::pair<char, int>('i', 90));
	map.insert(std::pair<char, int>('j', 100));
	EXPECT_EQ(map.size(), 3);

	std::map<char, int>::iterator it = map.begin();
	map.insert(it, std::pair<char, int>('e', 50));
	map.insert(it, std::pair<char, int>('f', 60));
	map.insert(it, std::pair<char, int>('g', 70));
	EXPECT_EQ(map.size(), 6);

	map.insert(MyMap.begin(), MyMap.end());
	it = map.begin();

	char c = 'a';
	for (int i = 10; i < 110; i += 10, c++, it++) {
		EXPECT_EQ(it->first, c);
		EXPECT_EQ(it->second, i);
	}
	EXPECT_EQ(map.size(), 10);
}

TEST_F(TestMap, TestMapErase) {
	EXPECT_EQ(MyMap.size(), 4);
	
	MyMap.erase(itb);
	EXPECT_EQ(MyMap.size(), 3);
	MyMap.erase('b');
	EXPECT_EQ(MyMap.size(), 2);

	MyMap.insert(std::pair<char, int>('e', 50));
	MyMap.insert(std::pair<char, int>('f', 60));
	MyMap.insert(std::pair<char, int>('g', 70));
	MyMap.insert(std::pair<char, int>('h', 80));
	EXPECT_EQ(MyMap.size(), 6);

	std::map<char, int> map(MyMap);
	std::map<char, int>::iterator it = MyMap.begin();
	std::map<char, int>::iterator it2 = MyMap.find('h');
	MyMap.erase(it, it2);
	EXPECT_EQ(MyMap.size(), 1);
	EXPECT_EQ(MyMap['h'], 80);
	EXPECT_EQ(MyMap['g'], 0);
	MyMap.erase('z');
	MyMap.erase('y');
	EXPECT_EQ(MyMap.size(), 2);

	it = map.begin();
	map.erase('f');
    map.erase('g');
    EXPECT_EQ(it->first, 'c');
    it++;
    EXPECT_EQ(it->first, 'd');
    it++;
    EXPECT_EQ(it->first, 'e');
    it++;
    EXPECT_EQ(it->first, 'h');
}

TEST_F(TestMap, TestMapSwap) {
	std::map<char, int> map;

	map.insert(std::pair<char, int>('h', 80));
	map.insert(std::pair<char, int>('i', 90));
	map.insert(std::pair<char, int>('j', 100));
	EXPECT_EQ(map.size(), 3);

	map.swap(MyMap);
	EXPECT_EQ(map.size(), 4);
	EXPECT_EQ(MyMap.size(), 3);

	EXPECT_EQ(map['a'], 10);
	EXPECT_EQ(map['b'], 20);
	EXPECT_EQ(map['c'], 30);
	EXPECT_EQ(map['d'], 40);

	EXPECT_EQ(MyMap['h'], 80);
	EXPECT_EQ(MyMap['i'], 90);
	EXPECT_EQ(MyMap['j'], 100);
}

TEST_F(TestMap, TestMapClear) {
	EXPECT_EQ(MyMap.size(), 4);
	EXPECT_FALSE(MyMap.empty());

	MyMap.clear();
	EXPECT_EQ(MyMap.size(), 0);
	EXPECT_TRUE(MyMap.empty());
}

TEST_F(TestMap, TestMapKeyComp) {
	std::map<char, int>::key_compare myComp = MyMap.key_comp();

	EXPECT_TRUE(myComp('a', 'b'));
	EXPECT_TRUE(myComp('b', 'c'));
	EXPECT_TRUE(myComp('c', 'd'));
	EXPECT_FALSE(myComp('d', 'c'));

	for (; itb != MyMap.end(); itb++)
		EXPECT_TRUE(myComp(itb->first, itb->first + 1));
}

TEST_F(TestMap, TestMapValueComp) {
	std::map<char, int>::value_compare valueComp = MyMap.value_comp();

	std::pair<const char, int> highest = std::make_pair('e', 50);
	for (; itb != ite; itb++)
		EXPECT_TRUE(valueComp(*itb, highest));
}

TEST_F(TestMap, TestMapFind) {
	std::map<char, int>::iterator first = MyMap.find('a');
	EXPECT_EQ(first->first, 'a');
	EXPECT_EQ(first->second, 10);
	
	std::map<char, int>::iterator second = MyMap.find('b');
	EXPECT_EQ(second->first, 'b');
	EXPECT_EQ(second->second, 20);
	
	std::map<char, int>::iterator third = MyMap.find('c');
	EXPECT_EQ(third->first, 'c');
	EXPECT_EQ(third->second, 30);

	std::map<char, int>::iterator it = MyMap.find('f');

	EXPECT_EQ(it, MyMap.end());

	std::map<char, int> const cMap(MyMap);

	std::map<char, int>::const_iterator cit = cMap.find('c');
	EXPECT_EQ(cit->first, 'c');
	EXPECT_EQ(cit->second, 30);
}

TEST_F(TestMap, TestMapCount) {
	EXPECT_EQ(MyMap.count('a'), 1);
	EXPECT_EQ(MyMap.count('b'), 1);
	EXPECT_EQ(MyMap.count('c'), 1);
	EXPECT_EQ(MyMap.count('d'), 1);
	EXPECT_EQ(MyMap.count('f'), 0);
	EXPECT_EQ(MyMap.count('g'), 0);
	EXPECT_EQ(MyMap.count('h'), 0);

	MyMap.erase('a');
	EXPECT_EQ(MyMap.count('a'), 0);
}

TEST_F(TestMap, TestMapLowerBound) {
	std::map<char, int>::iterator it = MyMap.lower_bound('a');
	EXPECT_EQ(it->first, 'a');
	EXPECT_EQ(it->second, 10);

	it = MyMap.lower_bound('b');
	EXPECT_EQ(it->first, 'b');
	EXPECT_EQ(it->second, 20);

	MyMap.erase('c');
	it = MyMap.lower_bound('c');
	EXPECT_EQ(it->first, 'd');
	EXPECT_EQ(it->second, 40);

	MyMap['c'] = 30;

	const std::map<char, int> map(MyMap);
	std::map<char, int>::const_iterator cit = map.lower_bound('a');
	EXPECT_EQ(cit->first, 'a');
	EXPECT_EQ(cit->second, 10);
	
	std::map<char, int>::const_iterator cit2 = map.lower_bound('i');
	EXPECT_EQ(cit2, map.end());
}

TEST_F(TestMap, TestMapUpperBound) {
	std::map<char, int>::iterator it = MyMap.upper_bound('a');
	EXPECT_EQ(it->first, 'b');
	EXPECT_EQ(it->second, 20);

	it = MyMap.upper_bound('b');
	EXPECT_EQ(it->first, 'c');
	EXPECT_EQ(it->second, 30);

	MyMap.erase('c');
	it = MyMap.upper_bound('c');
	EXPECT_EQ(it->first, 'd');
	EXPECT_EQ(it->second, 40);

	MyMap['c'] = 30;

	const std::map<char, int> map(MyMap);
	std::map<char, int>::const_iterator cit = map.upper_bound('a');
	EXPECT_EQ(cit->first, 'b');
	EXPECT_EQ(cit->second, 20);
	
	std::map<char, int>::const_iterator cit2 = map.lower_bound('i');
	EXPECT_EQ(cit2, map.end());
}

TEST_F(TestMap, TestMapEqualRange) {
	MyMap['i'] = 100;

	std::pair<std::map<char, int>::iterator, std::map<char, int>::iterator> ret;
	ret = MyMap.equal_range('a');
	EXPECT_EQ(ret.first->first, 'a');
	EXPECT_EQ(ret.first->second, 10);
	EXPECT_EQ(ret.second->first, 'b');
	EXPECT_EQ(ret.second->second, 20);

	ret = MyMap.equal_range('b');
	EXPECT_EQ(ret.first->first, 'b');
	EXPECT_EQ(ret.first->second, 20);
	EXPECT_EQ(ret.second->first, 'c');
	EXPECT_EQ(ret.second->second, 30);

	ret = MyMap.equal_range('g');
	EXPECT_EQ(ret.first->first, 'i');
	EXPECT_EQ(ret.first->second, 100);
	EXPECT_EQ(ret.second->first, 'i');
	EXPECT_EQ(ret.second->second, 100);

	const std::map<char, int> map(MyMap);
	std::pair<std::map<char, int>::const_iterator, std::map<char, int>::const_iterator> cret;
	
	cret = map.equal_range('a');
	EXPECT_EQ(cret.first->first, 'a');
	EXPECT_EQ(cret.first->second, 10);
	EXPECT_EQ(cret.second->first, 'b');
	EXPECT_EQ(cret.second->second, 20);

	cret = map.equal_range('b');
	EXPECT_EQ(cret.first->first, 'b');
	EXPECT_EQ(cret.first->second, 20);
	EXPECT_EQ(cret.second->first, 'c');
	EXPECT_EQ(cret.second->second, 30);

	cret = map.equal_range('g');
	EXPECT_EQ(cret.first->first, 'i');
	EXPECT_EQ(cret.first->second, 100);
	EXPECT_EQ(cret.second->first, 'i');
	EXPECT_EQ(cret.second->second, 100);
}

TEST_F(TestMap, TestMapGetAllocator) {
	std::allocator<std::pair<const char, int>> alloc;
	EXPECT_EQ(MyMap.get_allocator(), alloc);
}

TEST_F(TestMap, TestMapRelationalOperators) {
	std::map<char, int> map(MyMap);

	map['e'] = 50;
	map['f'] = 60;
	map['g'] = 70;
	const std::map<char, int> map2(map);

	EXPECT_FALSE(MyMap == map);
	EXPECT_TRUE(MyMap != map);
	EXPECT_TRUE(MyMap < map);
	EXPECT_FALSE(MyMap > map);
	EXPECT_TRUE(MyMap <= map);
	EXPECT_FALSE(MyMap >= map);

	EXPECT_FALSE(MyMap == map2);
	EXPECT_TRUE(MyMap != map2);
	EXPECT_TRUE(MyMap < map2);
	EXPECT_FALSE(MyMap > map2);
	EXPECT_TRUE(MyMap <= map2);
	EXPECT_FALSE(MyMap >= map2);

	EXPECT_TRUE(map == map2);
	EXPECT_FALSE(map != map2);
	EXPECT_FALSE(map < map2);
	EXPECT_FALSE(map > map2);
	EXPECT_TRUE(map <= map2);
	EXPECT_TRUE(map >= map2);
}

TEST_F(TestMap, TestMapNonMemberSwap) {
	std::map<char, int> map(MyMap);

	map['f'] = 100;
	EXPECT_EQ(MyMap.size(), 4);
	EXPECT_EQ(map.size(), 5);

	std::swap(map, MyMap);
	EXPECT_EQ(MyMap.size(), 5);
	EXPECT_EQ(map.size(), 4);

	EXPECT_TRUE(map != MyMap);
	EXPECT_FALSE(map == MyMap);
}

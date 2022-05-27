#include <gtest/gtest.h>
#include <rb_tree.hpp>
#include <rb_tree_iterator.hpp>
#include <functional.hpp>

class TestRbTree : public ::testing::Test {

	public:
		ft::rb_tree<int, int, ft::select1st<ft::pair<const int, int>>>	tree;

		void SetUp() {
			tree.insert_unique(ft::make_pair<int, int>(13, 13));
			tree.insert_unique(ft::make_pair<int, int>(17, 17));
			tree.insert_unique(ft::make_pair<int, int>(8, 8));
			tree.insert_unique(ft::make_pair<int, int>(11, 11));
			tree.insert_unique(ft::make_pair<int, int>(15, 15));
			tree.insert_unique(ft::make_pair<int, int>(22, 22));
			tree.insert_unique(ft::make_pair<int, int>(1, 1));
			tree.insert_unique(ft::make_pair<int, int>(25, 25));
			tree.insert_unique(ft::make_pair<int, int>(6, 6));
			tree.insert_unique(ft::make_pair<int, int>(27, 27));
		}

};

TEST(TestNode, TestNodeConstructors) {
	ft::Node<int>	node;

	EXPECT_EQ(node.parent, ft::_nullptr);
	EXPECT_EQ(node.right, ft::_nullptr);
	EXPECT_EQ(node.left, ft::_nullptr);

	ft::Node<int>	node1(1, ft::color::RED, ft::_nullptr);
	EXPECT_EQ(node1.parent, ft::_nullptr);
	EXPECT_EQ(node1.right, ft::_nullptr);
	EXPECT_EQ(node1.left, ft::_nullptr);

	ft::Node<int>	node2(node1);
	EXPECT_EQ(node2.parent, ft::_nullptr);
	EXPECT_EQ(node2.right, ft::_nullptr);
	EXPECT_EQ(node2.left, ft::_nullptr);
	EXPECT_EQ(node2.color, ft::color::RED);

	ft::Node<int>	node3;
	node3 = node2;
	EXPECT_EQ(node3.parent, ft::_nullptr);
	EXPECT_EQ(node3.right, ft::_nullptr);
	EXPECT_EQ(node3.left, ft::_nullptr);
	EXPECT_EQ(node3.color, ft::color::RED);

}

TEST_F(TestRbTree, TestTreeConstructor) {
	ft::rb_tree<int, int, ft::select1st<ft::pair<const int, int>>> t;

	EXPECT_EQ(t.get_root()->color, ft::color::BLACK);
	EXPECT_EQ(t.size(), 0);

	ft::rb_tree<int, int, ft::select1st<ft::pair<const int, int>>>	t2(tree);
	EXPECT_TRUE(t2 == tree);
}

TEST_F(TestRbTree, TestRbTreeInsert) {
	EXPECT_EQ(tree.get_root()->data->first, 13);
	EXPECT_EQ(tree.get_root()->color, ft::color::BLACK);
	EXPECT_EQ(tree.get_root()->parent, tree.get_nil());
	EXPECT_EQ(tree.get_root()->left->data->first, 8);
	EXPECT_EQ(tree.get_root()->left->color, ft::color::RED);
	EXPECT_EQ(tree.get_root()->left->left->data->first, 1);
	EXPECT_EQ(tree.get_root()->left->left->color, ft::color::BLACK);
	EXPECT_EQ(tree.get_root()->left->left->right->data->first, 6);
	EXPECT_EQ(tree.get_root()->left->left->right->color, ft::color::RED);
	EXPECT_EQ(tree.get_root()->left->right->data->first, 11);
	EXPECT_EQ(tree.get_root()->left->right->color, ft::color::BLACK);
	EXPECT_EQ(tree.get_root()->right->data->first, 17);
	EXPECT_EQ(tree.get_root()->right->color, ft::color::RED);
	EXPECT_EQ(tree.get_root()->right->left->data->first, 15);
	EXPECT_EQ(tree.get_root()->right->left->color, ft::color::BLACK);
	EXPECT_EQ(tree.get_root()->right->right->data->first, 25);
	EXPECT_EQ(tree.get_root()->right->right->color, ft::color::BLACK);
	EXPECT_EQ(tree.get_root()->right->right->left->data->first, 22);
	EXPECT_EQ(tree.get_root()->right->right->left->color, ft::color::RED);
	EXPECT_EQ(tree.get_root()->right->right->right->data->first, 27);
	EXPECT_EQ(tree.get_root()->right->right->right->color, ft::color::RED);
	EXPECT_EQ(tree.get_root()->right->right->right->right, tree.get_nil());
	EXPECT_EQ(tree.get_root()->right->right->right->left, tree.get_nil());
}

TEST_F(TestRbTree, TestRbTreeRemove) {
	EXPECT_EQ(tree.size(), 10);
	EXPECT_EQ(tree.get_root()->data->first, 13);

	tree.erase(13);
	EXPECT_EQ(tree.get_root()->data->first, 15);
	EXPECT_EQ(tree.get_root()->color, ft::color::BLACK);
	EXPECT_EQ(tree.get_root()->right->data->first, 25);
	EXPECT_EQ(tree.get_root()->right->color, ft::color::RED);
	EXPECT_EQ(tree.get_root()->right->left->data->first, 17);
	EXPECT_EQ(tree.get_root()->right->left->color, ft::color::BLACK);
	EXPECT_EQ(tree.size(), 9);

	tree.erase(11);
	EXPECT_EQ(tree.get_root()->data->first, 15);
	EXPECT_EQ(tree.get_root()->left->data->first, 6);
	EXPECT_EQ(tree.get_root()->left->left->data->first, 1);
	EXPECT_EQ(tree.get_root()->left->left->left, tree.get_nil());
	EXPECT_EQ(tree.get_root()->left->left->right, tree.get_nil());
	EXPECT_EQ(tree.get_root()->left->right->data->first, 8);
	EXPECT_EQ(tree.get_root()->left->right->left, tree.get_nil());
	EXPECT_EQ(tree.get_root()->left->right->right, tree.get_nil());
	EXPECT_EQ(tree.size(), 8);

	tree.erase(17);
	EXPECT_EQ(tree.get_root()->right->data->first, 25);
	EXPECT_EQ(tree.get_root()->right->color, ft::color::RED);
	EXPECT_EQ(tree.get_root()->right->left->data->first, 22);
	EXPECT_EQ(tree.get_root()->right->left->color, ft::color::BLACK);
	EXPECT_EQ(tree.get_root()->right->right->data->first, 27);
	EXPECT_EQ(tree.get_root()->right->right->color, ft::color::BLACK);
	EXPECT_EQ(tree.size(), 7);

	ft::rb_tree<int, int, ft::select1st<ft::pair<const int, int>>> tree2;
	tree2.insert_unique(ft::make_pair(1, 1));
	EXPECT_EQ(tree2.size(), 1);
	ft::rb_tree<int, int, ft::select1st<ft::pair<const int, int>>>::iterator it = tree2.find(1);
	tree2.erase(it);
	EXPECT_EQ(tree2.size(), 0);
}

TEST_F(TestRbTree, TestRbTreeEmpty) {
	EXPECT_FALSE(tree.empty());

	ft::rb_tree<int, int, ft::select1st<ft::pair<const int, int>>> tree2;
	EXPECT_TRUE(tree2.empty());
}

TEST_F(TestRbTree, TestRbTreeSize) {
	EXPECT_EQ(tree.size(), 10);

	ft::rb_tree<int, int, ft::select1st<ft::pair<const int, int>>> tree2;
	EXPECT_EQ(tree2.size(), 0);
}

TEST_F(TestRbTree, TestRbTreeClear) {
	tree.clear();

	EXPECT_EQ(tree.get_root(), tree.get_nil());
	EXPECT_EQ(tree.size(), 0);
}

TEST_F(TestRbTree, TestRbTreeIterators) {
	ft::rb_tree<int, int, ft::select1st<ft::pair<const int, int>>>::iterator it = tree.begin();

	EXPECT_EQ(it->first, 1);
	EXPECT_EQ(it->second, 1);
	++it;
	
	EXPECT_EQ(it->first, 6);
	EXPECT_EQ(it->second, 6);
	++it;

	EXPECT_EQ(it->first, 8);
	EXPECT_EQ(it->second, 8);
	++it, ++it, ++it;

	EXPECT_EQ(it->first, 15);
	EXPECT_EQ(it->second, 15);
	++it, ++it, ++it, it++;

	EXPECT_EQ(it->first, 27);
	EXPECT_EQ(it->second, 27);
	it++;

	EXPECT_EQ(it, tree.end());

	ft::rb_tree<int, int, ft::select1st<ft::pair<const int, int>>>::iterator itb = tree.end();

	--itb;
	EXPECT_EQ(itb->first, 27);
	EXPECT_EQ(itb->second, 27);

	--itb;
	EXPECT_EQ(itb->first, 25);
	EXPECT_EQ(itb->second, 25);
	--itb, --itb, --itb, --itb;

	EXPECT_EQ(itb->first, 13);
	EXPECT_EQ(itb->second, 13);
	itb--, itb--, itb--;

	EXPECT_EQ(itb->first, 6);
	EXPECT_EQ(itb->second, 6);
	--itb;

	EXPECT_EQ(itb->first, 1);
	EXPECT_EQ(itb->second, 1);

	EXPECT_EQ(itb, tree.begin());
}

TEST_F(TestRbTree, TestRbTreeReverseIterator) {
	ft::rb_tree<int, int, ft::select1st<ft::pair<const int, int>>>::reverse_iterator it = tree.rbegin();

	EXPECT_EQ(it->first, 27);
	EXPECT_EQ(it->second, 27);

	++it;
	EXPECT_EQ(it->first, 25);
	EXPECT_EQ(it->second, 25);
	++it, ++it, ++it, ++it;

	EXPECT_EQ(it->first, 13);
	EXPECT_EQ(it->second, 13);
	it++, it++, it++;

	EXPECT_EQ(it->first, 6);
	EXPECT_EQ(it->second, 6);
	++it;

	EXPECT_EQ(it->first, 1);
	EXPECT_EQ(it->second, 1);
	it++;
	EXPECT_EQ(it, tree.rend());

	ft::rb_tree<int, int, ft::select1st<ft::pair<const int, int>>>::reverse_iterator itb = tree.rend();

	--itb;
	EXPECT_EQ(itb->first, 1);
	EXPECT_EQ(itb->second, 1);
	--itb;
	
	EXPECT_EQ(itb->first, 6);
	EXPECT_EQ(itb->second, 6);
	--itb;

	EXPECT_EQ(itb->first, 8);
	EXPECT_EQ(itb->second, 8);
	--itb, --itb, --itb;

	EXPECT_EQ(itb->first, 15);
	EXPECT_EQ(itb->second, 15);
	--itb, --itb, --itb, itb--;

	EXPECT_EQ(itb->first, 27);
	EXPECT_EQ(itb->second, 27);
	itb--;

	EXPECT_EQ(itb, tree.rbegin());
}

TEST_F(TestRbTree, TestRbTreeIteratorOperatorsRelational) {
	ft::rb_tree<int, int, ft::select1st<ft::pair<const int, int>>>::iterator it = tree.begin();
	ft::rb_tree<int, int, ft::select1st<ft::pair<const int, int>>>::iterator it2 = tree.begin();

	EXPECT_TRUE(it == it2);
	EXPECT_FALSE(it != it2);
	it2++;
	EXPECT_TRUE(it != it2);
	EXPECT_FALSE(it == it2);

	ft::rb_tree<int, int, ft::select1st<ft::pair<const int, int>>> const tree2(tree);

	ft::rb_tree<int, int, ft::select1st<ft::pair<const int, int>>>::const_iterator it3 = tree2.begin();

	EXPECT_TRUE(it == it3);
	EXPECT_FALSE(it != it3);
	it3++;
	EXPECT_TRUE(it != it3);
	EXPECT_FALSE(it == it3);
}

TEST_F(TestRbTree, TestRbTreeOperatorsRelational) {
	ft::rb_tree<int, int, ft::select1st<ft::pair<const int, int>>> const tree2(tree);
	
	EXPECT_TRUE(tree == tree2);
	EXPECT_FALSE(tree != tree2);
	EXPECT_FALSE(tree > tree2);
	EXPECT_FALSE(tree < tree2);
	EXPECT_TRUE(tree <= tree2);
	EXPECT_TRUE(tree >= tree2);

	tree.insert_unique(ft::make_pair<int, int>(200, 200));
	
	EXPECT_TRUE(tree != tree2);
	EXPECT_FALSE(tree == tree2);
	EXPECT_TRUE(tree > tree2);
	EXPECT_FALSE(tree < tree2);
	EXPECT_TRUE(tree >= tree2);
	EXPECT_FALSE(tree <= tree2);
}
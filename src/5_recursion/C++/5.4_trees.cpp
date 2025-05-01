#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <iomanip>
#include <concepts>
#include <functional>
#include <variant>





namespace binary_tree
{

// ******** DEFENITION ********

template <std::default_initializable T>
struct Node
{
	Node() : left(nullptr), right(nullptr), val(T()) {}
	Node(const T& val) : left(nullptr), right(nullptr), val(val) {}

	Node* left;
	Node* right;
	T val;
};

template <typename T>
struct NodeValue {
	Node<T>* node;
};

template <typename Func, typename T>
concept is_visit_func_for_tree_node = requires(Func f, Node<T>* node)
{
	f(node);
};



// ******** CREATE AND DESTROY ********

template <std::destructible T>
void delete_tree(Node<T>* tree)
{
	if (!tree) {
		return;
	}

	delete_tree(tree->left);
	delete_tree(tree->right);
	delete tree;
}

template <typename T>
[[nodiscard]] Node<T>* create_tree(const std::vector<T>& vec, const T& nullVal)
{
	if (vec.empty()) {
		return nullptr;
	}

	std::queue<Node<T>**> q;
	Node<T>* result = nullptr;
	Node<T>** tmp = nullptr;
	q.push(&result);

	for (auto& val : vec) {
		if (q.empty()) {
			delete_tree(result);
			return nullptr;
		}

		if (val == nullVal) {
			q.pop();
			continue;
		}

		tmp = q.front();
		q.pop();
		*tmp = new Node(val);
		q.push(&(*tmp)->left);
		q.push(&(*tmp)->right);
	}

	return result;
}



// ******** PRINT ********

template <typename Print_Type> requires requires(const Print_Type& val) {std::cout << val;}
void print_node(const Print_Type& val, int spaceCount)
{
	std::cout << std::setw(2 * (spaceCount + 1)) << val << std::endl;
}

template <typename T>
void print_tree(Node<T>* tree, int h = 0)
{
	if (!tree) {
		print_node('*', h);
		return;
	}

	print_tree(tree->right, h + 1);
	print_node(tree->val, h);
	print_tree(tree->left, h + 1);
}



// ******** BYPASS ********

template <typename T, is_visit_func_for_tree_node<T> Func>
void direct_bypass(Node<T>* tree, Func visit)
{
#if 0
	if (!tree) {
		return;
	}

	visit(tree);
	direct_bypass(tree->left, visit);
	direct_bypass(tree->right, visit);
#endif

#if 1
	std::stack<Node<T>*> st;
	st.push(tree);
	while (!st.empty()) {
		tree = st.top();
		st.pop();

		if (!tree) {
			continue;
		}

		visit(tree);
		st.push(tree->right);
		st.push(tree->left);
	}
#endif
}

template <typename T, is_visit_func_for_tree_node<T> Func>
void reverse_bypass(Node<T>* tree, Func visit)
{
#if 0
	if (!tree) {
		return;
	}

	reverse_bypass(tree->left, visit);
	reverse_bypass(tree->right, visit);
	visit(tree);
#endif

#if 1
	std::stack<std::variant<NodeValue<T>, Node<T>*>> st;
	st.push(tree);
	while (!st.empty()) {
		auto& var = st.top();
		st.pop();

		if (std::holds_alternative<NodeValue<T>>(var)) {
			visit(std::get<NodeValue<T>>(var).node);
			continue;
		}

		tree = std::get<Node<T>*>(var);
		if (!tree) {
			continue;
		}
		st.push(NodeValue<T>{tree});
		st.push(tree->right);
		st.push(tree->left);
	}
#endif
}

template <typename T, is_visit_func_for_tree_node<T> Func>
void transverse_bypass(Node<T>* tree, Func visit)
{
#if 0
	if (!tree) {
		return;
	}

	transverse_bypass(tree->left, visit);
	visit(tree);
	transverse_bypass(tree->right, visit);
#endif

#if 1
	std::stack<std::variant<NodeValue<T>, Node<T>*>> st;
	st.push(tree);
	while (!st.empty()) {
		auto& var = st.top();
		st.pop();

		if (std::holds_alternative<NodeValue<T>>(var)) {
			visit(std::get<NodeValue<T>>(var).node);
			continue;
		}

		tree = std::get<Node<T>*>(var);
		if (!tree) {
			continue;
		}
		st.push(tree->right);
		st.push(NodeValue<T>{tree});
		st.push(tree->left);
	}
#endif
}

template <typename T, is_visit_func_for_tree_node<T> Func>
void level_bypass(Node<T>* tree, Func visit)
{
	std::queue<Node<T>*> qu;
	qu.push(tree);
	while (!qu.empty()) {
		tree = qu.front();
		qu.pop();

		if (!tree) {
			continue;
		}
		visit(tree);
		qu.push(tree->left);
		qu.push(tree->right);
	}
}



// ******** TREE PARAMETERS ********

template <typename T>
[[nodiscard]] int nodes_count(const Node<T>* tree) noexcept
{
	if (!tree) {
		return 0;
	}

	return nodes_count(tree->left) + nodes_count(tree->right) + 1;
}

template <typename T>
[[nodiscard]] int height(const Node<T>* tree) noexcept
{
	if (!tree) {
		return -1;
	}

	return std::max(height(tree->left), height(tree->right)) + 1;
}



// ******** FIND MAX ELEM ********

template <typename Iter>
concept comparable = requires(Iter it1, Iter it2) {
	{*it1 < *it2} -> std::convertible_to<bool>;
};

template <typename Iter>
concept comparable_iter_value = std::input_or_output_iterator<Iter> && comparable<Iter>;


template <comparable_iter_value Iter>
Node<std::remove_reference_t<decltype( *std::declval<Iter>() )>>* create_tournament_tree(Iter begin, Iter end)
{
	using Type = std::remove_reference_t<decltype(*begin)>;

	auto lastIndex = std::distance(begin, end) - 1;
	auto mid = std::next(begin, lastIndex / 2);

	Node<Type>* node = new Node<Type>;
	if (!lastIndex) {
		node->val = *mid;
		return node;
	}

	auto nextMid = std::next(mid);
	node->left = create_tournament_tree(begin, nextMid);
	node->right = create_tournament_tree(nextMid, end);
	node->val = std::max(node->left->val, node->right->val);
	return node;
}

}





int main(int, char**)
{
	try {
#if 0
		std::vector<char> treeTemplate = {'A', 'B', 'C', 'D', '\0', 'F', 'G'};
		binary_tree::Node<char>* tree = binary_tree::create_tree(treeTemplate, '\0');
		if (!tree) {
			std::cout << "binary_tree::create_tree ERROR!\n";
			return 0;
		}

		binary_tree::transverse_bypass(tree, [](binary_tree::Node<char>* node){ std::cout << node->val << std::endl; });
		binary_tree::reverse_bypass(tree, [](binary_tree::Node<char>* node){ std::cout << node->val << std::endl; });
		binary_tree::direct_bypass(tree, [](binary_tree::Node<char>* node){ std::cout << node->val << std::endl; });
		binary_tree::level_bypass(tree, [](binary_tree::Node<char>* node){ std::cout << node->val << std::endl; });
		binary_tree::print_tree(tree);
		std::cout << binary_tree::nodes_count(tree) << std::endl;
		std::cout << binary_tree::height(tree) << std::endl;
		binary_tree::delete_tree(tree);

#endif

#if 1
		std::vector<char> vec = {'A', 'M', 'P', 'R', 'O', 'L', 'E'};
		binary_tree::Node<char>* tournament = binary_tree::create_tournament_tree(vec.begin(), vec.end());
		binary_tree::print_tree(tournament);
		binary_tree::delete_tree(tournament);

#endif

	} catch (std::exception e) {
		std::cout << e.what();
		return 1;
	}


	return 0;
}
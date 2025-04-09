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
concept IsVisitFuncForTreeNode = requires(Func f, Node<T>* node)
{
	f(node);
};



// ******** CREATE AND DESTROY ********

template <std::destructible T>
void deleteTree(Node<T>* tree)
{
	if (!tree) {
		return;
	}

	deleteTree(tree->left);
	deleteTree(tree->right);
	delete tree;
}

template <typename T>
[[nodiscard]] Node<T>* createTree(const std::vector<T>& vec, const T& nullVal)
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
			deleteTree(result);
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
void printNode(const Print_Type& val, int spaceCount)
{
	std::cout << std::setw(2 * (spaceCount + 1)) << val << std::endl;
}

template <typename T>
void printTree(Node<T>* tree, int h = 0)
{
	if (!tree) {
		printNode('*', h);
		return;
	}

	printTree(tree->right, h + 1);
	printNode(tree->val, h);
	printTree(tree->left, h + 1);
}



// ******** BYPASS ********

template <typename T, IsVisitFuncForTreeNode<T> Func>
void directBypass(Node<T>* tree, Func visit)
{
#if 0
	if (!tree) {
		return;
	}

	visit(tree);
	directBypass(tree->left, visit);
	directBypass(tree->right, visit);
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

template <typename T, IsVisitFuncForTreeNode<T> Func>
void reverseBypass(Node<T>* tree, Func visit)
{
#if 0
	if (!tree) {
		return;
	}

	reverseBypass(tree->left, visit);
	reverseBypass(tree->right, visit);
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

template <typename T, IsVisitFuncForTreeNode<T> Func>
void transverseBypass(Node<T>* tree, Func visit)
{
#if 0
	if (!tree) {
		return;
	}

	transverseBypass(tree->left, visit);
	visit(tree);
	transverseBypass(tree->right, visit);
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

template <typename T, IsVisitFuncForTreeNode<T> Func>
void levelBypass(Node<T>* tree, Func visit)
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
[[nodiscard]] int nodesCount(const Node<T>* tree) noexcept
{
	if (!tree) {
		return 0;
	}

	return nodesCount(tree->left) + nodesCount(tree->right) + 1;
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
Node<std::remove_reference_t<decltype( *std::declval<Iter>() )>>* createTournamentTree(Iter begin, Iter end)
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
	node->left = createTournamentTree(begin, nextMid);
	node->right = createTournamentTree(nextMid, end);
	node->val = std::max(node->left->val, node->right->val);
	return node;
}

}





int main(int, char**)
{
	try {
#if 0
		std::vector<char> treeTemplate = {'A', 'B', 'C', 'D', '\0', 'F', 'G'};
		binary_tree::Node<char>* tree = binary_tree::createTree(treeTemplate, '\0');
		if (!tree) {
			std::cout << "binary_tree::createTree ERROR!\n";
			return 0;
		}

		binary_tree::transverseBypass(tree, [](binary_tree::Node<char>* node){ std::cout << node->val << std::endl; });
		binary_tree::reverseBypass(tree, [](binary_tree::Node<char>* node){ std::cout << node->val << std::endl; });
		binary_tree::directBypass(tree, [](binary_tree::Node<char>* node){ std::cout << node->val << std::endl; });
		binary_tree::levelBypass(tree, [](binary_tree::Node<char>* node){ std::cout << node->val << std::endl; });
		binary_tree::printTree(tree);
		std::cout << binary_tree::nodesCount(tree) << std::endl;
		std::cout << binary_tree::height(tree) << std::endl;
		binary_tree::deleteTree(tree);

#endif

#if 1
		std::vector<char> vec = {'A', 'M', 'P', 'R', 'O', 'L', 'E'};
		binary_tree::Node<char>* tournament = binary_tree::createTournamentTree(vec.begin(), vec.end());
		binary_tree::printTree(tournament);
		binary_tree::deleteTree(tournament);

#endif

	} catch (std::exception e) {
		std::cout << e.what();
		return 1;
	}


	return 0;
}
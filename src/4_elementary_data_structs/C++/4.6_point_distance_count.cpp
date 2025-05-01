#include <iostream>
#include <random>
#include <concepts>
#include <cmath>


struct Point
{
	Point(double x, double y) : x(x), y(y) {}

	double x;
	double y;
};

struct Node
{
	Node(const Point& p, Node* next): p(p), next(next) {}

	Point p;
	Node* next;
};

using Elem = Node*;



template <typename Ty>
concept default_init_or_pointer = std::default_initializable<Ty> || std::is_pointer_v<Ty>;

template <default_init_or_pointer Ty>
Ty** allocate_2D(size_t rows, size_t cols);

template <typename Ty>
void deallocate_2D(Ty** array, size_t rows);

template <typename Ty>
concept has_next_property = requires(Ty node) {
	{node->next++} -> std::same_as<Ty>;
};

template <has_next_property Ty>
void deallocate_lists_from_2D(Ty** array, size_t rows, size_t cols);



static const int N = 100;
static const double d = 0.1;
static const int G = static_cast<int>(1. / d);
static size_t count = 0;
static Elem** grid = nullptr;


void insert_point(Point&& p);
double distance(const Point& p1, const Point& p2);


int main(int, char**)
{
	// G + 2 - Чтобы свободно проводить проверки квадратов
	// вокруг целевого без дополнительных проверок (т.е. фиктивная граница)
	grid = allocate_2D<Elem>(G + 2, G + 2);

	std::random_device dev;
	std::mt19937 gen(dev());
	std::uniform_real_distribution rdis(0.0, 1.0);

	for (int i = 0; i < N; ++i) {
		std::cout << rdis(gen) << "\n";
		insert_point(Point(rdis(gen), rdis(gen)));
	}

	std::cout << "Sections count = " << count << std::endl;

	deallocate_lists_from_2D<Elem>(grid, G + 2, G + 2);
	deallocate_2D(grid, G + 2);

	return 0;
}





template <default_init_or_pointer Ty>
Ty** allocate_2D(size_t rows, size_t cols)
{
	Ty** array = new Ty*[rows];
	for (int i = 0; i < rows; ++i) {
		array[i] = new Ty[cols];
		for (int j = 0; j < cols; ++j) {
			if constexpr (std::is_pointer_v<Ty>) {
				array[i][j] = nullptr;
			} else {
				array[i][j] = Ty();
			}
		}
	}

	return array;
}

template <typename Ty>
void deallocate_2D(Ty** array, size_t rows)
{
	for (int i = 0; i < rows; ++i) {
		delete[] array[i];
	}

	delete[] array;
}

template <has_next_property Ty>
void deallocate_lists_from_2D(Ty** array, size_t rows, size_t cols)
{
	Ty nodeForDelete = nullptr;
	Ty tmp = nullptr;

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			nodeForDelete = array[i][j];
			while (nodeForDelete) {
				tmp = nodeForDelete->next;
				delete nodeForDelete;
				nodeForDelete = tmp;
			}
			array[i][j] = nullptr;
		}
	}
}



void insert_point(Point&& p)
{
	int X = static_cast<int>(p.x * G + 1);
	int Y = static_cast<int>(p.y * G + 1);

	Elem node = new Node(p, grid[X][Y]);
	for (int i = X - 1; i <= X + 1; ++i) {
		for (int j = Y - 1; j <= Y + 1; ++j) {
			for (Elem x = node; x != nullptr; x = x->next) {
				if (distance(x->p, p) <= d) {
					++count;
				}
			}
		}
	}

	grid[X][Y] = node;
}

double distance(const Point& p1, const Point& p2)
{
	return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

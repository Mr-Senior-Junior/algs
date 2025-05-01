#pragma once
#include <iostream>
#include <concepts>
#include <random>
#include <chrono>



namespace helper_impl
{

template <typename Iter>
concept printable_iterator = 	
	std::input_or_output_iterator<Iter> &&
	requires(std::remove_reference_t<decltype(*std::declval<Iter>())> val) {
		std::cout << val;
	};
}


template <typename Array>
concept is_cmp_array = requires(Array arr) {
	{arr[0] < arr[0]} -> std::convertible_to<bool>;
};


template <typename Iter>
concept out_iterator =
	std::output_iterator<Iter, std::remove_reference_t<decltype(*std::declval<Iter>())>>;


template <typename Iter>
concept comparable_iter_value =
	std::input_or_output_iterator<Iter> &&
	requires(Iter it1, Iter it2) {
		{*it1 < *it2} -> std::convertible_to<bool>;
	};



template <helper_impl::printable_iterator Iter>
void print_collection(Iter begin, Iter end)
{
	while (begin != end) {
		std::cout << *begin << " ";
		std::advance(begin, 1);
	}
	std::cout << std::endl;
}

template <std::ranges::range Range>
void print_collection(Range&& r)
{
	print_collection(r.begin(), r.end());
}


int get_random_int()
{
	static std::random_device dev;
	static std::mt19937 gen(dev());
	static std::uniform_int_distribution dist(0, 1000);

	return dist(gen);
}


template <out_iterator Iter>
void random_init(Iter inserter, size_t size) 
{
	for (size_t i = 0; i < size; ++i) {
		inserter = get_random_int();
	}
}


template <typename Fun, typename... Args> requires std::invocable<Fun, Args...>
[[nodiscard]] auto function_execution_time(Fun&& fun, Args&&... args)
{
	auto start = std::chrono::steady_clock::now();
	fun(std::forward<Args>(args)...);
	auto finish = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
}

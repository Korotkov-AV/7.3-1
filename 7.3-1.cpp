// 7.3-1.cpp : 


#include <iostream>
#include<deque>
#include<future>

void findMin(std::deque<int> l, int start, std::promise<int> p) {
	auto min = start;
	for (auto iter = min; iter < l.size(); iter++) {
		if (l[iter] < l[min]) min = iter;
	}
	p.set_value(min);
}

void sort(std::deque<int>& l) {
	for (int i = 0; i < l.size(); i++)
	{
		std::promise<int> prom;
		std::future<int> fut = prom.get_future();
		auto min = std::async(findMin, l, i, std::move(prom));
		std::swap(l[fut.get()], l[i]);
	}
}

int main()
{
	std::deque<int> list(11);
	for (int i = 0; i < list.size(); i++) {
		list[i] = std::rand();
		std::cout << list[i] << " ";
	}

	sort(list);
	std::cout << "\n\n";

	for (auto n : list) {
		std::cout << n << " ";
	}
}
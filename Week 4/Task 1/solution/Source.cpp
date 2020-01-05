#include <iostream>
#include <list>
#include <algorithm>
#include <vector>

int main()
{
	int n;
	std::cin >> n;

	std::list<int> lst;
	std::vector<std::list<int>::iterator> pos(100000, lst.end());

	int num1, num2;

	while (n-- != 0)
	{
		std::cin >> num1 >> num2;		
		pos[num1] = lst.insert(pos[num2], num1);
	}

	for (const auto& i : lst)
	{
		std::cout << i << ' ';
	}

	return 0;
}
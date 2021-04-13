#include <iostream>
#include <cstdlib>
#include <List.h>

int main()
{
	TList<int> MyList0;
	TList<int> MyList1;
	TList<int> MyList2;

	MyList0.InsFirst(3);
	MyList0.InsLast(33);
	MyList0.InsLast(333);

	MyList2.InsFirst(1);
	MyList2.InsLast(1);
	MyList2.InsLast(1);

	MyList1.InsFirst(3);
	MyList1.InsLast(33);
	MyList1.InsLast(333);


	if (MyList0 == MyList1)
		std::cout << "два списка равны\n";
	else
		std::cout << "два списка не равны\n";

	if (MyList0 == MyList2)
		std::cout << "два списка равны\n";
	else
		std::cout << "два списка не равны\n";

	if (MyList2 == MyList1)
		std::cout << "два списка равны\n";
	else
		std::cout << "два списка не равны\n";

	std::cout << MyList0 << "\n";
	std::cout << MyList1 << "\n"; 
	std::cout << MyList2 << "\n";

	return 0;
}
#include <iostream>
#include <iomanip>
using namespace std;

void main() {
	enum weekday {monday, tuesday, wednesday, thursday, friday, saturday, sunday};
	float temp, avg = 0, max = -273.15;
		
	cout << "Input temperatures: " << endl;
	for (weekday wd=monday; wd <= sunday; wd=weekday(wd+1)) {
		cin >> temp;
		avg += temp;
		if (temp > max)
			max = temp;
	}
	
	cout << "Average: " << setiosflags(ios::fixed) << setprecision(2) << avg/7 << endl;
	cout << "Highest: " << max << endl;
}


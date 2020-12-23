#include "main.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;

	// test write uleb128 1607549357699 -> 839da2cbe42e;
	{
		fprintf(stderr, "\nWrite ULEB128\n");

		uintmax_t value = 1607549357699;
		uintmax_t bytesToAllocate = leb128::calcSizeOfUleb128(value);
		unsigned char* buffer = new unsigned char[bytesToAllocate];
		uintmax_t count = leb128::writeUleb128(buffer, value);
		string hex = helper::readBuffToHexStr(buffer, count);

		fprintf(stderr, "%llu - %llu\n", bytesToAllocate, count);
		fprintf(stderr, "%s\n", hex.c_str());

		delete[] buffer;
	}

	// test read uleb128 839da2cbe42e -> 1607549357699
	{
		fprintf(stderr, "\nRead ULEB128\n");

		unsigned char buffer[] = { 0x83, 0x9d, 0xa2, 0xcb, 0xe4, 0x2e };
		uintmax_t result;
		uintmax_t count = leb128::readUleb128(buffer, &result);
		fprintf(stderr, "%llu - %llu\n", result, count);
	}

	// test write leb128 123456 -> c0bb78;
	{
		fprintf(stderr, "\nWrite SLEB128\n");
	
		uintmax_t value = 123456;
		uintmax_t bytesToAllocate = leb128::calcSizeOfLeb128(value);
		unsigned char* buffer = new unsigned char[bytesToAllocate];
		uintmax_t count = leb128::writeLeb128(buffer, value);
		string hex = helper::readBuffToHexStr(buffer, count);

		fprintf(stderr, "%llu - %llu\n", bytesToAllocate, count);
		fprintf(stderr, "%s\n", hex.c_str());

		delete[] buffer;
	}

	// test read uleb128 c0c407 -> 123456
	{
		fprintf(stderr, "\nRead SLEB128\n");

		unsigned char buffer[] = { 0xc0, 0xc4, 0x07 };
		string hex = helper::readBuffToHexStr(buffer, 3);
		intmax_t expectedResult = 123456;
		fprintf(stderr, "%s -> %lli\n", hex.c_str(), expectedResult);

		intmax_t result;
		uintmax_t count = leb128::readLeb128(buffer, &result);
		fprintf(stderr, "[%llu, %llu, %u]\n", result, count, expectedResult == result);
	}

	return 0;
}

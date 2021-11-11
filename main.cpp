#include "main.h"

class TxnData {
protected:
	unsigned const char* buffer;
public:
	TxnData(unsigned const char* buffer) {
		this->buffer = buffer;
	}
	virtual void readBuffer() {}
	virtual std::string toString() { return "TxnData"; }
};

std::map<uintmax_t, std::function<TxnData*(unsigned char* buffer)>>mapOfTypes;

class TxnDataUserId : public TxnData {
	uintmax_t userId;
public:
	TxnDataUserId(unsigned char* buffer) : TxnData(buffer) {
		this->userId = 0;
	}
	void readBuffer() {
		LEB128::readUnsigned(this->buffer, &this->userId);
	}
	std::string toString() { return "TxnDataUserId"; }
};

class ExternalTxn {
	unsigned char* buffer;
	uintmax_t version;
	uintmax_t type;
	bool valid;
	Txn::DataWrapper* data;
public:
	ExternalTxn(unsigned char* buffer) {
		this->valid = false;
		this->data = nullptr;
		this->buffer = buffer;

		uintmax_t shift = 0;
		// read field: version
		shift+= LEB128::readUnsigned(buffer + shift, &this->version);
		// read field: txn type
		shift+= LEB128::readUnsigned(buffer + shift, &this->type);

		if (Txn::typeExist(this->type) == true) {
			Txn::TypeApi* $txnApi = Txn::getTypeApi(this->type);

			this->data = $txnApi->createDataWrapper(this->buffer);
			this->data->readBuffer();
			this->valid = true;

			std::cout << this->version << " & " << this->type << " " << this->data->toString() << "\n";
		}
	}
	~ExternalTxn() {
		delete this->data;
	}
};

int main()
{
	Txn::init();

	std::cout << "Hello CMake." << std::endl;

	// test write uleb128 1607549357699 -> 839da2cbe42e;
	{
		fprintf(stderr, "\nWrite ULEB128\n");

		uintmax_t value = 1607549357699;
		uintmax_t bytesToAllocate = LEB128::calcSizeOfUnsigned(value);
		unsigned char* buffer = new unsigned char[bytesToAllocate];
		uintmax_t count = LEB128::writeUnsigned(buffer, value);
		std::string hex = helper::readBuffToHexStr(buffer, count);

		fprintf(stderr, "%llu - %llu\n", bytesToAllocate, count);
		fprintf(stderr, "%s\n", hex.c_str());

		delete[] buffer;
	}

	// test read uleb128 839da2cbe42e -> 1607549357699
	{
		fprintf(stderr, "\nRead ULEB128\n");

		unsigned char buffer[] = { 0x83, 0x9d, 0xa2, 0xcb, 0xe4, 0x2e };
		uintmax_t result;
		uintmax_t count = LEB128::readUnsigned(buffer, &result);
		fprintf(stderr, "%llu - %llu\n", result, count);
	}

	// test write leb128 123456 -> c0bb78;
	{
		fprintf(stderr, "\nWrite SLEB128\n");
	
		uintmax_t value = 123456;
		uintmax_t bytesToAllocate = LEB128::calcSizeOfSigned(value);
		unsigned char* buffer = new unsigned char[bytesToAllocate];
		uintmax_t count = LEB128::writeSigned(buffer, value);
		std::string hex = helper::readBuffToHexStr(buffer, count);

		fprintf(stderr, "%llu - %llu\n", bytesToAllocate, count);
		fprintf(stderr, "%s\n", hex.c_str());

		delete[] buffer;
	}

	// test read uleb128 c0c407 -> 123456
	{
		fprintf(stderr, "\nRead SLEB128\n");

		unsigned char buffer[] = { 0xc0, 0xc4, 0x07 };
		std::string hex = helper::readBuffToHexStr(buffer, 3);
		intmax_t expectedResult = 123456;
		fprintf(stderr, "%s -> %lli\n", hex.c_str(), expectedResult);

		intmax_t result;
		uintmax_t count = LEB128::readSigned(buffer, &result);
		fprintf(stderr, "[%llu, %llu, %u]\n", result, count, expectedResult == result);
	}

	{
		unsigned char buffer[] = { 0x01, 0x55, 0x27 };
		ExternalTxn test(buffer);
	}

	return 0;
}

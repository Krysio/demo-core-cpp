#pragma once

#include "../main.h"

namespace Txn {
	class DataWrapper {
	protected:
		unsigned const char* buffer;
	public:
		DataWrapper(buffer_ptr buffer);
		virtual void readBuffer();
		virtual std::string toString();
	};

	class TypeApi {
	public:
		virtual DataWrapper* createDataWrapper(buffer_ptr buffer);
	};

	/******************************/

	typedef std::map<uintmax_t, TypeApi*> mapOfTypeApi;

	/******************************/

	bool
	typeExist(uintmax_t type);

	TypeApi*
	getTypeApi(uintmax_t type);

	void
	registerType(
		uintmax_t type,
		TypeApi* api
	);

	void
	init();
}

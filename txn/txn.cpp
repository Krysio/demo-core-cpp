#pragma once

#include "../main.h"

namespace Txn {
	DataWrapper::DataWrapper(buffer_ptr buffer) {
		this->buffer = buffer;
	}
	void DataWrapper::readBuffer() {}
	std::string DataWrapper::toString() {
		return "TxnDataWrapper";
	}

	DataWrapper* TypeApi::createDataWrapper(buffer_ptr buffer) {
		return nullptr;
	}

	/******************************/

	mapOfTypeApi typeMap = {};

	bool
	typeExist(uintmax_t type) {
		return typeMap.find(type) != Txn::typeMap.end();
	}

	void
	registerType(
		uintmax_t type,
		TypeApi* api
	) {
		typeMap.insert({type, api});
	}

	TypeApi*
	getTypeApi(
		uintmax_t type
	) {
		return typeMap.at(type);
	}

	/******************************/

	void init() {
		Txn::TypeRemoveUser::init();
	}
}

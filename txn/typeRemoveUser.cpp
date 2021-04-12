#include "../main.h"

namespace Txn {
	namespace TypeRemoveUser {
		class DataWrapper : public Txn::DataWrapper {
		public:
			DataWrapper(buffer_ptr buffer) : Txn::DataWrapper(buffer) {}
		};

		class Api : public Txn::TypeApi {
		public:
			Api() {}
			Txn::DataWrapper* createDataWrapper(buffer_ptr buffer) {
				return new DataWrapper(buffer);
			}
		};

		void init() {
			Txn::registerType(TYPE, new Api());
		}
	}
}

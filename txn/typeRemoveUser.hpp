constexpr auto TXN_REMOVE_USER = 0x55;

namespace Txn {
	namespace TypeRemoveUser {
		constexpr auto TYPE = TXN_REMOVE_USER;
		void init();
	}
}
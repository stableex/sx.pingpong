#include <eosio/transaction.hpp>
#include <eosio/crypto.hpp>

uint64_t pingpong::checksum256_to_uint64( const checksum256 hash )
{
	auto arr = hash.extract_as_byte_array();

	uint64_t serial = ((uint64_t)arr.data()[0] << 56) +
		((uint64_t)arr.data()[4] << 48) +
		((uint64_t)arr.data()[8] << 40) +
		((uint64_t)arr.data()[12] << 32) +
		((uint64_t)arr.data()[16] << 24) +
		((uint64_t)arr.data()[20] << 16) +
		((uint64_t)arr.data()[24] << 8) +
		(uint64_t)arr.data()[28];

	return serial;
}

eosio::checksum256 pingpong::get_tx_id()
{
    size_t size = eosio::transaction_size();
    char buf[size];
    size_t read = eosio::read_transaction( buf, size );
    eosio::check( size == read, "read_transaction failed");
    return eosio::sha256( buf, read );
}
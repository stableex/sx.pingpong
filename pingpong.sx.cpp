#include "pingpong.sx.hpp"

[[eosio::action]]
void pingpong::ping( optional<name> name )
{
	const checksum256 trx_id = get_tx_id();
	const uint64_t generated_uid = checksum256_to_uint64( trx_id );

	// clear any old pings
	clear();

	// create ping entry
    pingpong::pings_table _pings( get_self(), get_self().value );
    const auto ping_itr = _pings.find( generated_uid );
	check( ping_itr == _pings.end(), "uid already exists");

	_pings.emplace( get_self(), [&]( auto& row ) {
		row.uid = generated_uid;
		row.name = *name;
		row.trx_id = trx_id;
		row.timestamp = current_time_point();
	});
}

[[eosio::action]]
void pingpong::pong( const name account, const optional<checksum256> trx_id )
{
	require_auth( account );

	// transaction ID of pong
	const checksum256 pong_trx_id = get_tx_id();

	// provide either uid & transation id
	const uint64_t generated_uid = checksum256_to_uint64( get_latest_trx_id( trx_id ) );

	// add pong response to ping
	pingpong::pings_table _pings( get_self(), get_self().value );
    const auto ping_itr = _pings.find( generated_uid );
	check( ping_itr != _pings.end(), "uid does not exists");

	_pings.modify( ping_itr, get_self(), [&]( auto& row ) {
		// appoint account if first
		if ( !row.first ) row.first = account;

		// delta between start & now in milliseconds
		const microseconds before = row.timestamp.time_since_epoch();
		const microseconds now = current_time_point().time_since_epoch();

		// delta calculated in block numbers (1 block = 500ms)
		const int64_t delta = (now - before).count() / 1000 / 500;
		row.pongs[ pong_trx_id ] = delta;
	});
}

checksum256 pingpong::get_latest_trx_id( const optional<checksum256> trx_id )
{
	pingpong::pings_table _pings( get_self(), get_self().value );

	if ( trx_id ) return *trx_id;

	auto index = _pings.get_index<"bytimestamp"_n>();
	auto itr = index.rbegin();
	return itr->trx_id;
}

[[eosio::action]]
void pingpong::clear()
{
	pingpong::pings_table _pings( get_self(), get_self().value );
	auto index = _pings.get_index<"bytimestamp"_n>();

	// delete pings that are older than 1 hour (maximum of 2 per clear action)
	set<uint64_t> to_delete;
	for ( const auto row : index ) {
		const uint32_t delta = current_time_point().sec_since_epoch() - row.timestamp.sec_since_epoch();
		if ( delta < 3600 ) break;
		if ( to_delete.size() >= 2 ) break;
		to_delete.insert( row.uid );
	}

	// delete rows
	for ( const uint64_t uid : to_delete ) {
		_pings.erase( _pings.find( uid ) );
	}
}

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
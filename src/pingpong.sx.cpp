#include <pingpong.sx.hpp>

#include "utils.cpp"

[[eosio::action]]
void pingpong::ping( optional<uint64_t> uid, optional<name> type )
{
	const checksum256 trx_id = get_tx_id();
	const uint64_t generated_uid = uid ? *uid : checksum256_to_uint64( trx_id );

	// create ping entry
    pingpong::pings_table _pings( get_self(), get_self().value );
    const auto ping_itr = _pings.find( generated_uid );
	check( ping_itr == _pings.end(), "uid already exists");

	_pings.emplace( get_self(), [&]( auto& row ){
		row.uid = generated_uid;
		row.type = *type;
		row.trx_id = trx_id;
		row.timestamp = current_time_point();
	});
}

[[eosio::action]]
void pingpong::pong( const name account, const uint64_t uid )
{
	require_auth( account );

	// add pong response to ping
	pingpong::pings_table _pings( get_self(), get_self().value );
    const auto ping_itr = _pings.find( uid );
	check( ping_itr != _pings.end(), "uid does not exists");

	_pings.modify( ping_itr, get_self(), [&]( auto& row ) {
		// appoint account if first
		if ( !row.first ) row.first = account;

		// delta between start & now in milliseconds
		const microseconds before = row.timestamp.time_since_epoch();
		const microseconds now = current_time_point().time_since_epoch();
		const int64_t delta = (now - before).count() / 1000;
		row.pongs[ account ] = delta;
	});
}

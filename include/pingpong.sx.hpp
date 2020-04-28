#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>

#include <optional>

using namespace eosio;
using namespace std;

class [[eosio::contract("pingpong.sx")]] pingpong : public contract {

public:
	using contract::contract;

	/**
	 * ## TABLE `pings`
	 *
	 * ### multi-indexes
	 *
	 * | `param`        | `index_position` | `key_type` |
	 * |----------------|------------------|------------|
	 * | `type` 		| 2                | i64        |
	 * | `timestamp`    | 3                | i64        |
	 *
	 * ### params
	 *
	 * - `{uint64_t} uid` - [primary key] unique identifier
	 * - `{name} type` - type category (allows filtering by type)
	 * - `{time_point} timestamp` - timestamp when ping was executed
	 * - `{name} first` - first account to respond to ping
	 * - `{map<name, int64_t>} pongs` - accounts with their response time in block numbers (500ms per block)
	 * - `{checksum256} trx_id` - transaction ID
	 *
	 * ### example
	 *
	 * ```json
	 * {
	 *   "uid": 123,
	 *   "type": "myping",
	 *   "timestamp": "2020-04-21T17:12:51.500",
	 *   "first": "myaccount",
	 *   "pongs": [ { "key": "myaccount", "value": 3 } ]	,
	 *   "trx_id": "0311bad192115ef75abe1208330d2370a409a62a00fdb7140ef6fdf15931ef76"
	 * }
	 * ```
	 */
	struct [[eosio::table("pings"), eosio::contract("pingpong.sx")]] pings_row {
		uint64_t                	uid;
		name                		type;
		time_point                	timestamp;
		name                		first;
		map<name, int64_t>    		pongs;
		checksum256                	trx_id;

		uint64_t primary_key() const { return uid; }
		uint64_t by_type() const { return type.value; }
		uint64_t by_timestamp() const { return timestamp.time_since_epoch().count(); }
	};
	typedef eosio::multi_index< "pings"_n, pings_row,
		indexed_by<"bytype"_n, const_mem_fun<pings_row, uint64_t, &pings_row::by_type>>,
		indexed_by<"bytimestamp"_n, const_mem_fun<pings_row, uint64_t, &pings_row::by_timestamp>>
	> pings_table;

	/**
	 * ## ACTION `ping`
	 *
	 * Ping alerts users to reply with pong
	 *
	 * - **authority**: `any`
	 *
	 * ### params
	 *
	 * - `{name} [name=null]` - (optional) name of ping (allows filtering by name)
	 *
	 * ### Example
	 *
	 * ```bash
	 * $ cleos push action pingpong.sx ping '["myname"]' -p myaccount
	 * ```
	 */
	[[eosio::action]]
	void ping( optional<name> name );

	/**
	 * ## ACTION `pong`
	 *
	 * Pong replies to ping
	 *
	 * - **authority**: `account`
	 *
	 * ### params
	 *
	 * - `{name} account` - account replying to ping
	 * - `{uint64_t} trx_id` - transaction ID of ping
	 *
	 * ### Example
	 *
	 * ```bash
	 * $ cleos push action pingpong.sx pong '["myaccount", "02154c4be85e915117b3170782a7d30c41ec9772b8518d5608089fbcbc86c491"]' -p myaccount
	 * ```
	 */
	[[eosio::action]]
	void pong( const name account, const checksum256 trx_id );

	/**
	 * ## ACTION `clear`
	 *
	 * Deletes pings that are older than 1 hour (maximum of 2 per clear action)
	 *
	 * - **authority**: `any`
	 *
	 * ### Example
	 *
	 * ```bash
	 * $ cleos push action pingpong.sx clear '[]' -p myaccount
	 * ```
	 */
	[[eosio::action]]
	void clear();

	// action wrappers
	using ping_action = eosio::action_wrapper<"ping"_n, &pingpong::ping>;
	using pong_action = eosio::action_wrapper<"pong"_n, &pingpong::pong>;
	using clear_action = eosio::action_wrapper<"clear"_n, &pingpong::clear>;

private:
	uint64_t checksum256_to_uint64( const checksum256 hash );
	eosio::checksum256 get_tx_id();
};

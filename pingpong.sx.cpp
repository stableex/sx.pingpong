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
 * ### params
 *
 * - `{uint64_t} id` - unique ID
 * - `{checksum256} trx_id` - transaction ID
 * - `{name} name` - name of ping
 * - `{time_point} timestamp` - timestamp when ping was executed
 * - `{map<name, time_point>} pongs` - accounts with their response time using pong action
 *
 * ### example
 *
 * ```json
 * {
 *   "uid": 123,
 *   "trx_id": ??,
 *   "timestamp": ??,
 *   "pongs": ??
 * }
 * ```
 */
struct [[eosio::table("pings"), eosio::contract("pingpong.sx")]] pings_row {
	uint64_t                	uid;
	checksum256                	trx_id;
	time_point                	timestamp;
	map<name, time_point>    	pongs;

	uint64_t primary_key() const { return uid; }
	int64_t by_timestamp() const { return timestamp.time_since_epoch().count(); }
};
typedef eosio::multi_index< "pings"_n, pings_row,
	indexed_by<"bytimestamp"_n, const_mem_fun<pings_row, int64_t, &pings_row::by_timestamp>>
> pings_table;

/**
 * ## ACTION `ping`
 *
 * Ping alerts users to replay with pong
 *
 * - **authority**: `any`
 *
 * ### params
 *
 * - `{uint64_t} [uid=null]` - (optional) unique identifier number used to lookup ping
 *
 * ### Example
 *
 * ```bash
 * $ cleos push action pingpong.sx ping '[123]' -p myaccount
 * ```
 */
[[eosio::action]]
void ping( const optional<uint64_t> uid )
{
	print("ping");
}

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
 * - `{uint64_t} uid` - unique identifier number of ping
 * - `{checksum256} [trx_id=null]` - transaction ID of ping (additional assert)
 *
 * ### Example
 *
 * ```bash
 * $ cleos push action pingpong.sx pong '["myaccount", 123, null]' -p myaccount
 * ```
 */
[[eosio::action]]
void pong( const name account, const uint64_t uid, const optional<checksum256> trx_id )
{
	print("pong");
}

// action wrappers
using ping_action = eosio::action_wrapper<"ping"_n, &pingpong::ping>;
using pong_action = eosio::action_wrapper<"pong"_n, &pingpong::pong>;
};

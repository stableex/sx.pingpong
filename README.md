# SX `PingPong` ⚡️ - EOSIO Smart Contract

> Response time speed contract

## Table of Content

- [`concept`](#concept)
- [`examples`](#examples)

## Concept

1. Any user calls `ping` action.
2. Listening users respond with `pong` using the transaction ID.
3. Response times are recorded in `pings` table in terms of block number.

## Quickstart

```bash
# ping
cleos push action pingpong.sx ping '["myping"]' -p myaccount

# pong
cleos push action pingpong.sx pong '["myaccount", "0311bad192115ef75abe1208330d2370a409a62a00fdb7140ef6fdf15931ef76"]' -p myaccount
```

### Examples

- [get_pings](/examples/get_pings.js)
- [get_pings_by_timestamp](/examples/get_pings_by_timestamp.js)
- [get_pings_by_type](/examples/get_pings_by_type.js)
- [push_transaction](/examples/push_transaction.js)

## Chains

| **network** | **contract**     |
|-------------|--------------|
| EOS         | [`pingpong.sx`](https://bloks.io/account/pingpong.sx)
| BOS         | [`pingpong.sx`](https://bos.bloks.io/account/pingpong.sx)
| WAX         | [`pingpong.sx`](https://wax.bloks.io/account/pingpong.sx)
| Jungle2     | [`eosnpingpong`](https://jungle.bloks.io/account/eosnpingpong)
| Jungle3     | [`eosnpingpong`](https://jungle3.bloks.io/account/eosnpingpong)
| Kylin       | [`eosnpingpong`](https://kylin.bloks.io/account/eosnpingpong)
| WAX Test    | [`eosnpingpong`](https://wax-test.bloks.io/account/eosnpingpong)
| BOS Test    | [`eosnpingpong`](https://bos-test.bloks.io/account/eosnpingpong)

## Build

```bash
$ eosio-cpp pingpong.sx.cpp -o pingpong.sx.wasm
$ cleos set contract pingpong.sx . pingpong.sx.wasm pingpong.sx.abi
```

## TABLE `pings`

### multi-indexes

| `param`        | `index_position` | `key_type` |
|----------------|------------------|------------|
| `name` 		 | 2                | i64        |
| `timestamp`    | 3                | i64        |

### params

- `{uint64_t} uid` - [primary key] unique identifier
- `{name} name` - ping name (allows easy to filter using secondary index)
- `{time_point} timestamp` - timestamp when ping was executed
- `{name} first` - first account to respond to ping
- `{map<name, int64_t>} pongs` - transactions with their response time in block numbers (500ms per block)
- `{checksum256} trx_id` - transaction ID

### example

```json
{
    "uid": 123,
    "name": "myping",
    "timestamp": "2020-04-21T17:12:51.500",
    "first": "myaccount",
    "pongs": [ { "key": "f370a9bf27c659ee7c5ff9226dfe612420a261a91a14c15c244d067077fbea24", "value": 3 } ]	,
    "trx_id": "0311bad192115ef75abe1208330d2370a409a62a00fdb7140ef6fdf15931ef76"
}
```

## ACTION `ping`

Ping alerts users to replay with pong

- **authority**: `any`

### params

- `{name} [name=null]` - (optional) name of ping (allows filtering by name)

### Example

```bash
cleos push action pingpong.sx ping '["myping"]' -p myaccount
```

## ACTION `pong`

Pong replies to ping

- **authority**: `account`

### params

- `{name} account` - account replying to ping
- `{uint64_t} [trx_id=null]` - (optional) transaction ID of ping (default to latest ping)

### Example

```bash
$ cleos push action pingpong.sx pong '["myaccount", "02154c4be85e915117b3170782a7d30c41ec9772b8518d5608089fbcbc86c491"]' -p myaccount
$ cleos push action pingpong.sx pong '["myaccount", null]' -p myaccount
```

## ACTION `clear`

Deletes pings that are older than 1 hour (maximum of 2 per clear action)

- **authority**: `any`

### Example

```bash
$ cleos push action pingpong.sx clear '[]' -p myaccount
```

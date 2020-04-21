# SX `PingPong` ⚡️ - EOSIO Smart Contract

> Response time speed contract

## Table of Content

- [`concept`](#concept)
- [`examples`](#examples)

## Concept

1. Any user calls `ping` action.
2. Listening users respond with `pong` using the transaction ID and/or name of `ping`.
3. Response times are recorded in `pings` table.

## Quickstart

```bash
# ping
cleos push action pingpong.sx ping '[123, "mytype"]' -p myaccount

# pong
cleos push action pingpong.sx pong '["myaccount", 123]' -p myaccount
```

## Build

```bash
$ eosio-cpp ./src/pingpong.sx.cpp -o pingpong.sx.wasm -I include
$ cleos set contract pingpong.sx . pingpong.sx.wasm pingpong.sx.abi
```

## TABLE `pings`

### multi-indexes

| `param`        | `index_position` | `key_type` |
|----------------|------------------|------------|
| `type` 		| 2                | i64        |
| `timestamp`    | 3                | i64        |

### params

- `{uint64_t} uid` - [primary key] unique identifier
- `{name} type` - type category (allows filtering by type)
- `{time_point} timestamp` - timestamp when ping was executed
- `{name} first` - first account to respond to ping
- `{map<name, int64_t>} pongs` - accounts with their response time in milliseconds
- `{checksum256} trx_id` - transaction ID

### example

```json
{
"uid": 123,
"type": "myping",
"timestamp": "2020-04-21T17:12:51.500",
"first": "myaccount",
"pongs": [ { "key": "myaccount", "value": 1500 } ]	,
"trx_id": "0311bad192115ef75abe1208330d2370a409a62a00fdb7140ef6fdf15931ef76"
}
```

## ACTION `ping`

Ping alerts users to replay with pong

- **authority**: `any`

### params

- `{uint64_t} [uid=null]` - (optional) unique identifier number used to lookup ping
- `{name} type` - type category (allows filtering by type)

### Example

```bash
# ping
cleos push action pingpong.sx ping '[123, "mytype"]' -p myaccount

# pong
cleos push action pingpong.sx pong '["myaccount", 123]' -p myaccount
```

### Examples JS

- [get_pings](/examples/get_pings.js)
- [get_pings_by_timestamp](/examples/get_pings_by_timestamp.js)
- [get_pings_by_type](/examples/get_pings_by_type.js)
- [push_transaction](/examples/push_transaction.js)

## ACTION `pong`

Pong replies to ping

- **authority**: `account`

### params

- `{name} account` - account replying to ping
- `{uint64_t} uid` - unique identifier number of ping

### Example

```bash
$ cleos push action pingpong.sx pong '["myaccount", 123]' -p myaccount
```

## ACTION `clear`

Deletes pings that are older than 1 hour (maximum of 2 per clear action)

- **authority**: `any`

### Example

```bash
$ cleos push action pingpong.sx clear '[]' -p myaccount
```

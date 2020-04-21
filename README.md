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
cleos push action pingpong.sx ping '[123]' -p myaccount

# pong
cleos push action pingpong.sx pong '["myaccount", 123, null]' -p myaccount
```

## Build

```bash
$ eosio-cpp pingpong.sx.cpp -o pingpong.sx.wasm
$ cleos set contract pingpong.sx . pingpong.sx.wasm pingpong.sx.abi
```

## ACTION `ping`

Ping alerts users to replay with pong

- **authority**: `any`

### params

- `{uint64_t} [uid=null]` - (optional) unique identifier number used to lookup ping

### Example

```bash
$ cleos push action pingpong.sx ping '[123]' -p myaccount
```

## ACTION `pong`

Pong replies to ping

- **authority**: `account`

### params

- `{name} account` - account replying to ping
- `{uint64_t} uid` - unique identifier number of ping
- `{checksum256} [trx_id=null]` - transaction ID of ping (additional assert)

### Example

```bash
$ cleos push action pingpong.sx pong '["myaccount", 123, null]' -p myaccount
```

## TABLE `pings`

### params

- `{uint64_t} id` - unique ID
- `{checksum256} trx_id` - transaction ID
- `{name} name` - name of ping
- `{time_point} timestamp` - timestamp when ping was executed
- `{map<name, time_point>} pongs` - accounts with their response time using pong action

### example

```json
{
    "uid": 123,
    "trx_id": ??,
    "timestamp": ??,
    "pongs": ??
}
```
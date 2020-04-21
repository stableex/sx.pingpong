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
#!/usr/bin/env bash

# unlock wallet
mkdir -p dist
cleos wallet unlock --password $(cat ~/eosio-wallet/.pass)

# Ricardian Contract sha256
shasum -a 256 icons/pingpong.png

# build contract
eosio-cpp pingpong.sx.cpp -o pingpong.sx.wasm

# create accounts
cleos system newaccount eosio pingpong.sx EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV --stake-net "1.0000 EOS" --stake-cpu "5.0000 EOS" --buy-ram "100.0000 EOS"
cleos system newaccount eosio myaccount EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV --stake-net "1.0000 EOS" --stake-cpu "5.0000 EOS" --buy-ram "100.0000 EOS"
cleos system newaccount eosio toaccount EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV --stake-net "1.0000 EOS" --stake-cpu "5.0000 EOS" --buy-ram "100.0000 EOS"

# deploy smart contract
cleos set contract pingpong.sx . pingpong.sx.wasm pingpong.sx.abi

# ping & pong
cleos push action pingpong.sx ping '["myping"]' -p myaccount
cleos push action pingpong.sx pong '["myaccount", null]' -p myaccount

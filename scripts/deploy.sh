#!/usr/bin/env bash

mkdir -p dist
cleos wallet unlock --password $(cat ~/eosio-wallet/.pass)

# create accounts
cleos system newaccount eosio pingpong.sx EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV --stake-net "1.0000 EOS" --stake-cpu "5.0000 EOS" --buy-ram "100.0000 EOS"
cleos system newaccount eosio myaccount EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV --stake-net "1.0000 EOS" --stake-cpu "5.0000 EOS" --buy-ram "100.0000 EOS"
cleos system newaccount eosio toaccount EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV --stake-net "1.0000 EOS" --stake-cpu "5.0000 EOS" --buy-ram "100.0000 EOS"

# deploy smart contract
cleos set contract pingpong.sx . pingpong.sx.wasm pingpong.sx.abi

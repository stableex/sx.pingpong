#!/usr/bin/env bash

# 0.5 second ping & pong
cleos push action pingpong.sx ping '[500, "myping"]' -p myaccount
sleep 0.5
cleos push action pingpong.sx pong '["myaccount", 500]' -p myaccount
cleos push action pingpong.sx pong '["toaccount", 500]' -p toaccount

# 1 second ping & pong
cleos push action pingpong.sx ping '[1000, "toping"]' -p toaccount
sleep 1
cleos push action pingpong.sx pong '["toaccount", 1000]' -p toaccount
cleos push action pingpong.sx pong '["myaccount", 1000]' -p myaccount

# 1.5 second ping & pong
cleos push action pingpong.sx ping '[1500, null]' -p myaccount
sleep 1.5
cleos push action pingpong.sx pong '["myaccount", 1500]' -p myaccount

# uid based on transaction ID
cleos push action pingpong.sx ping '[null, null]' -p myaccount
#!/usr/bin/env bash

# ping & pong
cleos push action pingpong.sx ping '["myping"]' -p myaccount
cleos push action pingpong.sx pong '["myaccount", null]' -p myaccount

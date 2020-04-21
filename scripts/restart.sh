#!/usr/bin/env bash

./scripts/kill_nodeos.sh
./scripts/start_nodeos.sh
./scripts/deploy.sh
./scripts/test.sh

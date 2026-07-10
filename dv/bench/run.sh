#!/bin/sh
# build + run the submem/amc/cache bench across seeds.
#   usage: ./run.sh [nseeds] [ops-per-seed]
# BENCH_TRACE=1 ./run.sh 1  -> dumps bench.vcd for the (single) run
set -e
cd "$(dirname "$0")"
ROOT=../..

NSEEDS=${1:-10}
OPS=${2:-50000}

verilator --cc --exe --build --trace -Wno-fatal -j 0 \
  -I$ROOT/core -I$ROOT/core/modules \
  --top-module submem_tb \
  submem_tb.v axi_slave_beh.v cache_bram.v \
  $ROOT/core/modules/submem.v $ROOT/core/modules/cache.v $ROOT/core/modules/amc.v \
  submem_tb.cpp -o submem_bench --Mdir obj >/dev/null

s=1
while [ "$s" -le "$NSEEDS" ]; do
  ./obj/submem_bench +seed=$s +ops=$OPS || { echo "SEED $s FAILED"; exit 1; }
  s=$((s + 1))
done
echo "all $NSEEDS seeds passed"

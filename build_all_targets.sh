#!/usr/bin/env bash

set -xe

cheribuild.py rtld-tests-native --skip-update "$@"
cheribuild.py rtld-tests-mips --skip-update "$@"
for bits in 128 256; do
	for abi in legacy pcrel plt; do
		cheribuild.py rtld-tests-cheri --cross-target-suffix=$abi --cap-table-abi=$abi --$bits --skip-update "$@"
	done
done

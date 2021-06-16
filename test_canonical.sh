#!/bin/bash

testAnnotate() {
    ./build/newsbot json test/data/canonical_input.json > canonical_annotation.json
    diff test/data/canonical_annotation.json canonical_annotation.json
    ret=$?
    assertEquals $ret 0
}

testTop() {
    ./build/newsbot top test/data/canonical_input.json > canonical_top.json
    diff test/data/canonical_top.json canonical_top.json
    ret=$?
    assertEquals $ret 0
}

. shunit2-2.1.6/src/shunit2

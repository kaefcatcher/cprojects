#!/bin/bash

if [ ! -x "./s21_grep" ]; then
    echo "Error: s21_grep executable not found!"
    exit 1
fi

if ! command -v grep &> /dev/null; then
    echo "Error: grep command not found!"
    exit 1
fi

run_test_case() {
    local description="$1"
    shift
    ./s21_grep "$@" > "$temp_file"
    grep "$@" > "$temp_file"_system

    if diff "$temp_file" "$temp_file"_system > /dev/null; then
        echo -e "Test $description \033[32mpassed\033[0m"
    else
        echo -e "Test $description \033[31mfailed\033[0m: Output of s21_grep does not match system's grep."

    fi

    rm -f "$temp_file" "$temp_file"_system
}

temp_file=$(mktemp)

run_test_case "Basic Pattern Search" "in" 1.txt
run_test_case "Case-Insensitive Search" -i "IN" 1.txt
run_test_case "Invert Match" -v "in" 1.txt
run_test_case "Count Matches" -c "in" 1.txt
run_test_case "Print Filename" -l "in" 1.txt
run_test_case "Print Line Numbers" -n "in" 1.txt
run_test_case "Extended Regular Expression" -e "in" 1.txt
run_test_case "Suppress Warnings" -s "in" 1.txt
run_test_case "File Pattern Search" -f "pat.txt" 1.txt
run_test_case "Combination of flags" -i -v -n "in" 1.txt
run_test_case "Combination of flags with count" -i -v -n -c "in" 1.txt
run_test_case "Combination of flags with line numbers and print filename" -n -l "in" 1.txt
run_test_case "Combination of flags with extended regexp" -i -v -n -e "in" 1.txt
run_test_case "Combination of flags with suppress warnings" -i -v -n -s "in" 1.txt
run_test_case "Combination of flags with multiple files" -i -v -n "in" 1.txt "2.txt" "3.txt"
run_test_case "Combination of flags with count and multiple files" -i -v -n -c "in" 1.txt "2.txt" "3.txt"
run_test_case "Combination of flags with line numbers and print filename with multiple files" -n -l "in" 1.txt "2.txt" "3.txt"
run_test_case "Combination of flags with extended regexp and multiple files" -i -v -n -e "in" 1.txt "2.txt" "3.txt"
run_test_case "Combination of flags with suppress warnings and multiple files" -i -v -n -s "in" "1.txt" "2.txt" "3.txt"

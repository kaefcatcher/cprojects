#!/bin/bash

run_test_case() {
  local options=$1
  shift
  local files=("$@")

  echo -e "Testing with options: \033[34m$options\033[0m"
  echo "Files: ${files[@]}"

  for file in "${files[@]}"; do
    s21_cat_output=$(./s21_cat $options "$file")
    native_cat_output=$(cat $options "$file")

    if [ "$s21_cat_output" == "$native_cat_output" ]; then
      echo -e "Test \033[32mpassed\033[0m: Output of s21_cat matches native cat for $file."
    else
      echo -e "Test \033[31mfailed\033[0m: Output of s21_cat does not match native cat for $file."
    fi

    echo "--------------------------------------"
  done

  echo "======================================"
}

run_test_case "" "1.txt" "2.txt" "3.txt"
run_test_case "-e" "1.txt" "2.txt" "3.txt"
run_test_case "-b" "1.txt" "2.txt" "3.txt"
run_test_case "-n" "1.txt" "2.txt" "3.txt"
run_test_case "-s" "1.txt" "2.txt" "3.txt"
run_test_case "-t" "1.txt" "2.txt" "3.txt"
run_test_case "-e -n" "1.txt" "2.txt" "3.txt"
run_test_case "-e -b -n" "1.txt" "2.txt" "3.txt"
run_test_case "-s -t" "1.txt" "2.txt" "3.txt"
run_test_case "-e -n -t" "1.txt" "2.txt" "3.txt"

// ikitt for Advent of Code 2023

use core::num::ParseIntError;
use std::fs::read_to_string;

pub fn compute_part_1() -> u64 {
    read_input();
    0
}
pub fn compute_part_2() -> u64 {
    0
}

pub fn int_str_to_int(int_str: String) -> Vec<u8> {
    let int_str_trime: String = int_str.trim().to_string();
    println!("Will split and map '{}'", int_str_trime);
    int_str_trime
        .split_whitespace()
        .map(|one_int_str| one_int_str.parse::<u8>().unwrap())
        .collect::<Vec<u8>>() //).collect::<Vec<&str>>()[1].to_string();
}

pub fn read_input() -> Vec<(Vec<u8>, Vec<u8>)> {
    // let input_path = ".\\input\\y23_d04_in.txt";
    let input_path = "./input/y23_d04_test1.txt";
    let mut result: Vec<(Vec<u8>, Vec<u8>)> = vec![];
    for line in read_to_string(input_path).unwrap().lines() {
        println!("line input is {}", line);
        let mut numbers: String = line.split(':').collect::<Vec<&str>>()[1].to_string();
        let mut winning_numbers: Vec<u8> =
            int_str_to_int(numbers.split('|').collect::<Vec<&str>>()[1].to_string());
        let mut youhave_numbers: Vec<u8> =
            int_str_to_int(numbers.split('|').collect::<Vec<&str>>()[1].to_string());
        println!(
            "The winning numbers are {:#?}, and number you have are {:#?}",
            winning_numbers, youhave_numbers
        );
    }
    return result;
}

// ikitt for Advent of Code 2023

use crate::helper::int_str_to_int;
use core::num::ParseIntError;
use std::{fs::read_to_string, vec};

pub fn compute_part_1() -> u64 {
    0
}

pub fn compute_part_2() -> u64 {
    0
}

//Vec<(Vec<u8>, Vec<u8>)>
pub fn read_input() {
    // let input_path = "./input/y23_d04_in.txt"; // => xxx for part 1 and ???? for part 2
    let input_path = "./input/y23_d05_test1.txt"; // Expect 35 for part 1 and xx for part 2
    let full_input = read_to_string(input_path).unwrap();
    let mut input_lines = full_input.lines();
    let seed = int_str_to_int(
        input_lines
            .next()
            .clone()
            .unwrap()
            .split(':')
            .collect::<Vec<&str>>()[1]
            .to_string(),
    );

    // for line in read_to_string(input_path).unwrap().lines() {
    //     println!("line input is {}", line);
    //     let mut numbers: String = line.split(':').collect::<Vec<&str>>()[1].to_string();
    //     let mut winning_numbers: Vec<u8> =
    //         int_str_to_int(numbers.split('|').collect::<Vec<&str>>()[0].to_string());
    //     let mut youhave_numbers: Vec<u8> =
    //         int_str_to_int(numbers.split('|').collect::<Vec<&str>>()[1].to_string());
    //     println!(
    //         "The winning numbers are {:#?}, and number you have are {:#?}",
    //         winning_numbers, youhave_numbers
    //     );
    //     result.push((winning_numbers, youhave_numbers));
    // }
    // result
}

// ikitt for Advent of Code 2023

use crate::helper::{int_str_to_int, int_str_to_int_t};
use core::num::ParseIntError;
use std::collections::HashMap;
use std::{fs::read_to_string, vec};

pub fn compute_part_1() -> u64 {
    let (mut seed, list_of_converting_map) = read_input();
    for conversion_map in list_of_converting_map {
        let mut new_seed: Vec<u64> = Vec::new();
        for one_of_seed in seed.clone() {
            if let Some(new_value) = conversion_map.get(&one_of_seed) {
                println!("Converting {} to {}", one_of_seed, new_value);
                new_seed.push(*new_value);
            } else {
                println!("Keeping {}", one_of_seed);
                new_seed.push(one_of_seed);
            }
        }
        println!("Converted seed: {:?} to {:?}", seed, new_seed);
        seed = new_seed;
    }
    *seed.iter().min().unwrap() as u64
}

pub fn compute_part_2() -> u64 {
    0
}

// Input format: <destination range start>  <the source range start> <range length>
//      Not in range mean no change
//Vec<(Vec<u64>, Vec<u64>)>
pub fn read_input() -> (Vec<u64>, Vec<HashMap<u64, u64>>) {
    let input_path = "./input/y23_d05_in.txt"; // => xxx for part 1 and ???? for part 2
                                               // let input_path = "./input/y23_d05_test1.txt"; // Expect 35 for part 1 and xx for part 2
    let full_input = read_to_string(input_path).unwrap();
    let mut input_lines = full_input.lines();
    let seed = int_str_to_int_t::<u64>(
        input_lines
            .next()
            .unwrap()
            .split(':')
            .collect::<Vec<&str>>()[1]
            .to_string(),
    );

    // Each HashMap if for one block of input, defining evry conversion present in the input
    let mut list_of_converting_map: Vec<HashMap<u64, u64>> = Vec::new();

    let mut current_map: HashMap<u64, u64> = HashMap::new();
    for line in input_lines {
        if line.is_empty() {
            // Finish previous block
            if !current_map.is_empty() {
                list_of_converting_map.push(current_map);
            }
            current_map = HashMap::new();
            continue;
        } else if line.starts_with(['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']) {
            // This is a new block
            let numbers: Vec<u64> = int_str_to_int_t::<u64>(line.to_string());
            // println!("Create range from : {:?}", numbers);
            for i in 0..numbers[2] {
                // println!(
                //     "  Will insert {} + {} : {} + {}",
                //     numbers[1], i, numbers[0], i,
                // );
                current_map.insert(numbers[1] + i, numbers[0] + i);
            }
        } else {
            //println!("Ignoring line: {}", line);
            continue;
        }
    }
    list_of_converting_map.push(current_map);
    // println!("list_of_converting_map is: {:?}", list_of_converting_map);

    // for line in read_to_string(input_path).unwrap().lines() {
    //     println!("line input is {}", line);
    //     let mut numbers: String = line.split(':').collect::<Vec<&str>>()[1].to_string();
    //     let mut winning_numbers: Vec<u64> =
    //         int_str_to_int(numbers.split('|').collect::<Vec<&str>>()[0].to_string());
    //     let mut youhave_numbers: Vec<u64> =
    //         int_str_to_int(numbers.split('|').collect::<Vec<&str>>()[1].to_string());
    //     println!(
    //         "The winning numbers are {:#?}, and number you have are {:#?}",
    //         winning_numbers, youhave_numbers
    //     );
    //     result.push((winning_numbers, youhave_numbers));
    // }
    // result
    (seed, list_of_converting_map)
}

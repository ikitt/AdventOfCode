// ikitt for Advent of Code 2023

use crate::helper::int_str_to_int;
use core::num::ParseIntError;
use std::{fs::read_to_string, vec};

pub fn compute_part_1() -> u64 {
    let mut score = 0;
    let input = read_input();
    println!("The input is {:#?}", input);
    for (winning_numbers, youhave_numbers) in input {
        let mut count = 0;
        for one_of_yours in youhave_numbers {
            if winning_numbers.contains(&one_of_yours) {
                count += 1;
            } else {
                println!(
                    "You don't have {one_of_yours} in your hand {:?}",
                    winning_numbers
                );
            }
        }
        println!();
        if count > 0 {
            println!(
                "Got {count} winning number => score += {}",
                2_u32.pow(count - 1)
            );
            score += 2_u32.pow(count - 1);
        } else {
            println!("Got 0 winning number => score")
        }
    }
    println!("The score is {score}");
    score as u64
}

pub fn compute_part_2() -> u64 {
    let input = read_input();
    let mut count_cards = vec![1; input.len()];

    for (card_number, (winning_numbers, youhave_numbers)) in input.iter().enumerate() {
        let mut count = 0;
        for (i, one_of_yours) in youhave_numbers.iter().enumerate() {
            if winning_numbers.contains(one_of_yours) {
                count += 1;
                println!("Card {card_number} has count +1");
            }
        }
        for i in 1..(count + 1) {
            println!("Add +{} to {}", count_cards[card_number], card_number + i);
            count_cards[card_number + i] += count_cards[card_number];
        }
    }
    let res: u64 = count_cards.iter().sum();
    println!("The total number of cards is {res}");
    res
}

// pub fn int_str_to_int(int_str: String) -> Vec<u8> {
//     let int_str_trime: String = int_str.trim().to_string();
//     println!("Will split and map '{}'", int_str_trime);
//     int_str_trime
//         .split_whitespace()
//         .map(|one_int_str| one_int_str.parse::<u8>().unwrap())
//         .collect::<Vec<u8>>() //).collect::<Vec<&str>>()[1].to_string();
// }

pub fn read_input() -> Vec<(Vec<u8>, Vec<u8>)> {
    let input_path = "./input/y23_d04_in.txt"; // => 21959 for part 1 and ???? for part 2
                                               // let input_path = "./input/y23_d04_test1.txt"; // Expect 13 for part 1 and 30 for part 2
    let mut result: Vec<(Vec<u8>, Vec<u8>)> = vec![];
    for line in read_to_string(input_path).unwrap().lines() {
        println!("line input is {}", line);
        let mut numbers: String = line.split(':').collect::<Vec<&str>>()[1].to_string();
        let mut winning_numbers: Vec<u8> =
            int_str_to_int(numbers.split('|').collect::<Vec<&str>>()[0].to_string());
        let mut youhave_numbers: Vec<u8> =
            int_str_to_int(numbers.split('|').collect::<Vec<&str>>()[1].to_string());
        println!(
            "The winning numbers are {:#?}, and number you have are {:#?}",
            winning_numbers, youhave_numbers
        );
        result.push((winning_numbers, youhave_numbers));
    }
    result
}

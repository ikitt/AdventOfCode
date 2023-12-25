// ikitt for Advent of Code 2023

use std::fs::read_to_string;
use regex::Regex;
use std::collections::HashMap;

pub fn compute_part_1() -> u64 {
    let res:u64 = 0;
    // let input_path: &str = ".\\input\\y23_d02_in.txt";
    let input_path: &str = ".\\input\\y23_d02_test1.txt";

    let mut base_pool: HashMap<&str, u64> = HashMap::new();
    base_pool.insert("red", 12);
    base_pool.insert("green", 13);
    base_pool.insert("blue", 14);

    // Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green

    // let re = Regex::new(r"Game \d+\: ((\d+ \w+,?);? ?)+").unwrap();
    let re_id: Regex = Regex::new(r"Game (\d+):").unwrap();
    let re_hand: Regex = Regex::new(r"( \d+ \w+,?)+").unwrap();
    for line in read_to_string(input_path).unwrap().lines() {
        let game_id: u64 = re_id.captures(line).unwrap().get(1).unwrap().as_str().parse::<u64>().unwrap();
        println!("Game id is {}", re_id.captures(line).unwrap().get(1).unwrap().as_str());
        re_hand.find_iter(line).for_each(|cap| {println!("{}", cap.as_str()); });  //https://stackoverflow.com/questions/58010114/capture-all-regex-matches-into-a-vector
    }

    return res;
}

pub fn compute_part_2() -> u64 {
    let res:u64 = 0;
    // let input_path: &str = ".\\input\\y23_d02_in.txt";
    let input_path: &str = ".\\input\\y23_d02_test1.txt";
    return res;
}

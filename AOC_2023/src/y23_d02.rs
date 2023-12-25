// ikitt for Advent of Code 2023

use std::fs::read_to_string;
use regex::{Regex, Split};
use std::collections::HashMap;

pub fn compute_part_1() -> u64 {
    let mut res:u64 = 0;
    let input_path: &str = ".\\input\\y23_d02_in.txt";
    // let input_path: &str = ".\\input\\y23_d02_test1.txt";

    let base_pool = HashMap::from([
        ("red", 12),
        ("green", 13),
        ("blue", 14),
    ]);

    // Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green

    // let re = Regex::new(r"Game \d+\: ((\d+ \w+,?);? ?)+").unwrap();
    let re_id: Regex = Regex::new(r"Game (\d+):").unwrap();
    let re_hand: Regex = Regex::new(r"( \d+ \w+,?)+").unwrap();
    for line in read_to_string(input_path).unwrap().lines() {
        let mut game_valid: bool = true;
        let game_id: u64 = re_id.captures(line).unwrap().get(1).unwrap().as_str().parse::<u64>().unwrap();
        println!("Game id is {}", game_id);
        re_hand.find_iter(line).for_each(|cap| { //Break or continue not allowed with for_each but it is with for loop, would have been better.
            println!("{}", cap.as_str());
            cap.as_str().split(',').into_iter().for_each(|color_draw: &str|{
                let mut color_draw_split: std::str::Split<'_, char> = color_draw.trim().split(' ');
                let draw_size: u64 = color_draw_split.next().unwrap().parse::<u64>().unwrap();
                let color: &str = color_draw_split.next().unwrap();
                if draw_size > *base_pool.get(color).unwrap(){
                    println!("Game {} not possible due to {} {} is higger than {} from base pool", game_id,draw_size, color, base_pool.get(color).unwrap());
                    game_valid = false;
                }
            });
        });
        if game_valid {
            res += game_id;
        }
    }

    return res; // => res is 2716
}

pub fn compute_part_2() -> u64 {
    let mut res:u64 = 0;
    let input_path: &str = ".\\input\\y23_d02_in.txt";
    // let input_path: &str = ".\\input\\y23_d02_test1.txt";

    let re_hand: Regex = Regex::new(r"( \d+ \w+,?)+").unwrap();
    for line in read_to_string(input_path).unwrap().lines() {
        let mut min_pool: HashMap<&str, u64> = HashMap::from([
            ("red", 0),
            ("green", 0),
            ("blue", 0),
        ]);
        re_hand.find_iter(line).for_each(|cap| { //Break or continue not allowed with for_each but it is with for loop, would have been better.
            println!("{}", cap.as_str());
            cap.as_str().split(',').into_iter().for_each(|color_draw: &str|{
                let mut color_draw_split: std::str::Split<'_, char> = color_draw.trim().split(' ');
                let draw_size: u64 = color_draw_split.next().unwrap().parse::<u64>().unwrap();
                let color: &str = color_draw_split.next().unwrap();
                *min_pool.get_mut(color).unwrap() = draw_size.max(*min_pool.get(color).unwrap());
            });
        });
        let mut power: u64 =1;
        for key in min_pool.keys() {
            print!("min cube number for {} is {} and power is ", key, min_pool.get(key).unwrap());
            power *= min_pool.get(key).unwrap();
        }
        println!("and power is {}", power);
        res += power;
    }

    return res; // => res is 72227
}

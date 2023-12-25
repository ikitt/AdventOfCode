// ikitt for Advent of Code 2023

use std::fs::read_to_string;
use std::cmp;
use regex::Regex;
use std::collections::HashMap;

pub fn compute_part_1() -> u64 {
    let input_path = ".\\input\\y23_d01_in.txt";
    // let input_path = ".\\input\\y23_d01_test1.txt";
    let mut result: u64 = 0;
    for line in read_to_string(input_path).unwrap().lines() {

        let re = Regex::new(r"(\d|one|two|three|four|five|six|seven|eight|nine)").unwrap();
        let my_caps: Vec<u64> = re.find_iter(line).filter_map(|cap| cap.as_str().parse().ok()).collect();  //https://stackoverflow.com/questions/58010114/capture-all-regex-matches-into-a-vector
        result += my_caps.first().unwrap()*10 + my_caps.last().unwrap();
    }
    println!("result = {}", result); //=> 55002 is good
    return result;
}

pub fn compute_part_2() -> u64 {
    let mut str2num: HashMap<&str, u64> = HashMap::new();
    str2num.insert("one", 1);
    str2num.insert("two", 2);
    str2num.insert("three", 3);
    str2num.insert("four", 4);
    str2num.insert("five", 5);
    str2num.insert("six", 6);
    str2num.insert("seven", 7);
    str2num.insert("eight", 8);
    str2num.insert("nine", 9);
    str2num.insert("1", 1);
    str2num.insert("2", 2);
    str2num.insert("3", 3);
    str2num.insert("4", 4);
    str2num.insert("5", 5);
    str2num.insert("6", 6);
    str2num.insert("7", 7);
    str2num.insert("8", 8);
    str2num.insert("9", 9);

    let input_path = ".\\input\\y23_d01_in.txt";
    // let input_path = ".\\input\\y23_d01_test2.txt";
    let mut result: u64 = 0;
    for line in read_to_string(input_path).unwrap().lines() {
        let mut line_match: HashMap<usize, u64> = HashMap::new();
        for re_str in vec![r"\d", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]
        {
            line_match.extend(get_regex_res(re_str, line));
        }
        let line_add: u64 = line_match.get(line_match.keys().max().unwrap()).unwrap() + line_match.get(line_match.keys().min().unwrap()).unwrap()*10;
        result += line_add;
        // println!("{}; match are {:?}; line_add is {}", line.to_string(), line_match, line_add);
    }
    println!("result = {}", result); // 55061 is too low; 55093 is good !
    return result;
}

pub fn get_regex_res(re_str: &str, line: &str) -> HashMap<usize, u64> {
    let mut str2num: HashMap<&str, u64> = HashMap::new();
    str2num.insert("one", 1);
    str2num.insert("two", 2);
    str2num.insert("three", 3);
    str2num.insert("four", 4);
    str2num.insert("five", 5);
    str2num.insert("six", 6);
    str2num.insert("seven", 7);
    str2num.insert("eight", 8);
    str2num.insert("nine", 9);
    str2num.insert("1", 1);
    str2num.insert("2", 2);
    str2num.insert("3", 3);
    str2num.insert("4", 4);
    str2num.insert("5", 5);
    str2num.insert("6", 6);
    str2num.insert("7", 7);
    str2num.insert("8", 8);
    str2num.insert("9", 9);

    let mut result: HashMap<usize, u64> = HashMap::new();
    let re = Regex::new(re_str).unwrap();
    re.find_iter(line).for_each(|cap| {result.insert(cap.start(),*str2num.get(cap.as_str()).unwrap());});
    return result;
}
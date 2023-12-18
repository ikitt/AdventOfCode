// ikitt for Advent of Code 2023

use std::fs::read_to_string;
use std::cmp;
use regex::Regex;
use std::collections::HashMap;



// fn computeFuelReq(mass: f64) -> u64 {
//     let mut fuelReq: u64;
//     fuelReq = ((mass/3.0).floor() - 2.0) as u64;
//     return fuelReq
// }

pub fn compute_day_1_part_1() -> u64 {
    let input_path = "C:\\Users\\Valentin\\Medoc\\workspace\\AdventOfCode\\AOC_2023\\input\\Y23Day01_in.txt";
    // let input_path = "C:\\Users\\Valentin\\Medoc\\workspace\\AdventOfCode\\AOC_2023\\input\\Y23Day01_test1.txt";
    let mut result: u64 = 0;
    for line in read_to_string(input_path).unwrap().lines() {

        let re = Regex::new(r"(\d|one|two|three|four|five|six|seven|eight|nine)").unwrap();
        let my_caps: Vec<u64> = re.find_iter(line).filter_map(|cap| cap.as_str().parse().ok()).collect();  //https://stackoverflow.com/questions/58010114/capture-all-regex-matches-into-a-vector
        result += my_caps.first().unwrap()*10 + my_caps.last().unwrap();
        // println!("{} with {:?} => {} {} => {}", line.to_string(), my_caps, my_caps.first().unwrap(), my_caps.last().unwrap(), my_caps.first().unwrap()*10 + my_caps.last().unwrap());
    }
    println!("result = {}", result);
    return result;
}

pub fn compute_day_1_part_2() -> u64 {
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

    // let input_path = "C:\\Users\\Valentin\\Medoc\\workspace\\AdventOfCode\\AOC_2023\\input\\Y23Day01_in.txt";
    let input_path = "C:\\Users\\Valentin\\Medoc\\workspace\\AdventOfCode\\AOC_2023\\input\\Y23Day01_test2.txt";
    let mut result: u64 = 0;
    for line in read_to_string(input_path).unwrap().lines() {

        let re = Regex::new(r"(\d|one|two|three|four|five|six|seven|eight|nine)").unwrap();
        println!("{}", line.to_string());
        // for cap in re.find_iter(line) { println!("  {}",cap.as_str())};
        println!("{}", str2num.get(re.find_iter(line).next().unwrap().as_str()).unwrap()*10 + str2num.get(re.find_iter(line).last().unwrap().as_str()).unwrap());
        result += str2num.get(re.find_iter(line).next().unwrap().as_str()).unwrap()*10 + str2num.get(re.find_iter(line).last().unwrap().as_str()).unwrap();
    }
    println!("result = {}", result); // 55061 is too low
    return result;
}

// ikitt for Advent of Code 2023

use crate::helper::{int_str_to_int, int_str_to_int_t};
use core::num::ParseIntError;
use std::collections::HashMap;
use std::{fs::read_to_string, vec};

pub fn compute_part_1() -> u64 {
    let (mut seed, list_of_converting_list) = read_input();
    for conversion_list in list_of_converting_list {
        let mut new_seed: Vec<u64> = seed.clone();
        for (i, one_of_seed) in seed.clone().iter().enumerate() {
            for conversion_line in conversion_list.clone() {
                if one_of_seed >= &conversion_line.1
                    && one_of_seed < &(conversion_line.1 + conversion_line.2)
                {
                    // This is a conversion
                    // println!(
                    // "Converting {} to {}",
                    // one_of_seed,
                    // one_of_seed + conversion_line.0 - conversion_line.1
                    // );
                    new_seed[i] = one_of_seed + conversion_line.0 - conversion_line.1;
                    break; // No need to check other conversions for this seed
                }
            }
        }
        // println!("Converted seed: {:?} to {:?}", seed, new_seed);
        seed = new_seed;
    }
    *seed.iter().min().unwrap()
}

pub fn compute_part_2() -> u64 {
    let (mut seed, list_of_converting_list) = read_input();
    let mut paired_seed: Vec<(u64, u64)> = Vec::new();
    for i in 0..(seed.len() / 2) {
        paired_seed.push((seed[2 * i], seed[2 * i] + seed[2 * i + 1] - 1));
    }
    for converting_list in list_of_converting_list {
        let mut new_seed_range: Vec<(u64, u64)> = Vec::new(); // Update value

        loop {
            let mut tmp_remain_list: Vec<(u64, u64)> = Vec::new(); // left and/or right ranges that are not converted
            for seed_range in paired_seed.clone() {
                let mut seed_has_intersection: bool = false;
                for conversion_line in converting_list.clone() {
                    if let Some(intersect_range) = get_intersection(
                        seed_range,
                        (conversion_line.1, conversion_line.1 + conversion_line.2 - 1),
                    ) {
                        seed_has_intersection = true;
                        let updated_range = (
                            intersect_range.0 + conversion_line.0 - conversion_line.1,
                            intersect_range.1 + conversion_line.0 - conversion_line.1,
                        );
                        println!(
                            "   Intersection bewteen [{:?},{:?}] and [{:?},{:?}] give [{:?},{:?}]",
                            seed_range.0,
                            seed_range.1,
                            conversion_line.1,
                            conversion_line.1 + conversion_line.2 - 1,
                            updated_range.0,
                            updated_range.1
                        );
                        // println!(
                        //     "Converting range {:?} to {:?} using conversion {:?}",
                        //     seed_range, updated_range, conversion_line
                        // );
                        new_seed_range.push(updated_range);
                        let (remain_before_opt, remain_after_opt) =
                            get_range_difference(seed_range, intersect_range);
                        if let Some(remain_before) = remain_before_opt {
                            // println!("Remaining before {:?} is {:?}", seed_range, remain_before);
                            tmp_remain_list.push(remain_before);
                        }
                        if let Some(remain_after) = remain_after_opt {
                            // println!("Remaining after {:?} is {:?}", seed_range, remain_after);
                            tmp_remain_list.push(remain_after);
                        }
                    }
                }
                if !seed_has_intersection {
                    new_seed_range.push(seed_range);
                }
            }
            if tmp_remain_list.is_empty() {
                break;
            }
            paired_seed = tmp_remain_list
        }
        println!("Before shrinkage New paired seed: {:?}", new_seed_range);
        new_seed_range.sort_by(|a, b| a.0.cmp(&b.0));
        let mut shrinked_new_seed_range: Vec<(u64, u64)> = Vec::new();
        for seed_range in new_seed_range {
            if let Some(last) = shrinked_new_seed_range.last_mut() {
                if last.1 >= seed_range.0 {
                    // Merge ranges
                    println!(
                        "      Merging ranges {:?} and {:?} into {:?}",
                        *last,
                        seed_range,
                        (last.0, last.1.max(seed_range.1))
                    );
                    last.1 = last.1.max(seed_range.1);
                } else {
                    println!("      Unchanged range: {:?}", seed_range);
                    shrinked_new_seed_range.push(seed_range);
                }
            } else {
                println!("      Unchanged range: {:?}", seed_range);
                shrinked_new_seed_range.push(seed_range);
            }
        }
        paired_seed = shrinked_new_seed_range;
        println!("New paired seed: {:?}", paired_seed);
    }
    // if let Some()
    // println!("Final paired seed: {:?}", paired_seed);
    *paired_seed.iter().map(|(start, end)| start).min().unwrap()
}

fn get_intersection(range1: (u64, u64), range2: (u64, u64)) -> Option<(u64, u64)> {
    let start = range1.0.max(range2.0);
    let end = range1.1.min(range2.1);
    if start < end {
        Some((start, end))
    } else {
        None
    }
}

fn get_range_difference(
    range_base: (u64, u64),
    range_substractor: (u64, u64),
) -> (Option<(u64, u64)>, Option<(u64, u64)>) {
    if let Some(intersection) = get_intersection(range_base, range_substractor) {
        let mut low_range: Option<(u64, u64)> = None;
        let mut up_range: Option<(u64, u64)> = None;
        if range_base.0 < intersection.0 {
            low_range = Some((range_base.0, intersection.0 - 1));
        }
        if intersection.1 < range_base.1 {
            up_range = Some((intersection.1 + 1, range_base.1));
        }
        (low_range, up_range)
    } else {
        // If there is no intersection, the whole ranges are part of the symmetric difference
        (Some(range_base), None)
    }
}

// Input format: <destination range start>  <the source range start> <range length>
//      Not in range mean no change
//Vec<(Vec<u64>, Vec<u64>)>
pub fn read_input() -> (Vec<u64>, Vec<Vec<(u64, u64, u64)>>) {
    let input_path = "./input/y23_d05_in.txt"; // => 107430936 for part 1 and 23738616 for part 2 (not 0)
                                               // let input_path = "./input/y23_d05_test1.txt"; // Expect 35 for part 1 and 46 for part 2
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
    let mut list_of_converting_list: Vec<Vec<(u64, u64, u64)>> = Vec::new();

    let mut current_list: Vec<(u64, u64, u64)> = Vec::new();
    for line in input_lines {
        if line.is_empty() {
            // Finish previous block
            if !current_list.is_empty() {
                list_of_converting_list.push(current_list);
            }
            current_list = Vec::new();
            continue;
        } else if line.starts_with(['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']) {
            // This is a new block
            let numbers: Vec<u64> = int_str_to_int_t::<u64>(line.to_string());
            current_list.push((numbers[0], numbers[1], numbers[2]))
            // println!("Create range from : {:?}", numbers);
        } else {
            //println!("Ignoring line: {}", line);
            continue;
        }
    }
    list_of_converting_list.push(current_list);

    (seed, list_of_converting_list)
}

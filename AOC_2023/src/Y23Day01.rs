// ikitt for Advent of Code 2023

use std::fs::read_to_string;
use std::cmp;



// fn computeFuelReq(mass: f64) -> u64 {
//     let mut fuelReq: u64;
//     fuelReq = ((mass/3.0).floor() - 2.0) as u64;
//     return fuelReq
// }

pub fn compute_day_1_part_1() -> u64 {
    for line in read_to_string("C:\\Users\\Valentin\\Medoc\\workspace\\AdventOfCode\\AOC_2023\\input\\Y23Day01_in.txt").unwrap().lines() {
        println!("{}", line.to_string());
    }
    return 1;




    // let mut max_sum: u64 = 0;
    // let mut curr_sum: u64 = 0;
    // for idx in 0..INPUT.len() {
    //     if INPUT[idx].len() == 0
    //     {
    //         max_sum = cmp::max(curr_sum, max_sum);
    //         println!("Find a sum equal to {}", curr_sum);
    //         curr_sum = 0;
    //     }
    //     else
    //     {
    //         curr_sum += INPUT[idx].parse::<u64>().unwrap();
    //     }
    // }
    // return max_sum;
}

// fn compute_day_1_part_2() -> u64 {
//     let mut top_three: [u64; 3] = [0,0,0]; //max on left, min on right
//     let mut max_sum: u64 = 0;
//     let mut curr_sum: u64 = 0;
//     for idx in 0..INPUT.len() {
//         if INPUT[idx].len() == 0
//         {
//             max_sum = cmp::max(curr_sum, max_sum);
//             add_to_top_three(curr_sum,&mut top_three);
//             curr_sum = 0;
//         }
//         else
//         {
//             curr_sum += INPUT[idx].parse::<u64>().unwrap();
//         }
//     }
//     return max_sum;
// }

// fn add_to_top_three(new: u64, top_three: &mut [u64;3])
// {
//     for idx in 0..3
//     {
//         if new > top_three[idx]
//         {
//             for in_idx in 2..idx
//             {
//                 top_three[in_idx + 1] = top_three[in_idx];
//             }
//             top_three[idx] = new;
//             println!("new top tree is [{},{},{}]", top_three[0],top_three[1],top_three[2]);
//             break;
//         }
//     }
// }

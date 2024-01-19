// ikitt for Advent of Code 2023

use std::fs::read_to_string;
use regex::{Regex, Split};
use std::collections::HashMap;

struct Star {
    row: usize,
    col: usize,
    neighbors: Vec<u64>,
}

impl Star {
    // A constructor to create a new Star for part 2
    fn new(row_in: usize, col_in: usize) -> Star {
        Star {
            row: row_in,
            col: col_in,
            neighbors: vec![],
        }
    }

    // An instance method
    fn add_neighbor(&mut self, neighbor: u64) {
        self.neighbors.push(neighbor);
    }
}

pub fn compute_part_1() -> u64 {
    let mut res:u64 = 0;
    let input_path: &str = ".\\input\\y23_d03_in.txt";
    // let input_path: &str = ".\\input\\y23_d03_test1.txt"; // give 539590

    let table: Vec<Vec<char>> = input_as_table(input_path);

    for (row,line) in table.iter().enumerate() {
        let mut current_number: u64 = 0;
        let mut is_number: bool = false;
        let mut is_valid_number: bool = false;
        for (col,ch) in line.iter().enumerate() {
            if table[row][col].is_digit(10) {
                is_number = true;
                current_number = current_number*10 + u64::from(table[row][col].to_digit(10).unwrap());
                if !(is_valid_number) && has_symbol_neighbor(row, col, &table) {
                    // println!("first valid {row} {col}");
                    is_valid_number = true;
                }
            }
            else {
                if is_number && !is_valid_number {
                    // println!("c {current_number}; valid {is_valid_number}");
                }
                if is_valid_number {
                    res = res + current_number;
                }
                is_number = false;
                current_number = 0;
                is_valid_number = false;
            }
        }
        if is_valid_number {
            res = res + current_number;
        }
    }
    
    return res; // res is 539590
}

pub fn compute_part_2() -> u64 {
    /*
    Analyse des nombres
    Pour chaque nombre sauvegarder les étoiles adjacentes
    Créer une struct pour chaque étoile avec la position et les nombres adjacents 
    Stocker ces structs dans une HashMap <positon, struct>
        Si la position est déjà connu, ajouter le nombre courant
        Sinon créé la struct et la poussé dans la HashMap
    Analyser toutes les structs, celle qui ont exactement 2 nombres adjacents doivent être incluse dans le résultats.
     */

    let mut res:u64 = 0;
    // let input_path: &str = ".\\input\\y23_d03_in.txt"; // 81285307 is too high
    let input_path: &str = ".\\input\\y23_d03_test1.txt"; // give 467835

    let table: Vec<Vec<char>> = input_as_table(input_path);
    let mut star_map: HashMap<[usize; 2], Star> = HashMap::new();

    let mut star_pos_list: Vec<[usize;2]> = vec![];
    for (row,line) in table.iter().enumerate() {
        let mut current_number: u64 = 0;
        let mut is_number: bool = false;
        for (col,ch) in line.iter().enumerate() {
            if table[row][col].is_digit(10) {
                is_number = true;
                current_number = current_number*10 + u64::from(table[row][col].to_digit(10).unwrap());                

                add_stars(row, col, &table, &mut star_pos_list)
            }
            else {
                if is_number { // End of a number
                    star_pos_list.sort();
                    star_pos_list.dedup();
                    println!("Read number {} which has {} stars as neighbors.", current_number, star_pos_list.len());
                    star_pos_list.clone().into_iter().for_each(|star_pos: [usize; 2]| {
                        create_or_push_star(&star_pos, current_number, &mut star_map);
                    });
                    star_pos_list.clear();
                }
                is_number = false;
                current_number = 0;
            }
        }
    }

    for (pos, star) in star_map.iter(){
        println!("Star at pos {:?}, has neighbor {:?} ", pos, star.neighbors);
        if (star.neighbors.len() == 2){
            res = res + (star.neighbors[0] * star.neighbors[1]);
        }
    }
    return res;
}

pub fn input_as_table(input_pth : &str) -> Vec<Vec<char>> {
    let mut table: Vec<Vec<char>> = vec![];
    for line in read_to_string(input_pth).unwrap().lines() {
        let mut table_line: Vec<char> = vec![];
        for ch in line.chars() {
            table_line.push(ch)
            // print!("row {row_id} col {col_id} char {ch};");
        }
        table.push(table_line);
        // println!("");
    }
    // println!("{:?}", table); // Debug print
    return table;
}

pub fn has_symbol_neighbor(row:usize, col:usize, table: &Vec<Vec<char>>) -> bool {
    let max_row = table.len()-1;
    let max_col = table[0].len()-1;

    if row > 0 {
        if is_symbor(table[row-1][col]) {
            return true;
        }
    }
    if row < max_row {
        if is_symbor(table[row+1][col]) {
            return true;
        }
    }
    if col > 0 {
        if is_symbor(table[row][col-1]) {
            return true;
        }
    }
    if col < max_col {
        if is_symbor(table[row][col+1]) {
            return true;
        }
    }
    if row > 0 && col > 0{
        if is_symbor(table[row-1][col-1]) {
            return true;
        }
    }
    if row > 0 && col < max_col{
        if is_symbor(table[row-1][col+1]) {
            return true;
        }
    }
    if row < max_row && col > 0{
        if is_symbor(table[row+1][col-1]) {
            return true;
        }
    }
    if row < max_row && col < max_col {
        if is_symbor(table[row+1][col+1]) {
            return true;
        }
    }
    return false;
}


pub fn add_stars(row:usize, col:usize, table: &Vec<Vec<char>>, star_pos_list: &mut Vec<[usize; 2]>) {
    let max_row = table.len()-1;
    let max_col = table[0].len()-1;

    if row > 0 {
        if is_star(table[row-1][col]) {
            star_pos_list.push([row-1,col]);
        }
    }
    if row < max_row {
        if is_star(table[row+1][col]) {
            star_pos_list.push([row+11,col]);
        }
    }
    if col > 0 {
        if is_star(table[row][col-1]) {
            star_pos_list.push([row,col-1]);
        }
    }
    if col < max_col {
        if is_star(table[row][col+1]) {
            star_pos_list.push([row,col+1]);
        }
    }
    if row > 0 && col > 0{
        if is_star(table[row-1][col-1]) {
            star_pos_list.push([row-1,col-1]);
        }
    }
    if row > 0 && col < max_col{
        if is_star(table[row-1][col+1]) {
            star_pos_list.push([row-1,col+1]);
        }
    }
    if row < max_row && col > 0{
        if is_star(table[row+1][col-1]) {
            star_pos_list.push([row+1,col-1]);
        }
    }
    if row < max_row && col < max_col {
        if is_star(table[row+1][col+1]) {
            star_pos_list.push([row+1,col+1]);
        }
    }
}

pub fn is_symbor(ch: char) -> bool {
    let is_dig: bool = ch.is_digit(10);
    let is_point: bool = ch == '.';
    return !(is_dig || is_point)
}

pub fn is_star(ch: char) -> bool {
    return ch == '*';
}

pub fn create_or_push_star(star_pos: &[usize; 2], current_number: u64, star_map: &mut HashMap<[usize;2], Star>){
    if !star_map.contains_key(star_pos)
    {
        star_map.insert(star_pos.clone(), Star::new(star_pos[0].clone(), star_pos[1].clone()));
    }
    star_map.get_mut(star_pos).unwrap().neighbors.push(current_number.clone());
}